typedef unsigned char u8;
typedef unsigned int u32;

extern u32 lbl_8064D18C;
extern void* lbl_8064C4E0;
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void*);
extern int fn_80201B5C(void*);
extern void* fn_80201B8C(void*);
extern u32 fn_80201B54(void*);
extern void* fn_80201BC8(void*);
extern int fn_801DC20C(u32, u32, int);
extern void fn_8020123C(int, u32, u32, u32);
extern void fn_801E79A0(void*, int);
extern int fn_801E79FC(void*, int);
extern u32 fn_802019EC(int, int);
extern void fn_801DB8A0(u32, int);

void fn_801DB9E0(u32 flags, int expected, u32 value, int* changed)
{
    void* event;

    for (event = fn_80201B9C(); event != 0; event = fn_80201BC0(event)) {
        u32 object;
        switch (fn_80201B5C(event)) {
        case 0x19:
        case 0x18:
        case 0x22:
        case 0x31:
        case 0x57:
            /* These event layouts select an embedded object and mask. */
            object = *(u32*)((u8*)fn_80201B8C(event) + 0xC);
            if (fn_801DC20C(flags, object, expected)) {
                u32 id = fn_80201B54(event);
                fn_8020123C(0xC4, id, id, value);
            }
            break;
        case 0x1A:
            object = *(u32*)((u8*)fn_80201B8C(event) + 0x30);
            if (fn_801DC20C(flags, *(u32*)((u8*)object + 8), expected)) {
                u32 id = fn_80201B54(event);
                fn_8020123C(0x39, id, id, 0);
            }
            break;
        case 0x32:
            object = fn_802019EC(0x1C3, 0x8B);
            fn_801DB8A0(object, 0x43);
            fn_801E79A0(lbl_8064C4E0, object);
            *changed = 1;
            break;
        case 0x5B:
            object = fn_80201B54(event);
            if (fn_80201BC8(event) != 0 && fn_801DC20C(flags, object, expected)) {
                fn_8020123C(0x4B, object, object, 0);
            }
            break;
        default:
            if (lbl_8064D18C == 0x8B && fn_801E79FC(lbl_8064C4E0, 0x20B)) {
                fn_801E79A0(lbl_8064C4E0, 0x20B);
            }
            break;
        }
    }
}
