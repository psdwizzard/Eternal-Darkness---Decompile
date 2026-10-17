/* fn_802345E4: residue 2 inverse (Vorbis res2_inverse). */

typedef int s32;

typedef struct DecodeAux DecodeAux;
typedef struct Codebook {
    s32 dim;
    s32 entries;
    void *c;
    void *valuelist;
    void *quantlist;
    DecodeAux *decode_tree;
} Codebook;

typedef struct ResidueInfo {
    s32 begin;
    s32 end;
    s32 grouping;
    s32 partitions;
    s32 groupbook;
    s32 secondstages[64];
} ResidueInfo;

typedef struct ResidueLook {
    ResidueInfo *info;
    s32 map;
    s32 parts;
    s32 stages;
    Codebook *fullbooks;
    Codebook *phrasebook;
    Codebook ***partbooks;
    s32 partvals;
    s32 **decodemap;
} ResidueLook;

typedef struct OggPackBuffer {
    s32 endbyte;
    s32 endbit;
    unsigned char *buffer;
    unsigned char *ptr;
    s32 storage;
} OggPackBuffer;

typedef struct VorbisBlock {
    float **pcm;
    OggPackBuffer opb;
} VorbisBlock;

void *fn_8022F8C4(s32 size);
s32 fn_80230718(Codebook *book, OggPackBuffer *b);
s32 fn_80230128(Codebook *book, float **a, s32 offset, s32 ch, OggPackBuffer *b, s32 n);

s32 fn_802345E4(register VorbisBlock *arg_vb, register ResidueLook *arg_look,
                register float **arg_in, register s32 *arg_nonzero, register s32 arg_ch)
{
    register ResidueInfo *info;
    register s32 samples_per_partition;
    s32 partitions_per_word, partvals, partwords;
    register s32 ch;
    register float **in;
    register ResidueLook *look;
    register VorbisBlock *vb;
    s32 j, column;
    register s32 position;
    register s32 **word;
    register s32 offset, mask;
    s32 stage_offset;
    register s32 i;
    s32 k;
    register s32 s;
    register s32 *nonzero;
    register s32 **partword;
    register s32 *nz;
    register s32 **allocated;
    /* ASM: mr keeps the saved arguments as copies rather than folded addi instructions. */
    asm {
        or vb, arg_vb, arg_vb
        or look, arg_look, arg_look
        or in, arg_in, arg_in
        or nonzero, arg_nonzero, arg_nonzero
        or ch, arg_ch, arg_ch
    }
    info = arg_look->info;
    samples_per_partition = info->grouping;
    partitions_per_word = arg_look->phrasebook->dim;
    partvals = (info->end - info->begin) / samples_per_partition;
    partwords = (partvals + partitions_per_word - 1) / partitions_per_word;
    allocated = fn_8022F8C4(partwords * sizeof(*partword));
    /* ASM: mr preserves the two pointer copies; C folds them to addi and extends the nonzero lifetime. */
    asm {
        or nz, nonzero, nonzero
        or partword, allocated, allocated
    }
    for (j = 0; j < ch; nz++, j++) {
        if (*nz) break;
    }
    if (j == ch) return 0;
    for (s = 0, stage_offset = 0; s < look->stages; stage_offset += sizeof(Codebook *), s++) {
        register s32 one;
        /* ASM: li, mr and slw retain initialization order and copies that C folds or reschedules. */
        asm {
            li i, 0
            li one, 1
            or word, partword, partword
            or offset, i, i
            slw mask, one, s
        }
        while (i < partvals) {
            if (s == 0) {
                s32 temp = fn_80230718(look->phrasebook, &vb->opb);
                if (temp == -1) goto done;
                *word = look->decodemap[temp];
                if (*word == 0) goto done;
            }
            /* ASM: mr prevents folding the position copy into addi. */
            asm { or position, offset, offset }
            k = 0;
            column = 0;
            while (k < partitions_per_word && i < partvals) {
                s32 entry = *(s32 *)((unsigned char *)*word + column);
                /* The stage masks follow the five scalar residue fields. */
                s32 flags = ((s32 *)info)[entry + 5];
                flags &= mask;
                if (flags) {
                    Codebook *stagebook = *(Codebook **)(stage_offset + (unsigned int)look->partbooks[entry]);
                    if (stagebook) {
                        register float **channels;
                        s32 begin = info->begin;
                        /* ASM: mr keeps the channel pointer copy from folding to addi. */
                        asm { or channels, in, in }
                        if (fn_80230128(stagebook, channels, begin + position,
                            ch, &vb->opb, samples_per_partition) == -1)
                            goto done;
                    }
                }
                position += samples_per_partition;
                offset += samples_per_partition;
                i++;
                column += sizeof(s32);
                k++;
            }
            word++;
        }
    }
done:
    return 0;
}
