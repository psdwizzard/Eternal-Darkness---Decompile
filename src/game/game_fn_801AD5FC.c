typedef unsigned char u8;

typedef struct EffectSlot {
    int object_id;
    int handle;
    int resource;
    u8 x;
    u8 y;
    u8 active;
    u8 pad[5];
} EffectSlot;

extern EffectSlot lbl_8060B204[2];
extern int lbl_8064D300;
extern int lbl_8064D2FC;
extern int lbl_8064C2D0;
extern int fn_801AD848(int);
extern int fn_801AD7C0(int, int);
extern void fn_801AD46C(u8*, u8*);
extern void* memset(void*, int, unsigned long);

int fn_801AD5FC(int index, int force)
{
    int result = 0;

    if (lbl_8064D300 == 3) {
        if (force != 0 || lbl_8060B204[index].active == 0) {
            lbl_8060B204[index].active = 1;
            lbl_8060B204[index].object_id = lbl_8064C2D0;
            lbl_8060B204[index].handle = fn_801AD848(index);
            lbl_8060B204[index].handle = fn_801AD7C0(lbl_8060B204[index].handle, 3);
            lbl_8060B204[index].resource = lbl_8064D2FC;
            fn_801AD46C(&lbl_8060B204[index].x, &lbl_8060B204[index].y);
        }
        result = 1;
    } else {
        memset(&lbl_8060B204[index], 0, sizeof(EffectSlot));
    }
    return result;
}
