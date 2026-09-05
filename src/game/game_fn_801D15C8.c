typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object Object;
struct Object {
    u32 unk0;
    int flags;
    u32 unk8;
    int id;
    u32 unk10;
    Object* next;
    u8 pad18[0xAC];
    u8 control;
    u8 control2;
    u8 padC6[0xF2A];
    u8 state;
    u8 type;
};

extern Object* lbl_8064D544;
extern int fn_80201AE4(void);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern void* fn_80201B8C(void);

void fn_801D15C8(int id)
{
    Object* object = lbl_8064D544;

    while (object != 0) {
        if (object->id == id) {
            int kind = object->flags & 0x1FF0;
            if (kind == 0x1010 && object->type == 2) {
                object->state |= 2;
                object->control2 = 0;
                object->control |= 0x14;
            } else if (kind == 0x810 && object->type == 3) {
                object->state |= 2;
            }
        }
        object = object->next;
    }

    if (id == fn_80201AE4()) {
        void* item = fn_80204844(fn_80201B9C(), 0x22);
        if (item != 0) {
            void* manager = fn_80201B8C();
            void* state = *(void**)((u8*)manager + 0x3C);
            *(int*)((u8*)state + 8) = 1;
        }
    }
}
