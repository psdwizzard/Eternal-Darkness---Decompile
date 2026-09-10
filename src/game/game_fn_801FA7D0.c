typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MotionObject {
    u8 pad00[0x6C];
    void (*callback)(void*);
    u8 pad70[4];
    struct MotionObject* child;
    float time;
} MotionObject;

typedef struct MotionGlobals {
    void* entry;
    MotionObject* object;
    float secondary_time;
    float time;
    int value;
    int type;
} MotionGlobals;

extern MotionGlobals lbl_8063E9C8;
extern u8 lbl_802FC708[];
extern u8 lbl_802FC768[];
extern MotionObject* fn_801F7AF8(void);
extern void* fn_80144628(int, void*, int);
extern void fn_801446AC(void*, int);
extern int fn_80144608(void*);
extern void fn_801A5C30(int);
extern int fn_801FA198(void*, void*, int, int, int, int, int, int, void*);

void fn_801FA774(MotionObject*);

void fn_801FA7D0(void* resource, u16 value, int type, int set_child, int global_value,
                 float time, float secondary_time)
{
    lbl_8063E9C8.secondary_time = secondary_time;
    lbl_8063E9C8.time = time;
    lbl_8063E9C8.object = fn_801F7AF8();
    lbl_8063E9C8.value = global_value;
    lbl_8063E9C8.type = type;

    switch (type) {
    case 0:
        *(u16*)(lbl_802FC708 + 0x52) = value;
        lbl_8063E9C8.entry = fn_80144628(3, lbl_802FC708, 0);
        fn_801446AC(lbl_8063E9C8.entry, 1);
        fn_80144608(lbl_8063E9C8.entry);
        break;
    case 1:
        *(u16*)(lbl_802FC768 + 0x52) = value;
        lbl_8063E9C8.entry = fn_80144628(3, lbl_802FC768, 0);
        fn_801446AC(lbl_8063E9C8.entry, 1);
        fn_80144608(lbl_8063E9C8.entry);
        break;
    }

    fn_801A5C30(0);
    fn_801FA198(resource, lbl_8063E9C8.object, 0, 2, 0, 0, 0, 0, 0);
    lbl_8063E9C8.object->callback = (void (*)(void*))fn_801FA774;
    if (set_child != 0) {
        lbl_8063E9C8.object->child->time = time;
        lbl_8063E9C8.object->child->callback = (void (*)(void*))fn_801FA774;
    }
}
