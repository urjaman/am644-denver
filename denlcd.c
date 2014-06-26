#include "main.h"
#include "denlcd.h"

#define nop asm volatile("nop\n\t")

#define SCLK_PORT PORTA
#define SID_PORT PORTA
#define SCLK 1
#define SID 2
#define LCE 3
#define DTH 4


#if 0
// Compatible version
static void spiwrite(uint8_t c) {
  int8_t i;
  for (i=7; i>=0; i--) {
    SCLK_PORT &= ~_BV(SCLK);
    if (c & 0x80)
      SID_PORT |= _BV(SID);
    else
      SID_PORT &= ~_BV(SID);
    c = c<<1;
    nop;
    SCLK_PORT |= _BV(SCLK);
    nop;
  }
}
#else
#define bld(to,bit_to) bld2(to,bit_to)
#define bst(from,bit_from) bst2(from,bit_from)
#define bld2(to,bit_to) asm("bld %0, " #bit_to "\n\t" : "+r" (to) :)
#define bst2(from,bit_from) asm("bst %0, " #bit_from "\n\t" :: "r" (from))

// This code should be ok for F_CPU <= 20Mhz (because LCD max 5Mhz)
// Provides F = F_CPU/4, 50/50 duty cycle, tested with F_CPU = 12Mhz
// Assumes SCLK_PORT == SID_PORT.
// Note: if you have an ISR that touches this port, cli() this sequence.
static void spiwrite(uint8_t c) {
  // add cli() here if needed
  uint8_t p = SID_PORT & ~_BV(SCLK);
  bst(c,7);
  bld(p,SID);
  SID_PORT = p;
  bst(c,6);
  SCLK_PORT |= _BV(SCLK);
  bld(p,SID);
  SID_PORT = p;
  bst(c,5);
  SCLK_PORT |= _BV(SCLK);
  bld(p,SID);
  SID_PORT = p;
  bst(c,4);
  SCLK_PORT |= _BV(SCLK);
  bld(p,SID);
  SID_PORT = p;
  bst(c,3);
  SCLK_PORT |= _BV(SCLK);
  bld(p,SID);
  SID_PORT = p;
  bst(c,2);
  SCLK_PORT |= _BV(SCLK);
  bld(p,SID);
  SID_PORT = p;
  bst(c,1);
  SCLK_PORT |= _BV(SCLK);
  bld(p,SID);
  SID_PORT = p;
  bst(c,0);
  SCLK_PORT |= _BV(SCLK);
  bld(p,SID);
  SID_PORT = p;
  nop; // you can put the sei() here instead of the nop
  SCLK_PORT |= _BV(SCLK);
}
#endif

void denlcd_frame(uint8_t *data)
{
    /* This sounds fucked up, but also, this is what the datasheet says to do...*/
    /* Note: Also, it works. */
    spiwrite(0x82);
    SCLK_PORT |= _BV(LCE);
    for (uint8_t i=0;i<19;i++) spiwrite(data[i]);
    spiwrite(0x08); // Control data - no used segments in the last byte
    SCLK_PORT &= ~_BV(LCE);
}

void denlcd_init(void)
{
    uint8_t init_frame[19];
    SCLK_PORT |= _BV(SCLK);
    DDRA |= _BV(SCLK);
    SCLK_PORT |= _BV(LCE);
    DDRA |= _BV(LCE);
    DDRA |= _BV(SID);
    _delay_us(250);
    SCLK_PORT &= ~_BV(LCE);
    memset(init_frame,0xFF,19);
    denlcd_frame(init_frame);
}

#define FONT_BASE 0x30
#define FONT_COUNT 10


#define VUR 0x0001
#define VDR 0x0002
#define DDR 0x0004
#define DUR 0x0008
#define HMR 0x0010
#define DNB 0x0020
#define UPB 0x0040
#define VMB 0x0080
#define DDL 0x0100
#define DUL 0x0200
#define HML 0x0400
#define VDL 0x0800
#define VUL 0x1000

/*

|-------|
|\  |  /|
| \ | / |
|  \|/  |
|---|---|
|  /|\  |
| / | \ |
|/  |  \|
---------

|--UPB--|
VD  V  DV
U U M U U
L  LBR  R
|HML HMR|
V  DVD  V
D D M D D
LL  B  RR
|--DNB--|

*/

static const uint16_t fontdata[FONT_COUNT] PROGMEM = {
    UPB | DNB | VUL | VUR | VDL | VDR, // 0
    VUR | VDR, // 1
    UPB | VUR | HMR | HML | VDL | DNB, // 2
    UPB | VUR | HMR | VDR | DNB, // 3
    VUL | HML | HMR | VUR | VDR, // 4
    UPB | VUL | HML | HMR | VDR | DNB, // 5
    UPB | VUL | HML | HMR | VDR | DNB | VDL, // 6
    UPB | VUR | VDR, // 7, EXP.
    UPB | VUL | VUR | VDL | VDR | DNB | HML | HMR, // 8
    UPB | VUL | VUR | HML | HMR | VDR | DNB, // 9
};

static void denlcd_plot_char(uint8_t* buf, uint8_t idx, uint8_t ch)
{
    uint16_t gfx = 0; /* Default/Missing Character is blank... */
    if (idx>7) return ; /* Doesnt exist. */
    if ((ch>=FONT_BASE)&&(ch<(FONT_BASE+FONT_COUNT))) {
        gfx = pgm_read_word(&(fontdata[ch-FONT_BASE]));
    }

    switch (idx) {
        case 0:
            buf[0] &= 0xC0;
            buf[1] &= 0x01;
            buf[0] |= gfx>>7;
            buf[1] |= gfx<<1;
            break;

        case 1:
            buf[2] &= 0x80;
            buf[3] &= 0x03;
            buf[2] |= gfx>>6;
            buf[3] |= gfx<<2;
            break;

        case 2:
            buf[4] = gfx>>5;
            buf[5] &= 0x07;
            buf[5] |= gfx<<3;
            break;

        case 3:
            buf[5] &= 0xFE;
            buf[5] |= gfx>>12;
            buf[6] = gfx>>4;
            buf[7] &= 0x0F;
            buf[7] |= gfx<<4;
            break;

        case 4:
            buf[7] &= 0xFC;
            buf[7] |= gfx>>11;
            buf[8] = gfx>>3;
            buf[9] &= 0x1F;
            buf[9] |= gfx<<5;
            break;

        case 5:
            buf[9]  &= 0xF8;
            buf[9] |= gfx>>10;
            buf[10] = gfx>>2;
            buf[11] &= 0x3F;
            buf[11] |= gfx<<6;
            break;

        case 6:
            buf[11] &=  0xF0;
            buf[11] |= gfx>>9;
            buf[12] = gfx>>1;
            buf[13] &= 0x7F;
            buf[13] |= gfx<<7;
            break;

        case 7:
            buf[13] &= 0xE0;
            buf[13] |= gfx>>8;
            buf[14] = gfx;
            break;
    }
}

void denlcd_write_string(uint8_t *buf, uint8_t *string)
{
    for (uint8_t i=0;i<8;i++) {
        if (!string[i]) break;
        denlcd_plot_char(buf,i,string[i]);
    }
}
