typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct KeymapEntry {
    u16 id;
    s8 transpose;
    u8 panning;
    s16 prioOffset;
    u16 pad;
} KeymapEntry;

extern KeymapEntry* fn_801BD0EC(u16);
extern u16 fn_801CAFAC(u8, u8, u8);
extern u32 fn_801B5C14(u8, u8, u8, u32, u32*);
extern u32 fn_801C0BC8(u16, u8, u8, u16, u8, u8, u8, u8, u8, u8, u16, u16, u8, u8, u8, u32);
extern u32 fn_801B5E9C(u16, s16, u8, u16, u8, u8, u8, u8, u8, u8, u16, u16, u32, u8, u8, u32);

#define dataGetKeymap fn_801BD0EC
#define inpGetMidiCtrl fn_801CAFAC
#define do_voice_portamento fn_801B5C14
#define macStart fn_801C0BC8
#define StartLayer fn_801B5E9C

static inline u32 check_portamento(u8 key, u8 midi, u8 midiSet, u32 newVID, u32* vid)
{
    u32 rejected;

    if (inpGetMidiCtrl(0x41, midi, midiSet) > 0x1F80) {
        *vid = do_voice_portamento(key & 0x7F, midi, midiSet, newVID, &rejected);
        return !rejected;
    }
    *vid = 0xFFFFFFFF;
    return 1;
}

u32 fn_801B6270(u16 id, s16 prio, u8 maxVoices, u16 allocId, u8 key, u8 vol, u8 pan, u8 midi, u8 midiSet,
                u8 section, u16 step, u16 trackid, u32 vidFlag, u8 vGroup, u8 studio, u32 itd)
{
    u8 o;
    KeymapEntry* keymap;
    s32 p;
    s32 k;
    u32 handle;

    if ((keymap = (KeymapEntry*)dataGetKeymap(id)) != 0) {
        o = key & 0x7F;
        if (keymap[o].id != 0xFFFF) {
            if ((keymap[o].id & 0xC000) != 0x4000) {
                if ((keymap[o].panning & 0x80) == 0) {
                    p = keymap[key].panning - 0x40;
                    p += pan;
                    if (p < 0) {
                        pan = 0;
                    } else if (p > 0x7F) {
                        pan = 0x7F;
                    } else {
                        pan = p;
                    }
                } else {
                    pan = 0x80;
                }

                k = (key & 0x7F) + keymap[o].transpose;
                k = k > 0x7F ? 0x7F : k < 0 ? 0 : k;

                prio += keymap[o].prioOffset;
                prio = prio > 0xFF ? 0xFF : prio < 0 ? 0 : prio;

                if ((keymap[o].id & 0xC000) == 0) {
                    if (!check_portamento(k & 0xFF, midi, midiSet, vidFlag, &handle)) {
                        return -1;
                    }
                    if (handle != 0xFFFFFFFF) {
                        return handle;
                    }
                    return macStart(keymap[o].id, prio, maxVoices, allocId, k | (key & 0x80), vol, pan, midi, midiSet, section, step, trackid, vidFlag, vGroup, studio, itd);
                }
                return StartLayer(keymap[o].id, prio, maxVoices, allocId, k | (key & 0x80), vol, pan, midi, midiSet, section, step, trackid, vidFlag & 0xff, vGroup, studio, itd);
            }
        }
    }
    return -1;
}
