typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef unsigned char u8;
typedef struct Target Target;
typedef struct Voice Voice;

typedef struct State {
    unsigned char pad[0x90];
    Vec3 first;
    Vec3 second;
    Vec3 third;
    Vec3 fourth;
} State;

extern State lbl_80608020;
extern unsigned char lbl_806080E0[];
extern int lbl_8064D2F4;
extern float lbl_80650E60;
extern float lbl_80650E64;
extern float lbl_80650E68;
extern float lbl_80650E6C;
extern float lbl_80650E70;

extern int fn_801C9914(Voice*, Vec3*, Vec3*, Vec3*, float, float, float, Vec3*,
                       void*, u8, Target*);
extern void* memset(void*, int, unsigned long);
extern void fn_801ACC94(int);

void fn_801AAA28(void)
{
    float value = lbl_80650E60;

    lbl_80608020.first.x = value;
    lbl_80608020.first.y = value;
    lbl_80608020.first.z = value;
    lbl_80608020.second.x = value;
    lbl_80608020.second.y = value;
    lbl_80608020.second.z = value;
    lbl_80608020.third.x = value;
    lbl_80608020.third.y = value;
    lbl_80608020.third.z = lbl_80650E64;
    lbl_80608020.fourth.x = value;
    lbl_80608020.fourth.y = lbl_80650E68;
    lbl_80608020.fourth.z = value;

    fn_801C9914((Voice*)&lbl_80608020, &lbl_80608020.first, &lbl_80608020.second,
                &lbl_80608020.third, lbl_80650E6C, lbl_80650E6C, lbl_80650E70,
                &lbl_80608020.fourth, (void*)0, 0, (Target*)0);
    memset(lbl_806080E0, 0, 0x2F80);
    lbl_8064D2F4 = 1;
    fn_801ACC94(1);
}
