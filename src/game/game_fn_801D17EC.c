typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object Object;
struct Object {
    u32 timer;
    u32 flags;
    void* data;
    u32 unkC;
    u32 unk10;
    Object* next;
    u32 unk18;
    void (*callback)(Object*);
    u8 pad20[0xFD2];
    u8 state2;
    u8 padFF3;
    u16 counter;
};

extern Object* lbl_8064D544;
extern u32 lbl_8064C300;
extern int fn_8015E4E8(void);
extern int fn_8015C628(void*);

void fn_801D17EC(void)
{
    Object* object = lbl_8064D544;
    int mode = fn_8015E4E8();

    while (object != 0) {
        if ((mode != 0 && (object->state2 & 0x80) != 0) ||
            (mode == 0 && ((object->state2 & 5) != 0 ||
             fn_8015C628(object->data) != 0))) {
            if (object->timer == 0 && object->counter != 0) {
                object->counter = 0;
                object->timer = 0x10000;
            }
            if ((object->timer >> 16) > object->counter) {
                int count = (object->timer >> 16) - object->counter;
                int i = 0;
                while (i < count) {
                    object->callback(object);
                    object->counter++;
                    i++;
                }
            }
            object->timer += lbl_8064C300;
        }
        object = object->next;
    }
}
