typedef unsigned int u32;

typedef struct Resource Resource;
typedef struct Voice Voice;

struct Resource {
    char pad00[8];
    u32 flags;
};

struct Voice {
    Voice* previous;
    Voice* next;
    Resource* resource;
};

extern unsigned char sndActive;
extern Voice* s3dListenerRoot;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

static inline void ReleaseResource(Resource* resource)
{
    u32 count = 0;
    Voice* current = s3dListenerRoot;
    while (current != 0) {
        if (current->resource == resource) {
            count++;
        }
        current = current->previous;
    }
    if (count == 1) {
        resource->flags &= 0x7FFFFFFF;
        resource->flags |= 0x40000000;
    }
}

int sndRemoveListener(Voice* voice)
{
    if (sndActive != 0) {
        hwDisableIrq();
        if (voice->resource != 0) {
            ReleaseResource(voice->resource);
        }
        if (voice->previous != 0) {
            voice->previous->next = voice->next;
        }
        if (voice->next != 0) {
            voice->next->previous = voice->previous;
        } else {
            s3dListenerRoot = voice->previous;
        }
        hwEnableIrq();
        return 1;
    }
    return 0;
}
