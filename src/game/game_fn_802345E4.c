/* fn_802345E4: residue 2 inverse (Vorbis res2_inverse). */

typedef int s32;

typedef struct Codebook {
    s32 dim;
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

typedef struct VorbisBlock {
    s32 pad0;
    s32 opb;
} VorbisBlock;

void *fn_8022F8C4(s32 size);
s32 fn_80230718(Codebook *book, void *b);
s32 fn_80230128(Codebook *book, s32 **a, s32 offset, s32 ch, void *b, s32 n);

s32 fn_802345E4(VorbisBlock *vb, ResidueLook *look, s32 **in, s32 *nonzero, s32 ch) {
    s32 i, j, k, l, s;
    ResidueInfo *info = look->info;

    s32 samples_per_partition = info->grouping;
    s32 partitions_per_word = look->phrasebook->dim;
    s32 n = info->end - info->begin;

    s32 partvals = n / samples_per_partition;
    s32 partwords = (partvals + partitions_per_word - 1) / partitions_per_word;
    s32 **partword = (s32 **)fn_8022F8C4(partwords * sizeof(*partword));

    for (j = 0; j < ch; j++) {
        if (nonzero[j]) break;
    }
    if (j == ch) return 0;

    for (s = 0; s < look->stages; s++) {
        for (i = 0, l = 0; i < partvals; l++) {
            if (s == 0) {
                s32 temp = fn_80230718(look->phrasebook, &vb->opb);
                if (temp == -1) goto eopbreak;
                partword[l] = look->decodemap[temp];
                if (partword[l] == 0) goto errout;
            }

            for (k = 0; k < partitions_per_word && i < partvals; k++, i++) {
                if (info->secondstages[partword[l][k]] & (1 << s)) {
                    Codebook *stagebook = look->partbooks[partword[l][k]][s];
                    if (stagebook) {
                        if (fn_80230128(stagebook, in, info->begin + i * samples_per_partition,
                                        ch, &vb->opb, samples_per_partition) == -1)
                            goto eopbreak;
                    }
                }
            }
        }
    }

errout:
eopbreak:
    return 0;
}
