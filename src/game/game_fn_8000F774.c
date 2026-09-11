typedef unsigned char u8;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Request {
    Vec3 position;
    float scale;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    u8 pad34[4];
} Request;

typedef struct ItemArray {
    void** items;
    u8 pad04[0x14];
    void* data;
} ItemArray;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern s32 lbl_8064D18C;
extern void* lbl_8064C554;
extern s32 lbl_8064DD08;
extern s32 lbl_8064DD0C;
extern s32 lbl_8064DD10;
extern s32 lbl_8064DD14;
extern s32 lbl_8064DD18;
extern s32 lbl_8064DD1C;
extern s32 lbl_8064DD20;
extern s32 lbl_8064DD24;
extern s32 lbl_8064DD28;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void* fn_8016A784(void*, int);
extern void fn_8016A830(void*, double);
extern void fn_8016A7D8(void*);
extern void fn_80163BB4(void*, const char*, ...);
extern void fn_80043F44(Request*);
extern void* fn_80034708(Request*);
extern void *fn_80201BC8();
extern s32 fn_80036E14(void*);
extern u32 fn_8011F950(void*);
extern void fn_8012B7A0(void*, float);
extern void fn_80201D54(void*, s32);
extern void fn_802015A4(void*);
extern void fn_800CCA44(void*);
extern s32 fn_801261F4(void*);
extern int fn_801E8328();
extern void* fn_8012C62C(void*, s32, void*, void*, void*, s32);
extern void* fn_80156DA0(s32, void*);
extern s32 fn_8011FCB0(void*);
extern void fn_801568C8(void*, void*, void*, void*);
extern void fn_80156904(void*, void*);
extern void fn_801568FC(void*, void*);
extern void fn_801568C0(void*, void*);
extern void fn_801568B8(void*, void*);
extern void fn_8015690C(void*, void*);
extern void fn_80156918(void*, void*);
extern void* fn_80204A8C(void);
extern void fn_80204CE4(void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void* fn_80201C24();
extern void fn_80157B80(void*, s32);
extern unsigned int fn_8011FA8C(void*, int, int);
extern int fn_80201B44();
extern void *fn_80201814();
extern void* fn_80201C2C(void*);
extern void* fn_80204C2C(void*);
extern int fn_80201B54();
extern void* fn_80158598(void*, s32);
extern s32 fn_80158264(void*, void*, s32);
extern void fn_80157E34(void*, s32, void*, void*, s32);

extern s32 fn_8002A590(void*);
extern s32 fn_8002A508(void*);
extern void fn_8002AC60(void);
extern s32 fn_8002AA18(void*, void*, s32);
extern void fn_8002A4C8(void*);

/* NonMatching: remaining differences are register allocation only. */
s32 fn_8000F774(void* script)
{
    void* script_reg;
    void* view;
    Vec3s* position;
    s32 mode;
    void* handle;
    void* callback;
    void* found;
    ItemArray* array;
    s32 index;
    s32 v0a;
    s32 v1a;
    s32 v2a;
    s32 v0b;
    s32 v1b;
    s32 v2b;
    s32 v0c;
    s32 v1c;
    s32 v2c;
    Request req;

    script_reg = script;
    if (fn_8016A598(script_reg) != 11) {
        fn_80163BB4(script_reg, lbl_8023BEF8, 11,
                    fn_8016A598(script_reg));
        return 0;
    }

    fn_80043F44(&req);
    req.f10 = (s32)fn_8016A694(script_reg, 1);
    req.f14 = (s32)fn_8016A694(script_reg, 2);
    index = (s32)fn_8016A694(script_reg, 3);
    if (index == -1) {
        index = req.f2C;
    }
    req.f2C = index;
    index = (s32)fn_8016A694(script_reg, 4);
    if (index == -1) {
        index = req.f18;
    }
    req.f18 = index;
    index = (s32)fn_8016A694(script_reg, 5);
    if (index == -1) {
        index = req.f1C;
    }
    req.f1C = index;
    index = (s32)fn_8016A694(script_reg, 6);
    if (index == -1) {
        index = req.f20;
    }
    req.f20 = index;
    index = (s32)fn_8016A694(script_reg, 7);
    if (index == -1) {
        index = req.f24;
    }
    req.f24 = index;
    index = (s32)fn_8016A694(script_reg, 8);
    if (index == -1) {
        index = req.f28;
    }
    req.f28 = index;
    req.scale = (float)fn_8016A694(script_reg, 9);
    position = fn_8016A784(script_reg, 10);
    index = (s32)fn_8016A694(script_reg, 11);
    if (index == -1) {
        index = req.f30;
    }
    req.f30 = index;
    req.position.x = position->x;
    req.position.y = position->y;
    req.position.z = position->z;

    view = fn_80034708(&req);
    if (view == 0) {
        goto no_view;
    }

    handle = fn_80201BC8(view);
    mode = fn_80036E14(view);
    if (handle != 0 && fn_8011F950(handle) != 0) {
        fn_8012B7A0(handle, req.scale);
    }
    fn_80201D54(view, req.f2C);
    fn_802015A4(view);
    fn_800CCA44(view);

    if (handle != 0 && req.f2C == lbl_8064D18C && req.f30 != 9) {
        fn_801261F4(handle);
    }

    if (req.f30 == 1 || req.f30 == 6 || req.f30 == 8) {
        fn_801E8328(1, view);
        if (req.f30 != 8 && mode == 2) {
            goto done;
        }
        fn_801261F4(handle);
        v2a = lbl_8064DD10;
        v1a = lbl_8064DD0C;
        v0a = lbl_8064DD08;
        fn_8012C62C(handle, 15, &v0a, &v1a, &v2a, 4);
    } else if (req.f30 == 9) {
        fn_801E8328(29, view);
    } else if (req.f30 == 5) {
        goto done;
    } else if (req.f30 == 2) {
        mode = (s32)fn_80156DA0(3, 0);
        if (mode != 0) {
            if (fn_8011FCB0(handle) != 0) {
                callback = (void*)fn_8002A508;
            } else {
                callback = (void*)fn_8002A590;
            }
            fn_801568C8((void*)mode, callback, (void*)fn_8002AC60,
                        (void*)fn_8002AA18);
            fn_80156904((void*)mode, 0);
            fn_801568FC((void*)mode, 0);
            fn_801568C0((void*)mode, 0);
            fn_801568B8((void*)mode, 0);
            fn_8015690C((void*)mode, (void*)fn_8002A4C8);
            fn_80156918((void*)mode, view);
        }
    } else if (req.f30 == 4) {
        mode = (s32)fn_80204A8C();
        fn_801E8328(1, view);
        fn_801261F4(handle);
        v2b = lbl_8064DD1C;
        v1b = lbl_8064DD18;
        v0b = lbl_8064DD14;
        fn_8012C62C(handle, 15, &v0b, &v1b, &v2b, 4);
        fn_80204CE4(view, (void*)mode);
    } else if (req.f30 == 7) {
        mode = (s32)fn_80204A8C();
        fn_801E8328(1, view);
        fn_801261F4(handle);
        v2c = lbl_8064DD28;
        v1c = lbl_8064DD24;
        v0c = lbl_8064DD20;
        fn_8012C62C(handle, 15, &v0c, &v1c, &v2c, 4);
        fn_80204CE4(view, (void*)mode);
        fn_80201D2C(view, 0x24);
        fn_80201D14(view, 1);
        fn_80157B80(fn_80201C24(view), 0x80);
    } else if (req.f30 == 3) {
        void* object;

        handle = fn_80201BC8(view);
        fn_8011FA8C(handle, 0, 0x100);
        fn_801261F4(handle);
        object = fn_80156DA0(3, 0);
        if (fn_8011FCB0(handle) != 0) {
            callback = (void*)fn_8002A508;
        } else {
            callback = (void*)fn_8002A590;
        }
        fn_801568C8(object, callback, (void*)fn_8002AC60,
                    (void*)fn_8002AA18);
        fn_801568FC(object, (void*)fn_8002AA18);
        fn_8015690C(object, (void*)fn_8002A4C8);
        fn_80156918(object, view);
        lbl_8064C554 = object;
        found = fn_80201C2C(fn_80201814(fn_80201B44()));
        if (found == 0) {
            found = fn_80204C2C(fn_80201814(fn_80201B44()));
        }
        fn_80204CE4(view, found);
        array = fn_80201C24(view);
        found = fn_80158598((void*)fn_80201B44(), 0);
        if (found != 0) {
            index = fn_80158264(found, array, 1);
            array = *(ItemArray**)array;
            fn_80157E34(found, fn_80201B54(view),
                        array->items[index], array->data, 0);
        }
        lbl_8064C554 = 0;
    }

done:
    fn_8016A830(script_reg, (double)(s32)fn_80201B54(view));
    goto return_one;
no_view:
    fn_8016A7D8(script_reg);
return_one:
    return 1;
}
