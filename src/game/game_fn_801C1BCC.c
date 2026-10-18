typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Voice {
    u8 pad_000[0x34];
    u32 field_034;
    u8 pad_038[0xBC];
    u32 index;
    u8 pad_0F8[0x14];
    u8 active;
    u8 pad_10D[0x10];
    u8 special;
} Voice;

typedef struct FreeLink {
    u8 previous;
    u8 next;
    u16 active;
} FreeLink;

extern FreeLink voiceList[64];
extern u8 voiceMusicRunning;
extern u8 voiceFxRunning;
extern u8 voiceListInsert;
extern u8 voiceListRoot;
extern void macMakeInactive(Voice*, int);
extern void voiceRemovePriority(Voice*);

void voiceFree(Voice* voice)
{
    register u32 index;
    register FreeLink* link;

    macMakeInactive(voice, 2);
    voiceRemovePriority(voice);
    voice->field_034 = 0;
    voice->active = 0;
    index = (u8)voice->index;
    link = &voiceList[index];
    if (link->active == 0) {
        link->active = 1;
        if (voiceListRoot != 0xFF) {
            link->next = 0xFF;
            link->previous = voiceListInsert;
            voiceList[voiceListInsert].next = index;
        } else {
            link->next = 0xFF;
            link->previous = 0xFF;
            voiceListRoot = index;
        }
        voiceListInsert = index;
        if (voice->special != 0) {
            voiceFxRunning--;
        } else {
            voiceMusicRunning--;
        }
    }
    voice->index = -1;
}
