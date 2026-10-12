typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Table Table;
typedef struct Path12 { char text[12]; } Path12;
typedef struct Path13 { char text[13]; } Path13;
typedef struct ResourceTable ResourceTable;
typedef struct DataHeader {
    u16 type;
    u8 reserved[6];
    u32 data;
} DataHeader;
typedef struct Entry110 Entry110;
typedef struct Entry0C Entry0C;
typedef struct LinkHeader {
    u16 type;
    u16 entryCount;
    Entry110* entries;
    u16 linkCount;
    u8 reserved[2];
    Entry0C* links;
} LinkHeader;
typedef struct ResourceHeader {
    ResourceTable* data;
    DataHeader first;
    LinkHeader second;
} ResourceHeader;

extern Path12 lbl_80238E14;
extern Path13 lbl_80238E20;
extern char lbl_8023E9B8[];
extern ResourceHeader lbl_80301CE8;
extern int lbl_8064B71C;
extern int lbl_8064C4E4;
extern Table* lbl_8064C520;
extern Table* lbl_8064C524;
extern Table* lbl_8064C528;
extern Table* lbl_8064C52C;
extern Table* lbl_8064C530;
extern int lbl_8064C594;
extern int lbl_8064C598;
extern int* lbl_8064C5A8;
extern int lbl_8064C7C0;
extern Table* lbl_8064C7D4[2];
extern int lbl_8064C7DC;
extern int lbl_8064C7F4;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);
extern int fn_80007D00(int);
extern int fn_80007E38(int);
extern int fn_80008724(int);
extern u32 fn_8002487C(void*, void*);
extern void fn_80042810(int);
extern void fn_80042CAC(int, int);
extern void fn_80043628(void);
extern void fn_80043708(int);
extern int fn_80047428(int);
extern u8 fn_80052218(int);
extern int fn_800F9D4C(char*, const char*, ...);
extern void* fn_80125788(void*);
extern void fn_8013816C(void);
extern void fn_801383B4(int, int);
extern void* fn_80138A6C(u32, int);
extern void* fn_80138B90(void*, int, int);
extern void fn_801391D4(short, int);
extern void fn_80139C1C(int);
extern void fn_80142944(void);
extern int fn_8015D9C8(void*, int);
extern void fn_8015DAB0(ResourceTable*);
extern void fn_8015E794(void);
extern long fn_801A9480(void);
extern void fn_801E85A8(Table*);
extern void* fn_801E86A0(Table*, u32);
extern void fn_801E86D8(Table*, Table*);
extern u32 fn_801E88E4(Table*);
extern u32 fn_801E9564(const u8*, LinkHeader*);
extern u32 fn_801E971C(const u8*, DataHeader*);

void fn_80043838(int requestedChapter, u8 immediate)
{
    Path12 path;
    char name[16];
    Path13 scriptPath;
    char* strings;
    int chapter;
    int archiveEntry;
    void* entry;
    int currentAudioGroup;
    int archiveId;
    u32 i;
    u32 j;
    void* second;
    int interrupts;
    int requestedAudioGroup;
    void* first;

    chapter = requestedChapter;
    strings = lbl_8023E9B8;
    path = lbl_80238E14;
    scriptPath = lbl_80238E20;
    requestedAudioGroup = fn_80052218(chapter);
    currentAudioGroup = fn_801A9480();
    lbl_8064C7DC = 0;
    interrupts = OSDisableInterrupts();
    if (currentAudioGroup != requestedAudioGroup) {
        lbl_8064C7F4 = 1;
    }
    if (immediate != 0) {
        lbl_8064C7F4 = 0;
    }
    OSRestoreInterrupts(interrupts);

    if (chapter == 16) {
        chapter = 0;
    }
    if (chapter == 15) {
        archiveId = fn_80007D00(chapter);
        archiveEntry = fn_80008724(fn_80007E38(chapter));
        lbl_8064B71C = fn_80008724(fn_80007E38(chapter));
        fn_801391D4((short)archiveId, archiveEntry);
        fn_8002487C((void*)chapter, 0);
        return;
    }
    if (chapter == 1) {
        lbl_8064C598 = 0;
        lbl_8064C594 = 0;
    } else if (chapter == 2) {
        lbl_8064C594 = 0;
    }

    path.text[5] = chapter / 10 + '0';
    path.text[6] = chapter % 10 + '0';
    fn_80043628();
    fn_8013816C();
    fn_80142944();
    lbl_8064C4E4 = 0;
    lbl_8064C524 = fn_80138B90(path.text, 0, 1);
    fn_801E85A8(lbl_8064C524);
    lbl_8064C528 = fn_801E86A0(lbl_8064C524, 0);
    lbl_8064C52C = fn_801E86A0(lbl_8064C524, 1);
    lbl_8064C530 = fn_801E86A0(lbl_8064C524, 2);
    lbl_80301CE8.data = fn_801E86A0(lbl_8064C524, 3);
    first = fn_801E86A0(lbl_8064C524, 4);
    second = fn_801E86A0(lbl_8064C524, 5);
    fn_801E85A8(lbl_8064C528);
    fn_801E85A8(lbl_8064C52C);
    fn_801E85A8(lbl_8064C530);
    fn_80043708(chapter);
    if (lbl_80301CE8.data != 0) {
        fn_8015DAB0(lbl_80301CE8.data);
    }
    if (first != 0) {
        fn_801E971C(first, &lbl_80301CE8.first);
    }
    if (second != 0) {
        fn_801E9564(second, &lbl_80301CE8.second);
    }

    /* Each alignment supplies a different chapter resource table. */
    switch (chapter) {
    case 5:
        {
            Table* extra = 0;
            switch (*lbl_8064C5A8) {
            case 1: extra = fn_80138B90(strings + 0x130, 0, 1); break;
            case 2: extra = fn_80138B90(strings + 0x140, 0, 1); break;
            case 3: extra = fn_80138B90(strings + 0x14C, 0, 1); break;
            }
            fn_801E85A8(extra);
            fn_801E86D8(lbl_8064C528, extra);
        }
        break;
    case 9:
        {
            Table* extra = 0;
            switch (*lbl_8064C5A8) {
            case 1: extra = fn_80138B90(strings + 0x158, 0, 1); break;
            case 2: extra = fn_80138B90(strings + 0x168, 0, 1); break;
            case 3: extra = fn_80138B90(strings + 0x174, 0, 1); break;
            }
            fn_801E85A8(extra);
            fn_801E86D8(lbl_8064C528, extra);
        }
        break;
    case 10:
        {
            Table* extra = 0;
            switch (*lbl_8064C5A8) {
            case 1: extra = fn_80138B90(strings + 0x180, 0, 1); break;
            case 2: extra = fn_80138B90(strings + 0x190, 0, 1); break;
            case 3: extra = fn_80138B90(strings + 0x19C, 0, 1); break;
            }
            fn_801E85A8(extra);
            fn_801E86D8(lbl_8064C528, extra);
        }
        break;
    }

    /* Construct each distinct chapter resource only once. */
    fn_80139C1C(fn_801E88E4(lbl_8064C528));
    for (i = 0; i < fn_801E88E4(lbl_8064C528); i++) {
        entry = fn_801E86A0(lbl_8064C528, i);
        if (entry != 0) {
            for (j = 0; j < i; j++) {
                if (fn_801E86A0(lbl_8064C528, j) == entry) {
                    break;
                }
            }
            if (j == i) {
                fn_80125788(entry);
            }
        }
    }
    /* Load common slots that are not already resident. */
    for (i = 0; i < fn_801E88E4(lbl_8064C520); i++) {
        entry = fn_801E86A0(lbl_8064C520, i);
        if (entry != 0) {
            for (j = 0; j < i; j++) {
                if (fn_801E86A0(lbl_8064C520, j) == entry) {
                    break;
                }
            }
            if (j == i && entry != 0 && fn_80047428(i) == 0) {
                fn_801383B4(i, 0);
            }
        }
    }

    if (chapter == 3) {
        lbl_8064C7C0 = 0;
        lbl_8064C7D4[0] = fn_80138A6C(0x83A70, 0);
        lbl_8064C7D4[1] = fn_80138A6C(0x83A70, 0);
        fn_80042CAC(0, 0);
        fn_80042CAC(1, 0);
    }
    fn_8015E794();
    /* Repeat for chapter slots before merging the common table. */
    for (i = 0; i < fn_801E88E4(lbl_8064C528); i++) {
        entry = fn_801E86A0(lbl_8064C528, i);
        if (entry != 0) {
            for (j = 0; j < i; j++) {
                if (fn_801E86A0(lbl_8064C528, j) == entry) {
                    break;
                }
            }
            if (j == i && entry != 0 && fn_80047428(i) == 0) {
                fn_801383B4(i, 0);
            }
        }
    }
    fn_801E86D8(lbl_8064C528, lbl_8064C520);
    archiveId = fn_80007D00(chapter);
    archiveEntry = fn_80008724(fn_80007E38(chapter));
    lbl_8064B71C = fn_80008724(fn_80007E38(chapter));
    fn_801391D4((short)archiveId, archiveEntry);

    if (chapter == 16) {
        chapter = 0;
    }
    scriptPath.text[6] = chapter / 10 + '0';
    scriptPath.text[7] = chapter % 10 + '0';
    fn_8015D9C8(scriptPath.text, 0xF69340);
    fn_800F9D4C(name, strings + 0x1A8, chapter);
    fn_8015D9C8(name, 0xFA63D0);
    fn_8015D9C8(strings + 0x1B4, 0xFB63D0);
    lbl_8064C7F4 = 0;
    fn_8002487C((void*)chapter, 0);
    fn_80042810(chapter);
}
