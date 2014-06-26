void denkbd_init(void);
uint8_t denkbd_isdata(void);
PGM_P denkbd_keyname(uint8_t key);
uint8_t denkbd_getkey(void);

#define KEY_PWR 1
#define KEY_UP 2
#define KEY_BND 3
#define KEY_DN 4
#define KEY_DISP 5
#define KEY_RIGHT 6
#define KEY_LEFT 7
#define KEY_MENU 8
#define KEY_AMS 9
#define KEY_MOD 10
#define KEY_MUTE 11
#define KEY_TA 12
#define KEY_PTY 13
#define KEY_1 14
#define KEY_2 15
#define KEY_3 16
#define KEY_4 17
#define KEY_5 18
#define KEY_6 19
#define KEY_RDS 20
#define KEY_MOD_REPEAT 128
