typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 data[0x188];
} Object;

extern void* fn_80149E04(void);
extern void fn_80147E88(void*);
extern void fn_801540EC(void*, void*);
extern void fn_80149B0C(void*, int, int);
extern void fn_8019CFC4(void*);
extern void fn_80148A98(void*, void*);
extern void fn_80149B38(void*);
extern void fn_80184740(void*);
extern int fn_801E8328(int, void*, u32);
extern void fn_80149EB8(void*);
extern u8 lbl_802FC5BC[];

void fn_80153FD0(u32 value, Object* object)
{
    void* resource;
    u8* child;
    u32* global;
    u32 config;

    resource = fn_80149E04();
    *(void**)(object->data + 0xC0) = resource;
    if (*(void* volatile*)(object->data + 0xC0) != 0) {
        fn_80147E88(object);
        fn_801540EC(object, *(void**)(object->data + 0xC0));
        fn_80149B0C(*(void**)(object->data + 0xC0), 0, 0);
        fn_8019CFC4(object);
        *(u32*)(object->data + 0x20) = value;
        *(u32*)(object->data + 0xA8) = value;
        resource = fn_80149E04();
        *(void**)(object->data + 0x184) = resource;
        if (*(void* volatile*)(object->data + 0x184) != 0) {
            child = object->data + 0xC4;
            fn_80147E88(child);
            fn_80148A98(child, *(void**)(object->data + 0x184));
            *(u32*)(child + 0x94) = 0;
            *(u8*)(*(u8**)(object->data + 0x184)) = object->data[0];
            fn_80149B38(*(void**)(object->data + 0x184));
            fn_80184740(child);
            child[0] = 0x14;
            ((signed char*)child)[3] = -4;
            child[0x14] = 10;
            *(u16*)(child + 4) = 0x50;
            global = (u32*)lbl_802FC5BC;
            config = global[3];
            *(u32*)(child + 0x2C) = config;
            child[0x2F] = 0xE0;
            fn_801E8328(0x1B, object, config);
        } else {
            fn_80149EB8(*(void**)(object->data + 0xC0));
        }
    }
}
