/* _2class: residue 2 classification (Vorbis _2class variant). */

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

s32 **_2class(void *vb, ResidueLook *look, float **in, s32 ch,
                  s32 (*classify)(float *, s32, ResidueLook *, s32, s32)) {
    s32 i, j, k, l;
    ResidueInfo *info = look->info;
    s32 n = info->end - info->begin;
    s32 samples_per_partition = info->grouping;
    s32 possible_partitions = info->partitions;
    s32 partvals = n / samples_per_partition;
    s32 **partword = (s32 **)fn_8022F8C4(sizeof(*partword));
    float *work = (float *)fn_8022F8C4(samples_per_partition * sizeof(float));
    s32 size = n * ch / samples_per_partition * sizeof(*partword[0]);

    partword[0] = (s32 *)fn_8022F8C4(size);
    memset(partword[0], 0, size);

    for (i = 0, k = 0, l = info->begin; i < partvals; i++) {
        for (j = 0; j < samples_per_partition; j++) {
            work[j] = in[k++][l];
            if (k >= ch) {
                k = 0;
                l++;
            }
        }
        partword[0][i] = classify(work, samples_per_partition, look, possible_partitions, i);
    }

    look->frames++;
    return partword;
}
