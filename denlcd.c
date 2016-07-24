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

#define FONT_BASE 0x20
#define FONT_COUNT 95


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
    0, // ' '
    VUL | DDL, // !
    VUL | VUR, // "
    UPB | HML | HMR | VMB | VUR | VDR, // #
    VMB | UPB | DNB | HML | HMR | VUL | VDR, // $
    DUR | DDL | DUL | DDR | HML | HMR | VUL | VDR, // %
    0, // &
    DUR, // '
    DUR | DDR, // (
    DUL | DDL, // )
    VMB | HML | HMR | DUL | DUR | DDL | DDR, // *
    VMB | HML | HMR, // +
    DDL, // ,
    HML | HMR, // -
    0, // .
    DUR | DDL, // /
    UPB | DNB | VUL | VUR | VDL | VDR | DDL | DUR, // 0
    VUR | VDR, // 1
    UPB | VUR | HMR | HML | VDL | DNB, // 2
    UPB | VUR | HMR | VDR | DNB, // 3
    VUL | HML | HMR | VUR | VDR, // 4
    UPB | VUL | HML | HMR | VDR | DNB, // 5
    UPB | VUL | HML | HMR | VDR | DNB | VDL, // 6
    UPB | VUR | VDR, // 7
    UPB | VUL | VUR | VDL | VDR | DNB | HML | HMR, // 8
    UPB | VUL | VUR | HML | HMR | VDR | DNB, // 9
    0, //:
    HML | DDL, //;
    DUR | DDR, //<
    HML | HMR | UPB, //=
    DUL | DDL, //>
    UPB | VUR | HMR | DDL, // ?
    0, // @
    UPB | VUL | VUR | HML | HMR | VDL | VDR, // A
    VUL | VDL | HML | HMR | VDR | DNB, // b
    UPB | VUL | VDL | DNB, // C
    VUR | VDR | HML | HMR | VDL | DNB, // d
    UPB | VUL | HML | VDL | DNB, // E
    UPB | VUL | HML | VDL, // F
    HMR | VDR | DNB | VDL | VUL | UPB, // G
    VUL | VDL | HML | HMR | VUR | VDR, //  H
    UPB | VMB | DNB, // I
    VUR | VDR | DNB | VDL, // J
    VUL | VDL | HML | DUR | DDR, // K
    VUL | VDL | DNB, // L
    VUL | VDL | DUL | DUR | VUR | VDR, // M
    VUL | VDL | DUL | DDR | VDR | VUR, // N
    UPB | VUL | VDL | DNB | VDR | VUR, // O
    UPB | VUL | VUR | HML | HMR | VDL, // P
    UPB | VUL | VDL | DNB | VDR | VUR | DDR, // Q
    UPB | VUL | HML | HMR | VUR | VDL | DDR, // R
    UPB | VUL | HML | HMR | VDR | DNB, // S
    UPB | VMB, // T
    VUL | VDL | DNB | VDR | VUR, // U
    DUL | DDR | VDR | VUR, // V
    VUL | VDL | DDL | DDR | VDR | VUR, // W
    DUL | DUR | DDL | DDR, //X
    DUL | DUR | DDL, // Y
    UPB | DUR | DDL | DNB, // Z
    VMB | DUR | DDR, // [
    DUL | DDR, // '\'
    VMB | DUL | DDL, // ]
    DDL | DDR, // ^
    DNB, // _
    DUL, // `
    UPB | VUR | HML | HMR | VDL | VDR | DNB, // a
    VUL | VDL | HML | HMR | VDR | DNB, // b
    HML | HMR | VDL | DNB, // c
    VUR | VDR | HML | HMR | VDL | DNB, // d
    UPB | VUL | HML | VDL | DNB, // E
    UPB | VUL | HML | VDL, // F
    HMR | VDR | DNB | VDL | VUL | UPB, // G
    VUL | VDL | HML | HMR | VDR, //  h
    UPB | VMB | DNB, // I
    VUR | VDR | DNB | VDL, // J
    VUL | VDL | HML | DUR | DDR, // K
    VUL | VDL | DNB, // L
    VUL | VDL | DUL | DUR | VUR | VDR, // M
    VDL | HML | HMR | VDR, // n
    VDL | DNB | VDR | HML | HMR, // o
    UPB | VUL | VUR | HML | HMR | VDL, // P
    UPB | VUL | VDL | DNB | VDR | VUR | DDR, // Q
    UPB | VUL | HML | HMR | VUR | VDL | DDR, // R
    UPB | VUL | HML | HMR | VDR | DNB, // S
    UPB | VMB, // T
    VDL | DNB | VDR, // u
    DUL | DDR | VDR | VUR, // V
    VUL | VDL | DDL | DDR | VDR | VUR, // W
    DUL | DUR | DDL | DDR, //X
    DUL | DUR | DDL, // Y
    UPB | DUR | DDL | DNB, // Z
    VMB | DUR | DDR | HML, // {
    VMB, // |
    VMB | DUL | DDL | HMR, // }
    VUL | DUL | HML | HMR | VDR | DDR, // ~
    0,
    UPB | VUL | VDL | DNB | HML, // €
    0,
    DDL,
    UPB | VUL | HML | VDL, // f
    DDL | VDR, // ,,
    DNB, // ...
    VMB | HML | HMR, // cross
    VMB | HML | HMR | UPB, // dl cross
    DDL | DDR, // ^
    0,
    UPB | VUL | HML | HMR | VDR | DNB, // S\/
    DUR | DDR, // <
    UPB | VUL | HML | VDL | DNB | VMB | HMR, //OE
    0,
    UPB | DUR | DDL | DNB, // Z\/
    0,
    0,
    DUL,
    DUR,
    DUL | VUR,
    VUL | DUR,
    VMB | HML | HMR | DUL | DUR | DDL | DDR,
    HML,
    HML | HMR,
    UPB,
    0,
    UPB | VUL | HML | HMR | VDR | DNB, // s\/
    DUL | DDL,
    UPB | VUL | HML | VDL | DNB | VMB | HMR, //oe
    0,
    UPB | DUR | DDL | DNB, // Z\/
    DUL | DUR | DDL, // Ÿ
    0, // NBSP
    VDR | DUR, // Inv !
    VMB | DNB | VDL | HML | HMR, // cent
    0,
    0,
    0,
    VMB, // |
    0,
    VUL | VUR //",
    HML | HMR | VDL | DNB | UPB, // copyright
    0,
    DUR | DDR,//<<
    HML | HMR | VDR,
    HML, // SHY
    UPB | VUR | HMR | HML | VUL | VDL | DDR, // (R)
    UPB, // Macron
    UPB | VUR | VUL | HML | HMR, // °
    VMB | HML | HMR | DNB,
    0,
    0,
    DUR,
    VUL | VDL | HML | HMR | VUR, // micro
    0.
    DDL,
    DDL,
    0,
    UPB | VUL | VUR | HML | HMR | DNB,
    DUL | DDL, // >>
    0,
    0,
    0,
    0, // inverted ? (0xBF)
};

/*
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
