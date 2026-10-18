typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct ShortVector {
    s16 x, y, z;
} ShortVector;

typedef struct Vector {
    float x, y, z;
} Vector;

typedef struct InstanceList {
    u8 count;
    u8 pad1[3];
    u16 active;
    u8 pad6[2];
    void *data[16];
    void *parameters[16];
    void *instances[16];
} InstanceList;

typedef struct InstanceType InstanceType;
struct InstanceType {
    u8 pad0[4];
    s16 type;
    u8 pad6[0x8A];
    void *(*create)(ShortVector *, ShortVector *, InstanceType *);
    void (*prepare)(InstanceType *);
    int mode;
    void (*getRotation)(void *, ShortVector *, void *, void *, InstanceType *);
    void (*getPosition)(void *, ShortVector *, void *, void *, InstanceType *);
    void (*initialize)(void *, void *);
    u8 padA8[0x14];
    u8 category;
    u8 special;
    u8 value;
};

extern unsigned int lbl_80651BB8;
extern u16 lbl_80651BBC;
extern unsigned int lbl_80651BC0;
extern u16 lbl_80651BC4;
extern void *fn_80156938(void *);
extern void fn_8017FF1C(void *, u8);
extern void fn_80180AC8(u8 *, u8);
extern void *fn_8014856C(void *, InstanceList *, s16, int);
extern void fn_801482B8(void *, void *, int);
extern void fn_801568B8(void *, void *);
extern void fn_80148940(InstanceList *);

void *fn_80148300(void *arg0, void *arg1, void *arg2)
{
    u8 failed;
    struct Object *object;
    char *current;
    int count;
    u16 mask;
    int i;
    void *result;
    InstanceType *type;
    InstanceList *list;
    void *source;
    ShortVector position;

    object = arg0;
    type = arg1;
    result = 0;
    failed = 0;
    *(unsigned int *)&position = lbl_80651BB8;
    *(u16 *)&position.z = lbl_80651BBC;
    if (object == 0)
        return 0;

    count = ((InstanceList *)arg2)->count;
    list = arg2;
    source = fn_80156938(object);
    if (type->prepare != 0)
        type->prepare(type);

    list->active = 0;
    current = (char *)list;
    mask = 1;
    for (i = 0; i < count; mask <<= 1, current += 4, i++) {
        ShortVector rotation;
        InstanceList *entry = (InstanceList *)current;
        *(unsigned int *)&rotation = lbl_80651BC0;
        *(u16 *)&rotation.z = lbl_80651BC4;
        if (type->getPosition != 0)
            type->getPosition(source, &position, entry->data[0], entry->parameters[0], type);
        if (type->getRotation != 0)
            type->getRotation(source, &rotation, entry->data[0], entry->parameters[0], type);
        entry->instances[0] = type->create(&position, &rotation, type);
        if (entry->instances[0] != 0) {
            fn_8017FF1C(entry->instances[0], type->category);
            if (type->special == 1)
                fn_80180AC8(entry->instances[0], 2);
            list->active |= mask;
            if (type->initialize != 0)
                type->initialize(entry->instances[0], entry->data[0]);
        } else {
            failed = 1;
            break;
        }
    }

    if (!failed) {
        Vector positionFloat;
        positionFloat.x = position.x;
        positionFloat.y = position.y;
        positionFloat.z = position.z;
        if (list->active != 0) {
            Vector initialPosition = positionFloat;
            result = fn_8014856C(&initialPosition, list, type->type, type->value);
            if (result != 0) {
                fn_801482B8(result, object, type->mode);
                if (type->special == 1)
                    fn_801568B8(result, 0);
            } else {
                failed = 1;
            }
        } else {
            failed = 1;
        }
    }
    if (failed)
        fn_80148940(list);
    return result;
}
