typedef unsigned char u8;
typedef unsigned int u32;

typedef struct VID_LIST {
    struct VID_LIST* next;
    struct VID_LIST* prev;
    u32 vid;
    u32 root;
} VID_LIST;

typedef struct SYNTH_VOICE {
    u8 pad_000[0xEC];
    u32 child;
    u32 parent;
    u32 id;
    VID_LIST* vidList;
    VID_LIST* vidMasterList;
    u8 pad_100[0x304];
} SYNTH_VOICE;

extern SYNTH_VOICE* lbl_8064D3D0;
extern VID_LIST* lbl_8064D45C;
extern VID_LIST* lbl_8064D460;
extern void fn_801C2754(SYNTH_VOICE* voice);

#define VID_UNLINK(field)                                                                                              \
    if (s->field->prev != 0) {                                                                                         \
        s->field->prev->next = s->field->next;                                                                         \
    } else {                                                                                                           \
        lbl_8064D45C = s->field->next;                                                                                 \
    }                                                                                                                  \
    if (s->field->next != 0) {                                                                                         \
        s->field->next->prev = s->field->prev;                                                                         \
    }                                                                                                                  \
    s->field->next = lbl_8064D460;                                                                                     \
    if (lbl_8064D460 != 0) {                                                                                           \
        lbl_8064D460->prev = s->field;                                                                                 \
    }                                                                                                                  \
    s->field->prev = 0;                                                                                                \
    lbl_8064D460 = s->field

void fn_801C106C(SYNTH_VOICE* state)
{
    SYNTH_VOICE* s = state;
    if (s->id != 0xffffffff) {
        fn_801C2754(state);
        if (s->parent != 0xffffffff) {
            lbl_8064D3D0[s->parent & 0xff].child = s->child;
            if (s->child != 0xffffffff) {
                lbl_8064D3D0[s->child & 0xff].parent = s->parent;
            }
            VID_UNLINK(vidList);
            s->vidList = 0;
        } else if (s->child != 0xffffffff) {
            s->vidList->root = s->child;
            lbl_8064D3D0[s->child & 0xff].parent = 0xffffffff;
            lbl_8064D3D0[s->child & 0xff].vidMasterList = s->vidMasterList;
            if (s->vidList != s->vidMasterList) {
                VID_UNLINK(vidList);
                s->vidList = 0;
            }
            s->vidList = 0;
            s->vidMasterList = 0;
        } else if (s->vidList != s->vidMasterList) {
            VID_UNLINK(vidList);
            s->vidList = 0;
            VID_UNLINK(vidMasterList);
            s->vidMasterList = 0;
        } else {
            VID_UNLINK(vidList);
            s->vidList = 0;
            s->vidMasterList = 0;
        }
    }
}
