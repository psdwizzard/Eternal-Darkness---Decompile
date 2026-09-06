typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int fn_800EFC6C(TRKBuffer *, int);
extern int fn_800EF86C(TRKBuffer *, u8 *);
extern int fn_800EF6EC(TRKBuffer *, u32 *);
extern int fn_800EFC9C(TRKBuffer *, int);
extern int fn_800EF2A0(TRKBuffer *);
extern int fn_800F3C98(u8, u32, u32);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

void fn_800F0CC4(TRKBuffer *buffer)
{
    u32 start;
    u32 end;
    u8 message_command;
    u8 options;
    int result;
    int retry;

    if (buffer->length != 10) {
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

    fn_800EFC6C(buffer, 0);
    result = fn_800EF86C(buffer, &message_command);
    if (result == 0) result = fn_800EF86C(buffer, &options);
    if (result == 0) result = fn_800EF6EC(buffer, &start);
    if (result == 0) result = fn_800EF6EC(buffer, &end);

    if (start > end) {
        fn_800EFC9C(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0x13);
        retry = 3;
        do {
            result = fn_800EF2A0(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        return;
    }

    if (result == 0)
        result = fn_800F3C98(options, start, end);

    if (result == 0) {
        fn_800EFC9C(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0);
    }

    if (result != 0) {
        switch (result) {
        case 0x703:
            result = 0x12;
            break;
        default:
            result = 3;
            break;
        }
        fn_800EFC9C(buffer, 1);
        append(buffer, 0x80);
        append(buffer, (u8)result);
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
