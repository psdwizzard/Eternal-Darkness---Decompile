typedef signed int s32;

extern void* fn_80156938(void* object);
extern void* fn_801E8494(void);
extern void* fn_801E849C(void* node);
extern s32 fn_801E84A4(void* node);
extern void* fn_801E84AC(void* node);
extern void fn_801E8430(void* node);

void fn_802021EC(void* object)
{
    void* data;
    void* node;
    void* next;
    void* value;
    s32 type;

    data = fn_80156938(object);
    node = fn_801E849C(fn_801E8494());
    while (node != 0) {
        type = fn_801E84A4(node);
        next = fn_801E849C(node);
        value = fn_801E84AC(node);
        switch (type) {
        case 2:
            if (data == value) {
                fn_801E8430(node);
            }
            break;
        }
        node = next;
    }
}
