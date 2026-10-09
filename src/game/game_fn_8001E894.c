typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef struct TextDescriptor TextDescriptor;
typedef struct StateSnapshot StateSnapshot;
typedef struct Range Range;
typedef struct Object Object;

typedef struct WordBlock8 {
    s32 words[8];
} WordBlock8;

typedef struct WordBlock3 {
    s32 words[3];
} WordBlock3;

typedef struct WordBlock24 {
    s32 words[24];
} WordBlock24;

typedef struct RuntimeState {
    TextDescriptor* first_handle;
    TextDescriptor* second_handle;
    TextDescriptor* third_handle;
    u8 pad_0C[8];
    s32 previous_value;
    s32 value;
    s32 previous_state;
    s32 state;
    s32 counter;
    s32 selection;
    s32 current_index;
    u32 flags;
    u32 aux_handle;
    u32 sound_handle;
    u16 sound_id;
    u8 mode;
    u8 previous_mode;
    u8 timer;
} RuntimeState;

extern u8 lbl_80302400[];
typedef struct GameState {
    s32 scene_values[2];
    s32 chapter;
    s32 field0C;
    u32 flags;
    u8 pad14[0x1900];
    u8 field1914;
    u8 field1915;
    u16 field1916;
    u8 slot;
    u8 field1919;
    u8 field191A;
} GameState;
extern GameState lbl_803003C8;
extern u8 lbl_80238978[];
typedef struct MenuData {
    u8 pad00[0x538];
    s32 choices[42];
    u8 chapters[0x17C];
    u8 settings[0x19C];
    char first_path[0x10];
    char second_path[0x10];
} MenuData;
extern MenuData lbl_8023D020;
extern u8 lbl_8063D378[];

extern void* lbl_8064C504;
extern u32 lbl_8064C2AC;
extern u8 lbl_8064B2C4;
extern s32 lbl_8064B2C0;
extern s32 lbl_8064B2B8;
extern s32 lbl_8064C6BC[2];
extern u32 lbl_8064C6C4;
extern s32 lbl_8064C6D4;
extern s32 lbl_8064CBA4;
extern void* lbl_8064C4E0;
extern u32 lbl_8064C650;
extern s32 lbl_8064C6A0;
extern s32 lbl_8064C69C;
extern s32 lbl_8064CBA0;
extern void* lbl_8064CE80;
extern s32 lbl_8064D294;
extern s32 lbl_8064C694;

extern void fn_80144C40(void);
extern void fn_801E5FB0(void*);

extern void* fn_801E5D08(void*);
extern TextDescriptor* fn_801E6CA0(void*, u32, u32, u32, int);
extern void fn_801EF5EC(void);
extern void fn_8020ED80(s32);
extern void fn_8001DFEC(u8, u32);
extern void fn_8001DE84(u8, u32);
extern void fn_8001DE68(void);
extern void fn_8001DA18(void);
extern s32 fn_800B193C(void);
extern void fn_800B2AE8(short);
extern void fn_800B177C(int, void*);
extern void fn_800B689C(s32, s32);
extern void fn_800B2548(int, int);
extern void fn_8002387C(s32);
extern void fn_80023800(s32);
extern void fn_80023918(s32);
extern s64 fn_8020F088(void*);
extern s64 fn_800F5ECC(s64, s64);
extern float fn_800F6264(s64);
extern u32 fn_8020ED10(void);
extern void fn_8001F758();
extern void fn_801AD404(u8, u8, s32);
extern void fn_801AD490(void);
extern void fn_801A9964();
extern void fn_801E79A0(u8*, u32);
extern void fn_801E7974(u8*, u32);
extern void* fn_8012070C(void);
extern u32 fn_8015E918(char*, void*, u32, void*, u32);
extern int fn_801A98F4(int, void*);
extern void fn_800AFBA8(StateSnapshot*);
extern s32 fn_80045230(void);
extern void fn_800451C4(s32);
extern u32 fn_801E7578(u32);
extern s32 fn_801E75A4(u32, s32);
extern unsigned int fn_800FBFB0(void);
extern void fn_800427E0(s32);
extern void fn_80023674(void);
extern void fn_80023710(void);
extern s32 fn_80144470(s32);
extern void fn_80144430(s32, s32);
extern void fn_801441C0(s32, s32, s32);
extern void fn_801F8620(void);
extern s32 fn_801FA410(s32);
extern void fn_801F10BC(s32, s32, s32);
extern void fn_8011C6BC(s32, s32, u8);
extern void fn_8011D558(s32);
extern void* fn_801E8A8C();
extern void fn_801E8AEC(Range*, s32, s32, void*);
extern void fn_801E8B24(Object*, s32, s32);
extern u32 fn_80144710(u32, s32, s32);
extern void fn_80023A68(void);
extern void fn_801A96A8(s32, s32, s32);
extern void fn_8011C830(s32);
extern s32 fn_801F85A4(void);
extern void fn_80025A78(int);

static inline void start_menu_callback(void* callback, s32 event)
{
    fn_800B177C(3, callback);
    fn_800B689C(1, 1);
    fn_800B2548(event, 0);
}

static inline RuntimeState* runtime_state(u8* root)
{
    register RuntimeState* base = (RuntimeState*)(root + 0x1C);
    /* ASM: mr retains the subobject base. MWCC folds the equivalent
     * C pointer into accesses relative to the outer buffer. */
    asm { mr base, base }
    return base;
}

static inline void* menu_base(void* address)
{
    register void* base = address;
    /* ASM: mr retains the menu subobject base. MWCC folds the equivalent
     * C pointer into field offsets on the containing menu object. */
    asm { mr base, base }
    return base;
}

static inline u32 read_flags(u8* root, RuntimeState** out)
{
    RuntimeState* state = runtime_state(root);
    *out = state;
    return state->flags;
}

static inline void dispatch_menu_input(void)
{
    register short input;
    /* ASM: mr preserves the incoming r3 value for the callee's unused
     * short parameter. C would otherwise initialize or narrow the argument. */
    asm { mr input, r3 }
    fn_800B2AE8(input);
}

void fn_8001E894(void)
{
    MenuData* menu = &lbl_8023D020;
    u8* tables = lbl_80238978;
    u8* root = lbl_80302400;
    RuntimeState* runtime = (RuntimeState*)(root + 0x1C);
    s32 keep_timer = 1;

    fn_80144C40();

    switch (runtime->mode) {
    case 1:
    case 2:
    case 23:
    case 24:
    case 25:
    case 26:
    case 29:
    case 31:
        runtime_state(root)->flags |= 1;
        keep_timer = 0;
        break;

    case 18:
        keep_timer = 0;
        fn_801E5FB0(runtime->first_handle);
        fn_801E5FB0(runtime->second_handle);
        fn_801E5FB0(runtime->third_handle);
        runtime->first_handle = 0;
        runtime->second_handle = 0;
        runtime->third_handle = 0;
        if (runtime->previous_state == 0) {
            runtime->first_handle = fn_801E6CA0(lbl_8064C504, 0, 35, 0, 1);
            {
                u32* value = fn_801E5D08(runtime->first_handle);
                *value = lbl_8064C2AC;
            }
            fn_801EF5EC();
            fn_8020ED80(1);
        } else {
            runtime->first_handle = fn_801E6CA0(lbl_8064C504, 0, 36, 0, 1);
            {
                u32* value = fn_801E5D08(runtime->first_handle);
                *value = lbl_8064C2AC;
            }
            fn_8020ED80(0);
        }
        runtime->timer = 150;
        runtime->sound_id = 7;
        runtime->counter = 0;
        fn_8001DFEC(19, 0);
        runtime_state(root)->selection = 0;
        break;

    case 30:
        if (fn_800B193C()) {
            dispatch_menu_input();
            keep_timer = 0;
        } else if (!lbl_8064B2C4) {
            if ((lbl_8064C6BC[0] == 2 || lbl_8064C6BC[0] == 0) &&
                (lbl_8064C6BC[1] == 2 || lbl_8064C6BC[1] == 0)) {
                if (lbl_8064C6BC[0] == 0 && lbl_8064C6BC[1] == 0) {
                    start_menu_callback(fn_8002387C, 13);
                } else if ((lbl_8064C6BC[0] == 2 || lbl_8064C6BC[0] == 0) &&
                           (lbl_8064C6BC[1] == 2 || lbl_8064C6BC[1] == 0)) {
                    start_menu_callback(fn_8002387C, 14);
                } else {
                    fn_8002387C(1);
                }
            } else {
                fn_8002387C(1);
            }
        }
        break;

    case 8:
        if (fn_800B193C()) {
            dispatch_menu_input();
            keep_timer = 0;
        } else if (!lbl_8064B2C4) {
            if ((lbl_8064C6BC[0] == 2 || lbl_8064C6BC[0] == 0) &&
                (lbl_8064C6BC[1] == 2 || lbl_8064C6BC[1] == 0)) {
                if (!(lbl_8064C6C4 & 1)) {
                    lbl_8064C6C4 |= 1;
                    lbl_8064C6C4 &= ~2u;
                    start_menu_callback(fn_80023918, 34);
                } else {
                    lbl_8064C6C4 = 1;
                    fn_80023918(0);
                }
            } else {
                fn_80023800(1);
            }
        }
        break;

    case 3: {
        RuntimeState* state;
        s32 limit = *(s32*)(root + 0x2CC);
        float now;
        now = fn_800F6264(fn_800F5ECC(fn_8020F088(root + 0x60),
            (*(volatile u32*)0x800000F8 / 4) / 1000));
        lbl_8064C6D4 = 1;
        keep_timer = 0;
        if (fn_8020ED10() == 1)
            fn_8001F758(0, 0);
        state = runtime_state(root);
        if (state->previous_value == 255 && now > (float)limit) {
            fn_801AD404(0, 0, 10);
            fn_801AD490();
            fn_801AD404(100, 100, 1);
            fn_8001DFEC(1, 0);
            fn_8001DA18();
        }
        {
            RuntimeState* flags_state;
            u32 flags = read_flags(root, &flags_state);
            state->previous_value = 255;
            flags_state->flags = flags | 1;
        }
        break;
    }

    case 4:
    case 5:
    case 6:
    case 13:
        dispatch_menu_input();
        keep_timer = 0;
        break;

    case 7: {
        RuntimeState* aux_state;
        if (runtime->sound_handle != (u32)-1) {
            fn_801A9964(runtime->sound_handle);
            runtime->sound_handle = (u32)-1;
        }
        aux_state = runtime_state(root);
        if (aux_state->aux_handle != (u32)-1) {
            fn_801A9964(aux_state->aux_handle);
            aux_state->aux_handle = (u32)-1;
        }
        switch (runtime_state(root)->previous_state) {
        case 0:
            fn_801E79A0(lbl_8064C4E0, 0x37E);
            if (lbl_8064CBA4 == 1)
                fn_8015E918(menu->first_path, (void*)0xE72D60, 0x330E0, fn_8012070C(), 0x330E0);
            else
                fn_8015E918(menu->second_path, (void*)0xE72D60, 0x330E0, fn_8012070C(), 0x330E0);
            fn_8001DE84(8, 0);
            fn_8001DE68();
            fn_801A98F4(0x27A, (void*)100);
            break;
        case 1:
            fn_801E79A0(lbl_8064C4E0, 0x37E);
            if (lbl_8064CBA4 == 1)
                fn_8015E918(menu->first_path, (void*)0xE72D60, 0x330E0, fn_8012070C(), 0x330E0);
            else
                fn_8015E918(menu->second_path, (void*)0xE72D60, 0x330E0, fn_8012070C(), 0x330E0);
            fn_800B177C(0, fn_80023710);
            fn_800B689C(1, 1);
            fn_800B2548(1, 0);
            {
                /* Snapshot every word before changing the menu settings. */
                u8* settings = menu_base(menu->settings);
                const volatile s32* source = (const volatile s32*)(tables + 0x40);
                s32* destination = (s32*)(settings + 0x60);
                s32 word0 = source[0];
                s32 word1 = source[1];
                s32 word2 = source[2];
                s32 word3 = source[3];
                s32 word4 = source[4];
                s32 word5 = source[5];
                s32 word6 = source[6];
                s32 word7 = source[7];
                s32 word8 = source[8];
                s32 word9 = source[9];
                s32 word10 = source[10];
                s32 word11 = source[11];
                s32 word12 = source[12];
                s32 word13 = source[13];
                s32 word14 = source[14];
                s32 word15 = source[15];

                destination[0] = word0;
                destination[1] = word1;
                destination[2] = word2;
                destination[3] = word3;
                destination[4] = word4;
                destination[5] = word5;
                destination[6] = word6;
                destination[7] = word7;
                destination[8] = word8;
                destination[9] = word9;
                destination[10] = word10;
                destination[11] = word11;
                destination[12] = word12;
                destination[13] = word13;
                destination[14] = word14;
                destination[15] = word15;
            }
            fn_8001DE84(13, 0);
            runtime_state(root)->selection = 2;
            break;
        case 2:
            fn_800AFBA8((StateSnapshot*)(root + 0x2DC));
            fn_8001DE84(14, 0);
            lbl_8064B2C0 = 1;
            runtime->selection = 7;
            lbl_8064C650 = fn_801A98F4(0x2D3, (void*)100);
            break;
        case 4:
            fn_8001DE84(28, 0);
            break;
        case 3: {
            if (lbl_8064CBA4 == 1)
                fn_8015E918(menu->first_path, (void*)0xE72D60, 0x330E0, fn_8012070C(), 0x330E0);
            else
                fn_8015E918(menu->second_path, (void*)0xE72D60, 0x330E0, fn_8012070C(), 0x330E0);
            fn_8001DE84(9, 0);
            fn_801E7974(lbl_8064C4E0, 0x37E);
            runtime_state(root)->selection = 12;
            lbl_8064C650 = fn_801A98F4(0x2D2, (void*)100);
            break;
        }
        }
        keep_timer = 0;
        fn_801A98F4(0x279, (void*)100);
        break;
    }

    case 9:
    case 17: {
        WordBlock24 values;
        s32 index;
        s32* choices;
        values = *(WordBlock24*)(tables + 0x80);
        index = 0;
        if (runtime->mode == 17)
            index = 12;
        index = runtime_state(root)->previous_state + index;
        runtime->current_index = index;
        if (index == 12)
            runtime->current_index = 0;
        else if (index < 12)
            runtime->current_index++;
        index = runtime->current_index;
        choices = menu_base(menu->choices);
        if (choices[index] >= 0) {
            s32 value = values.words[index];
            lbl_803003C8.chapter = choices[index];
            lbl_803003C8.scene_values[0] = value;
            lbl_803003C8.scene_values[1] = value;
            lbl_803003C8.field1914 = 0;
            lbl_803003C8.field1916 = 0;
            lbl_803003C8.field191A = 0;
            fn_800451C4(fn_80045230());
            lbl_8064C6A0 = -1;
            lbl_8064C69C = -1;
            if (runtime->current_index == 14) {
                fn_8001DFEC(20, 0);
                runtime_state(root)->selection = 3;
            } else if (runtime->current_index == 15) {
                fn_8001DFEC(21, 0);
                runtime_state(root)->selection = 7;
            } else {
                u8 mode = runtime->mode;
                RuntimeState* selection_state = runtime_state(root);
                selection_state->selection = 3;
                if (mode == 9) {
                    if (lbl_803003C8.chapter == 1) {
                        fn_800451C4(0);
                        if ((s32)fn_801E7578(lbl_803003C8.slot) > 2) {
                            selection_state->selection = 2;
                            fn_8001DFEC(250, 0);
                        } else {
                            fn_801A9964(lbl_8064C650);
                            fn_8001DE84(30, 0);
                        }
                    } else {
                        fn_8001DFEC(11,
                            fn_801E75A4(lbl_803003C8.slot, 0) - 1);
                    }
                } else {
                    fn_8001DFEC(22, (s32)fn_800FBFB0() % 3);
                }
            }
        }
        break;
    }

    case 21: {
        WordBlock8 first;
        WordBlock8 second;
        WordBlock8 third;
        s32 index;
        s32* game;
        /* Snapshot the three source tables in their stored order. */
        first = *(volatile WordBlock8*)(tables + 0xE0);
        second = *(volatile WordBlock8*)(tables + 0x100);
        third = *(volatile WordBlock8*)(tables + 0x120);
        index = runtime->previous_state;
        game = lbl_803003C8.scene_values;
        *game++ = third.words[index];
        *(s32*)(menu->chapters + 0x3C) = first.words[index];
        menu->choices[15] = second.words[index];
        *game = third.words[index];
        fn_8001DFEC(22, (s32)fn_800FBFB0() % 3);
        runtime_state(root)->selection = 3;
        break;
    }

    case 20: {
        WordBlock3 values = *(WordBlock3*)(tables + 0x140);
        s32 index = runtime->previous_state;
        *(s32*)(menu->chapters + 0x38) = values.words[index];
        {
            fn_8001DFEC(22, (s32)fn_800FBFB0() % 3);
        }
        runtime->selection = 3;
        break;
    }

    case 14:
        if (fn_800B193C()) {
            dispatch_menu_input();
            keep_timer = 0;
            break;
        }
        switch ((u32)runtime->previous_state) {
        case 0:
            fn_800B177C(1, fn_80023674);
            fn_800B689C(0, 1);
            fn_800B2548(1, 0);
            break;
        case 1:
            if (lbl_803003C8.flags & 1)
                lbl_803003C8.flags &= ~1u;
            else
                lbl_803003C8.flags |= 1;
            break;
        case 2:
            lbl_8064CBA4 ^= 1;
            break;
        case 3: {
            u32 old = fn_80144470(1);
            fn_80144430(1, old ^ 1);
            if (old)
                fn_801441C0(1, 0, 30);
            break;
        }
        case 4: {
            fn_801F8620();
            fn_801FA410(8);
            fn_801F10BC(0, 0, 0);
            *(s32*)(lbl_8063D378 + 0x40) = 1;
            runtime->mode = 16;
            *(WordBlock8*)(menu->settings + 0x80) = *(WordBlock8*)(tables + 0x14C);
            fn_8011C6BC(0x66, 0x9A, 0xFE);
            break;
        }
        case 5:
            *(s32*)(menu->settings + 0x68) = 0;
            *(void**)(menu->settings + 0xC8) = fn_8011D558;
            lbl_8064CE80 = fn_801E8A8C(0);
            fn_801E8AEC(lbl_8064CE80, 0, 0x33, (void*)0x33);
            fn_801E8B24(lbl_8064CE80, lbl_8064CBA0, 0);
            fn_8001DE84(15, 0);
            break;
        case 6:
            switch (lbl_8064D294) {
            case 0: lbl_8064D294 = 1; break;
            case 1: lbl_8064D294 = 2; break;
            case 2: lbl_8064D294 = 0; break;
            }
            fn_801A96A8(lbl_8064D294, 1, 1);
            break;
        }
        break;

    case 10:
        if (fn_80144710(0x1000, 0, 0)) {
            if (lbl_8064B2B8)
                fn_80023A68();
            else if ((u32)lbl_8064C694 >= 0x21)
                fn_80023A68();
        }
        keep_timer = 0;
        break;

    case 250:
        if (runtime->previous_state == 1)
            fn_801E7974(lbl_8064C4E0, 13);
        fn_801A9964(lbl_8064C650);
        fn_8001DE84(30, 0);
        break;

    case 11:
    case 22:
        fn_800427E0(runtime_state(root)->previous_state + 1);
        if ((s32)fn_801E7578(lbl_803003C8.slot) > 2) {
            runtime_state(root)->selection = 2;
            fn_8001DFEC(250, 0);
        } else {
            fn_801A9964(lbl_8064C650);
            fn_8001DE84(30, 0);
        }
        break;

    case 16: {
        {
            /* Snapshot every word before changing the menu settings. */
            u8* settings = menu_base(menu->settings);
            const volatile s32* source = (const volatile s32*)(tables + 0x16C);
            s32* destination = (s32*)(settings + 0x80);
            s32 word0 = source[0];
            s32 word1 = source[1];
            s32 word2 = source[2];
            s32 word3 = source[3];
            s32 word4 = source[4];
            s32 word5 = source[5];
            s32 word6 = source[6];
            s32 word7 = source[7];

            destination[0] = word0;
            destination[1] = word1;
            destination[2] = word2;
            destination[3] = word3;
            destination[4] = word4;
            destination[5] = word5;
            destination[6] = word6;
            destination[7] = word7;
        }
        fn_8011C830(1);
        fn_801F85A4();
        runtime->previous_mode = runtime->mode;
        runtime->mode = 14;
        runtime->state = runtime->previous_state;
        runtime->previous_state = 4;
        runtime->selection = 7;
        lbl_8064B2C0 = 1;
        break;
    }

    case 251:
    case 252:
    case 253:
    case 254:
        fn_80025A78(1);
        break;

    default:
        keep_timer = 0;
        break;
    }

    if (keep_timer)
        fn_801A98F4(0x27C, (void*)100);
}
