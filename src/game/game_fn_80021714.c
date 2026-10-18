typedef float f32;

typedef f32 Mtx[3][4];

extern volatile f32 lbl_8064C65C;
extern volatile f32 lbl_8064C660;
extern const f32 lbl_8064DEA8;
extern const f32 lbl_8064DEE0;
extern const f32 lbl_8064DEE4;
extern const f32 lbl_8064DEE8;

extern void PSMTXTrans(Mtx, f32, f32, f32);
extern void PSMTXConcat(Mtx, Mtx, Mtx);
extern void GXLoadTexMtxImm(Mtx, int, int);

void fn_80021714(void)
{
    Mtx translation;
    Mtx scale;
    f32 wrap;
    f32 phase0;
    f32 half;

    PSMTXTrans(translation, lbl_8064DEA8, lbl_8064DEA8, lbl_8064DEA8);

    half = lbl_8064DEE4;
    scale[0][0] = half;
    scale[0][1] = lbl_8064DEA8;
    scale[0][2] = lbl_8064DEA8;
    scale[0][3] = lbl_8064DEA8;
    scale[1][0] = lbl_8064DEA8;
    scale[1][1] = half;
    scale[1][2] = lbl_8064DEA8;
    scale[1][3] = lbl_8064DEA8;
    scale[2][0] = lbl_8064DEA8;
    scale[2][1] = lbl_8064DEA8;
    scale[2][2] = lbl_8064DEA8;
    scale[2][3] = lbl_8064DEA8;

    {
        phase0 = lbl_8064C65C + lbl_8064DEE8;
        wrap = *(volatile f32 *)&lbl_8064DEE0;
        lbl_8064C65C = phase0;
        if (phase0 > wrap) {
            lbl_8064C65C = phase0 - wrap;
        }
    }

    {
        f32 wrap;
        f32 phase = lbl_8064C660;
        wrap = *(volatile f32 *)&lbl_8064DEE0;
        if (phase > wrap) {
            lbl_8064C660 = phase - wrap;
        }
    }

    PSMTXTrans(translation, -lbl_8064C65C, -lbl_8064C660,
                *(volatile f32 *)&lbl_8064DEA8);
    PSMTXConcat(scale, translation, scale);
    GXLoadTexMtxImm(scale, 0x21, 1);
}
