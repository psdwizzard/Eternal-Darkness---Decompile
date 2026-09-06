typedef unsigned char u8;

typedef struct GameObject {
    u8 pad00[0xC];
    int id;
    u8 pad10[4];
    struct GameObject* next;
    u8 pad18[0xFD9];
    u8 active;
} GameObject;

extern GameObject* lbl_8064D544;

int fn_801D30FC(int id)
{
    GameObject* object = lbl_8064D544;
    int found = 0;

    while (object != 0) {
        if (object->id == id && object->active == 1) {
            found = 1;
            break;
        }
        object = object->next;
    }
    return found;
}
