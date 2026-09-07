typedef unsigned char u8;
typedef unsigned int u32;

typedef struct ObjectInfo {
    u8 pad00[0x30];
    int* identity;
    u8 pad34[0x58];
    struct ObjectRuntime* runtime;
} ObjectInfo;

typedef struct ObjectRuntime {
    u8 pad00[0x38];
    int child;
} ObjectRuntime;

extern int lbl_8064D5A8;
extern void* lbl_8064D18C;
extern int fn_80201B64(void*);
extern ObjectInfo* fn_80201B8C(void*);
extern void* fn_80201814(int);
extern void fn_8020123C(int, int, int, int);
extern void fn_800CD8C0(void*, u32, void*, int, int);

void fn_801DD0A8(u32 flags, void* object, int kind)
{
    int type;
    ObjectInfo* info;
    int child;
    int valid;

    if (object == 0)
        return;
    type = fn_80201B64(object);
    if (type == 8)
        return;
    if (type == 57)
        return;

    valid = 1;
    info = fn_80201B8C(object);
    child = info->runtime->child;
    if (child != 0) {
        void* resolved = fn_80201814(child);
        if (resolved != 0) {
            ObjectInfo* child_info = fn_80201B8C(resolved);
            if (*child_info->identity == lbl_8064D5A8) {
                valid = 0;
            } else {
                fn_8020123C(57, child, child, 0);
            }
        } else {
            info->runtime->child = 0;
        }
    }
    if (valid != 0)
        fn_800CD8C0(lbl_8064D18C, flags, object, kind, 0);
}
