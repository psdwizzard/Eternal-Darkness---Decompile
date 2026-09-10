typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

typedef struct SAMPLE_INFO {
    u32 info;
    u32 addr;
    void* extraData;
    u32 offset;
    u32 length;
    u32 loop;
    u32 loopLength;
    u8 compType;
} SAMPLE_INFO;

typedef struct ADPCM_INFO {
    u8 pad00[2];
    u8 initialPS;
    u8 loopPS;
    u8 pad04[0x24];
} ADPCM_INFO;

typedef struct SynthJob {
    u32 unk00;
    u32 flags;
    u8 state;
    u8 format;
    u8 pad0A[2];
    u32 (*callback)(u8*, u32, u8*, u32, u32);
    u8* buffer;
    u32 size;
    u32 bytes;
    u32 last;
    ADPCM_INFO adpcm;
    u32 voice;
    u32 callbackUser;
    u32 frq;
    u8 pad54;
    u8 volume;
    u8 pan;
    u8 surroundPan;
    u8 auxAVolume;
    u8 auxBVolume;
    u8 pad5A[2];
    u8 studio;
    u8 streamHandle;
    u8 pad5E[6];
} SynthJob;

typedef struct SynthInfo {
    u32 sampleRate;
    u8 pad004[0x20C];
    u8 voiceCount;
} SynthInfo;

typedef struct SYNTH_VOICE {
    u8 pad_000[0xF4];
    u32 id;
    u8 pad_0F8[0x30C];
} SYNTH_VOICE;

extern u8 lbl_8064D3E8;
extern u8 lbl_8064D3E9;
extern SynthJob lbl_8061AE48[];
extern SynthInfo lbl_80619C20;
extern SYNTH_VOICE* lbl_8064D3D0;
extern u32 fn_801CD200(u8);
extern void DCInvalidateRange(void*, u32);
extern void fn_801CC718(u32, u16, SAMPLE_INFO*, u32, u32, u32, u32, u32);
extern void fn_801CCB98(u32, s32);
extern void fn_801CCCC4(u32, u32, f32, u32, u32, f32, f32);
extern void fn_801CCB34(u32, u8);
extern void fn_801CD138(u8*, u32, u32, u8, u32, u32);
extern u32 fn_801CD094(u32);
extern void fn_801CCB20(u32, u32);

#define streamCallCnt lbl_8064D3E8
#define streamCallDelay lbl_8064D3E9
#define streamInfo lbl_8061AE48
#define SYNTH_CONFIGURATION (&lbl_80619C20)
#define synthVoice lbl_8064D3D0
#define hwFlushStream fn_801CD200
#define hwInitSamplePlayback fn_801CC718
#define hwSetPitch fn_801CCB98
#define hwSetVolume fn_801CCCC4
#define hwStart fn_801CCB34
#define hwGetPos fn_801CD138
#define hwChangeStudio fn_801CD094
#define hwSetStreamLoopPS fn_801CCB20

void fn_801B941C(void)
{
    u32 i;
    u32 cpos;
    u32 len;
    SAMPLE_INFO newsmp;
    SynthJob* si;
    f32 f;

    if (streamCallCnt != 0) {
        --streamCallCnt;
        return;
    }
    streamCallCnt = streamCallDelay;
    si = streamInfo;
    for (i = 0; i < SYNTH_CONFIGURATION->voiceCount; ++i, ++si) {
        switch (si->state) {
        case 1:
            newsmp.info = si->frq | 0x40000000;
            newsmp.addr = hwFlushStream(si->streamHandle);
            newsmp.offset = 0;
            newsmp.length = si->size;
            newsmp.loop = 0;
            newsmp.loopLength = si->size;
            si->adpcm.loopPS = si->adpcm.initialPS = *si->buffer;
            DCInvalidateRange(si->buffer, 1);
            switch (si->format) {
            case 0:
                newsmp.compType = 2;
                break;
            case 1:
                newsmp.extraData = &si->adpcm;
                newsmp.compType = 4;
                break;
            }
            hwInitSamplePlayback(si->voice, 0xFFFF, &newsmp, 1, -1, synthVoice[si->voice].id, 1, 1);
            f = (f32)si->frq / (f32)SYNTH_CONFIGURATION->sampleRate;
            hwSetPitch(si->voice, f * 4096.0f);
            hwSetVolume(si->voice, 0, si->volume * (1 / 127.0f), si->pan << 16, si->surroundPan << 16,
                        si->auxAVolume * (1 / 127.0f), si->auxBVolume * (1 / 127.0f));
            hwStart(si->voice, si->studio);
            si->state = 2;
            if (!(si->flags & 0x20000)) {
                hwGetPos(si->buffer, 0, si->bytes, si->streamHandle, 0, 0);
            }
            break;
        case 2:
            cpos = hwChangeStudio(si->voice);

            if (si->format == 1) {
                cpos = (cpos / 14) * 14;
            }

            if (si->last != cpos) {
                if (si->last < cpos) {
                    switch (si->format) {
                    case 0:
                        if ((len = si->callback(si->buffer + si->last * 2, cpos - si->last, 0, 0, si->callbackUser)) != 0 &&
                            si->state == 2) {
                            cpos = (si->last + len) % si->size;
                            if (!(si->flags & 0x20000)) {
                                if (cpos != 0) {
                                    hwGetPos(si->buffer, si->last * 2, (cpos - si->last) * 2, si->streamHandle, 0, 0);
                                } else {
                                    hwGetPos(si->buffer, si->last * 2, (si->size - si->last) * 2, si->streamHandle, 0, 0);
                                }
                            }
                            si->last = cpos;
                        }
                        break;
                    case 1: {
                        u32 off = (si->last / 14) * 8;
                        if ((len = si->callback(si->buffer + off, cpos - si->last, 0, 0, si->callbackUser)) != 0 &&
                            si->state == 2) {
                            cpos = (si->last + len) % si->size;
                            if (!(si->flags & 0x20000)) {
                                if (cpos != 0) {
                                    hwGetPos(si->buffer, off, ((cpos + 13) / 14) * 8 - off, si->streamHandle, 0, 0);
                                } else {
                                    hwGetPos(si->buffer, off, si->bytes - off, si->streamHandle, 0, 0);
                                }
                            }
                            si->last = cpos;
                        }
                        break;
                    }
                    }
                } else if (cpos == 0) {
                    switch (si->format) {
                    case 0:
                        if ((len = si->callback(si->buffer + si->last * 2, si->size - si->last, 0, 0, si->callbackUser)) != 0 &&
                            si->state == 2) {
                            cpos = (si->last + len) % si->size;
                            if (!(si->flags & 0x20000)) {
                                if (cpos == 0) {
                                    hwGetPos(si->buffer, si->last * 2, si->bytes - si->last * 2, si->streamHandle, 0, 0);
                                } else {
                                    hwGetPos(si->buffer, si->last * 2, (cpos - si->last) * 2, si->streamHandle, 0, 0);
                                }
                            }
                            si->last = cpos;
                        }
                        break;
                    case 1: {
                        u32 off = (si->last / 14) * 8;
                        if ((len = si->callback(si->buffer + off, si->size - si->last, 0, 0, si->callbackUser)) != 0 &&
                            si->state == 2) {
                            cpos = (si->last + len) % si->size;
                            if (!(si->flags & 0x20000)) {
                                if (cpos == 0) {
                                    hwGetPos(si->buffer, off, si->bytes - off, si->streamHandle, 0, 0);
                                } else {
                                    hwGetPos(si->buffer, off, ((cpos + 13) / 14) * 8 - off, si->streamHandle, 0, 0);
                                }
                            }
                            si->last = cpos;
                        }
                        break;
                    }
                    }
                } else {
                    switch (si->format) {
                    case 0:
                        if ((len = si->callback(si->buffer + si->last * 2, si->size - si->last, si->buffer, cpos, si->callbackUser)) != 0 &&
                            si->state == 2) {
                            cpos = (si->last + len) % si->size;
                            if (!(si->flags & 0x20000)) {
                                if (len > si->size - si->last) {
                                    hwGetPos(si->buffer, si->last * 2, si->bytes - si->last * 2, si->streamHandle, 0, 0);
                                    hwGetPos(si->buffer, 0, cpos * 2, si->streamHandle, 0, 0);
                                } else if (cpos == 0) {
                                    hwGetPos(si->buffer, si->last * 2, si->bytes - si->last * 2, si->streamHandle, 0, 0);
                                } else {
                                    hwGetPos(si->buffer, si->last * 2, (cpos - si->last) * 2, si->streamHandle, 0, 0);
                                }
                            }
                            si->last = cpos;
                        }
                        break;
                    case 1: {
                        u32 off = (si->last / 14) * 8;
                        if ((len = si->callback(si->buffer + off, si->size - si->last, si->buffer, cpos, si->callbackUser)) != 0 &&
                            si->state == 2) {
                            cpos = (si->last + len) % si->size;
                            if (!(si->flags & 0x20000)) {
                                if (len > si->size - si->last) {
                                    hwGetPos(si->buffer, off, si->bytes - off, si->streamHandle, 0, 0);
                                    hwGetPos(si->buffer, 0, (cpos / 14) * 8, si->streamHandle, 0, 0);
                                } else if (cpos == 0) {
                                    hwGetPos(si->buffer, off, si->bytes - off, si->streamHandle, 0, 0);
                                } else {
                                    hwGetPos(si->buffer, off, ((cpos + 13) / 14) * 8 - off, si->streamHandle, 0, 0);
                                }
                            }
                            si->last = cpos;
                        }
                        break;
                    }
                    }
                }

                if (si->state == 2 && !(si->flags & 0x20000) && si->format == 1) {
                    hwSetStreamLoopPS(si->voice, *(u32*)((u32)si->buffer + 0x40000000) >> 24);
                }
            }
            break;
        }
    }
}
