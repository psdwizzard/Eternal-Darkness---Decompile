typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SND_ROOM {
    u8 pad00[0x1C];
    u8 studio;
} SND_ROOM;

typedef struct SND_STUDIO_INPUT {
    u8 vol;
    u8 volA;
    u8 volB;
    u8 srcStudio;
} SND_STUDIO_INPUT;

typedef struct SND_DOOR {
    struct SND_DOOR* next;
    u8 pad04[0x10];
    float open;
    u8 pad18[4];
    u8 fxVol;
    u8 destStudio;
    u8 pad1E[2];
    SND_ROOM* a;
    SND_ROOM* b;
    u32 flags;
    u8 pad2C[8];
    SND_STUDIO_INPUT input;
} SND_DOOR;

extern SND_DOOR* lbl_8064D4C8;
extern void fn_801B9310(u8, SND_STUDIO_INPUT*);
extern void fn_801B9330(u8, SND_STUDIO_INPUT*);

void fn_801C8600(void)
{
    SND_DOOR* link;
    float f;
    float v;

    for (link = lbl_8064D4C8; link != 0; link = link->next) {
        if ((link->flags & 0x80000000) == 0) {
            if (link->a->studio != 0xff) {
                if (link->b->studio != 0xff) {
                    v = link->open;
                    f = (1.0f - v) * v;
                    link->input.volA = (s32)((float)link->fxVol * v);
                    link->input.volB = 0;
                    link->input.vol = (s32)(127.0f * v);
                    if ((link->flags & 1) != 0) {
                        link->input.srcStudio = link->b->studio;
                        fn_801B9310(link->a->studio, &link->input);
                    } else {
                        link->input.srcStudio = link->a->studio;
                        fn_801B9310(link->b->studio, &link->input);
                    }
                    link->flags |= 0x80000000;
                }
            }
        } else {
            u8 sourceVoice = link->a->studio;

            if (sourceVoice == 0xff || link->b->studio == 0xff) {
                if ((sourceVoice != 0xff && sourceVoice == link->destStudio) ||
                    (link->b->studio != 0xff && link->b->studio == link->destStudio)) {
                    fn_801B9330(link->destStudio, &link->input);
                }
                link->flags &= 0x7fffffff;
            } else {
                v = link->open;
                f = (1.0f - v) * v;
                link->input.volA = (s32)((float)link->fxVol * v);
                link->input.volB = 0;
                link->input.vol = (s32)(127.0f * v);
            }
        }
    }
}
