typedef unsigned char u8;

typedef struct MotionObject {
    u8 pad00[0x6C];
    void (*callback)(void*);
    u8 pad70[4];
    struct MotionObject* child;
} MotionObject;

typedef struct MotionGlobals {
    void* entry;
    MotionObject* object;
    float scale;
    float time;
    int value;
    int type;
} MotionGlobals;

extern MotionGlobals lbl_8063E9C8;
extern void fn_80144C40(void);
extern void fn_80144680(void*);
extern void fn_801F85A4(void);
extern void fn_801A5C30(int);
extern void fn_8016B400(int, int, int);

void fn_801FAB0C(void)
{
    if (lbl_8063E9C8.entry != 0) {
        fn_80144C40();
        fn_801F85A4();
        lbl_8063E9C8.object->callback = 0;
        lbl_8063E9C8.object->child->callback = 0;
        lbl_8063E9C8.object = 0;
        fn_80144680(lbl_8063E9C8.entry);
        lbl_8063E9C8.entry = 0;
        fn_801A5C30(1);
        if (lbl_8063E9C8.value > 0) {
            fn_8016B400(lbl_8063E9C8.value, 0, 0);
        }
    }
}
