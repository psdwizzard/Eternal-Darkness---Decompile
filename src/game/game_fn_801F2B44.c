typedef float Mtx[3][4];

extern Mtx lbl_8063C068;
extern float lbl_80651348;
extern float lbl_8065134C;
extern float lbl_806513A8;
extern float lbl_806513D0;

extern void PSMTXConcat(Mtx, Mtx, Mtx);
extern void PSMTXInvXpose(Mtx, Mtx);
extern void PSMTXTrans(Mtx, float, float, float);
extern void PSMTXScale(Mtx, float, float, float);
extern void GXLoadTexMtxImm(Mtx, int, int);

void fn_801F2B44(void)
{
    Mtx temporary;
    Mtx output;

    PSMTXInvXpose(lbl_8063C068, output);
    PSMTXScale(temporary, lbl_806513A8, lbl_806513D0, lbl_80651348);
    PSMTXConcat(temporary, output, output);
    PSMTXTrans(temporary, lbl_806513A8, lbl_806513A8, lbl_8065134C);
    PSMTXConcat(temporary, output, output);
    GXLoadTexMtxImm(output, 0x30, 1);
}
