typedef unsigned char u8;
typedef unsigned int u32;

#pragma use_lmw_stmw on

extern void DCFlushRange(void*, u32);

u32 fn_8015CBB0(const u8* source, u32 source_size, u8* destination)
{
    u8 stack[32];
    u8 prefix[256];
    u8 suffix[256];
    u8* output = destination;
    u32 consumed = 0;
    u32 output_size = 0;

    while (consumed < source_size) {
        int width = *source++;
        int next_code;
        int i;

        consumed++;
        for (i = 0; i < 256; i++)
            prefix[i] = i;

        next_code = 0;
        for (;;) {
            if (width > 127) {
                next_code = width + next_code;
                width = 0;
                next_code -= 127;
            }
            if (next_code == 256)
                break;

            for (i = 0; i <= width; i++) {
                prefix[next_code] = *source++;
                consumed++;
                if (next_code != prefix[next_code]) {
                    suffix[next_code] = *source++;
                    consumed++;
                }
                next_code++;
            }
            if (next_code == 256)
                break;
            width = *source++;
            consumed++;
        }

        {
            int value;
            int stack_size;
            int count;

            count = ((u32)source[0] << 24) >> 16;
            count += source[1];
            source += 2;
            consumed += 2;
            stack_size = 0;
            for (;;) {
                int code;

                if (stack_size != 0) {
                    code = stack[--stack_size];
                } else {
                    if (count-- == 0)
                        break;
                    code = *source++;
                    consumed++;
                }

                value = prefix[code];
                if (code == value) {
                    *output++ = code;
                    output_size++;
                } else {
                    stack[stack_size++] = suffix[code];
                    stack[stack_size++] = value;
                }
            }
        }
    }

    DCFlushRange(destination, output_size);
    return output_size;
}
