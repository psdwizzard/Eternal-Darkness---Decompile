typedef unsigned char u8;

typedef struct Event Event;
typedef struct List List;

extern u8* cseq;
extern Event* GenerateNextTrackEvent(u8);
extern void InsertGlobalEvent(List*, Event*);

void InitTrackEventsSection(u8 owner)
{
    u8 selected;
    unsigned int offset;
    unsigned int second_i;
    unsigned int first_i;
    Event* event;

    if (*(u8**)(cseq + 0x14E4) == 0) {
        for (first_i = 0; first_i < 0x40; first_i++) {
            event = GenerateNextTrackEvent((u8)first_i);
            if (event != 0)
                InsertGlobalEvent((List*)(cseq + 0x14E8), event);
        }
    } else {
        selected = owner;
        offset = selected * 0x38;

        for (second_i = 0; second_i < 0x40; second_i++) {
            if (selected == (*(u8**)(cseq + 0x14E4))[second_i]) {
                event = GenerateNextTrackEvent((u8)second_i);
                if (event != 0)
                    InsertGlobalEvent((List*)(cseq + 0x14E8 + offset), event);
            }
        }
    }
}
