typedef unsigned short u16;

extern const float lbl_8064EBD8;
extern unsigned int lbl_8064D18C;
extern void fn_801AAE68(float, int, int, int, void*, int, int, int, u16, int);

void fn_8008CA84(void* source)
{
    float intensity = lbl_8064EBD8;

    fn_801AAE68(intensity, 301, 100, 0, source, 2, 2, 0,
               (u16)lbl_8064D18C, 0);
}
