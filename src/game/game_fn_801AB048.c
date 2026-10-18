typedef struct Record {
    unsigned char pad00[0x74];
    int handle;
    unsigned char pad78[0x17];
    signed char active;
    unsigned char pad90[2];
    signed char async;
} Record;

extern void fn_801B05B0(int, int);
extern void sndRemoveEmitter(Record*);

void fn_801AB048(Record* record)
{
    if (record != 0 && record->active != 0) {
        if (record->async != 0) {
            if (record->handle != -1) {
                fn_801B05B0(record->handle, 0);
                record->handle = -1;
            }
        } else {
            sndRemoveEmitter(record);
        }
        record->active = 0;
    }
}
