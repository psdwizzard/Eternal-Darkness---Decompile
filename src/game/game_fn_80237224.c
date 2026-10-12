#include "src/game/types.h"

/* The stream and decoder objects are private to the audio library. */
typedef struct AudioSync { s32 state[7]; } AudioSync;
typedef struct AudioPage { u8 *header; s32 headerSize; u8 *body; s32 bodySize; } AudioPage;
typedef struct AudioPacket { u8 *data; s32 size; s32 beginning; s32 end; s32 position; s32 number; } AudioPacket;
typedef struct AudioStream { s32 state[16]; } AudioStream;
typedef struct AudioInfo {
    s32 version;
    s32 channels;
    s32 rate;
    s32 bitrateUpper;
    s32 bitrateNominal;
    s32 bitrateLower;
    s32 bitrateWindow;
    void *codec;
} AudioInfo;
typedef struct AudioComment { char **comments; s32 *lengths; s32 count; char *vendor; } AudioComment;
typedef struct AudioDecoder { s32 state[19]; } AudioDecoder;
typedef struct AudioBlock { s32 state[25]; } AudioBlock;
typedef struct AudioTimer {
    const char *name;
    s32 index;
    long long elapsed;
    s32 state[6];
    long long started;
    s32 active;
} AudioTimer;
typedef struct AudioVoice { s32 state[2]; s32 flags; s32 rest[4]; } AudioVoice;

extern s32 fn_8020AFE4(s32);
extern void fn_8020EF54(AudioTimer *, const char *);
extern void fn_8020EF80(AudioTimer *);
extern long long fn_8020F088(AudioTimer *);
extern void fn_8020F0F8(AudioTimer *);
extern s32 fn_8022EAA4(AudioStream *, AudioPacket *);
extern s32 fn_8022EBD4(AudioStream *, AudioPage *);
extern s32 fn_8022EF30(AudioSync *, AudioPage *);
extern s32 fn_8022F1A8(AudioSync *, s32);
extern void *fn_8022F1D0(AudioSync *, s32);
extern s32 fn_8022F28C(AudioSync *);
extern s32 fn_8022F2C4(AudioSync *);
extern s32 fn_8022F63C(AudioStream *, s32);
extern s32 fn_8022F6CC(AudioPage *);
extern s32 fn_8022F6F0(AudioPage *);
extern void fn_8022F8F8(void);
extern void fn_8022F8FC(void);
extern s32 fn_8022F93C(AudioDecoder *, s32);
extern s32 fn_8022F974(AudioDecoder *, s16 ***);
extern s32 fn_8022FA30(AudioDecoder *, AudioBlock *);
extern s32 fn_8022FE1C(AudioDecoder *, AudioInfo *);
extern s32 fn_802300D0(AudioDecoder *, AudioBlock *);
extern s32 fn_80231F10(AudioInfo *, AudioComment *, AudioPacket *);
extern void fn_8023283C(AudioInfo *);
extern void fn_8023287C(AudioComment *);
extern s32 fn_80236164(AudioBlock *, AudioPacket *);
extern s32 fn_80237704(s16 *, s32, s32);
extern s32 fn_80237A04(void *, s32);
extern void fn_80237DB4(const char *);
extern char lbl_8023B8E0[];
extern s16 lbl_80647C5C[654];
extern volatile AudioVoice lbl_8064A548[2];
extern s32 lbl_8064C3C8;
extern s32 lbl_8064C4D8;
extern s32 lbl_8064DC34;
extern s32 lbl_8064DC38;
extern s32 lbl_8064DC4C;
extern s32 lbl_8064DC54;
extern s32 lbl_8064DC74;

void fn_80237224(s32 source)
{
    AudioDecoder decoder;
    AudioBlock block;
    AudioStream stream;
    AudioTimer timer;
    AudioSync sync;
    AudioPacket packet;
    AudioInfo info;
    AudioPage page;
    AudioComment comment;
    s16 **pcm;
    s32 done;
    s32 bytes;
    s32 headers;
    s32 result;
    s32 samples;
    s32 channel;
    s32 i;
    char **comments;
    volatile AudioVoice *voice;
    s16 *dest;
    s16 *input;
    s32 *channels;
    s32 channelCount;
    s32 stride;
    s16 sample;

    fn_8020AFE4(lbl_8064C3C8);
    fn_8020EF54(&timer, lbl_8023B8E0);
    fn_8020F0F8(&timer);
    fn_8020EF80(&timer);
    fn_8022F2C4(&sync);
    fn_80237DB4((const char *)source);
    done = 0;
    source = fn_80237A04(fn_8022F1D0(&sync, 0x1000), 0x1000);
    fn_8022F1A8(&sync, source);
    switch (fn_8022EF30(&sync, &page)) {
    case 1: break;
    default: goto cleanup;
    }
    fn_8022F63C(&stream, fn_8022F6CC(&page));
    fn_8023283C(&info);
    fn_8023287C(&comment);
    if (fn_8022EBD4(&stream, &page) < 0) goto cleanup;
    if (fn_8022EAA4(&stream, &packet) != 1) goto cleanup;
    fn_8022F8FC();
    if (fn_80231F10(&info, &comment, &packet) < 0) goto cleanup;
    fn_8022F8FC();
    /* Finish the two remaining codec header packets before decoding. */
    headers = 0;
    while (headers < 2) {
        while (headers < 2) {
            result = fn_8022EF30(&sync, &page);
            if (result == 0) break;
            if (result == 1) {
                fn_8022EBD4(&stream, &page);
                while (headers < 2) {
                    result = fn_8022EAA4(&stream, &packet);
                    if (result == 0) break;
                    if (result < 0) break;
                    fn_80231F10(&info, &comment, &packet);
                    headers++;
                }
            }
        }
        bytes = fn_80237A04(fn_8022F1D0(&sync, 0x1000), 0x1000);
        if (bytes == 0 && headers < 2) break;
        fn_8022F1A8(&sync, bytes);
    }
    comments = comment.comments;
    while (*comments) comments++;
    channels = &info.channels;
    lbl_8064C4D8 = 512 / *channels;
    fn_8022F8FC();
    fn_8022FE1C(&decoder, &info);
    fn_8022F8FC();
    fn_802300D0(&decoder, &block);
    fn_8022F8FC();
    while (!done) {
        while (!done) {
            result = fn_8022EF30(&sync, &page);
            if (result == 0) break;
            if (result < 0) {
                done = 1;
                break;
            }
            fn_8022EBD4(&stream, &page);
            do {
                result = fn_8022EAA4(&stream, &packet);
                if (result == 0 || lbl_8064DC4C) break;
                if (result >= 0) {
                    if (fn_80236164(&block, &packet) == 0) {
                        fn_8022FA30(&decoder, &block);
                    }
                    while ((result = fn_8022F974(&decoder, &pcm)) > 0) {
                        samples = lbl_8064C4D8;
                        if (result < samples) samples = result;
                        /* Convert the separate channels into interleaved PCM. */
                        channelCount = *channels;
                        for (channel = 0; channel < channelCount; channel++) {
                            dest = lbl_80647C5C + channel;
                            input = pcm[channel];
                            stride = *channels;
                            for (i = 0; i < samples; i++) {
                                sample = *input++;
                                *dest = sample;
                                dest += stride;
                            }
                        }
                        if (fn_80237704(lbl_80647C5C, samples, *channels)) {
                            lbl_8064DC74 = 0;
                            lbl_8064DC54 = 0;
                            break;
                        }
                        fn_8022F8FC();
                        fn_8022F93C(&decoder, samples);
                    }
                }
            } while (!lbl_8064DC4C);
            if (fn_8022F6F0(&page) || lbl_8064DC4C) done = 1;
        }
        if (!done) {
            bytes = fn_80237A04(fn_8022F1D0(&sync, 0x1000), 0x1000);
            fn_8022F1A8(&sync, bytes);
            if (bytes == 0) done = 1;
        }
    }
    fn_8022F8F8();
cleanup:
    fn_8020F088(&timer);
    fn_8022F28C(&sync);
    lbl_8064DC34 = 0;
    lbl_8064DC38 = 0;
    voice = lbl_8064A548;
    if (voice[0].flags) {
        voice[0].flags = (voice[0].flags & ~1) | 2;
    }
    voice = &lbl_8064A548[1];
    if (voice->flags) {
        voice->flags = (voice->flags & ~1) | 2;
    }
}
