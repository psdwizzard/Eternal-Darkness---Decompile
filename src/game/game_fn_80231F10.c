/* Parse a Vorbis identification, comment, or setup header packet. */
#include "src/game/types.h"

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

typedef struct AudioComment {
    char **comments;
    s32 *lengths;
    s32 count;
    char *vendor;
} AudioComment;

typedef struct AudioPacket {
    u8 *data;
    s32 size;
    s32 beginning;
    s32 end;
    s32 position;
    s32 number;
} AudioPacket;

typedef struct BitReader {
    s32 endByte;
    s32 endBit;
    u8 *buffer;
    u8 *ptr;
    s32 storage;
} BitReader;

extern void fn_8022EA4C(void *, u8 *, s32);
extern s32 fn_8022E868(void *, s32);
extern void *memset(void *, int, unsigned long);
extern int fn_800F98EC(const void *, const void *, unsigned long);
extern s32 fn_8023258C(AudioInfo *, void *);
extern s32 fn_80232430(AudioComment *, void *);
extern s32 fn_80232078(AudioInfo *, void *);
extern const char lbl_806517E8[3];

s32 fn_80231F10(AudioInfo *info, AudioComment *comment, AudioPacket *packet)
{
    BitReader reader;
    u8 signature[2];

    if (packet != 0) {
        u8 *cursor;
        s32 type;
        s32 i;
        fn_8022EA4C(&reader, packet->data, packet->size);
        type = fn_8022E868(&reader, 8);
        memset(signature, 0, sizeof(signature));
        cursor = signature;
        i = 1;
        do {
            *cursor++ = fn_8022E868(&reader, 8);
        } while (i-- != 0);
        if (fn_800F98EC(signature, lbl_806517E8, 2) != 0) {
            return -0x84;
        }
        switch (type) {
        case 1:
            if (!packet->beginning) return -0x85;
            if (info->rate) return -0x85;
            return fn_8023258C(info, &reader);
        case 3:
            if (!info->rate) return -0x85;
            return fn_80232430(comment, &reader);
        case 5:
            if (!info->rate || !comment->vendor) return -0x85;
            return fn_80232078(info, &reader);
        default:
            return -0x85;
        }
    }
    return -0x85;
}
