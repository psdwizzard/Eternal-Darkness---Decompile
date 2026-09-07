typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 pad00[4];
    u32 flags;
    int type;
    u32 event;
    int handle;
    u8 pad14[0x14];
    void (*callback)(struct Object*, u32);
    u32 callback_arg;
    u8 pad30[8];
    u8 position[12];
    void* attached;
    u8 pad48[0x74];
    int field_BC;
    u8 padC0[0xF30];
    u8 object_flags;
    u8 padFF1[3];
    u16 state;
} Object;

extern int lbl_8064D18C;
extern u32 lbl_8064D6EC;
extern void* lbl_8064C5A8;
extern short lbl_8023BA30[][5];

extern void* fn_80201814(u32);
extern int fn_80201B64(void*);
extern void fn_8016B400(int, int, int);
extern void fn_801FE22C(void*);
extern void fn_801B05B0(int, int);
extern void fn_801DC418(Object*);
extern void fn_801DC2B8(u32, u32, u32, void*, void*);
extern void fn_801F74C8(int, int, int);
extern void fn_801441C0(int, int, int);
extern void fn_801DB9E0(u32, u32, void*, int*);
extern void fn_801A5C30(int);
extern int fn_801D38E8(u32);

void fn_801DC49C(Object* object)
{
    if (object->type != lbl_8064D18C || (object->object_flags & 1)) {
        if (object->state > 0xB9 && object->field_BC != 0) {
            switch (object->type) {
            case 0x8B:
            case 0x129:
            case 0x12A: {
                void* event = fn_80201814(object->event);
                if (event != 0 && fn_80201B64(event) != 8) {
                    fn_8016B400(0x72E, 0, 0);
                }
                break;
            }
            }
        }
        if (object->attached != 0) {
            fn_801FE22C(object->attached);
        }
        if (object->handle != -1) {
            fn_801B05B0(object->handle, 10);
        }
        fn_801DC418(object);
        return;
    }

    switch (object->state) {
    case 0x14:
        fn_801DC2B8(object->type, object->flags, object->event,
                    object->position, &object->attached);
        break;
    case 0xAF: {
        int first = 0xF;
        int second = 2;
        int third = 0xF;
        switch (object->flags & 0x70000) {
        case 0x10000:
            first = 0xF;
            second = 3;
            third = 0x1E;
            break;
        case 0x20000:
            first = 0x19;
            second = 5;
            third = 0x28;
            break;
        case 0x40000:
            first = 0x23;
            second = 7;
            third = 0x32;
            break;
        }
        fn_801F74C8(first, 1, second);
        fn_801441C0(1, 1, third);
        break;
    }
    case 0xB9: {
        void* event = fn_80201814(object->event);
        fn_801DB9E0(object->flags, object->event, object->position,
                    &object->field_BC);
        if (event != 0 && fn_80201B64(event) != 8 && object->field_BC != 0) {
            lbl_8064D6EC = 1;
            fn_801A5C30(0);
        }
        break;
    }
    case 0xDC: {
        void* event = fn_80201814(object->event);
        if (event != 0 && fn_80201B64(event) != 8) {
            if (object->field_BC != 0) {
                lbl_8064D6EC = 0;
                fn_801A5C30(1);
                fn_8016B400(0x72E, 0, 0);
            }
            if (lbl_8064D18C == 0x44) {
                if ((object->flags & 8) ||
                    lbl_8023BA30[fn_801D38E8(object->flags)]
                                    [*(u32*)lbl_8064C5A8] == 1) {
                    fn_8016B400(0x44A, 0, 0);
                }
            }
        }
    }
    case 0x104:
        if (object->callback != 0) {
            object->callback(object, object->callback_arg);
        }
        fn_801DC418(object);
        break;
    }
}
