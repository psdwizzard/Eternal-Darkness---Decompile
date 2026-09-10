typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Record {
    unsigned char pad[0x28];
    u32 value;
    unsigned char tail[0x30];
} Record;

extern int lbl_8064D17C;
extern void* lbl_8064D18C;
extern void* memset(void*, int, unsigned long);
extern u16* fn_8015C414(int, u16*);
extern u16 fn_8015C470(int);
extern Record* fn_8015C3E0(int);
extern void fn_80159F34(void*, int, u16*);

void fn_8015BCB0(void)
{
    u16 source_count;
    u16 values[4];
    u16* source;
    u16* output;
    Record* records;
    u16 record_count;
    int used = 0;
    int i;
    int limit;

    memset(values, -1, sizeof(values));
    source = fn_8015C414(2, &source_count);
    if (source != 0 && source_count != 0) {
        output = values;
        limit = lbl_8064D17C;
        for (i = 0; i < source_count; i++) {
            if (used < limit) {
                *output++ = *source;
                used++;
            }
            source++;
        }
    }
    record_count = fn_8015C470(2);
    if (record_count != 0) {
        u16* record_output;
        int record_limit;
        int remaining;

        records = fn_8015C3E0(2);
        record_output = values + used;
        record_limit = lbl_8064D17C;
        remaining = record_count;
        while (remaining > 0) {
            if (used < record_limit) {
                *record_output++ = records->value;
                used++;
            }
            records++;
            remaining--;
        }
    }
    fn_80159F34(lbl_8064D18C, used, values);
}
