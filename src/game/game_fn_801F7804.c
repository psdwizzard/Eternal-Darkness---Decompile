typedef void (*Callback)(void*);

extern unsigned char lbl_8063CD18[];
extern void* lbl_8064C824;
extern int lbl_8064C3B0;
extern float lbl_80651488;

extern int fn_801A6D94(void*);
extern void fn_8016B400(int, int, int);

#define PTR(p, o) (*(void**)((unsigned char*)(p) + (o)))
#define CB(p, o) (*(Callback*)((unsigned char*)(p) + (o)))
#define INT(p, o) (*(int*)((unsigned char*)(p) + (o)))
#define FLT(p, o) (*(float*)((unsigned char*)(p) + (o)))

void fn_801F7804(void* state)
{
    void* target = PTR(state, 0x70);
    float divisor;
    int dx;
    int dy;
    int dz;

    if (target == 0) {
        return;
    }

    if (target == lbl_8063CD18 + 0x220 && fn_801A6D94(lbl_8064C824) == 0) {
        lbl_8064C3B0--;
        if (lbl_8064C3B0 < 0x50) {
            FLT(target, 8) += lbl_80651488;
        }
        if (lbl_8064C3B0 < 0) {
            lbl_8064C3B0 = 0xA0;
        }
    }

    divisor = FLT(state, 0x30);
    FLT(state, 0x48) -= (FLT(state, 0x48) - FLT(target, 0x48)) / divisor;
    FLT(state, 0x4C) -= (FLT(state, 0x4C) - FLT(target, 0x4C)) / divisor;
    FLT(state, 0x50) -= (FLT(state, 0x50) - FLT(target, 0x50)) / divisor;
    FLT(state, 0x00) -= (FLT(state, 0x00) - FLT(target, 0x00)) / divisor;
    FLT(state, 0x04) -= (FLT(state, 0x04) - FLT(target, 0x04)) / divisor;
    FLT(state, 0x08) -= (FLT(state, 0x08) - FLT(target, 0x08)) / divisor;
    FLT(state, 0x30) -= (FLT(state, 0x30) - FLT(target, 0x30)) / divisor;
    FLT(state, 0x28) -= (FLT(state, 0x28) - FLT(target, 0x28)) / divisor;
    FLT(state, 0x2C) -= (FLT(state, 0x2C) - FLT(target, 0x2C)) / divisor;
    FLT(state, 0x34) -= (FLT(state, 0x34) - FLT(target, 0x34)) / divisor;
    FLT(state, 0x38) -= (FLT(state, 0x38) - FLT(target, 0x38)) / divisor;

    dx = (int)((FLT(state, 0) - FLT(target, 0)) / divisor);
    dy = (int)((FLT(state, 4) - FLT(target, 4)) / divisor);
    dz = (int)((FLT(state, 8) - FLT(target, 8)) / divisor);
    if (dx == 0 && dy == 0 && dz == 0 && PTR(target, 0x74) != 0) {
        void* linked = PTR(target, 0x74);
        if ((INT(linked, 0x20) == 4 || INT(linked, 0x20) == 5) &&
            (INT(target, 0x20) == 4 || INT(target, 0x20) == 5)) {
            Callback target_cb = CB(target, 0x80);
            Callback state_cb = CB(state, 0x80);
            if (target_cb != 0) {
                target_cb(target);
            } else {
                if (state_cb != 0) {
                    state_cb(state);
                }
                if (INT(target, 0x44) > 0) {
                    fn_8016B400(INT(target, 0x44), 0, 0);
                    INT(target, 0x44) = 0;
                }
            }
        }
        if (INT(target, 0x20) == 3) {
            INT(target, 0x20) = 2;
            if (INT(target, 0x44) > 0) {
                fn_8016B400(INT(target, 0x44), 0, 0);
                INT(target, 0x44) = 0;
            }
        }
    }
}
