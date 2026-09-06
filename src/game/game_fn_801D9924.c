typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern Object* lbl_8064D544;

int fn_801D9924(int id)
{
    Object* object = lbl_8064D544;
    int found = 0;

    while (object != 0) {
        if (*(int*)(object->bytes + 0xC) == id &&
            (*(int*)(object->bytes + 4) & 0x1FF0) == 0x500 &&
            (object->bytes[0xFF1] == 0 || object->bytes[0xFF1] == 6)) {
            found = 1;
            break;
        }
        object = *(Object**)(object->bytes + 0x14);
    }
    return found;
}
