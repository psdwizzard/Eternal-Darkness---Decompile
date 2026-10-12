typedef unsigned int u32;
typedef int s32;
typedef float f32;

typedef struct AudioGraph {
    void *unused;
    s32 channelCount;
    char pad08[0x14];
    s32 *sampleCounts;
} AudioGraph;

typedef struct AudioDefinition {
    AudioGraph *graph;
    char pad04[0x44];
    void ***sources;
} AudioDefinition;

typedef struct AudioContext {
    f32 **buffers;
    char pad04[0x14];
    s32 leftIndex;
    s32 sampleIndex;
    s32 rightIndex;
    s32 sampleCount;
    char pad28[0x10];
    AudioDefinition *definition;
} AudioContext;

typedef struct ChannelMap {
    s32 outputCount;
    s32 channelIndex[306];
    s32 pairCount;
    s32 firstPair[256];
    s32 secondPair[256];
} ChannelMap;

typedef struct AudioOp {
    char pad00[0x1c];
    void *(*create)(AudioContext *, void *);
    void (*run)(AudioContext *, void *, void *, f32 *);
} AudioOp;

typedef struct OutputOp {
    char pad00[0x20];
    void (*run)(AudioContext *, void *, f32 **, s32 *);
} OutputOp;

typedef struct AudioJob {
    void *settings;
    ChannelMap *map;
    void *pad08;
    void **createInputs;
    void **runInputs;
    char pad14[0xc];
    AudioOp **createOps;
    OutputOp **runOps;
} AudioJob;

extern void *memset(void *, int, unsigned long);
extern void fn_80233658(void *, f32 *, f32 *);
extern f32 fn_8023633C(void *, s32, s32, s32, s32);
extern f32 lbl_80651830;

s32 fn_80232C44(AudioContext *context, AudioJob *job)
{
    f32 *inputs[2];
    s32 inputActive[2];
    s32 active[2];
    void *created[2];
    void **createdBase = created;
    s32 *activeBase = active;
    AudioDefinition *definition = context->definition;
    AudioGraph *graph = definition->graph;
    ChannelMap *map = job->map;
    void ***sources = definition->sources;
    void *settings = job->settings;
    s32 *counts = graph->sampleCounts;
    s32 samples = counts[context->sampleIndex];
    s32 leftCount, rightCount, scaleCount;
    s32 left, right;
    s32 i, j;
    s32 halfSamples;

    context->sampleCount = samples;
    leftCount = counts[context->leftIndex];
    scaleCount = counts[context->sampleIndex];
    rightCount = counts[context->rightIndex];
    left = ((s32)((u32)leftCount >> 31) + leftCount) >> 1;
    right = ((s32)((u32)rightCount >> 31) + rightCount) >> 1;
    for (i = 0; i < graph->channelCount; i++) {
        s32 index = map->channelIndex[i];
        createdBase[i] = job->createOps[index]->create(context, job->createInputs[index]);
        if (createdBase[i] != 0) {
            activeBase[i] = 1;
        } else {
            activeBase[i] = 0;
        }
        memset(context->buffers[i], 0, ((u32)samples << 1) & 0x7ffffffe);
    }

    for (i = 0; i < map->pairCount; i++) {
        s32 a = map->firstPair[i];
        if (activeBase[a] != 0 || activeBase[map->secondPair[i]] != 0) {
            activeBase[a] = 1;
            activeBase[map->secondPair[i]] = 1;
        }
    }

    {
        s32 outputOffset = 0;
        for (i = 0; i < map->outputCount; i++, outputOffset += 4) {
            s32 n = 0;
            s32 *inputStatus = inputActive;
            for (j = 0; j < graph->channelCount; j++) {
                if (map->channelIndex[j] == i) {
                    if (activeBase[j] != 0) {
                        *inputStatus = 1;
                    } else {
                        *inputStatus = 0;
                    }
                    inputs[n] = context->buffers[j];
                    inputStatus++;
                    n++;
                }
            }
            (*(OutputOp **)((char *)job->runOps + outputOffset))->run(
                context, *(void **)((char *)job->runInputs + outputOffset),
                inputs, inputActive);
        }
    }

    halfSamples = ((s32)((u32)samples >> 31) + samples) >> 1;
    {
        f32 zero = lbl_80651830;
        for (i = map->pairCount - 1; i >= 0; i--) {
            f32 *a = context->buffers[map->firstPair[i]];
            f32 *b = context->buffers[map->secondPair[i]];
            for (j = 0; j < halfSamples; j++) {
                f32 x = *a;
                f32 y = *b;
                if (x > zero) {
                    if (y > zero) {
                        *a = x;
                        *b = x - y;
                    } else {
                        *b = x;
                        *a = x + y;
                    }
                } else if (y > zero) {
                    *a = x;
                    *b = x + y;
                } else {
                    *b = x;
                    *a = x - y;
                }
                a++;
                b++;
            }
        }
    }

    {
        void **createdCursor = createdBase;
        s32 bufferOffset = 0;
        s32 *channel = map->channelIndex;
        for (i = 0; i < graph->channelCount; i++) {
            s32 index = *channel;
            job->createOps[index]->run(context, job->createInputs[index],
                                        *createdCursor,
                                        *(f32 **)((char *)context->buffers + bufferOffset));
            channel++;
            createdCursor++;
            bufferOffset += 4;
        }
    }

    for (i = 0; i < graph->channelCount; i++) {
        void *source = *sources[context->sampleIndex + 1];
        fn_80233658(source, context->buffers[i], context->buffers[i]);
    }

    for (i = 0; i < graph->channelCount; i++) {
        f32 *buffer = context->buffers[i];
        if (activeBase[i] != 0) {
            for (j = 0; j < samples; j++) {
                buffer[j] *= fn_8023633C(*(void **)((char *)settings + 4), j,
                                          scaleCount, left, right);
            }
        } else {
            f32 zeroFill = lbl_80651830;
            f32 *cursor = buffer;
            j = 0;
            while (j < samples) {
                *cursor++ = zeroFill;
                j++;
            }
        }
    }
    return 0;
}
