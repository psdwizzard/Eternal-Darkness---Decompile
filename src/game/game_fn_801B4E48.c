typedef unsigned char u8;

typedef struct Event Event;
typedef struct List {
    u8 pad00[0x1C];
    Event* head;
} List;

extern u8* cseq;
extern Event* GenerateNextTrackEvent(u8);
extern void InsertGlobalEvent(List*, Event*);

void InitTrackEvents(void)
{
    unsigned int i;
    Event* event;
    u8* state = cseq;

    if (*(u8**)(state + 0x14E4) == 0) {
        for (i = 0; i < 0x40; i++) {
            event = GenerateNextTrackEvent((u8)i);
            if (event != 0)
                InsertGlobalEvent((List*)(cseq + 0x14E8), event);
        }
    } else {
        for (i = 0; i < 0x40; i++) {
            event = GenerateNextTrackEvent((u8)i);
            if (event != 0) {
                state = cseq;
                InsertGlobalEvent((List*)(state + 0x14E8 +
                                    (*(u8**)(state + 0x14E4))[i] * 0x38),
                            event);
            }
        }
    }
}
