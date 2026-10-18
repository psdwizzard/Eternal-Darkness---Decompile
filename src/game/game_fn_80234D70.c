/* _01class: residue 0/1 classification (Vorbis _01class variant). */

typedef int s32;

typedef struct ResidueInfo {
    s32 begin;
    s32 end;
    s32 grouping;
    s32 partitions;
} ResidueInfo;

typedef struct ResidueLook {
    ResidueInfo *info;
    s32 pad04[10];
    s32 frames;
} ResidueLook;

void *fn_8022F8C4(s32 size);
void *memset(void *dest, int value, unsigned long size);

s32 **_01class(void *vb, ResidueLook *look, float **in, s32 ch,
                  s32 (*classify)(float *, s32, ResidueLook *, s32, s32)) {
    s32 i, j;
    ResidueInfo *info = look->info;
    s32 samples_per_partition = info->grouping;
    s32 possible_partitions = info->partitions;
    s32 n = info->end - info->begin;
    s32 partvals = n / samples_per_partition;
    s32 **partword = (s32 **)fn_8022F8C4(ch * sizeof(*partword));

    for (j = 0; j < ch; j++) {
        partword[j] = (s32 *)fn_8022F8C4(partvals * sizeof(*partword[j]));
        memset(partword[j], 0, partvals * sizeof(*partword[j]));
    }

    for (i = 0; i < partvals; i++) {
        for (j = 0; j < ch; j++) {
            partword[j][i] = classify(in[j] + (i * samples_per_partition + info->begin),
                                      samples_per_partition, look,
                                      possible_partitions, i);
        }
    }

    look->frames++;
    return partword;
}
