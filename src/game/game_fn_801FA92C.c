typedef struct MotionGlobals {
    void* entry;
    void* object;
    float secondary_time;
    float time;
    int value;
    int type;
} MotionGlobals;

extern MotionGlobals lbl_8063E9C8;
extern void fn_8011E310(int, int, int, int, int, int, int);
extern void fn_80144C4C(void*);

void fn_801FA92C(void)
{
    if (lbl_8063E9C8.entry != 0) {
        switch (lbl_8063E9C8.type) {
        case 0:
            fn_8011E310(2, 0x31, 0, 0x32, 0, 0, 0);
            break;
        case 1:
            fn_8011E310(2, 0x36, 0, 0x32, 0, 0, 0);
            break;
        }
        fn_80144C4C(lbl_8063E9C8.entry);
    }
}
