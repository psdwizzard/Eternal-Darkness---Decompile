typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
} Vec;

typedef struct ShortCoord3 {
    short x, y, z;
} ShortCoord3;

typedef struct PositionKey {
    u32 flags;
    ShortCoord3 value;
} PositionKey;

typedef struct VertexData {
    char data[0xE];
    signed char active;
    char pad_F;
} VertexData;

typedef struct RotationKey {
    u32 flags;
    VertexData value;
} RotationKey;

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

typedef struct Definition {
    u8 pad0[8];
    u16 limit;
} Definition;

typedef struct Track {
    u16 posKeys;
    u8 pad2[6];
    u16 rotKeys;
    u8 padA[6];
} Track;

typedef struct Entry {
    u32 key;
    f32 value;
} Entry;

typedef struct EntryList {
    u32 count;
    Entry* entries;
} EntryList;

typedef struct SearchState {
    u32 key;
    s32 direction;
    s32 distance;
    s32 span;
    Entry* current;
    Entry* previous;
} SearchState;

typedef struct Animation {
    Track* tracks;
    u8 pad4[0xC];
    EntryList channels[32];
} Animation;

typedef struct ChannelState {
    u8 pad0[0x24];
    u32 flags;
} ChannelState;

typedef struct TrackState {
    u8 pad0[0xC];
    s32 posTime;
    s32 posLength;
    PositionKey* posFrom;
    PositionKey* posTo;
    u8 pad1C[0xC];
    s32 rotTime;
    s32 rotLength;
    RotationKey* rotFrom;
    RotationKey* rotTo;
    u8 pad38[0x10];
} TrackState;

typedef struct Owner {
    u8 pad0[0x3C];
    Definition* definition;
    u8 pad40[0x154 - 0x40];
    Vec* positions;
    Vec4* rotations;
    SearchState* searchStates;
    u8* trackStates;
    u8 pad164[0x29C - 0x164];
    ChannelState* channelStates;
    u8 pad2A0[0x2A8 - 0x2A0];
    u8* trackFlags;
} Owner;

typedef struct Runtime {
    u8 pad0[0xF4];
    u32 flags;
} Runtime;

extern void* fn_80128E6C(void* owner);
extern s32 fn_80134FF8(void* owner, Animation* anim);
extern u16 fn_8012927C(Owner* owner);
extern s32 fn_80126A00(EntryList* list, SearchState* state, s32 amount, f32* output);
extern void fn_80124664(Owner* owner, s32 index, u32 arg, f32 value);
extern s32 fn_80126E80(Track* track, TrackState* state, s32 time);
extern void fn_80127CE4(PositionKey* from, PositionKey* to, Vec* out, f32 t);
extern void fn_80127B90(RotationKey* from, RotationKey* to, Vec4* out, f32 t);
extern Vec fn_801231D8(Owner* owner, s32 time);
extern Runtime* fn_80128E30(Owner* owner);

extern f32 lbl_80650188;

s32 fn_80126B3C(Owner* owner, s32 time)
{
    u16 rootTrack;
    f32 zero;
    f32 value;
    s32 channelResult;
    Track* track;
    s32 i;
    s32 result;
    Track* tracks;
    Vec pos;
    Vec root;
    s32 count;
    TrackState* state;
    Definition* definition;
    Animation* anim;
    s32 updated;

    channelResult = 0;
    result = 0;
    updated = 0;
    definition = owner->definition;
    anim = fn_80128E6C(owner);
    fn_80134FF8(owner, anim);
    tracks = anim->tracks;
    count = definition->limit;
    rootTrack = fn_8012927C(owner);
    if (rootTrack != 0xFFFF) {
        count++;
    }

    for (i = 0; i < 32; i++) {
        if (anim->channels[(u32)i].count != 0) {
            if (owner->searchStates == 0) {
                break;
            }
            channelResult |= fn_80126A00(&anim->channels[(u32)i], &owner->searchStates[(u32)i], time, &value);
            if (channelResult == 0 && !(owner->channelStates[(u32)i].flags & 8)) {
                fn_80124664(owner, i, 0, value);
            }
        }
    }

    for (i = count; i > 0; i--) {
    }

    for (i = 0; i < count; i++) {
        track = &tracks[i];
        if (track->posKeys != 0 || track->rotKeys != 0) {
            state = (TrackState*)(owner->trackStates + i * 0x4C + 4);
            result |= fn_80126E80(track, state, time);
            updated = 1;
            owner->trackFlags[i] = 0;
            if (track->posKeys != 0 && i != rootTrack) {
                if (result == 0) {
                    fn_80127CE4(state->posFrom, state->posTo, &owner->positions[i],
                                (f32)state->posTime / (f32)state->posLength);
                }
                owner->trackFlags[i] |= 2;
            }
            if (track->rotKeys != 0) {
                if (result == 0) {
                    fn_80127B90(state->rotFrom, state->rotTo, &owner->rotations[i],
                                (f32)state->rotTime / (f32)state->rotLength);
                }
                owner->trackFlags[i] |= 1;
            }
        }
    }

    if (rootTrack != 0xFFFF) {
        root = fn_801231D8(owner, time);
        pos = root;
        if (!(fn_80128E30(owner)->flags & 4)) {
            owner->positions[rootTrack].x = pos.x;
            owner->positions[rootTrack].y = pos.y;
            owner->positions[rootTrack].z = pos.z;
        } else {
            zero = lbl_80650188;
            owner->positions[rootTrack].x = zero;
            owner->positions[rootTrack].y = zero;
            owner->positions[rootTrack].z = zero;
        }
    }

    if (!updated && channelResult != 0) {
        result = 1;
    }
    return result;
}
