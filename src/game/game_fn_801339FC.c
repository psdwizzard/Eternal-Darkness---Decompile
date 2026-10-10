typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Object {
    Vec3 position;
    char pad_C[0x30];
    void* resource;
    char pad_40[0x214];
    int flags;
} Object;
typedef struct Entry {
    Object* object;
    u32 id;
    u32 field_8;
    void* link;
    void* resource;
    Vec3 position;
    u32 field_20;
    u8 field_24, field_25, flags, field_27;
} Entry;
typedef struct Manager {
    char pad_0[5];
    u8 count;
    u8 range;
    char pad_7[9];
    Entry* entries;
} Manager;
typedef struct ResourceInfo {
    char pad_0[0x98];
    short type;
} ResourceInfo;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct GlobalState {
    char pad_0[0x38];
    Color field_38;
} GlobalState;
typedef struct SceneState {
    char pad_0[0x1C8];
    int field_1C8;
} SceneState;

extern int fn_800CC2D8(void*, int);
extern void fn_8011F0E8(Vec3*, Vec3*);
extern void fn_8011F7E0(Object*, int);
extern void fn_80126880(void*);
extern void fn_8012BA28(u8*);
extern void fn_8012C478(void*, int, int);
extern void fn_80132C24(void);
extern void fn_80132C94(Manager*);
extern void fn_80132D50(void);
extern int fn_801386FC(u8);
extern void fn_80139940(int);
extern void fn_801568B8(void*, void*);
extern void fn_801568C0(void*, void*);
extern void fn_801568FC(void*, void*);
extern int fn_80156FF4(void*);
extern ResourceInfo* fn_80201B8C(void*);
extern Object* fn_80201BC8(void*);
extern void* fn_80201BD0(void*);
extern void* fn_80205288(void*);
extern GlobalState lbl_802FC5BC;
extern SceneState lbl_8030F540;
extern int lbl_8064B800, lbl_8064CBB8, lbl_8064CF44;
extern int lbl_8064D7E0[2], lbl_8064D7E8[2], lbl_8064D7F0[2];
extern int lbl_8064D7F8[2], lbl_8064D800[2];
extern const Color lbl_8065025C;

void fn_801339FC(Manager* arg)
{
    Manager* manager;
    Object* object;
    int i;
    void* resource;
    void* node;
    void* special;
    void* linked;
    Object* target;
    manager = arg;
    lbl_8064CF44 = 0;
    if (manager != 0) {
        i = 0;
        while (i < manager->count) {
            object = manager->entries[i].object;
            resource = manager->entries[i].resource;
            node = fn_80201BD0(object);
            if (fn_80201B8C(node)->type == 0x1D) {
                special = manager->entries[i].resource;
                if (special != 0) {
                    fn_801568B8(special, 0);
                    fn_801568C0(special, 0);
                    fn_801568FC(special, 0);
                    fn_80126880(object);
                }
                fn_8012BA28(object->resource);
                fn_80156FF4(special);
            } else {
                linked = fn_80205288(node);
                if (object != 0) {
                    object->flags &= ~0x8000;
                    fn_801568C0(resource, manager->entries[i].link);
                    fn_8011F0E8(&manager->entries[i].object->position,
                                &manager->entries[i].position);
                    if (linked != 0) {
                        target = fn_80201BC8(linked);
                        fn_8012C478(target, 0xF, 1);
                        if ((u8)fn_800CC2D8(target, 0)) {
                            fn_8012C478(target, 0x10, 0);
                        }
                        if ((u8)fn_800CC2D8(target, 1)) {
                            fn_8012C478(target, 0x11, 0);
                        }
                    }
                    if (object != 0) {
                        fn_8011F7E0(object, 0);
                    }
                }
            }
            i++;
        }
    }
    fn_80132C24();
    fn_80132D50();
    fn_80132C94(manager);
    lbl_8064B800 = 1;
    lbl_8064CBB8 = 1;
    lbl_802FC5BC.field_38 = lbl_8065025C;
    lbl_8030F540.field_1C8 = -2;
    fn_80139940(1);
    fn_801386FC(manager->range);
    lbl_8064D7F0[0] = 0;
    lbl_8064D7F0[1] = 0;
    lbl_8064D800[0] = 0;
    lbl_8064D800[1] = 0;
    lbl_8064D7F8[0] = 0;
    lbl_8064D7F8[1] = 0;
    lbl_8064D7E8[0] = 0;
    lbl_8064D7E8[1] = 0;
    lbl_8064D7E0[0] = 0;
    lbl_8064D7E0[1] = 0;
}
