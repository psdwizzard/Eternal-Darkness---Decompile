typedef signed char s8;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Record {
    void* objects[11];
    u32 values[11];
    u8 pad_58;
    u8 type;
    u8 pad_5A[2];
    s16 ids[11];
} Record;

typedef struct Header {
    int count;
    Record* records;
} Header;

typedef struct Context {
    u8 data[20];
} Context;

extern int lbl_8064D7D8;
extern Record* lbl_8064D8A0[2];
extern Context lbl_8063F020[2];
extern u8 lbl_8030F540[];
extern char lbl_80649A38[];
extern char lbl_8030C8AC[];

extern void** fn_801FF2F8(Context*, s16);
extern void fn_8015DAB0(void*);
extern void fn_801FF4D4(Context*, void*, u32, s16);
extern void fn_801FF5EC(Context*, Context*);
extern void fn_801FF838(Context*, int);
extern void fn_801FF23C(int, Record*, Record*);
extern void fn_80133300(void);
extern void fn_800F8BAC(const char*, const char*, int);

void fn_801FF008(Header* header, int arg)
{
    int result = 2;
    int i;
    int record_offset = 0;
    int count = header->count;
    Record* output = lbl_8064D8A0[lbl_8064D7D8];

    for (i = 0; i < count; i++) {
        int id_offset;
        int value_offset;
        Record* destination;
        int j;
        *output = *(Record*)((u8*)header->records + record_offset);

        id_offset = 0;
        value_offset = id_offset;
        destination = output;
        for (j = 0; j < 11; j++, value_offset += 4,
             destination = (Record*)((u8*)destination + 4), id_offset += 2) {
            s16 id = *(s16*)((u8*)header->records + record_offset +
                            id_offset + 0x5C);
            if (id != -1) {
                u32 value = *(u32*)((u8*)header->records + record_offset +
                                   value_offset + 0x2C);
                if (fn_801FF2F8(&lbl_8063F020[lbl_8064D7D8], id) == 0) {
                    u8 type = output->type;
                    if (type != 0 && type == (s8)lbl_8030F540[0x1E0]) {
                        result = 0;
                    }
                    if (type != 0 && type != (s8)lbl_8030F540[0x1E0]) {
                        if (result == 2) {
                            result = 1;
                        }
                    } else if (*(void**)((u8*)header->records + record_offset +
                                        value_offset) != 0) {
                        void* object = *(void**)((u8*)header->records +
                                                record_offset + value_offset);
                        if (object == 0) {
                            fn_800F8BAC(lbl_80649A38, lbl_8030C8AC, 371);
                        }
                        fn_8015DAB0(object);
                        destination->objects[0] = object;
                        fn_801FF4D4(&lbl_8063F020[lbl_8064D7D8], object,
                                    value, id);
                    }
                }
            }
        }
        output++;
        record_offset += sizeof(Record);
    }

    {
        int old_index = lbl_8064D7D8;
        Record* old_output = lbl_8064D8A0[old_index];
        fn_801FF5EC(&lbl_8063F020[old_index],
                    &lbl_8063F020[old_index ^ 1]);
        fn_801FF838(&lbl_8063F020[lbl_8064D7D8 ^ 1], arg);
        fn_801FF23C(header->count, header->records, old_output);
    }

    if (result == 1 && *(s16*)(lbl_8030F540 + 0x1D6) == -1) {
        fn_80133300();
    }
}
