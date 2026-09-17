typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

extern void* fn_80201814(int);
extern void* fn_80155DB4(void);
extern void* fn_80149E04(void);
extern void fn_80147E88(void*);
extern void fn_8014F4CC(void*, void*);
extern void fn_8019B13C(void*);
extern u32 fn_80148300(void*, void*, void*);
extern void fn_80149EB8(void*);
extern int fn_801D3A24(int, int);
extern void fn_8019AE88(void);
extern float lbl_806511CC;
extern float lbl_806511E8;

void fn_801DE5DC(int owner, int value)
{
    u8 packet[0xc8];
    void* manager;
    void* object;
    void* second_object;
    s16 code;

    fn_80201814(owner);
    manager = fn_80155DB4();
    if (manager == 0)
        return;
    object = fn_80149E04();
    if (object == 0)
        return;

    fn_80147E88(packet);
    fn_8014F4CC(packet, object);
    *(int*)(packet + 0xa8) = owner;
    *(int*)((u8*)object + 8) = 0;
    *(int*)((u8*)object + 0x48) = 1;
    fn_8019B13C(packet);
    *(s16*)(packet + 4) = 0x5c;
    *(u8*)(packet + 1) = 0x10;
    *(s16*)(packet + 6) = 0x7a;
    *(u8*)(packet + 2) = 0xe1;
    *(signed char*)(packet + 3) = -5;
    *(int*)(packet + 0x1c) = 0;
    *(int*)(packet + 0x20) = 0;
    *(int*)(packet + 0x24) = 1;
    *(int*)(packet + 0x28) = 1;
    packet[0x16] = 0xe1;
    packet[0x17] = 0xe1;
    *(float*)(packet + 0x34) = lbl_806511CC;
    *(int*)(packet + 0x38) = value;
    if (fn_80148300(manager, packet, object) != 0) {
        second_object = fn_80149E04();
        if (second_object == 0)
            return;
        fn_80147E88(packet);
        fn_8014F4CC(packet, second_object);
        *(int*)(packet + 0xa8) = owner;
        *(void (**)(void))(packet + 0x90) = fn_8019AE88;
        *(int*)((u8*)second_object + 8) = 0;
        *(int*)((u8*)second_object + 0x48) = 1;
        fn_8019B13C(packet);
        code = fn_801D3A24(value, 0x31);
        *(s16*)(packet + 4) = code;
        *(u8*)(packet + 1) = 0x20;
        *(s16*)(packet + 6) = 0x7a;
        *(u8*)(packet + 2) = 0xff;
        *(signed char*)(packet + 3) = -5;
        *(int*)(packet + 0x1c) = 0;
        *(int*)(packet + 0x20) = 0;
        packet[0x16] = 0x0f;
        packet[0x17] = 0xff;
        *(float*)(packet + 0x34) = lbl_806511E8;
        *(int*)(packet + 0x38) = value;
        if (fn_80148300(manager, packet, second_object) == 0)
            fn_80149EB8(second_object);
        return;
    }

    fn_80149EB8(object);
}
