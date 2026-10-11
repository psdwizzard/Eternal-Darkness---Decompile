typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
#define NULL ((void *)0)

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct CamState {
    u8 pad0[0x20];
    Vec3 position;
    u8 pad2C[0x58 - 0x2C];
    float facing;
    s16 mode;
    u8 room;
} CamState;

typedef struct CamParams {
    int objectId;
    int target;
    int room;
} CamParams;

extern int fn_80201B54();
extern void *fn_80201B3C();
extern void *fn_80201B8C();
extern void *fn_80201814();
extern void fn_802020B4();
extern void fn_8020104C(int, int, int, int, float);
extern void fn_80070E98();
extern void *fn_80201BC8();
extern void fn_800AE954();
extern int fn_80201EB8();
extern void fn_8011F114(Vec3 *, void *);
extern float fn_8012B750(void *);
extern void fn_801FA454();
extern int fn_801E741C();
extern void fn_800EAC84();
extern void fn_80049774();
extern int fn_800462C8();
extern int fn_801E79FC(void *, int);
extern void fn_8015C948();
extern void fn_801AC350();
extern void fn_800EAF48();

extern char lbl_8024A290[][12];
extern CamParams lbl_80325F38;
extern void *lbl_8064C4E0;
extern float lbl_8064F870;

void fn_800EAD50(void *object) {
    char (*strings)[12] = lbl_8024A290;
    int objectId;
    void *target;
    CamState *cam;
    u8 *link;
    u8 *objectData;
    u16 linkTarget;
    void *runtime;
    void *found;
    int title;
    int message;
    u8 room;
    Vec3 position;
    Vec3 unused;

    objectId = fn_80201B54(object);
    target = fn_80201B3C();
    if (target != NULL) {
        link = fn_80201B8C(target);
    } else {
        link = NULL;
    }
    objectData = fn_80201B8C(object);
    cam = *(CamState **)link;
    link = *(u8 **)(objectData + 0x60);
    found = fn_80201814(*(int *)link);
    if (found != NULL) {
        fn_802020B4(found, 0);
        fn_8020104C(8, objectId, *(int *)link, 0, lbl_8064F870);
    }
    fn_80070E98(target);
    if (cam->mode == 0x53) {
        return;
    }
    runtime = fn_80201BC8(target);
    linkTarget = *(u16 *)(link + 0x17C);
    fn_800AE954();
    cam->mode = fn_80201EB8(target);
    fn_8011F114(&position, runtime);
    cam->position = position;
    cam->facing = fn_8012B750(runtime);
    cam->room = *(int *)(objectData + 0x94);
    fn_801FA454(1, 2);
    title = fn_801E741C(strings[0]);
    runtime = fn_80201BC8(target);
    room = cam->room;
    fn_8011F114(&unused, runtime);
    lbl_80325F38.target = linkTarget;
    lbl_80325F38.objectId = objectId;
    lbl_80325F38.room = room;
    fn_800EAC84(target, room, &lbl_80325F38);
    fn_802020B4(target, 0);
    fn_80049774(0);
    if (fn_800462C8(1) == 0 && fn_801E79FC(lbl_8064C4E0, 0x28) == 0) {
        message = fn_801E741C(strings[1]);
    } else {
        message = fn_801E741C(strings[2]);
    }
    fn_8015C948(0x53, title, message, 0, 0, 0xBE, 0x80, 0x10, fn_800EAF48, &lbl_80325F38, 1);
    fn_801AC350(0, 1, 0);
}
