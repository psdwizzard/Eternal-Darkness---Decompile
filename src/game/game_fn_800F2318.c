typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern void fn_800EFC9C(TRKBuffer *, u8);
extern int fn_800EF2A0(TRKBuffer *);
extern int fn_800EFBC8(TRKBuffer *, const u8 *, u32);
extern int fn_800F4420(unsigned char *);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

static inline int appendChecked(TRKBuffer *buffer, u8 value)
{
    if (buffer->position >= 0x880)
        return 0x301;
    buffer->data[buffer->position++] = value;
    buffer->length++;
    return 0;
}

void fn_800F2318(TRKBuffer *buffer)
{
    unsigned char state[32];
    int result;
    int retry;

    if (buffer->length != 1) {
        fn_800EFC9C(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 2);
        retry = 3;
        do {
            result = fn_800EF2A0(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        return;
    }

    fn_800EFC9C(buffer, 1);
    append(buffer, 0x80);
    append(buffer, 0);

    result = fn_800F4420(state);
    if (result == 0)
        result = fn_800EFBC8(buffer, state, sizeof(state));
    if (result == 0)
        result = appendChecked(buffer, 2);

    if (result != 0) {
        fn_800EFC9C(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 3);
        retry = 3;
        do {
            result = fn_800EF2A0(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    } else {
        retry = 3;
        do {
            result = fn_800EF2A0(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    }
}
