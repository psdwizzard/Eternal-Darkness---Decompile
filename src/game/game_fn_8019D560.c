typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Config {
    u8 size;
    u8 depth;
    u8 mode;
    s8 shift;
    u16 rate;
    u16 pad_6;
    u16 limit;
    u8 pad_A[0xA];
    u16 period;
    u16 pad_16;
    u8 levels[4];
    u8 flag_1C;
    u8 gain;
    u8 flag_1E;
    u8 flag_1F;
    u8 count;
    u8 flag_21;
    s8 direction;
    u8 flag_23;
} Config;

extern int fn_8018F0A0(void);

void fn_8019D560(Config* config)
{
    config->size = 0x20;
    config->depth = 4;
    config->mode = 0x80;
    config->shift = -4;
    config->rate = 7;
    config->limit = 0x20;
    config->pad_6 = 0;
    config->flag_1C = 1;
    config->period = 0xC;
    config->flag_1E = 2;
    config->gain = 0x40;
    config->levels[0] = 0xC0;
    config->levels[1] = 0xC0;
    config->levels[2] = 0xC0;
    config->levels[3] = 0x80;
    config->pad_16 = 0;
    config->flag_1F = 1;
    config->count = 2;
    config->flag_21 = 1;
    config->direction = fn_8018F0A0() ? -1 : 1;
    config->flag_23 = 0;
}
