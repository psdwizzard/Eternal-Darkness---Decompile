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

extern unsigned char lbl_8064D3A0;
extern Voice* lbl_8064D4C0;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);

static inline void ReleaseResource(Resource* resource)
{
    u32 count = 0;
    Voice* current = lbl_8064D4C0;
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

int fn_801C9938(Voice* voice)
{
    if (lbl_8064D3A0 != 0) {
        fn_801CE2B8();
        if (voice->resource != 0) {
            ReleaseResource(voice->resource);
        }
        if (voice->previous != 0) {
            voice->previous->next = voice->next;
        }
        if (voice->next != 0) {
            voice->next->previous = voice->previous;
        } else {
            lbl_8064D4C0 = voice->previous;
        }
        fn_801CE280();
        return 1;
    }
    return 0;
}
