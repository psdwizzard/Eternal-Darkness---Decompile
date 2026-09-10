typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct LAYER {
    u16 id;
    u8 keyLow;
    u8 keyHigh;
    s8 transpose;
    u8 volume;
    s16 prioOffset;
    u8 panning;
    u8 pad[3];
} LAYER;

typedef struct McmdVoiceState {
    u8 pad000[0xEC];
    u32 child;
    u32 parent;
    u8 padF4[0x11C - 0xF4];
    u8 block;
    u8 pad11D[0x404 - 0x11D];
} McmdVoiceState;

extern McmdVoiceState* lbl_8064D3D0;
extern LAYER* fn_801BD15C(u16, u16*);
extern u16 fn_801CAFAC(u8, u8, u8);
extern u32 fn_801B5C14(u8, u8, u8, u32, u32*);
extern u32 fn_801C13C0(McmdVoiceState*);
extern u32 fn_801C0BC8(u16, u8, u8, u16, u8, u8, u8, u8, u8, u8, u16, u16, u32, u8, u8, u32);
extern u32 fn_801B6270(u16, s16, u8, u16, u8, u8, u8, u8, u8, u8, u16, u16, u32, u8, u8, u32);

#define synthVoice lbl_8064D3D0
#define dataGetLayer fn_801BD15C
#define inpGetMidiCtrl fn_801CAFAC
#define do_voice_portamento fn_801B5C14
#define vidMakeRoot fn_801C13C0
#define macStart fn_801C0BC8
#define StartKeymap fn_801B6270

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

u32 fn_801B5E9C(u16 layerID, s16 prio, u8 maxVoices, u16 allocId, u8 key, u8 vol, u8 panning, u8 midi,
                u8 midiSet, u8 section, u16 step, u16 trackid, u32 vidFlag, u8 vGroup, u8 studio, u32 itd)
{
    u16 count;
    u32 vid;
    u32 new_id;
    u32 id;
    LAYER* l;
    s32 pan;
    s32 note;
    u8 scaledVol;
    u8 mKey;

    vid = 0xFFFFFFFF;
    if ((l = dataGetLayer(layerID, &count)) == 0) {
        goto end;
    }

    mKey = key & 0x7f;
    for (; count != 0; --count, l++) {
        if (l->id == 0xffff || l->keyLow > mKey || l->keyHigh < mKey) {
            continue;
        }

        note = mKey + l->transpose;
        note = note > 127 ? 127 : note < 0 ? 0 : note;

        if ((l->id & 0xC000) == 0) {
            if (check_portamento(note, midi, midiSet, 0, &new_id)) {
                if (new_id != 0xFFFFFFFF) {
                    goto apply_new_id;
                } else {
                    goto start_new_id;
                }
            }
            continue;
        }

    start_new_id:
        if ((l->panning & 0x80) == 0) {
            pan = l->panning - 0x40;
            pan += panning;
            pan = pan < 0 ? 0 : pan > 0x7f ? 0x7f : pan;
        } else {
            pan = 0x80;
        }

        scaledVol = (vol * l->volume) / 0x7f;
        prio += l->prioOffset;
        prio = prio > 0xff ? 0xff : prio < 0 ? 0 : prio;

        switch (l->id & 0xC000) {
        case 0:
            new_id = macStart(l->id, prio, maxVoices, allocId, note | (key & 0x80), scaledVol, pan, midi, midiSet, section, step, trackid, 0, vGroup, studio, itd);
            break;
        case 0x4000:
            new_id = StartKeymap(l->id, prio, maxVoices, allocId, note | (key & 0x80), scaledVol, pan, midi, midiSet, section, step, trackid, 0, vGroup, studio, itd);
            break;
        case 0x8000:
            new_id = fn_801B5E9C(l->id, prio, maxVoices, allocId, note | (key & 0x80), scaledVol, pan, midi, midiSet, section, step, trackid, 0, vGroup, studio, itd);
            break;
        }

        if (new_id != 0xFFFFFFFF) {
        apply_new_id:
            if (vid == 0xFFFFFFFF) {
                if (vidFlag != 0) {
                    vid = vidMakeRoot(&synthVoice[new_id & 0xff]);
                } else {
                    vid = new_id;
                }
            } else {
                synthVoice[id & 0xff].child = new_id;
                synthVoice[new_id & 0xff].parent = id;
            }
            id = new_id;
            while (synthVoice[id & 0xff].child != 0xFFFFFFFF) {
                synthVoice[id & 0xff].block = 1;
                id = synthVoice[id & 0xff].child;
            }
            synthVoice[id & 0xff].block = 1;
        }
    }

end:
    return vid;
}
