/* Return the available decoded samples and optional planar PCM pointers. */
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

extern void fn_8022F8FC(void);

int fn_8022F974(AudioState *state, s16 ***pcm)
{
    AudioInfo *info = state->info;
    fn_8022F8FC();
    if (state->pcm_read > -1 && state->pcm_read < state->center) {
        if (pcm != 0) {
            int i;
            for (i = 0; i < info->channels; i++) {
                state->pcm_return[i] = state->pcm[i] + state->pcm_read;
            }
            *pcm = state->pcm_return;
        }
        return state->center - state->pcm_read;
    }
    return 0;
}
