typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct Manager {
    char pad_00[5]; u8 count; char pad_06[10]; char* records;
    char vectors[0x20]; int limit;
} Manager;
typedef struct Batch {
    char pad_00[0x7C]; u8 kind; char pad_7D[5]; u16 adjustment;
} Batch;
typedef struct Descriptor {
    char pad_00[0xC]; int resource; int handle; char pad_14[0xA];
    s16 state; char pad_20[8];
} Descriptor;

extern char lbl_8030F540[], lbl_803003C8[];
extern Descriptor lbl_80241DE8[];
extern char lbl_8063CD18[], lbl_8063C6B8[], lbl_8063D378[], lbl_8063D400[];
extern float lbl_80650228;
extern int lbl_8064CF6C, lbl_8064CF40, lbl_80651BA0, lbl_8064D18C;
extern int lbl_8064C600, lbl_8064C850;
extern u8 lbl_8064CF48;

extern Manager* fn_8015E4A4(void);
extern Batch* fn_8015E1A8(int);
extern void fn_801313D8(void), fn_801FA410(int), fn_80236A1C(void*);
extern void fn_801F348C(int*, int), fn_801F8994(void*, float, void*);
extern void fn_8016B400(int, int, int), fn_80131A28(int);
extern void fn_80042F7C(int, int), fn_80237D2C(int), fn_801EFE84(int);
extern void fn_80131AA8(int, int), fn_8012A254(void*);
extern int fn_8012AFC4(void*), fn_80236D30(void), fn_80133300(void);
extern void fn_80132794(Manager*, Batch*), fn_80132B24(Batch*, int);
extern void fn_80132DD0(Batch*, int), fn_80133EC0(Manager*, Batch*);
extern void fn_80131E8C(Manager*, Batch*), fn_8013310C(Batch*);
extern void fn_80133C20(Manager*, Batch*), fn_80133D00(Manager*, Batch*, int);
extern void fn_80132A4C(Batch*), fn_80132FF8(int);

/* NonMatching: honest-C reconstruction of the transition resource validation,
 * batch setup, timing adjustment, and fallback paths. */
int fn_80131460(void)
{
    Manager* manager = fn_8015E4A4();
    int state = *(int*)(lbl_8030F540 + 0x1C8);
    int selected = state >> 1;
    lbl_8064CF6C = 0;
    if (state == 0) {
        Descriptor* descriptor;
        u8 kind;
        int timer;
        fn_801313D8();
        *(int*)(lbl_8030F540 + 0x1CC) = 0;
        timer = lbl_80651BA0;
        fn_801F348C(&timer, 100);
        lbl_8064CF40 = 0;
        fn_801FA410(9);
        *(float*)(lbl_8063CD18 + 0x4F8) = lbl_80650228;
        *(float*)(lbl_8063C6B8 + 0x4F8) = lbl_80650228;
        *(float*)(lbl_8063D378 + 0x30) = lbl_80650228;
        *(float*)(lbl_8063D400 + 0x30) = lbl_80650228;
        fn_801F8994(lbl_8063D378, *(float*)((char*)manager + 0x20),
                    (char*)manager + 0x14);
        fn_801F8994(lbl_8063D400, *(float*)((char*)manager + 0x20),
                    (char*)manager + 0x24);
        kind = *(u8*)(lbl_8030F540 + 0x1DA);
        descriptor = &lbl_80241DE8[kind];
        if (descriptor->resource != -1) fn_80236A1C(descriptor);
        descriptor = &lbl_80241DE8[*(u8*)(lbl_8030F540 + 0x1DA)];
        if (descriptor->handle != -1) fn_8016B400(descriptor->handle, 0, 0);
        fn_80131A28(lbl_8064D18C);
        kind = *(u8*)(lbl_8030F540 + 0x1DA);
        descriptor = &lbl_80241DE8[kind];
        if (descriptor->state != -1 && *(s8*)(lbl_8030F540 + 0x1DC) == 0 &&
            (*(u8*)(lbl_803003C8 + 0x1914) != 0 || kind == 0x60 ||
             (u8)(kind - 0x49) <= 2 || kind == 0x57 || kind == 0x83 ||
             kind == 0x84))
            fn_80042F7C(descriptor->state, 0);
        lbl_8064C600 = 3;
        fn_80237D2C(0);
        fn_801EFE84(0);
    }
    fn_80131AA8(*(u8*)(lbl_8030F540 + 0x1DA), selected);
    if (*(int*)(lbl_8030F540 + 0x1C8) < 0) return 0;
    {
        int i, offset;
        for (i = 0, offset = 0; i < manager->count; i++, offset += 0x28) {
            void* object = *(void**)(manager->records + offset);
            if (object != 0 && fn_8012AFC4(object) != 0) {
                int j, inner_offset;
                for (j = 0, inner_offset = 0; j < manager->count;
                     j++, inner_offset += 0x28)
                    fn_8012A254(*(void**)(manager->records + inner_offset));
                return 0;
            }
        }
    }
    {
        s16 transition = *(s16*)(lbl_8030F540 + 0x1D6);
        if (transition != -1)
        *(s16*)(lbl_8030F540 + 0x1D6) = lbl_8064C850;
        else if (transition == -1)
            *(int*)(lbl_8030F540 + 0x1CC) += 1;
    }
    {
        int i = 0;
        while (i < *(s16*)(lbl_8030F540 + 0x1D6) + 1) {
            Batch* batch = fn_8015E1A8(selected);
            if ((*(int*)(lbl_8030F540 + 0x1C8) & 1) == 0) {
                fn_80132794(manager, batch);
                fn_80132B24(batch, manager->limit - selected);
                fn_80132DD0(batch, selected);
                fn_80133EC0(manager, batch);
            }
            fn_80131E8C(manager, batch);
            fn_8013310C(batch);
            fn_80133C20(manager, batch);
            lbl_8064CF48 = batch->kind;
            fn_80133D00(manager, batch, selected);
            if (batch->adjustment != 0) {
                if (fn_80236D30() != 0) {
                    u8 kind = *(u8*)(lbl_8030F540 + 0x1DA);
                    int adjustment;
                    if (kind == 0x8F)
                        batch->adjustment = 0x598;
                    else if (kind == 0xAB)
                        batch->adjustment = 0x598;
                    else if (kind == 0xAC)
                        batch->adjustment = 0x598;
                    adjustment = (batch->adjustment - selected) * 2;
                    *(s16*)(lbl_8030F540 + 0x1D6) -= adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) += adjustment;
                    batch->adjustment = 0;
                } else batch->adjustment = 0;
            }
            if ((*(int*)(lbl_8030F540 + 0x1C8) & 1) == 0)
                fn_80132A4C(batch);
            if (*(s16*)(lbl_8030F540 + 0x1D6) > i) {
                fn_80133300();
                selected = *(int*)(lbl_8030F540 + 0x1C8) >> 1;
            }
            if (*(int*)(lbl_8030F540 + 0x1C8) == -2) break;
            i++;
        }
    }
    if (*(s16*)(lbl_8030F540 + 0x1D6) == -1 &&
        *(int*)(lbl_8030F540 + 0x1C8) != -2) {
        int index = *(int*)(lbl_8030F540 + 0x1C8) >> 1;
        Batch* batch = fn_8015E1A8(index);
        if ((*(int*)(lbl_8030F540 + 0x1C8) & 1) == 0) {
            int zero = 0;
            fn_80132794(manager, batch);
            fn_80131E8C(manager, batch);
            fn_8013310C(batch);
            fn_80132B24(batch, manager->limit - index);
            fn_80132DD0(batch, index);
            fn_80133C20(manager, batch);
            lbl_8064CF48 = batch->kind;
            fn_80132A4C(batch);
            while (lbl_8064CF6C != 0) {
                lbl_8064CF6C = zero;
                fn_80132A4C(batch);
            }
        } else {
            fn_80133C20(manager, batch);
            lbl_8064CF48 = batch->kind;
            fn_8013310C(batch);
            *(int*)(lbl_8030F540 + 0x1C8) -= 1;
        }
        fn_80132FF8(index + *(int*)(lbl_8030F540 + 0x1CC));
    }
    if (lbl_8064C850 != 0) {
        if (lbl_8064C850 < 0) *(s16*)(lbl_8030F540 + 0x1D6) = 0;
        lbl_8064C850 = 0;
    }
    return 2;
}
