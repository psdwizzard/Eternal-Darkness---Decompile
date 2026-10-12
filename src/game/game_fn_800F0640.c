typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int fn_800EFC6C(TRKBuffer *, u32);
extern void fn_800EFC9C(TRKBuffer *, u8);
extern int fn_800EF86C(TRKBuffer *, u8 *);
extern int fn_800EF6EC(TRKBuffer *, u32 *);
extern int fn_800EF2A0(TRKBuffer *);
extern int TRKTargetStopped(void);
extern u32 fn_800F3EDC(void);
extern int fn_800F3EEC(u32, u32, int);
extern int fn_800F3F68(u32, int);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

static inline int reply(TRKBuffer *buffer, u8 status)
{
    int result;
    int retry;

    fn_800EFC9C(buffer, 1);
    append(buffer, 0x80);
    append(buffer, status);
    retry = 3;
    do {
        result = fn_800EF2A0(buffer);
        retry--;
        if (result == 0) break;
    } while (retry > 0);
    return result;
}

void fn_800F0640(TRKBuffer *buffer)
{
    u32 range_start;
    u32 range_end;
    u8 command;
    u8 options;
    u8 count;
    u32 pc;
    int result;

    if (buffer->length < 3) {
        reply(buffer, 2);
        return;
    }

    fn_800EFC6C(buffer, 0);
    result = fn_800EF86C(buffer, &command);
    if (result == 0) result = fn_800EF86C(buffer, &options);

    switch (options) {
    case 0:
    case 0x10:
        if (result == 0) result = fn_800EF86C(buffer, &count);
        if (count < 1) {
            reply(buffer, 0x11);
            return;
        }
        break;
    case 1:
    case 0x11:
        if (buffer->length != 10) {
            reply(buffer, 2);
            return;
        }
        if (result == 0) result = fn_800EF6EC(buffer, &range_start);
        if (result == 0) result = fn_800EF6EC(buffer, &range_end);
        pc = fn_800F3EDC();
        if (pc < range_start || pc > range_end) {
            reply(buffer, 0x11);
            return;
        }
        break;
    default:
        reply(buffer, 0x12);
        return;
    }

    if (!TRKTargetStopped()) {
        reply(buffer, 0x16);
        return;
    }

    result = reply(buffer, 0);
    if (result == 0) {
        switch (options) {
        case 0:
        case 0x10:
            fn_800F3F68(count, options == 0x10);
            break;
        case 1:
        case 0x11:
            fn_800F3EEC(range_start, range_end, options == 0x11);
            break;
        }
    }
}
