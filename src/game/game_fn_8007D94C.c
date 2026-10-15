typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct FourWords { u32 words[4]; } FourWords;
typedef union Rotation { Vec4 vector; FourWords words; } Rotation;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct SearchResult { u8 header[8]; Vec3 position; u8 tail[0x18]; } SearchResult;
typedef struct ModeState { u8 pad[8]; int mode; } ModeState;
typedef struct ObjectState {
    u8 pad[0x6c];
    void (*update)(void *);
    u8 pad70[4];
    struct ObjectState *child;
} ObjectState;
typedef struct MenuEntry { u8 pad[12]; void *context; u8 tail[16]; } MenuEntry;
typedef struct SceneEntry {
    u8 pad[0x2c]; int key;
    u8 pad30[0x38]; u32 flags;
    u8 pad6c[8];
} SceneEntry;
typedef struct Scene {
    u8 pad[0xb0]; u16 count; u8 padb2[2]; SceneEntry *entries;
} Scene;
typedef struct GameState {
    u8 pad0[0x18];
    u8 active; /* 0x18 */
    u8 pad19[0x1];
    u8 submode; /* 0x1A */
    u8 pad1B[0x39];
    float angle1; /* 0x54 */
    u8 pad58[0x2C];
    float angle2; /* 0x84 */
    u8 pad88[0x30];
    float angle3; /* 0xB8 */
    u8 padBC[0xD0];
    Vec3 position; /* 0x18C */
    Vec3 target; /* 0x198 */
    Vec3 direction; /* 0x1A4 */
    u8 pad1B0[0xC];
    int positionInitialized; /* 0x1BC */
    float selectionAngle; /* 0x1C0 */
    u8 pad1C4[0x7];
    s8 screen; /* 0x1CB */
    s8 selectionState; /* 0x1CC */
    s8 selectedItem; /* 0x1CD */
    s8 selections[18]; /* 0x1CE */
    u8 runeFlags[3]; /* 0x1E0 */
    u8 pad1E3[0x1];
} GameState;
typedef struct CameraPair { Vec3 first, second; u8 tail[8]; } CameraPair;
typedef struct ModelGroup {
    u8 pad[0x94]; void *primary, *secondary; u8 tail[0x1c];
} ModelGroup;
typedef struct MenuState {
    void *model; /* 0x0 */
    u8 pad4[8];
    CameraPair cameras[3];
    ModelGroup groups[5];
    void *model404; /* 0x404 */
    int value408; /* 0x408 */
    int value40C; /* 0x40C */
    int value410; /* 0x410 */
    int value414; /* 0x414 */
    int counter; /* 0x418 */
    void *pair[2][2]; /* 0x41C */
    s8 selectedGroup; /* 0x42C */
    u8 pad42D[0x3];
    void *model430; /* 0x430 */
    ObjectState * object; /* 0x434 */
    int value438; /* 0x438 */
    int value43C; /* 0x43C */
    int value440; /* 0x440 */
    u8 pad444[0x53];
    u8 flag497; /* 0x497 */
    void *text[3]; /* 0x498 */
    u8 pad4A4[0x16C];
    void *range; /* 0x610 */
    void *models[5]; /* 0x614 */
    u32 mask; /* 0x628 */
    int firstBit; /* 0x62C */
} MenuState;
extern Vec3 lbl_80239208[];
extern char lbl_80244870[];
extern ModeState lbl_803003C8;
extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern Color lbl_8064C2B4;
extern u8 *lbl_8064C4E0;
extern void *lbl_8064C4E4, *lbl_8064C508;
extern int *lbl_8064C5A8;
extern void *lbl_8064C8E8, *lbl_8064C8EC;
extern int lbl_8064C904, lbl_8064C908, lbl_8064C90C, lbl_8064D18C;
extern float lbl_8064EA08, lbl_8064EA0C, lbl_8064EA10, lbl_8064EA14;
extern void fn_8000738C(void);
extern void fn_8007D744(int);
extern void fn_8008210C(int, int);
extern int fn_800835CC(int);
extern void fn_80083938(void);
extern u32 fn_80113B64(void);
extern void fn_8011DD8C(int, int);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void fn_80120AD0(void *, const Vec3 *, u16, u32, float, float);
extern void fn_80128F74(void *, u32);
extern int fn_801290D0(void *);
extern void fn_8012CBE8(u8 *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern void fn_8012CDF0(u8 *, int, FourWords, int);
extern int fn_80144608(void *);
extern void *fn_80144628(int, int, int);
extern void fn_80144680(void *);
extern void fn_801446AC(void *, int);
extern void fn_801446D4(void **, void *);
extern void *fn_80158CC8(int, int, void *);
extern void *fn_8015C28C(int);
extern int fn_8015C4A4(void *, int);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_801A5C30(int);
extern int fn_801A98F4(int, void *);
extern void *fn_801E5D94(short, short, u8, s8, float, u32, Color, u16, const char *, ...);
extern void *fn_801E6CA0(void *, u32, u32, u32, int);
extern u32 fn_801E741C(const char *);
extern u32 fn_801E7578(u32);
extern void fn_801E79A0(u8 *, u32);
extern void fn_801E7DCC(const char *, ...);
extern void *fn_801E8A8C(void);
extern void fn_801E8AEC(void *, int, int, void *);
extern void fn_801E8B10(void *, u32, u32, u32, u32);
extern void fn_801E8B24(void *, int, int);
extern int fn_801F6228(u32, u16, u16);
extern void fn_801F63E4(u32, u16);
extern void *fn_801F7AF8(void);
extern int fn_801FA198(void *, void *, int, int, int, int, int, int, void *);
extern void fn_801FA748(int, Vec3 *);
extern void *fn_80201814(int);
extern int fn_802019EC(int, int);
extern void *fn_80201BC8(void *);
extern void fn_80211AAC(const Vec3 *, Vec3 *);
extern void *memset(void *, int, unsigned long);
extern void fn_80080FEC(int, int);
extern void fn_80081254(int, int);
extern void fn_800812E4(int, int);
extern void fn_80081874(int, int);
extern void fn_800824C8(int, int);
extern void fn_80083F78(int, int);
extern void fn_801F7C04(void *);

/* Create the selected menu and its scene objects.
 * The shared data pool contains menu entries, chapter IDs, and resource names. */
void fn_8007D94C(int screen)
{
    Vec3 *vectors = lbl_80239208;
    char *data = lbl_80244870;
    SearchResult result;
    Vec3 origin = vectors[0];
    Vec3 zero;
    Rotation modelRotation;
    Vec3 modelAxis;
    Rotation groupRotation;
    fn_801FA748(2, &origin);
    if (lbl_8064C8E8 != 0) {
        fn_80144680(lbl_8064C8E8);
        lbl_8031CBA0.screen = -1;
        lbl_8064C8E8 = 0;
    }
    switch (screen) {
    case 11: {
        int chapter = 0;
        u8 *flags;
        lbl_8064C8E8 = fn_80144628(5, (int)(data + 0x9c), 0);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        fn_801446D4(lbl_8064C8E8, fn_800824C8);
        switch (lbl_8064D18C) {
        case 0xda: chapter = 1; break;
        case 0x47: chapter = 2; break;
        }
        flags = (u8 *)&lbl_8031CBA0 + chapter;
        if (*(flags += 0x1e0) & 1)
            lbl_8031CD84.text[0] = fn_801E6CA0(lbl_8064C508, 2, 1, 0, 1);
        else
            lbl_8031CD84.text[0] = fn_801E6CA0(lbl_8064C508, 2, 0, 0, 1);
        if (*flags & 2)
            lbl_8031CD84.text[1] = fn_801E6CA0(lbl_8064C508, 2, 3, 0, 1);
        else
            lbl_8031CD84.text[1] = fn_801E6CA0(lbl_8064C508, 2, 2, 0, 1);
        if (*flags & 4)
            lbl_8031CD84.text[2] = fn_801E6CA0(lbl_8064C508, 2, 5, 0, 1);
        else
            lbl_8031CD84.text[2] = fn_801E6CA0(lbl_8064C508, 2, 4, 0, 1);
        break;
    }
    case 9:
    case 10: {
        int selection = 0;
        int resource = 0x7e6;
        u16 state = 0x100;
        u16 style = 0;
        u32 key;
        int alternate;
        int i, count;
        zero = vectors[1];
        key = fn_801E741C(data + 0x4dc);
        alternate = 0;
        if (lbl_803003C8.mode == 9) alternate = 1;
        lbl_8031CD84.range = fn_801E8A8C();
        if (lbl_803003C8.mode == 13) {
            lbl_8064C8E8 = fn_80144628(2, (int)(data + 0x19c), 0);
            lbl_8064C904 = -1;
            lbl_8064C908 = 0;
            lbl_8064C90C = 0;
            count = lbl_8064C5A8[-1] - 1;
            lbl_8031CBA0.selections[14] = 5;
            lbl_8031CBA0.selections[8] = count;
        } else {
            lbl_8064C8E8 = fn_80144628(3, (int)(data + 0x13c), 0);
        }
        switch (fn_800835CC(4)) {
        case 0: state = 0x20; style = 1; break;
        case 1: state = 8; style = 3; break;
        case 2: state = 0x10; style = 2; break;
        }
        fn_801F63E4(key, style);
        fn_801F6228(key, 0, 2);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        fn_801446D4(lbl_8064C8E8, fn_800812E4);
        memset(lbl_8031CD84.models, 0, 0x14);
        /* Each chapter exposes a different range of the acquired-rune mask. */
        switch (lbl_8064D18C) {
        case 0x108:
        case 0x11f: {
            int bit, modelIndex = 0;
            lbl_8031CD84.firstBit = 0;
            lbl_8031CD84.mask = fn_80113B64() & 0x7;
            if (lbl_8031CD84.mask == 0) {
                fn_801E7DCC(data + 0x4f4);
                lbl_8031CD84.mask = 0x7;
            }
            for (bit = 1; bit & 0x7; bit <<= 1, resource++) {
                if (bit & fn_80113B64()) {
                    Vec3 first, second, third;
                    lbl_8031CD84.models[modelIndex] = fn_80201BC8(fn_80201814(fn_802019EC(resource, lbl_8064D18C)));
                    switch (bit) {
                    case 1:
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0x222, lbl_8064EA08, lbl_8064EA08);
                        break;
                    case 2:
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0x20a, lbl_8064EA08, lbl_8064EA08);
                        break;
                    case 4:
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0x212, lbl_8064EA08, lbl_8064EA08);
                        break;
                    case 8:
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                        fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0x242, lbl_8064EA08, lbl_8064EA08);
                        break;
                    }
                    third = zero;
                    second = zero;
                    first = zero;
                    fn_8012CBE8(lbl_8031CD84.models[modelIndex], 15, &first, &second, &third, 0);
                    modelIndex++;
                }
            }
            break;
        }
        case 0x10b:
        case 0x122: {
            u16 objectState;
            int bit, modelIndex = 0;
            lbl_8031CD84.firstBit = 4;
            lbl_8031CD84.mask = fn_80113B64() & 0x1f0;
            if (lbl_8031CD84.mask == 0) {
                fn_801E7DCC(data + 0x4f4);
                lbl_8031CD84.mask = 0x1f0;
            }
            objectState = state | 0x202;
            for (bit = 16; bit & 0x1f0; bit <<= 1, resource++) {
                if (bit & fn_80113B64()) {
                    Vec3 first, second, third;
                    lbl_8031CD84.models[modelIndex] = fn_80201BC8(fn_80201814(fn_802019EC(resource, lbl_8064D18C)));
                    fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                    fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, objectState, lbl_8064EA08, lbl_8064EA08);
                    third = zero;
                    second = zero;
                    first = zero;
                    fn_8012CBE8(lbl_8031CD84.models[modelIndex], 15, &first, &second, &third, 0);
                    modelIndex++;
                }
            }
            break;
        }
        case 0x105:
        case 0x11c: {
            u16 objectState;
            int bit, modelIndex = 0;
            lbl_8031CD84.firstBit = 9;
            lbl_8031CD84.mask = fn_80113B64() & 0x1e00;
            if (lbl_8031CD84.mask == 0) {
                fn_801E7DCC(data + 0x4f4);
                lbl_8031CD84.mask = 0x1e00;
            }
            objectState = state | 0x202;
            for (bit = 512; bit & 0x1e00; bit <<= 1, resource++) {
                if (bit & fn_80113B64()) {
                    Vec3 first, second, third;
                    lbl_8031CD84.models[modelIndex] = fn_80201BC8(fn_80201814(fn_802019EC(resource, lbl_8064D18C)));
                    fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                    fn_80120AD0(lbl_8031CD84.models[modelIndex], 0, 100, objectState, lbl_8064EA08, lbl_8064EA08);
                    third = zero;
                    second = zero;
                    first = zero;
                    fn_8012CBE8(lbl_8031CD84.models[modelIndex], 15, &first, &second, &third, 0);
                    modelIndex++;
                }
            }
            break;
        }
        default:
            lbl_8031CD84.firstBit = 13;
            lbl_8031CD84.mask = fn_80113B64() & 0x2000;
            if (lbl_8031CD84.mask == 0) {
                fn_801E7DCC(data + 0x4f4);
                lbl_8031CD84.mask = 0x2000;
            }
            if (lbl_8031CD84.mask != 0) {
                Vec3 first, second, third;
                lbl_8031CD84.models[0] = fn_80201BC8(fn_80201814(fn_802019EC(0x7e6, lbl_8064D18C)));
                fn_80120AD0(lbl_8031CD84.models[0], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                fn_80120AD0(lbl_8031CD84.models[0], 0, 100, (u16)(state | 0x202), lbl_8064EA08, lbl_8064EA08);
                third = zero;
                second = zero;
                first = zero;
                fn_8012CBE8(lbl_8031CD84.models[0], 15, &first, &second, &third, 0);
            }
            break;
        }
        {
            int *chapters = (int *)(data + 0x10) + alternate;
            GameState *saved = (GameState *)((u8 *)&lbl_8031CBA0 + alternate);
            for (i = 0; i < 9; i++) {
                if (lbl_8064D18C == *chapters)
                    selection = saved->selections[0];
                chapters += 2;
                saved = (GameState *)((u8 *)saved + 2);
            }
        }
        lbl_8031CBA0.selectionState = 0;
        selection -= lbl_8031CD84.firstBit;
        selection = 0 > selection ? 0 : selection;
        fn_801E8AEC(lbl_8031CD84.range, 0, fn_801E7578(lbl_8031CD84.mask), (void *)5);
        fn_801E8B10(lbl_8031CD84.range, 1, 1, 0, 0);
        count = fn_801E7578(lbl_8031CD84.mask);
        fn_801E8B24(lbl_8031CD84.range, selection, 0);
        lbl_8031CBA0.selectionAngle = (float)selection * (lbl_8064EA0C / (float)count);
        break;
    }
    case 8: {
        int alternate = lbl_8064D18C != 0x4e;
        lbl_8064C8E8 = fn_80144628(3, (int)(data + 0x1dc), 0);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        lbl_8031CD84.pair[alternate][0] = fn_80201BC8(fn_80201814(fn_802019EC(0x28a, lbl_8064D18C)));
        lbl_8031CD84.pair[alternate][1] = fn_80201BC8(fn_80201814(fn_802019EC(0x28b, lbl_8064D18C)));
        fn_8008210C(0, 1);
        break;
    }
    case 7:
        lbl_8031CD84.counter = 0x578;
        lbl_8064C8E8 = fn_80144628(2, (int)(data + 0x23c), 0);
        fn_8000738C();
        fn_801446D4(lbl_8064C8E8, fn_80081254);
        break;
    case 5:
        lbl_8064C8EC = fn_801E5D94(320, 50, 0, 99, lbl_8064EA08, 11, lbl_8064C2B4, 0, data + 0x53c);
        lbl_8064C8E8 = fn_80144628(0, 0, 0);
        fn_801446D4(lbl_8064C8E8, fn_80080FEC);
        break;
    case 0: {
        int i;
        CameraPair *cameras;
        lbl_8064C8E8 = fn_80144628(4, (int)(data + 0x27c), 0);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        lbl_8031CBA0.active = 1;
        lbl_8031CBA0.submode = 0;
        lbl_8031CD84.model = fn_80201BC8(fn_80201814(fn_802019EC(0xa5, lbl_8064D18C)));
        fn_8011DD8C(2, 0);
        fn_8011DD8C(4, 0);
        fn_8011F6A4(lbl_8031CD84.model, 2, 15, -1, &result, 1);
        if (lbl_8031CBA0.positionInitialized == 0) {
            Vec3 found = result.position;
            lbl_8031CBA0.position = found;
            lbl_8031CBA0.target = found;
            lbl_8031CBA0.target.y -= lbl_8064EA10;
            lbl_8031CBA0.direction = vectors[2];
            fn_80211AAC(&lbl_8031CBA0.direction, &lbl_8031CBA0.direction);
            lbl_8031CBA0.positionInitialized = 1;
        }
        cameras = lbl_8031CD84.cameras;
        for (i = 0; i < 3; i++) {
            int first = -1, second = -1;
            short *position;
            switch (i) {
            case 0:
                first = fn_8015C4A4((void *)fn_801E741C(data + 0x548), 2);
                second = first;
                break;
            case 1:
                first = fn_8015C4A4((void *)fn_801E741C(data + 0x554), 2);
                second = first;
                break;
            case 2:
                first = fn_8015C4A4((void *)fn_801E741C(data + 0x560), 2);
                second = fn_8015C4A4((void *)fn_801E741C(data + 0x56c), 2);
                break;
            }
            position = fn_80158CC8(first, 2, cameras[i].tail);
            cameras[i].first.x = position[0];
            cameras[i].first.y = position[1];
            cameras[i].first.z = position[2];
            position = fn_80158CC8(second, 2, cameras[i].tail);
            cameras[i].second.x = position[0];
            cameras[i].second.y = position[1];
            cameras[i].second.z = position[2];
        }
        break;
    }
    case 1: {
        lbl_8064C8E8 = fn_80144628(4, (int)(data + 0x2fc), 0);
        fn_801446D4(lbl_8064C8E8, fn_80081874);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        lbl_8031CD84.value408 = 0;
        lbl_8031CD84.value40C = 0;
        lbl_8031CD84.value410 = 0;
        lbl_8031CD84.value414 = 2;
        lbl_8031CD84.counter = 0;
        lbl_8031CD84.model404 = fn_80201BC8(fn_80201814(fn_802019EC(0xad, lbl_8064D18C)));
        modelAxis = vectors[3];
        fn_8017A244(&modelAxis, &modelRotation.vector, lbl_8064EA14);
        fn_8012CDF0(lbl_8031CD84.model404, 8, modelRotation.words, 0);
        break;
    }
    case 2:
        lbl_8064C8E8 = fn_80144628(4, (int)(data + 0x37c), 0);
        fn_80128F74(lbl_8064C4E4, fn_801290D0(lbl_8064C4E4) | 4);
        fn_801A5C30(0);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        lbl_8031CD84.flag497 = 0;
        break;
    case 3:
        fn_801A5C30(0);
        lbl_8031CD84.value43C = 0;
        lbl_8064C8E8 = fn_80144628(3, (int)(data + 0x3fc), 0);
        fn_801446D4(lbl_8064C8E8, fn_80083F78);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        lbl_8031CD84.model430 = fn_80201BC8(fn_80201814(fn_802019EC(0xb7, lbl_8064D18C)));
        lbl_8031CD84.value438 = 0;
        lbl_8031CD84.value440 = 0;
        lbl_8031CBA0.selectedItem = -1;
        lbl_8031CD84.object = fn_801F7AF8();
        fn_801FA198((void *)fn_801E741C(data + 0x578), lbl_8031CD84.object, 0, 2, 0, 0, 0, 0, 0);
        lbl_8031CD84.object->update = fn_801F7C04;
        lbl_8031CD84.object->child->update = fn_801F7C04;
        fn_80083938();
        break;
    case 4: {
        Scene *scene = fn_8015C28C(2);
        void *resource;
        int i;
        void *selected;
        MenuEntry *entries;
        ModelGroup *groups;
        fn_801E79A0(lbl_8064C4E0, 0x112);
        lbl_8031CD84.selectedGroup = 1;
        for (i = 0; i < 5; i++) {
            lbl_8031CD84.groups[i].primary = 0;
            lbl_8031CD84.groups[i].secondary = 0;
        }
        lbl_8031CD84.groups[1].primary = fn_80201BC8(fn_80201814(fn_802019EC(0x8d9, lbl_8064D18C)));
        lbl_8031CD84.groups[2].secondary = fn_80201BC8(fn_80201814(fn_802019EC(0x8da, lbl_8064D18C)));
        lbl_8031CD84.groups[3].secondary = fn_80201BC8(fn_80201814(fn_802019EC(0x8db, lbl_8064D18C)));
        resource = fn_80201814(fn_802019EC(0x2711, lbl_8064D18C));
        if (resource != 0) fn_801A98F4(0x2b2, (void *)100);
        groups = lbl_8031CD84.groups;
        for (i = 0; i < scene->count; i++) {
            SceneEntry *entry = &scene->entries[i];
            if (entry->flags & 1) {
                switch (entry->key) {
                case 0x2cde7cef:
                    if (resource != 0) {
                        groups[1].secondary = fn_80201BC8(resource);
                        fn_8017A244((Vec3 *)((u8 *)&lbl_8031CD84 + 0x194), &groupRotation.vector, lbl_8031CBA0.angle1);
                        fn_8012CDF0(groups[1].secondary, 15, groupRotation.words, 0);
                    }
                    lbl_8031CD84.selectedGroup = 1;
                    break;
                case 0x2cdf3ced:
                    if (resource != 0) {
                        groups[2].primary = fn_80201BC8(resource);
                        fn_8017A244((Vec3 *)((u8 *)&lbl_8031CD84 + 0x240), &groupRotation.vector, lbl_8031CBA0.angle2);
                        fn_8012CDF0(groups[2].primary, 15, groupRotation.words, 0);
                    }
                    lbl_8031CD84.selectedGroup = 2;
                    break;
                case 0x2cdf9cec:
                    if (resource != 0) {
                        groups[3].primary = fn_80201BC8(resource);
                        fn_8017A244((Vec3 *)((u8 *)&lbl_8031CD84 + 0x2f8), &groupRotation.vector, lbl_8031CBA0.angle3);
                        fn_8012CDF0(groups[3].primary, 15, groupRotation.words, 0);
                    }
                    lbl_8031CD84.selectedGroup = 3;
                    break;
                }
            }
        }
        entries = (MenuEntry *)(data + 0x45c);
        selected = &lbl_8031CD84.groups[lbl_8031CD84.selectedGroup];
        entries[0].context = selected;
        entries[1].context = selected;
        entries[2].context = selected;
        entries[3].context = selected;
        lbl_8064C8E8 = fn_80144628(4, (int)entries, 0);
        fn_80144608(lbl_8064C8E8);
        fn_801446AC(lbl_8064C8E8, 1);
        break;
    }
    }
    lbl_8031CBA0.screen = screen;
    fn_8007D744(screen);
}
