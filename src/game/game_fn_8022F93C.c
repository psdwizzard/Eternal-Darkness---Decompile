/* Advance the decoded PCM read position without exceeding available samples. */
typedef signed short s16;

typedef struct AudioInfo {
    int version;
    int channels;
    int rate;
    int bitrate_upper;
    int bitrate_nominal;
    int bitrate_lower;
    int bitrate_window;
    void *codec_setup;
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

int fn_8022F93C(AudioState *state, int samples)
{
    if (samples != 0 && state->pcm_read + samples > state->center) {
        return -131;
    }
    state->pcm_read += samples;
    return 0;
}
