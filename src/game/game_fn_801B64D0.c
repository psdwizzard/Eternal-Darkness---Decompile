typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct SynthVoice {
    u8 pad000[0xEC];
    u32 child;
    u8 padF0[0x11C - 0xF0];
    u8 block;
    u8 pad11D[0x404 - 0x11D];
} SynthVoice;

extern SynthVoice* synthVoice;
extern u16 inpGetMidiCtrl(u8, u8, u8);
extern u32 do_voice_portamento(u8, u8, u8, u32, u32*);
extern u32 macStart(u16, u8, u8, u16, u8, u8, u8, u8, u8, u8, u16, u16, u32, u8, u8, u32);
extern u32 StartKeymap(u16, u8, u8, u16, u8, u8, u8, u8, u8, u8, u16, u16, u32, u8, u8, u32);
extern u32 StartLayer(u16, u8, u8, u16, u8, u8, u8, u8, u8, u8, u16, u16, u32, u8, u8, u32);
extern u32 vidGetInternalId(u32);

#define HWVOICE(i) (&synthVoice[i])

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

static inline void unblockAllAllocatedVoices(u32 vid)
{
    u32 vi;

    vi = vidGetInternalId(vid);
    while (vi != 0xFFFFFFFF) {
        HWVOICE(vi & 0xFF)->block = 0;
        vi = HWVOICE(vi & 0xFF)->child;
    }
}

u32 synthStartSound(u16 id, u8 prio, u8 maxVoices, u8 key, u8 vol, u8 pan, u8 midi, u8 midiSet, u8 section, u16 step,
                u16 trackid, u8 vGroup, s16 prioOffset, u8 studio, u32 itd)
{
    prio += prioOffset;
    prio = prio > 0xFF ? 0xFF : prio;

    switch (id & 0xC000) {
    case 0: {
        u32 handle;
        if (!check_portamento(key, midi, midiSet, 1, &handle)) {
            return -1;
        }
        if (handle != 0xFFFFFFFF) {
            return handle;
        }
        return macStart(id, prio, maxVoices, id, key, vol, pan, midi, midiSet, section, step, trackid, 1, vGroup, studio, itd);
    }
    case 0x4000: {
        u32 vid = StartKeymap(id, prio, maxVoices, id, key, vol, pan, midi, midiSet, section, step, trackid, 1, vGroup, studio, itd);
        if (vid != 0xFFFFFFFF) {
            unblockAllAllocatedVoices(vid);
        }
        return vid;
    }
    case 0x8000: {
        u32 vid = StartLayer(id, prio, maxVoices, id, key, vol, pan, midi, midiSet, section, step, trackid, 1, vGroup, studio, itd);
        if (vid != 0xFFFFFFFF) {
            unblockAllAllocatedVoices(vid);
        }
        return vid;
    }
    }
    return -1;
}
