#define NULL ((void *)0)

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SpawnRequest {
    Vec3 position;
    float scale;
    int kind;
    int subtype;
    int param18;
    int param1C;
    int param20;
    int param24;
    int count;
    int owner;
    int mode;
    u16 flags;
    u8 active;
    u8 pad37;
} SpawnRequest;

typedef struct ObjectInfo {
    u8 pad[0x9E];
    u8 state;
} ObjectInfo;

typedef void (*Callback)(void);

extern void fn_80043F44(SpawnRequest *request);
extern void *fn_80034708(SpawnRequest *request);
extern void *fn_80201BC8(void *object);
extern void fn_801261F4(void);
extern void fn_8012B7A0(void *model, float scale);
extern void fn_80201D54(void *object, int owner);
extern void fn_802015A4(void *object);
extern int fn_800CCA44(void *object);
extern int fn_801E8328(unsigned int mode, void *object);
extern void *fn_80156DA0(int type, void *arg);
extern void fn_80156904(void *task, Callback cb);
extern void fn_801568FC(void *task, Callback cb);
extern void fn_801568C0(void *task, Callback cb);
extern void fn_801568B8(void *task, Callback cb);
extern void fn_8015690C(void *task, Callback cb);
extern void fn_80156918(void *task, void *object);
extern void fn_801568C8(void *task, Callback a, Callback b, Callback c);
extern ObjectInfo *fn_80201B8C(void *object);
extern int fn_8011FCB0(void *model);
extern void *fn_80204A8C(void);
extern void fn_8012C62C(void *model, int a, int *b, int *c, int *d, int e);
extern int fn_80204CE4(void *object, void *handle);
extern void *fn_80201C2C(void *object);
extern void fn_8011FA8C(void *model, int a, int b);
extern void fn_80155DB4(void *object);
extern void *fn_80204C2C(void *object);
extern int ***fn_80201C24(void *object);
extern void *fn_80201B54(void *object);
extern void *fn_80158598(void *owner, int create);
extern void fn_801586CC(void *collection, int a, Callback b, Callback c);
extern void fn_800CC140(void *owner, void *target, int a, int b, int c);
extern void fn_80157FA8(void *collection);
extern void fn_80157C98(void *list, int a, int b);

extern void fn_8002A4C8(void);
extern void fn_8002A508(void);
extern void fn_8002A590(void);
extern void fn_8002A63C(void);
extern void fn_8002A754(void);
extern void fn_8002AA18(void);
extern void fn_8002AB84(void);
extern void fn_8002AC60(void);
extern void fn_800CBAB8(void);
extern void fn_800CBF40(void);

extern int lbl_8064E344;
extern int lbl_8064E348;
extern int lbl_8064E34C;

void *fn_800453E8(int kind, int subtype, int owner, int param18, int param1C,
                  int param20, int param24, int count, float scale,
                  Vec3 *position, int mode, void *source)
{
    SpawnRequest request;
    int c, b, a;
    void *object;
    void *model;
    void *link;
    void *handle;
    void *task;
    int ***list;
    void *srcOwner;
    void *dstOwner;
    void *collection;
    ObjectInfo *info;

    fn_80043F44(&request);
    request.kind = kind;
    request.subtype = subtype;
    request.owner = (owner == -1) ? request.owner : owner;
    request.param18 = (param18 == -1) ? request.param18 : param18;
    request.param1C = (param1C == -1) ? request.param1C : param1C;
    request.param20 = (param20 == -1) ? request.param20 : param20;
    request.param24 = (param24 == -1) ? request.param24 : param24;
    request.count = (count == -1) ? request.count : count;
    request.scale = scale;
    request.mode = (mode == -1) ? request.mode : mode;
    request.position.x = position->x;
    request.position.y = position->y;
    request.position.z = position->z;
    request.flags = 0;

    object = fn_80034708(&request);
    if (object != NULL) {
        model = fn_80201BC8(object);
        if (model != NULL) {
            fn_801261F4();
            fn_8012B7A0(model, request.scale);
        }
        fn_80201D54(object, request.owner);
        fn_802015A4(object);
        fn_800CCA44(object);
        if (request.mode == 1) {
            fn_801E8328(1, object);
        } else if (request.mode == 5) {
            task = fn_80156DA0(3, NULL);
            if (task != NULL) {
                fn_80156904(task, NULL);
                fn_801568FC(task, fn_8002AB84);
                fn_801568C0(task, fn_8002A63C);
                fn_801568B8(task, fn_8002AC60);
                fn_8015690C(task, fn_8002A4C8);
                fn_80156918(task, object);
                if (object != NULL) {
                    info = fn_80201B8C(object);
                    if (info != NULL) {
                        info->state = 3;
                    }
                }
            }
        } else if (request.mode == 2) {
            if (request.param1C <= 0) {
                request.param1C = 0x191;
            }
            task = fn_80156DA0(3, NULL);
            if (task != NULL) {
                fn_801568C8(task, fn_8011FCB0(model) ? fn_8002A508 : fn_8002A590,
                            fn_8002AC60, fn_8002AA18);
                fn_80156904(task, NULL);
                fn_801568FC(task, fn_8002AA18);
                fn_801568C0(task, NULL);
                fn_801568B8(task, NULL);
                fn_8015690C(task, NULL);
                fn_80156918(task, object);
            }
        } else if (request.mode == 4) {
            handle = fn_80204A8C();
            if (request.param1C <= 0) {
                request.param1C = 0x191;
            }
            a = lbl_8064E34C;
            b = lbl_8064E348;
            c = lbl_8064E344;
            fn_8012C62C(model, 0xF, &c, &b, &a, 4);
            fn_80204CE4(object, handle);
        } else if (request.mode == 3) {
            link = fn_80201C2C(source);
            fn_8011FA8C(model, 2, 0x800);
            handle = fn_80156DA0(3, NULL);
            fn_801568C8(handle, fn_8011FCB0(model) ? fn_8002A508 : fn_8002A590,
                        fn_8002AC60, fn_8002AA18);
            fn_801568FC(handle, fn_8002AA18);
            fn_8015690C(handle, fn_8002A4C8);
            fn_80156918(handle, object);
            fn_80156904(handle, fn_8002A754);
            fn_801568C0(handle, fn_8002A508);
            if (fn_8011FCB0(model)) {
                fn_801568C0(handle, fn_8002A508);
            } else {
                fn_801568C0(handle, fn_8002A590);
            }
            fn_801568B8(handle, fn_8002AC60);
            fn_80201BC8(source);
            fn_80155DB4(source);
            if (link == NULL) {
                link = fn_80204C2C(source);
            }
            fn_80204CE4(object, link);
            list = fn_80201C24(object);
            srcOwner = fn_80201B54(source);
            dstOwner = fn_80201B54(object);
            collection = fn_80158598(srcOwner, 0);
            if (collection == NULL) {
                collection = fn_80158598(srcOwner, 1);
                fn_801586CC(collection, 6, fn_800CBAB8, fn_800CBF40);
            }
            fn_800CC140(srcOwner, dstOwner, 0, ***list, 1);
            fn_80157FA8(collection);
            fn_80157C98(list, 0, 2);
        }
    }
    return object;
}
