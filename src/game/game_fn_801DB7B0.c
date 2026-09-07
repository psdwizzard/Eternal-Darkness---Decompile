typedef signed short s16;
typedef unsigned int u32;
typedef unsigned char u8;
extern void fn_801DC49C(void);
extern void fn_801D0CA4(void*);
extern void* fn_801D0D78(u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void* fn_801D38E8(u32);
extern void fn_801D38BC(void*,u32*,s16*);
extern int fn_801CEB2C(u32);
extern void fn_801CE594(u32,u32,u32,u32,u32,u32,u32,s16,u32,u32,u32,u32,u32,u32,u32);

void* fn_801DB7B0(u32 a,u32 b,u32 c,u32 d,u32 e,u32 f,u32 g,u32 h,u32 i)
{
    u32 temp_hi; s16 lo; u32 hi; void* object;
    object=fn_801D0D78(a,b,c,d,(u32)fn_801DC49C,f,g,h,i,e);
    *(u32*)((u8*)object+0xBC)=0;
    fn_801D38BC(fn_801D38E8(b),&temp_hi,&lo);
    hi=temp_hi;
    fn_801CE594(b,c,d,fn_801CEB2C(b),0xFA,lo,0x16,0x16,d,0xDC,0,0xC8,(u32)fn_801D0CA4,(u32)object,(u32)&hi);
    return object;
}
