typedef unsigned char u8;
typedef unsigned int u32;

extern void fn_801ED468(int);
extern void fn_801A852C(void*, int, int, u32);
extern void fn_801ECF50(int);
extern void fn_801ECEC8(int, int, int);
extern void GXBegin(int, int, int);
extern void fn_80188648(float, float, float);
extern void fn_8018855C(void);
extern void GXSetCoPlanar(int);

void fn_80188584(float* input)
{
    u8 color[4];
    u32 copy;

    color[0] = 0xFF;
    color[1] = 0xFF;
    color[2] = 0xFF;
    color[3] = 0xFF;
    fn_801ED468(0x1B);
    copy = *(u32*)color;
    fn_801A852C(&copy, -1, -1, 0x80000000);
    fn_801ECF50(4);
    fn_801ECEC8(1, 3, 0);
    GXBegin(0x90, 3, 3);
    fn_80188648(input[0], input[1], input[2]);
    fn_80188648(input[3], input[4], input[5]);
    fn_80188648(input[6], input[7], input[8]);
    fn_8018855C();
    GXSetCoPlanar(1);
}
