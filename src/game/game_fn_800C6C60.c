typedef struct ObjExtra {
    unsigned char pad0[0xBC];
    void *target; /* 0xBC */
} ObjExtra;

typedef struct ObjInfo {
    unsigned char pad0[0x8C];
    ObjExtra *extra; /* 0x8C */
    unsigned char pad90[0x9E - 0x90];
    unsigned char state; /* 0x9E */
    unsigned char flag;  /* 0x9F */
} ObjInfo;

extern void fn_80006954(int);
extern void fn_80046FC4(void *, int);
extern void fn_80047080(void *);
extern void *fn_8004918C(void);
extern void fn_8004948C(void *, void *, int);
extern int fn_800AD2B4(void);
extern void fn_800C96D4(void *, int, int, int, int, int, float);
extern void fn_800CF598(void *);
extern void fn_8011F0E8(void *, void *);
extern void *fn_8011F130(void *);
extern void fn_8011F9F8(void *);
extern unsigned int fn_8011FA8C(void *, int, int);
extern void fn_801261F4(void *);
extern void fn_8012B750(void *);
extern void fn_8012B7A0(void *);
extern void fn_8012C478(void *, int, int);
extern void *fn_80155DB4(void *);
extern void fn_801568C0(void *, void *);
extern void fn_801568FC(void *, void *);
extern void fn_801A7560(void *, void *);
extern void *fn_801A7780(void *);
extern void fn_801A7864(void *);
extern void fn_801DA220(void *, int);
extern void fn_801F6ED0(void *, void *);
extern void fn_802006D4(int, void *, int, int, int);
extern void fn_8020104C(int, void *, void *, int, float);
extern void fn_8020123C(int, void *, void *, void *);
extern void *fn_80201814(void *);
extern void fn_80201AF8(void *);
extern void *fn_80201B54(void *);
extern ObjInfo *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);
extern void fn_80201D3C(void *, int);
extern void fn_80201D54(void *, void *);
extern void *fn_80205288(void *);
extern void fn_800073E4(void);
extern void fn_8002A508(void);
extern void fn_8002AA18(void);

extern void *lbl_8064C4E4;
extern void *lbl_8064C5B4;
extern void *lbl_8064D18C;
extern float lbl_8064F200;
extern float lbl_8064F208;

void fn_800C6C60(void *object, void *arg1, ObjInfo *info) {
    void *handler;
    void *newObject;
    void *newRuntime;
    void *target;
    int extra;
    ObjInfo *newInfo;
    void *resource;
    void *owner;
    void *saved;

    extra = fn_800AD2B4();
    owner = fn_80201B54(object);
    fn_801568FC(fn_80155DB4(object), fn_8002AA18);
    fn_80201D3C(object, 1);
    info->state = 2;
    fn_800CF598(object);

    target = info->extra->target;
    newObject = fn_80201814(target);
    handler = fn_80155DB4(newObject);
    newRuntime = fn_80201BC8(newObject);
    newInfo = fn_80201B8C(newObject);

    fn_8020123C(0xF0, owner, target, (void *)2);
    fn_8020123C(0x3C, target, target, (void *)0);
    fn_8020123C(0xF0, target, owner, (void *)0x56);
    fn_8020123C(0xD5, target, owner, target);
    fn_8020104C(0x39, target, owner, 0, lbl_8064F208);
    fn_800C96D4(object, 0xFF, -1, 0, 100, 1, lbl_8064F200);
    fn_8011FA8C(arg1, 0xC0, 0);
    fn_801568FC(handler, fn_800073E4);
    fn_801568C0(handler, fn_8002A508);
    fn_80201D3C(newObject, 0);
    fn_80201D54(newObject, lbl_8064D18C);
    fn_8020123C(0xC0, fn_80201B54(newObject), info->extra->target, (void *)1);

    newInfo->state = 1;
    newInfo->flag = 1;
    newInfo->extra->target = 0;
    saved = fn_8011F130(arg1);
    fn_8011F0E8(newRuntime, saved);
    fn_8012B750(arg1);
    fn_8012B7A0(newRuntime);
    lbl_8064C5B4 = handler;
    fn_80201AF8(target);
    fn_801261F4(newRuntime);
    fn_8011F9F8(fn_80201BC8(fn_80205288(newObject)));
    fn_80046FC4(lbl_8064D18C, 0);
    fn_8012C478(newRuntime, 0xF, 1);
    fn_80047080(target);
    fn_802006D4(0, target, -1, 0x33, 0);
    fn_800C96D4(newObject, 1, 2, 0xFF, 100, 0, lbl_8064F200);
    fn_801DA220(target, 0);
    fn_8011FA8C(newRuntime, 0, 0xC0);
    fn_801F6ED0(lbl_8064C4E4, newRuntime);
    lbl_8064C4E4 = newRuntime;

    resource = fn_8004918C();
    fn_8004948C(newObject, resource, 0);
    fn_801A7864(resource);
    fn_801A7560(resource, fn_801A7780(resource));

    if (extra != 0) {
        fn_8020123C(0xFB, target, (void *)extra, target);
    }
    fn_80006954(0xB4);
}
