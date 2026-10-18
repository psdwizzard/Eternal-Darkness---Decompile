typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

typedef struct CPUType {
    u8 cpuMajor;
    u8 cpuMinor;
    u8 bigEndian;
    u8 defaultTypeSize;
    u8 fpTypeSize;
    u8 extended1TypeSize;
    u8 extended2TypeSize;
} CPUType;

extern void TRKResetBuffer(TRKBuffer *, u8);
extern int TRKMessageSend(TRKBuffer *);
extern int TRKTargetCPUType(CPUType *);

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

void TRKDoCPUType(TRKBuffer *buffer)
{
    CPUType cpuType;
    int result;
    int retry;

    if (buffer->length != 1) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 2);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        return;
    }

    TRKResetBuffer(buffer, 1);
    append(buffer, 0x80);
    append(buffer, 0);

    result = TRKTargetCPUType(&cpuType);
    if (result == 0) result = appendChecked(buffer, cpuType.cpuMajor);
    if (result == 0) result = appendChecked(buffer, cpuType.cpuMinor);
    if (result == 0) result = appendChecked(buffer, cpuType.bigEndian);
    if (result == 0) result = appendChecked(buffer, cpuType.defaultTypeSize);
    if (result == 0) result = appendChecked(buffer, cpuType.fpTypeSize);
    if (result == 0) result = appendChecked(buffer, cpuType.extended1TypeSize);
    if (result == 0) result = appendChecked(buffer, cpuType.extended2TypeSize);

    if (result != 0) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 3);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    } else {
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    }
}
