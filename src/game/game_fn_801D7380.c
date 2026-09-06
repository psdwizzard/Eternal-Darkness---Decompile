typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object Object;
struct Object {
    u32 field00;
    int flags;
    u8 pad08[0xC];
    Object* next;
    u8 pad18[0xA8];
    int owner;
    u8 padC4[0x76];
    u8 type13A;
    u8 pad13B[0xEB6];
    u8 stateFF1;
};

extern Object* lbl_8064D544;

void fn_801D7380(int owner)
{
    Object* object = lbl_8064D544;

    while (object != 0) {
        if ((object->flags & 0x1FF0) == 0x410 && object->stateFF1 == 5 &&
            object->owner == owner) {
            object->type13A |= 8;
            return;
        }
        object = object->next;
    }
}
