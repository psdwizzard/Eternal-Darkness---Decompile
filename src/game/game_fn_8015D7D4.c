extern unsigned char lbl_805E295C[];
extern unsigned char lbl_805FA1F0[];
extern unsigned char lbl_805FA210[];
extern unsigned char lbl_8064D130;
extern void fn_8015CDF0(void);
extern void fn_8015D670(void);
extern void fn_8015D6A0(void);
extern void fn_8020D1F0(void*, void*, int);
extern int fn_8020D318(void*, void*, int);
extern void fn_8021B730(void*, int, int, int, void*, void*, int, void*);
extern int fn_80213704(void*, void*, int, int, void*, int);

void fn_8015D7D4(void* output, void* file, int offset, unsigned int remaining,
                 unsigned char* buffers)
{
    int message;
    int buffer_index = 0;
    int chunk;
    unsigned char* next_buffer;

    while (fn_8020D318(lbl_805E295C, &message, 0)) {
    }
    fn_8020D1F0(lbl_805FA1F0, &lbl_8064D130, 2);

    if (remaining > 0x1000) {
        chunk = 0x1000;
        remaining -= 0x1000;
    } else {
        chunk = (remaining + 31) & ~31;
        remaining = 0;
    }
    fn_8015CDF0();
    while (!fn_80213704(file, buffers, chunk, offset, fn_8015D6A0, 2)) {
    }
    offset += chunk;

    while (remaining != 0) {
        fn_8020D318(lbl_805FA1F0, &message, 1);
        fn_8015CDF0();
        fn_8021B730(lbl_805FA210, 6, 0, 0,
                    buffers + buffer_index * 0x1000, output, chunk,
                    fn_8015D670);
        output = (char*)output + chunk;
        buffer_index ^= 1;
        if (remaining > 0x1000) {
            chunk = 0x1000;
            remaining -= 0x1000;
        } else {
            chunk = (remaining + 31) & ~31;
            remaining = 0;
        }
        next_buffer = buffers + buffer_index * 0x1000;
        while (!fn_80213704(file, next_buffer, chunk, offset,
                            fn_8015D6A0, 2)) {
        }
        offset += chunk;
        fn_8020D318(lbl_805E295C, &message, 1);
    }

    fn_8020D318(lbl_805FA1F0, &message, 1);
    fn_8021B730(lbl_805FA210, 6, 0, 0,
                buffers + buffer_index * 0x1000, output, chunk,
                fn_8015D670);
    fn_8020D318(lbl_805E295C, &message, 1);
}
