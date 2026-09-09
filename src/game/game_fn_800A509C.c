typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Owner800A509C {
    u8 pad0[0xBC];
    void* previous;
} Owner800A509C;

typedef struct Runtime800A509C {
    u8 pad0[0x8C];
    Owner800A509C* owner;
    u8 pad90[0xE];
    u8 state;
    u8 active;
} Runtime800A509C;

typedef struct Local800A509C {
    u8 pad0[0xC];
    float scale;
    u32 kind;
    u32 mode;
    u8 pad18[0x10];
    u32 count;
    int value;
    u8 pad30[4];
} Local800A509C;

extern void* lbl_8064C4E4;
extern int lbl_8064C5B4;
extern int lbl_8064D18C;
extern const float lbl_8064EEF8;
extern int fn_80201B44();
extern void fn_80043F44(Local800A509C*);
extern void *fn_80201814();
extern void* fn_80155DB4(void*);
extern void *fn_80201B8C();
extern void fn_801568FC(void*, void*);
extern void fn_8002AA18(void);
extern void fn_8002A508(void);
extern void fn_8002AC60(void);
extern void fn_8002A4C8(void);
extern void fn_800073E4(void);
extern void fn_80201D3C(void*, int);
extern void fn_80201D54(void*, int);
extern void fn_80046F28(void*, int);
extern int fn_80201AE4(void);
extern void fn_80046FC4(int, int);
extern void *fn_80201BC8();
extern void fn_8012C478(void*, int, int);
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Local800A509C*, void*, int
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void* fn_80034708(Local800A509C*);
extern int fn_801261F4(void*);
extern void fn_8012B7A0(void*, float);
extern int fn_80201B54();
extern void fn_80201AF8(int);
extern void fn_802015A4(void*);
extern void* fn_80156DA0(int, Local800A509C*);
extern void fn_80156904(void*, int);
extern void fn_801568C8(void*, void*, void*, void*);
extern void fn_801568C0(void*, void*);
extern void fn_801568B8(void*, void*);
extern void fn_8015690C(void*, void*);
extern void fn_80156918(void*, void*);
extern void fn_801F6ED0(void*, void*);
extern int fn_8004918C(void);
extern void fn_8004948C(void*, int, int);
extern void fn_801A7864(int);

void fn_800A509C(int mode)
{
    Local800A509C local;
    void* object;
    void* context;
    Runtime800A509C* runtime;
    void* created;
    void* createdContext;
    int original = fn_80201B44();
    void* callback;
    int handle;

    fn_80043F44(&local);
    object = fn_80201814(original);
    context = fn_80155DB4(object);
    switch (mode) {
    case 1:
        local.kind = 13;
        local.mode = 1;
        break;
    case 2:
        local.kind = 22;
        local.mode = 6;
        break;
    case 3:
        local.kind = 20;
        local.mode = 7;
        break;
    }

    runtime = ((Runtime800A509C*)fn_80201B8C(object));
    fn_801568FC(context, fn_8002AA18);
    fn_80201D3C(object, 1);
    fn_80201D54(object, -2);
    fn_80046F28(object, -2);
    if (original == fn_80201AE4()) {
        fn_80046FC4(-2, 0);
    }
    fn_8012C478(fn_80201BC8(object), 15, 0);
    runtime->state = 2;
    runtime->active = 1;
    local.count = 50;
    local.value = lbl_8064D18C;
    local.scale = lbl_8064EEF8;
    fn_80201E78(&local, object, lbl_8064D18C);

    created = fn_80034708(&local);
    createdContext = fn_80201BC8(created);
    runtime = ((Runtime800A509C*)fn_80201B8C(created));
    fn_801261F4(createdContext);
    fn_8012B7A0(createdContext, local.scale);
    fn_80201D54(created, local.value);
    fn_80201D3C(created, 0);
    runtime->state = 1;
    runtime->owner->previous = (void*)original;
    fn_80201AF8(fn_80201B54(created));
    fn_802015A4(created);

    callback = fn_80156DA0(3, &local);
    fn_80156904(callback, 0);
    fn_801568C8(callback, fn_8002A508, fn_8002AC60, fn_800073E4);
    fn_801568FC(callback, fn_800073E4);
    fn_801568C0(callback, fn_8002A508);
    fn_801568B8(callback, fn_8002AC60);
    fn_8015690C(callback, fn_8002A4C8);
    fn_80156918(callback, created);
    fn_801F6ED0(lbl_8064C4E4, createdContext);
    lbl_8064C4E4 = createdContext;
    lbl_8064C5B4 = (int)callback;
    handle = fn_8004918C();
    fn_8004948C(created, handle, 0);
    fn_801A7864(handle);
}
