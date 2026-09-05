typedef struct Object Object;

struct Object {
    char pad0[0x14];
    Object* next;
    Object* prev;
};

extern Object* lbl_8064D540;
extern Object* lbl_8064D544;
extern void* lbl_8064D554;
extern void fn_8017CE74(void*);

void fn_801D0E78(Object* object)
{
    Object* current = object;

    object = current->prev;
    if (object != 0) {
        object->next = current->next;
    }
    object = current->next;
    if (object != 0) {
        object->prev = current->prev;
    }
    if (lbl_8064D544 != 0 && current == lbl_8064D544) {
        lbl_8064D544 = current->next;
    }
    if (lbl_8064D540 != 0 && current == lbl_8064D540) {
        lbl_8064D540 = current->prev;
    }
    fn_8017CE74(lbl_8064D554);
}
