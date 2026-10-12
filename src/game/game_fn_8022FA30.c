/* Append a decoded audio block to planar signed 16-bit PCM buffers. */

typedef signed short s16;
typedef unsigned int u32;

typedef struct CodecSetup {
    int blocksizes[2];
} CodecSetup;

typedef struct AudioInfo {
    int version;
    int channels;
    int rate;
    int bitrate_upper;
    int bitrate_nominal;
    int bitrate_lower;
    int bitrate_window;
    CodecSetup *codec_setup;
} AudioInfo;

typedef struct AudioState {
    AudioInfo *info;
    s16 **pcm;
    s16 **pcm_return;
    int pcm_storage;
    int pcm_current;
    int pcm_read;
    int preextrapolate;
    int eof;
    int previous_window;
    int window;
    int next_window;
    long center;
    int granulepos;
    int sequence;
    int glue_bits;
    int time_bits;
    int floor_bits;
    int residue_bits;
} AudioState;

typedef struct PacketBits {
    long byte_offset;
    int bit_offset;
    unsigned char *buffer;
    unsigned char *cursor;
    long storage;
} PacketBits;

typedef struct AudioBlock {
    float **pcm;
    PacketBits packet;
    int previous_window;
    int window;
    int next_window;
    int pcm_end;
    int mode;
    int eof;
    int granulepos;
    int sequence;
    AudioState *state;
    void *local_storage;
    long local_top;
    long local_alloc;
    long total_use;
    struct AllocationChain *reap;
    int glue_bits;
    int time_bits;
    int floor_bits;
    int residue_bits;
} AudioBlock;

extern void *fn_800F9990(void *dest, const void *src, u32 size);

/* Signed halving with truncation toward zero. */
#define HALF_SAMPLES(n) (((int)((unsigned int)(n) >> 31) + (n)) >> 1)

extern float lbl_80651798; /* 32768.0f: normalized float to signed PCM scale. */

int fn_8022FA30(AudioState *state, AudioBlock *block)
{
    AudioInfo *info = state->info;
    CodecSetup *setup = info->codec_setup;
    int size, center, begin, end, overlap_begin, overlap_end;

    /* Reclaim samples already returned to the caller. */
    if (state->center > HALF_SAMPLES(setup->blocksizes[1]) && state->pcm_read > 768) {
        int shift = state->center - HALF_SAMPLES(setup->blocksizes[1]);
        if (state->pcm_read < shift)
            shift = state->pcm_read;
        state->pcm_current -= shift;
        state->center -= shift;
        state->pcm_read -= shift;
        if (shift) {
            int i;
            unsigned int offset;
            for (i = 0, offset = 0; i < info->channels; offset += sizeof(s16 *), i++) {
                s16 *pcm = *(s16 **)((char *)state->pcm + offset);
                fn_800F9990(pcm, pcm + shift, state->pcm_current * sizeof(s16));
            }
        }
    }

    state->previous_window = state->window;
    state->window = block->window;
    state->next_window = -1;
    state->glue_bits += block->glue_bits;
    state->time_bits += block->time_bits;
    state->floor_bits += block->floor_bits;
    state->residue_bits += block->residue_bits;
    if (state->sequence + 1 != block->sequence)
        state->granulepos = -1;
    state->sequence = block->sequence;

    /* Position the new block and select its overlap with the old block. */
    size = setup->blocksizes[state->window];
    center = state->center + (setup->blocksizes[state->previous_window] / 4 + size / 4);
    begin = center - HALF_SAMPLES(size);
    end = begin + size;
    switch (state->window) {
    case 0:
        overlap_begin = 0;
        overlap_end = HALF_SAMPLES(setup->blocksizes[0]);
        break;
    case 1:
        overlap_begin = setup->blocksizes[1] / 4 - setup->blocksizes[state->previous_window] / 4;
        overlap_end = overlap_begin + HALF_SAMPLES(setup->blocksizes[state->previous_window]);
        break;
    default:
        return -1;
    }

    {
        int i;
        for (i = 0; i < info->channels; i++) {
            int j;
            s16 *pcm = state->pcm[i] + begin;
            float *input = block->pcm[i];
            for (j = overlap_begin; j < overlap_end; j++) {
                float value = lbl_80651798 * input[j] + pcm[j];
                if (value > 32767.0f)
                    value = 32767.0f;
                if (value < -32768.0f)
                    value = -32768.0f;
                pcm[j] = value;
            }
            for (; j < size; j++) {
                float value = lbl_80651798 * input[j];
                if (value > 32767.0f)
                    value = 32767.0f;
                if (value < -32768.0f)
                    value = -32768.0f;
                pcm[j] = value;
            }
        }
    }

    /* Reconcile packet positions, including initial padding and end trim. */
    if (state->pcm_read == -1)
        state->pcm_read = center;
    if (state->granulepos == -1) {
        if (block->granulepos == -1)
            state->granulepos = 0;
        else
            state->granulepos = block->granulepos;
    } else {
        state->granulepos += center - state->center;
        if (block->granulepos != -1 && state->granulepos != block->granulepos) {
            if (state->granulepos > block->granulepos) {
                int extra = state->granulepos - block->granulepos;
                if (block->eof)
                    center -= extra;
                else if (block->sequence == 1) {
                    state->pcm_read += extra;
                    if (state->pcm_read > center)
                        state->pcm_read = center;
                }
            }
            state->granulepos = block->granulepos;
        }
    }
    state->center = center;
    state->pcm_current = end;
    if (block->eof)
        state->eof = 1;
    return 0;
}
