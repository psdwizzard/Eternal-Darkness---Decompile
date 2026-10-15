typedef unsigned char u8;
typedef struct Entry80201814 Entry80201814;

extern Entry80201814 *fn_80201814(int id);
extern void *fn_80201BC8(void *object);
extern u8 *fn_801294DC(void *owner, int kind, int flags, int mode);

int fn_8003CBA8(void *unused, int id)
{
    fn_801294DC(fn_80201BC8(fn_80201814(id)), 0x2C, 0x25, 0xA);
    return 1;
}
