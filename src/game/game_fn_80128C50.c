typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Runtime {
    u32 first[14];
    u32 second[14];
    u32 third[14];
    u32 valueA8;
    u32 valueAC;
    u32 valueB0;
    u32 valueB4;
    u32 valueB8;
    float valueBC;
    float valueC0;
    u32 valueC4;
    u32 valueC8;
    Vec3 vectorCC;
    Vec3 vectorD8;
    Vec3 vectorE4;
    s32 valueF0;
    u32 flags;
    u16 valueF8;
    u16 valueFA;
    u16 valueFC;
    u16 valueFE;
    u8 rest : 7;
    u8 flag : 1;
    u8 value101;
    u8 active[14];
} Runtime;

extern const float lbl_806501A8;
extern const float lbl_806501AC;
extern Vec3 lbl_8024EE48;

void fn_80128C50(Runtime* runtime)
{
    int i;
    for (i = 0; i < 14; i++) {
        runtime->active[i] = 0;
        runtime->first[i] = 0;
        runtime->second[i] = 0;
        runtime->third[i] = 0;
    }
    runtime->valueA8 = 0;
    runtime->valueAC = 0;
    runtime->valueB0 = 0;
    runtime->valueB4 = 0;
    runtime->valueB8 = 0;
    runtime->valueBC = lbl_806501AC;
    runtime->valueC0 = lbl_806501A8;
    runtime->valueC8 = 0x10000;
    runtime->vectorCC = lbl_8024EE48;
    runtime->vectorD8 = lbl_8024EE48;
    runtime->vectorE4 = lbl_8024EE48;
    runtime->valueF8 = 0;
    runtime->flags = 0;
    runtime->valueC0 = lbl_806501A8;
    runtime->valueFA = 0;
    runtime->valueFC = 1;
    runtime->rest = 0;
    runtime->value101 = 0;
    runtime->valueF0 = -1;
    runtime->valueFE = 0;
    runtime->flag = 0;
}
