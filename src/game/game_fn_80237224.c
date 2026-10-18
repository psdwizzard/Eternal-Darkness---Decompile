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

extern s32 OSCheckHeap(s32);
extern void OSInitStopwatch(AudioTimer *, const char *);
extern void OSStartStopwatch(AudioTimer *);
extern long long OSCheckStopwatch(AudioTimer *);
extern void OSResetStopwatch(AudioTimer *);
extern s32 ogg_stream_packetout(AudioStream *, AudioPacket *);
extern s32 ogg_stream_pagein(AudioStream *, AudioPage *);
extern s32 ogg_sync_pageout(AudioSync *, AudioPage *);
extern s32 ogg_sync_wrote(AudioSync *, s32);
extern void *ogg_sync_buffer(AudioSync *, s32);
extern s32 ogg_sync_clear(AudioSync *);
extern s32 ogg_sync_init(AudioSync *);
extern s32 ogg_stream_init(AudioStream *, s32);
extern s32 ogg_page_serialno(AudioPage *);
extern s32 ogg_page_eos(AudioPage *);
extern void fn_8022F8F8(void);
extern void fn_8022F8FC(void);
extern s32 vorbis_synthesis_read(AudioDecoder *, s32);
extern s32 vorbis_synthesis_pcmout(AudioDecoder *, s16 ***);
extern s32 vorbis_synthesis_blockin(AudioDecoder *, AudioBlock *);
extern s32 vorbis_synthesis_init(AudioDecoder *, AudioInfo *);
extern s32 vorbis_block_init(AudioDecoder *, AudioBlock *);
extern s32 vorbis_synthesis_headerin(AudioInfo *, AudioComment *, AudioPacket *);
extern void vorbis_info_init(AudioInfo *);
extern void vorbis_comment_init(AudioComment *);
extern s32 vorbis_synthesis(AudioBlock *, AudioPacket *);
extern s32 fn_80237704(s16 *, s32, s32);
extern s32 fn_80237A04(void *, s32);
extern void fn_80237DB4(const char *);
extern char lbl_8023B8E0[];
extern s16 lbl_80647C5C[654];
extern volatile AudioVoice lbl_8064A548[2];
extern s32 __OSCurrHeap;
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

    OSCheckHeap(__OSCurrHeap);
    OSInitStopwatch(&timer, lbl_8023B8E0);
    OSResetStopwatch(&timer);
    OSStartStopwatch(&timer);
    ogg_sync_init(&sync);
    fn_80237DB4((const char *)source);
    done = 0;
    source = fn_80237A04(ogg_sync_buffer(&sync, 0x1000), 0x1000);
    ogg_sync_wrote(&sync, source);
    switch (ogg_sync_pageout(&sync, &page)) {
    case 1: break;
    default: goto cleanup;
    }
    ogg_stream_init(&stream, ogg_page_serialno(&page));
    vorbis_info_init(&info);
    vorbis_comment_init(&comment);
    if (ogg_stream_pagein(&stream, &page) < 0) goto cleanup;
    if (ogg_stream_packetout(&stream, &packet) != 1) goto cleanup;
    fn_8022F8FC();
    if (vorbis_synthesis_headerin(&info, &comment, &packet) < 0) goto cleanup;
    fn_8022F8FC();
    /* Finish the two remaining codec header packets before decoding. */
    headers = 0;
    while (headers < 2) {
        while (headers < 2) {
            result = ogg_sync_pageout(&sync, &page);
            if (result == 0) break;
            if (result == 1) {
                ogg_stream_pagein(&stream, &page);
                while (headers < 2) {
                    result = ogg_stream_packetout(&stream, &packet);
                    if (result == 0) break;
                    if (result < 0) break;
                    vorbis_synthesis_headerin(&info, &comment, &packet);
                    headers++;
                }
            }
        }
        bytes = fn_80237A04(ogg_sync_buffer(&sync, 0x1000), 0x1000);
        if (bytes == 0 && headers < 2) break;
        ogg_sync_wrote(&sync, bytes);
    }
    comments = comment.comments;
    while (*comments) comments++;
    channels = &info.channels;
    lbl_8064C4D8 = 512 / *channels;
    fn_8022F8FC();
    vorbis_synthesis_init(&decoder, &info);
    fn_8022F8FC();
    vorbis_block_init(&decoder, &block);
    fn_8022F8FC();
    while (!done) {
        while (!done) {
            result = ogg_sync_pageout(&sync, &page);
            if (result == 0) break;
            if (result < 0) {
                done = 1;
                break;
            }
            ogg_stream_pagein(&stream, &page);
            do {
                result = ogg_stream_packetout(&stream, &packet);
                if (result == 0 || lbl_8064DC4C) break;
                if (result >= 0) {
                    if (vorbis_synthesis(&block, &packet) == 0) {
                        vorbis_synthesis_blockin(&decoder, &block);
                    }
                    while ((result = vorbis_synthesis_pcmout(&decoder, &pcm)) > 0) {
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
                        vorbis_synthesis_read(&decoder, samples);
                    }
                }
            } while (!lbl_8064DC4C);
            if (ogg_page_eos(&page) || lbl_8064DC4C) done = 1;
        }
        if (!done) {
            bytes = fn_80237A04(ogg_sync_buffer(&sync, 0x1000), 0x1000);
            ogg_sync_wrote(&sync, bytes);
            if (bytes == 0) done = 1;
        }
    }
    fn_8022F8F8();
cleanup:
    OSCheckStopwatch(&timer);
    ogg_sync_clear(&sync);
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
