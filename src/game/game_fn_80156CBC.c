typedef struct Object {
    char pad00[0x08];
    struct Object* next;
    char pad0C[0x0C];
    void (*callback)(struct Object*, void*);
    char pad1C[0x1C];
    void* callback_arg;
} Object;

typedef struct List {
    char pad00[0x08];
    Object* first;
} List;

extern List* fn_801560CC(int);
extern void GXSetCullMode(int);
extern int lbl_8064D0CC;

void fn_80156CBC(void)
{
    Object* object;
    int i;
    List* list = fn_801560CC(6);

    lbl_8064D0CC++;
    if (list != 0) {
        object = list->first;
        GXSetCullMode(0);
        while (object != 0) {
            if (object->callback != 0) {
                object->callback(object, object->callback_arg);
            }
            object = object->next;
        }
    }

    for (i = 8; i <= 125; i++) {
        list = fn_801560CC(i);
        if (list != 0) {
            Object* current = list->first;
            GXSetCullMode(0);
            while (current != 0) {
                if (current->callback != 0) {
                    current->callback(current, current->callback_arg);
                }
                current = current->next;
            }
        }
    }
    lbl_8064D0CC--;
}
