#include "main.h"
#include "uart.h"
#include "denkbd.h"

/* 1.14ms / (1s / (F_CPU / 1024)) */
#define BIT_THRESH 13
#define LONG_THRESH (BIT_THRESH*4)
#define TYPE_THRESH (BIT_THRESH*3)

/* I just assume the REM pin is PA0, fix it all over if not. */
/* Fuck you too :-) */
/* Also, we're just gonna use Timer2. HC. */

#define DKBUFSZ 8

struct denkbd_evt {
    uint8_t type;
    uint32_t data;
} dkbuf[DKBUFSZ];

static volatile uint8_t dkbuf_wp=0;
static uint8_t dkbuf_rp = 0;

static volatile uint8_t denkbd_state=0;
static volatile uint32_t denkbd_data=0;

ISR(PCINT0_vect)
{
    uint8_t diff = TCNT2;
    TCNT2 = 0;
    uint8_t nl = PINA&_BV(0);
    uint8_t s = denkbd_state;
    if (nl) { /* Diff = length of 0. */
        if ((s!=255)&&(diff > LONG_THRESH)) s = 1;
    } else { /* Diff = length of 1. */
        switch (s) {
            case 255:
                s = 0;
            case 0:
                //SEND('S');
                break;
            case 1:
                if (diff > TYPE_THRESH) {
                    s = 2;
                    //SEND('2');
                } else {
                    uint8_t wp = dkbuf_wp;
                    dkbuf[wp].type = 1;
                    dkbuf[wp].data = 0;
                    wp++;
                    if (wp>=DKBUFSZ) wp = 0;
                    dkbuf_wp = wp;
                    s = 0;
                    //SEND('R');
                }
                break;
            default:
                {
                uint32_t d = denkbd_data;
                d = d<<1;
                if (diff > BIT_THRESH) d |= 1;
                s++;
                if (s>=34) {
                    uint8_t wp = dkbuf_wp;
                    dkbuf[wp].type = 0;
                    dkbuf[wp].data = d;
                    wp++;
                    if (wp>=DKBUFSZ) wp = 0;
                    dkbuf_wp = wp;
                    s = 0;
                    //SEND('O');
                } else {
                    denkbd_data = d;
                    //SEND('B');
                }
                }
                break;
        }
    }
    denkbd_state = s;
}


ISR(TIMER2_OVF_vect) {
//    if (denkbd_state != 255) SEND('F');
    denkbd_state = 255; /* Excessively LONG level. */
}

void denkbd_init(void)
{
    TCNT2 = 0;
    TCCR2A = 0;
    TCCR2B = 7;
    TIFR2 = _BV(TOV2);
    TIMSK2 = _BV(TOIE2);
    PCMSK0 |= _BV(0);
    PCIFR = _BV(PCIF0);
    PCICR |= _BV(PCIE0);
}


uint8_t denkbd_isdata(void)
{
    if (dkbuf_wp!=dkbuf_rp) return 1;
    return 0;
}


static const uint16_t keylist[] PROGMEM = {
    0x30CF, // PWR
    0x609F, // UP
    0x38C7, // BND
    0xE01F, // DN
    0x6897, // DISP
    0x50AF, // RIGHT
    0xD02F, // LEFT
    0xC837, // MENU
    0xB847, // AMS
    0x9867, // MOD
    0x48B7, // MUTE
    0xF00F, // TA
    0x08F7, // PTY
    0x58A7, // 1
    0x807F, // 2
    0xD827, // 3
    0xC03F, // 4
    0x20DF, // 5
    0xA05F, // 6
    0x708F, // RDS
    0
};


static const char keynames[][6] PROGMEM = {
    "NOKEY",
    "PWR",
    "UP",
    "BND",
    "DN",
    "DISP",
    "RIGHT",
    "LEFT",
    "MENU",
    "AMS",
    "MOD",
    "MUTE",
    "TA",
    "PTY",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "RDS"
};


PGM_P denkbd_keyname(uint8_t key)
{
    key &= 0x7F;
    if (key>20) return NULL;
    return keynames[key];
}

uint8_t denkbd_getkey(void)
{
    static uint8_t last_key = 0;
    uint8_t type;
    uint32_t d;
    while (dkbuf_wp==dkbuf_rp); /* Wait for data. */
    type = dkbuf[dkbuf_rp].type;
    d = dkbuf[dkbuf_rp].data;
    dkbuf_rp++;
    if (dkbuf_rp>=DKBUFSZ) dkbuf_rp = 0;
    if (type==1) {
        if (!last_key) return 0;
        return last_key|KEY_MOD_REPEAT;
    }
    if ((d&0xFFFF0000) != 0x00FF0000) return 0;
    uint16_t dw = d;
    for (uint8_t i=0;;i++) {
        uint16_t cw = pgm_read_word(&(keylist[i]));
        if (!cw) return 0;
        if (dw==cw) {
            last_key = i+1;
            break;
        }
    }
    return last_key;
}
