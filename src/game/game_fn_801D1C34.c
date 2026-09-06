typedef signed int s32;
typedef unsigned int u32;

typedef struct EventPosition {
    float words[3];
} EventPosition;

typedef struct EventRecord {
    EventPosition position;
    u32 words[11];
} EventRecord;

extern EventRecord lbl_8023B570;
extern s32 lbl_8064D18C;
extern void* lbl_8064C4E0;

extern void* fn_80201814(s32);
extern void* fn_80201C24(void);
extern s32 fn_8015821C(void*);
extern void fn_801E7974(void*, s32);

void fn_801D1C34(EventRecord* output, s32 object, EventPosition position)
{
    EventRecord record;
    record = lbl_8023B570;
    record.position = position;
    record.words[8] = lbl_8064D18C;

    if (fn_80201814(object) != 0) {
        s32 type = fn_8015821C(fn_80201C24());

        switch (type) {
        case 227:
            record.words[1] = 25;
            record.words[2] = 189;
            record.words[3] = 166;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 159:
            record.words[1] = 25;
            record.words[2] = 103;
            record.words[3] = 15;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 123:
            record.words[1] = 25;
            record.words[2] = 11;
            record.words[3] = 19;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 124:
            fn_801E7974(lbl_8064C4E0, 240);
            record.words[1] = 25;
            record.words[2] = 98;
            record.words[3] = 92;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 32:
            record.words[1] = 25;
            record.words[2] = 54;
            record.words[3] = 31;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 37:
            record.words[1] = 25;
            record.words[2] = 52;
            record.words[3] = 34;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 230:
            record.words[1] = 74;
            record.words[2] = 111;
            record.words[3] = 104;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 131:
            record.words[1] = 25;
            record.words[2] = 221;
            record.words[3] = 131;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        case 238:
            record.words[1] = 25;
            record.words[2] = 239;
            record.words[3] = 239;
            record.words[7] = 30;
            record.words[9] = 4;
            break;
        }
    }

    *output = record;
}
