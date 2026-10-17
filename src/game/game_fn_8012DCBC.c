typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Owner Owner;

typedef struct ChannelState {
    u16 flags;
    u8 pad_002[6];
} ChannelState;

typedef struct Entry {
    u8 pad_000[8];
    u16 color_flags;
    u16 transform_flags;
    ChannelState channels[4];
    u8 color_start[4];
    u8 color_alternate[4];
    s8 color_amount[4];
    u8 color_end[4];
    s16 scale_start[3];
    s16 scale_alternate[3];
    s16 scale_amount[3];
    s16 scale_end[3];
    s16 translation_start[3];
    s16 translation_alternate[3];
    s16 translation_amount[3];
    s16 translation_end[3];
    u8 pad_06C[0x18];
    float weight_start;
    float weight_amount;
} Entry;

typedef struct OwnerLayout {
    u8 pad_000[0x240];
    Entry** entries;
} OwnerLayout;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern float lbl_806501D8;
extern float lbl_806501DC;
extern void fn_80125ECC(Owner* owner);
extern void fn_8012BE18(const s16* input, float* output, int format);
extern void fn_8012E19C(float* fraction, float* complement, float start,
                      float amount, float end, float alternate_end);

int fn_8012DCBC(Owner* owner, u32 index, int channel, float* complement,
                int* valid, u16 flags)
{
    Vec3 scale_start;
    Vec3 scale_amount;
    Vec3 scale_end;
    Vec3 scale_alternate;
    Vec3 translation_start;
    Vec3 translation_amount;
    Vec3 translation_end;
    Vec3 translation_alternate;
    float fraction;
    register Entry* entry;
    int result;

    fraction = 0.0f;
    result = 0;
    fn_80125ECC(owner);
    entry = ((OwnerLayout*)owner)->entries[index];
    if (entry != 0) {
        register Entry* channel_entry;
        register int channel_offset = channel * 8;

        /* ASM: add keeps the channel-relative base separate from the
         * flags displacement; MWCC folds equivalent C into lhzx. */
        asm { add channel_entry, entry, channel_offset }
        if ((channel_entry->channels[0].flags & 1) != 0) {
            result = 1;
            if (valid != 0) {
                *valid = 1;
            }
            switch (channel) {
            case 0:
                if ((flags & 2) != 0) {
                    if ((entry->color_flags & 2) != 0) {
                        fn_8012E19C(&fraction, complement, (float)entry->color_start[0],
                                    (float)entry->color_amount[0], (float)entry->color_end[0],
                                    (float)entry->color_alternate[0]);
                        fn_8012E19C(&fraction, complement, (float)entry->color_start[1],
                                    (float)entry->color_amount[1], (float)entry->color_end[1],
                                    (float)entry->color_alternate[1]);
                        fn_8012E19C(&fraction, complement, (float)entry->color_start[2],
                                    (float)entry->color_amount[2], (float)entry->color_end[2],
                                    (float)entry->color_alternate[2]);
                    } else {
                        result = 0;
                    }
                } else if ((flags & 4) != 0) {
                    if ((entry->color_flags & 4) != 0) {
                        fn_8012E19C(&fraction, complement, (float)entry->color_start[3],
                                    (float)entry->color_amount[3], (float)entry->color_end[3],
                                    (float)entry->color_alternate[3]);
                        if (valid != 0 && entry->color_amount[3] < 0) {
                            *valid = 0;
                        }
                    } else {
                        result = 0;
                    }
                }
                break;
            case 1:
                fn_8012BE18(entry->scale_start, &scale_start.x, 8);
                fn_8012BE18(entry->scale_amount, &scale_amount.x, 8);
                fn_8012BE18(entry->scale_end, &scale_end.x, 8);
                fn_8012BE18(entry->scale_alternate, &scale_alternate.x, 8);
                fn_8012E19C(&fraction, complement, scale_start.x, scale_amount.x,
                            scale_end.x, scale_alternate.x);
                fn_8012E19C(&fraction, complement, scale_start.y, scale_amount.y,
                            scale_end.y, scale_alternate.y);
                fn_8012E19C(&fraction, complement, scale_start.z, scale_amount.z,
                            scale_end.z, scale_alternate.z);
                if (valid != 0 && (scale_amount.x < lbl_806501D8 ||
                                  scale_amount.y < lbl_806501D8 ||
                                  scale_amount.z < lbl_806501D8)) {
                    *valid = 0;
                }
                break;
            case 2:
                fn_8012BE18(entry->translation_start, &translation_start.x, 6);
                fn_8012BE18(entry->translation_amount, &translation_amount.x, 6);
                fn_8012BE18(entry->translation_end, &translation_end.x, 6);
                fn_8012BE18(entry->translation_alternate, &translation_alternate.x, 6);
                fn_8012E19C(&fraction, complement, translation_start.x, translation_amount.x,
                            translation_end.x, translation_alternate.x);
                fn_8012E19C(&fraction, complement, translation_start.y, translation_amount.y,
                            translation_end.y, translation_alternate.y);
                fn_8012E19C(&fraction, complement, translation_start.z, translation_amount.z,
                            translation_end.z, translation_alternate.z);
                break;
            case 3:
                fn_8012E19C(&fraction, complement, entry->weight_start,
                            entry->weight_amount, lbl_806501DC, lbl_806501D8);
                break;
            }
        }
    }
    return result;
}
