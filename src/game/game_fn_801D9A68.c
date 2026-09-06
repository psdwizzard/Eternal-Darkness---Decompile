typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Object {
    u8 bytes[0x20];
} Object;

extern int lbl_8064D18C;
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void*);
extern int fn_80201B4C(void*);
extern int fn_80201B5C(void*);
extern int fn_80201EB8(void*);
extern int fn_80201B54(void*);
extern int fn_802019EC(int, int);
extern u64 fn_8020123C(int, int, int, int);
extern void fn_800CC3BC(int, int, int, int, u32, int);
extern void fn_8000BA98(int);
extern void fn_8016B400(int, int, int);

void fn_801D9A68(Object* self)
{
    void* node = fn_80201B9C();
    int offset = 0;
    int run_second = 1;

    if (lbl_8064D18C == 0x61) {
        int first = fn_802019EC(0x88A, lbl_8064D18C);
        int second = fn_802019EC(0x88B, lbl_8064D18C);
        int third = fn_802019EC(0x88C, lbl_8064D18C);

        if (first != -1 && second != -1 && third != -1) {
            int mode = 0;
            fn_800CC3BC(1, *(int*)(self->bytes + 0xC), first, 0,
                        *(u32*)(self->bytes + 4), 0);
            fn_800CC3BC(1, *(int*)(self->bytes + 0xC), second, 120,
                        *(u32*)(self->bytes + 4), 0);
            fn_800CC3BC(1, *(int*)(self->bytes + 0xC), third, 240,
                        *(u32*)(self->bytes + 4), 0);
            offset = 2;
            while (node != 0) {
                int state = fn_80201B4C(node);
                fn_80201B5C(node);
                if ((state == 1 || state == 0) &&
                    fn_80201EB8(node) == lbl_8064D18C) {
                    int actor = fn_80201B54(node);
                    if (*(int*)(self->bytes + 0xC) != actor &&
                        (u32)(fn_8020123C(0x3B, *(int*)(self->bytes + 0xC), actor, 1) & 0xFFFFFFFFULL) == 1) {
                        fn_800CC3BC(1, *(int*)(self->bytes + 0xC), actor, offset,
                                    *(u32*)(self->bytes + 4), 1);
                        offset += 0x20;
                    }
                }
                node = fn_80201BC0(node);
            }
            switch (*(u32*)(self->bytes + 4) & 0x70000) {
            case 0x10000: mode = 1; break;
            case 0x20000: mode = 2; break;
            case 0x40000: mode = 3; break;
            }
            fn_8000BA98(mode);
            fn_8016B400(0x3B8, 0, 0);
            run_second = 0;
        }
    }

    if (run_second != 0) {
        while (node != 0) {
            u32 state = fn_80201B4C(node);
            int type;
            type = fn_80201B5C(node);
            if ((state <= 1 || type == 0x58 || type == 0x39) &&
                fn_80201EB8(node) == lbl_8064D18C) {
                int actor = fn_80201B54(node);
                if (*(int*)(self->bytes + 0xC) != actor &&
                    (u32)(fn_8020123C(0x3B, *(int*)(self->bytes + 0xC), actor, 1) & 0xFFFFFFFFULL) == 1) {
                    fn_800CC3BC(1, *(int*)(self->bytes + 0xC), actor, offset,
                                *(u32*)(self->bytes + 4), 1);
                    offset += 0x20;
                }
            }
            node = fn_80201BC0(node);
        }
    }
}
