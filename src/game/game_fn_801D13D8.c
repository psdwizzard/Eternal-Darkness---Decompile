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
    u32 unk18;
    void (*callback)(Object*);
    u8 pad20[0xFD0];
    u8 state;
    u8 type;
};

extern Object* lbl_8064D544;
extern int fn_80201AE4(void);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern void* fn_80201B8C(void);
extern void* fn_80201ADC(void);
extern void* fn_80155DB4(void*);
extern void fn_8002F428(void*, void*);

void fn_801D13D8(int id, int notify)
{
    Object* object = lbl_8064D544;

    while (object != 0) {
        if (object->id == id && (object->flags & 0x1FF0) == 0x1010 &&
            object->type == 2) {
            object->state |= 2;
            if (notify != 0) {
                object->callback(object);
            }
            break;
        }
        object = object->next;
    }

    if (id == fn_80201AE4()) {
        void* item = fn_80204844(fn_80201B9C(), 0x22);
        if (item != 0) {
            void* manager = fn_80201B8C();
            void* state = *(void**)((u8*)manager + 0x3C);
            *(int*)((u8*)state + 8) = 1;
            if (notify != 0) {
                void* first = fn_80155DB4(item);
                void* second = fn_80155DB4(fn_80201ADC());
                fn_8002F428(first, second);
            }
        }
    }
}
