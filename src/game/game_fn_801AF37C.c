typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct WorkDesc {
    char* name;
    u16 value;
    u8 pad06[2];
    u32 size;
    u32 offset;
    char data[0x20];
} WorkDesc;

typedef struct StreamHeader {
    u8 pad00[4];
    u32 size;
    u32 value;
    u8 pad0C[0x10];
    char data[0x20];
} StreamHeader;

typedef struct Work {
    StreamHeader* source[2];
    char buffer0[0x3c];
    char buffer1[0x3c];
    char name0[0x32];
    char name1[0x32];
    WorkDesc desc[2];
    u8 pad144[0x18];
    u32 id;
    u8 pad160[0x10];
    volatile u8 state0;
    volatile u8 state1;
    u8 mode0;
    u8 mode1;
    u8 pad174[2];
    u8 option;
    u8 pad177[2];
    u8 parameter;
    u8 flag;
    u8 active;
    u8 type;
    u8 pad17d;
    u8 count;
    u8 pad17f;
    u8 style;
} Work;

extern Work* lbl_8064D310;
extern u32 lbl_8064D318;
extern char lbl_8064C2D8;
extern int fn_801AE2F4(void);
extern int sprintf(char*, char*, char*, u32, char*, ...);
extern int DVDOpen(char*, char*);
extern int DVDReadAsyncPrio(char*, void*, int, int, int (*)(int), int);
extern void DVDClose(char*);
extern int fn_801AF0E4(int);
extern int fn_801ADEEC(WorkDesc*, u8, int, int, u8, u8);
extern int fn_801ADFC4(WorkDesc*, char**, u8, u8, u8);
extern void* memcpy(void*, const void*, unsigned long);

int fn_801AF37C(Work* work)
{
    int done;
    u32 result;
    result = -1;

    if (lbl_8064D310 == 0 || lbl_8064D310 == work) {
        lbl_8064D310 = work;
        if (work->state0 == 2) {
            if (fn_801AE2F4() >= work->count) {
                done = 0;
                if (work->count == 1) {
                    if (work->style == 1) {
                        sprintf(work->name0, "%s%04dL%s", "audio/stream/",
                                    work->id, &lbl_8064C2D8);
                        work->name1[0] = 0;
                    } else {
                        sprintf(work->name0, "%s%04d%s",
                                    "audio/stream/", work->id, &lbl_8064C2D8);
                        work->name1[0] = 0;
                    }
                    work->state0 = 1;
                    work->state1 = 0;
                    work->mode0 = 1;
                    work->mode1 = 0;
                    if (DVDOpen(work->name0, work->buffer0)) {
                        while (!DVDReadAsyncPrio(work->buffer0, work->source[0], 0x60,
                                           0, fn_801AF0E4, 2)) {}
                    } else {
                        done = 1;
                    }
                } else if (work->count == 2) {
                    sprintf(work->name0, "%s%04dL%s", "audio/stream/",
                                work->id, &lbl_8064C2D8);
                    sprintf(work->name1, "%s%04dR%s",
                                "audio/stream/", work->id, &lbl_8064C2D8);
                    work->state0 = 1;
                    work->state1 = 1;
                    work->mode0 = 2;
                    work->mode1 = 2;
                    if (DVDOpen(work->name0, work->buffer0)) {
                        if (DVDOpen(work->name1, work->buffer1)) {
                            while (!DVDReadAsyncPrio(work->buffer0, work->source[0], 0x60,
                                               0, fn_801AF0E4, 2)) {}
                            while (!DVDReadAsyncPrio(work->buffer1, work->source[1], 0x60,
                                               0, fn_801AF0E4, 2)) {}
                        } else {
                            DVDClose(work->buffer0);
                            done = 1;
                        }
                    } else {
                        done = 1;
                    }
                } else {
                    done = 1;
                }
                if (done == 1) {
                    work->flag = 1;
                    lbl_8064D310 = 0;
                    work->mode0 = 0;
                    work->mode1 = 0;
                }
            }
        } else if (work->state0 == 3) {
            work->state0 = 1;
            while (!DVDReadAsyncPrio(work->buffer0, work->source[0], 0x60,
                               0, fn_801AF0E4, 2)) {}
        } else if (work->state1 == 3) {
            work->state1 = 1;
            while (!DVDReadAsyncPrio(work->buffer1, work->source[1], 0x60,
                               0, fn_801AF0E4, 2)) {}
        } else if (work->state0 == 0 && work->state1 == 0) {
            int i;
            if (work->flag == 1) {
                lbl_8064D310 = 0;
            } else {
                for (i = 0; i < work->count; i++) {
                    memcpy(work->desc[i].data, work->source[i]->data, 0x20);
                    work->desc[i].name = work->name0;
                    work->desc[i].value = work->source[i]->value;
                    work->desc[i].offset = (work->source[i]->size >> 1) & ~0x1f;
                    work->desc[i].size = 0x60;
                }
                if (work->count == 1) {
                    result = fn_801ADEEC(work->desc, work->option, 0x40, 0,
                                         work->parameter, work->active);
                } else {
                    work->desc[1].name = work->name1;
                    result = fn_801ADFC4(work->desc, &work->desc[1].name,
                                        work->option, work->parameter, work->active);
                }
                if (result != -1) {
                    lbl_8064D310 = 0;
                }
            }
        }
    }
    lbl_8064D318 = work->id;
    return result;
}
