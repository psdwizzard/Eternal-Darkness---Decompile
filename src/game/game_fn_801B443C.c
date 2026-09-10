typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SynthTrackCommand {
    u32 value0;
    u8 pad04[4];
    u16 command;
    u16 arg;
} SynthTrackCommand;

typedef struct SynthTrackCursor {
    u8* base;
    SynthTrackCommand* current;
} SynthTrackCursor;

typedef struct SynthTimedInput {
    u32 nextTime;
} SynthTimedInput;

typedef struct SynthSequenceState {
    u32 lastTime;
    u32 baseTime;
    u8* noteData;
    u8 pad0C[12];
    SynthTimedInput pitchBend;
    u8 pad1C[8];
    SynthTimedInput modulation;
    u8 pad28[4];
} SynthSequenceState;

typedef struct SynthSequenceEvent {
    u8 pad00[8];
    u32 time;
    u8* data;
    SynthSequenceState* state;
    u8 type;
    u8 trackId;
    u8 pad16[2];
} SynthSequenceEvent;

typedef struct SynthSection {
    u8 pad00[0x12];
    u8 loopDisable;
    u8 pad13[0x38 - 0x13];
} SynthSection;

typedef struct SynthSequencer {
    u8 pad000[0x124];
    SynthTrackCursor track[0x48];
    SynthSequenceState pattern[0x40];
    u8 padE64[0x80];
    SynthSequenceEvent channelEvents[0x40];
    u8* keyGroupMap;
    u8 pad14E8[0x150C - 0x14E8];
    SynthSection section[1];
} SynthSequencer;

extern SynthSequencer* lbl_8064D380;
#define cseq lbl_8064D380
#define TRACK_CMD(t) ((t)->current)

SynthSequenceEvent* fn_801B443C(u8 channel)
{
    u32 trackId;
    SynthTrackCursor* track;
    SynthSequenceEvent* ev;
    SynthSequenceState* pattern;
    u32 patternTime;
    u32 pitchTime;
    u32 modTime;

    trackId = channel;
    track = &cseq->track[channel];
    pattern = &cseq->pattern[trackId];

    if (track->current != 0) {
        ev = &cseq->channelEvents[trackId];
        ev->trackId = channel;
        ev->state = pattern;

        for (;;) {
            if (pattern->noteData == 0) {
            process_track_command:
                if (TRACK_CMD(track)->command == 0xFFFF) {
                    track->current = 0;
                    return 0;
                }

                if (TRACK_CMD(track)->command == 0xFFFE) {
                    if (cseq->keyGroupMap == 0) {
                        if (cseq->section[0].loopDisable) {
                            track->current = 0;
                            return 0;
                        }
                    } else if (cseq->section[cseq->keyGroupMap[trackId]].loopDisable) {
                        track->current = 0;
                        return 0;
                    }

                    ev->type = 3;
                    ev->time = TRACK_CMD(track)->value0;
                    track->current = (SynthTrackCommand*)(track->base + TRACK_CMD(track)->arg * sizeof(SynthTrackCommand));
                    return ev;
                }

                ev->type = 4;
                ev->time = TRACK_CMD(track)->value0;
                ev->data = (u8*)track->current;
                track->current = TRACK_CMD(track) + 1;
                return ev;
            }

            pitchTime = pattern->pitchBend.nextTime;
            modTime = pattern->modulation.nextTime;

            for (;;) {
                patternTime = *(u16*)pattern->noteData + pattern->lastTime;
                if (patternTime < pitchTime) {
                    if (patternTime >= modTime) {
                        goto modulation_event;
                    }
                    if (pattern->noteData[2] == 0xFF && pattern->noteData[3] == 0xFF) {
                        pattern->noteData = 0;
                        goto process_track_command;
                    }

                    ev->data = pattern->noteData;
                    pattern->lastTime = patternTime;

                    if ((pattern->noteData[2] & 0x80) != 0) {
                        pattern->noteData += 4;
                    } else if ((pattern->noteData[2] | pattern->noteData[3]) == 0) {
                        pattern->noteData += 4;
                        continue;
                    } else {
                        pattern->noteData += 6;
                    }
                    ev->type = 0;
                    ev->time = patternTime + pattern->baseTime;
                } else if (pitchTime < modTime) {
                    ev->time = pitchTime + pattern->baseTime;
                    ev->type = 2;
                } else {
                modulation_event:
                    ev->time = modTime + pattern->baseTime;
                    ev->type = 1;
                }
                return ev;
            }
        }
    }

    return 0;
}
