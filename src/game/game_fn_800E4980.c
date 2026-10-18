typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void *lbl_8064C4E4;
extern Vec3 lbl_80325CE0;
extern float lbl_8064F6B0;
extern float lbl_8064F6B4;
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_8011F114();

void fn_800E4980(void)
{
    if (lbl_8064C4E4 != 0) {
        fn_8011F114(&lbl_80325CE0, lbl_8064C4E4);
        lbl_80325CE0.x += (1024 - rand()) & 0x7ff;
        lbl_80325CE0.y += (1024 - rand()) & 0x7ff;
        lbl_80325CE0.z += lbl_8064F6B4;
    } else {
        lbl_80325CE0.x = lbl_8064F6B0;
        lbl_80325CE0.y = lbl_8064F6B0;
        lbl_80325CE0.z = lbl_8064F6B0;
    }
}
