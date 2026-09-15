typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Batch {
    char pad_0[0x60];
    char* records;
    char pad_64[0x1A];
    u8 count;
} Batch;

typedef struct Record {
    unsigned int words[3];
    float vector[2];
    float scale;
} Record;

typedef struct Quad {
    unsigned int word[4];
} Quad;

typedef struct Pair {
    unsigned int word[2];
} Pair;

typedef struct RuntimeSlot {
    char pad_0[0x50];
    int handle;
    float output[6];
    Quad value_words;
    u16 value;
    char pad_7E[0xA];
    u8 kind;
    char pad_89[0xF];
    int state;
} RuntimeSlot;

typedef struct SlotStride {
    char bytes[0x78];
} SlotStride;

extern RuntimeSlot lbl_8030F540[];
extern float lbl_80650228;
extern float lbl_8065024C;
extern float lbl_80650250;

extern void* fn_801FD6F4(int);
extern void fn_801FD6AC(void*, Record*, float*, int);
extern void fn_801FE8DC(float*, float, float, float);
extern int fn_801E8328();

void fn_80132B24(Batch* batch, u16 value)
{
    int offset;
    RuntimeSlot* slot;
    int i;

    if (batch->count != 0) {
        i = 0;
        slot = lbl_8030F540;
        offset = 0;
        while (i < batch->count) {
            Record* record = (Record*)(batch->records + offset);
            void* resource = fn_801FD6F4(slot->handle);

            if (resource != 0) {
                fn_801FD6AC((char*)resource + 0x34, record, record->vector,
                            (int)(record->scale * lbl_8065024C));
            } else {
                *(Pair*)&slot->value_words = *(Pair*)record;
                slot->value_words.word[2] = record->words[2];
                slot->value_words.word[3] = *(unsigned int*)record->vector;
                slot->state = 0;
                slot->value = value;
                *(u8*)((char*)slot + 0x87) = 0;
                slot->kind = 7;
                fn_801FE8DC(slot->output, lbl_80650228, lbl_80650228,
                            lbl_80650250);
                fn_801E8328(0x20, &slot->handle);
            }
            offset += sizeof(Record);
            slot = (RuntimeSlot*)((char*)slot + 0x78);
            i++;
        }
    }
}
