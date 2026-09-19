typedef unsigned char u8;
typedef unsigned int u32;

typedef struct BitStream {
    void* source;
    u32 remaining;
    u32 total;
    u8 data[0x24];
    void* destination;
    u32 pad34;
    u32 mode;
    u32 start;
    u32 end;
    u32 limit;
    void* reader;
} BitStream;

extern char lbl_8024F038[];
extern void fn_80158E7C(int);
extern void fn_80158E84(int);
extern int fn_8020D318(void*, void*, int);
extern void fn_80155BB0(char*, char*, ...);
extern void* memset(void*, int, u32);
extern void fn_8015B628(BitStream*);
extern int fn_8015B5C8(BitStream*);
extern void DCFlushRange(void*, u32);

int fn_8015B274(void* source, void* destination, u8* output, int unused,
                u32 start, u32 limit, void* reader, int mode)
{
    u32 scratch;
    u8 expansion[0x20];
    BitStream stream;
    u8 first[0x100];
    u8 second[0x100];
    u8* out = output;
    char* strings = lbl_8024F038;
    u32 written = 0;
    int code;
    int index;
    int count;
    int depth;
    int value;

    fn_80158E7C(3);
    if (fn_8020D318(reader, &scratch, 0) != 0) {
        fn_80155BB0(strings + 0xb0, strings + 0xc8);
    }

    memset(&stream, 0, sizeof(stream));
    stream.total = 0;
    stream.source = source;
    stream.destination = destination;
    stream.remaining = 0;
    stream.mode = mode;
    stream.limit = limit;
    stream.start = start;
    stream.end = start + limit;
    stream.reader = reader;
    fn_8015B628(&stream);

    if (mode == 0) {
        for (count = 0; count < 0x40; count++) {
            *out++ = fn_8015B5C8(&stream);
        }
    } else if (mode == 1) {
        for (count = 0; count < 4; count++) {
            *out++ = fn_8015B5C8(&stream);
            written++;
        }
        if (*(u32*)output != 0x04030201) {
            fn_80158E84(5);
            fn_80155BB0(strings + 0xb0, strings + 0xe8,
                        *(u32*)output, 0x04030201);
        }
        out = output;
    }

    do {
        code = (u8)fn_8015B5C8(&stream);
        for (index = 0; index < 0x100; index++) {
            first[index] = index;
        }

        index = 0;
        for (;;) {
            if (code > 0x7f) {
                index += code - 0x7f;
                code = 0;
            }
            if (index == 0x100) {
                break;
            }
            for (count = 0; count <= code; count++, index++) {
                if (index >= 0x100 && mode == 1) {
                    fn_80158E84(3);
                }
                first[index] = fn_8015B5C8(&stream);
                if (index != first[index]) {
                    second[index] = fn_8015B5C8(&stream);
                }
            }
            if (index == 0x100) {
                break;
            }
            code = (u8)fn_8015B5C8(&stream);
        }

        count = (u8)fn_8015B5C8(&stream) << 8;
        count += (u8)fn_8015B5C8(&stream);
        depth = 0;
        for (;;) {
            if (depth != 0) {
                value = expansion[--depth];
            } else {
                if (count-- == 0) {
                    break;
                }
                value = (u8)fn_8015B5C8(&stream);
            }
            if (value == first[value]) {
                *out++ = value;
                written++;
            } else {
                expansion[depth++] = second[value];
                expansion[depth++] = first[value];
            }
        }
    } while (stream.source != 0 || stream.remaining != 0);

    DCFlushRange(output, written);
    return written;
}
