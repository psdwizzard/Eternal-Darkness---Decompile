extern unsigned char lbl_805E295C[];
extern unsigned char lbl_805FA1F0[];
extern unsigned char lbl_805FA210[];
extern unsigned char lbl_8064D130;
extern void fn_8015CDF0(void);
extern void fn_8015D670(void);
extern void fn_8015D6A0(void);
extern void OSInitMessageQueue(void*, void*, int);
extern int OSReceiveMessage(void*, void*, int);
extern void ARQPostRequest(void*, int, int, int, void*, void*, int, void*);
extern int DVDReadAsyncPrio(void*, void*, int, int, void*, int);

void fn_8015D7D4(void* output, void* file, int offset, unsigned int remaining,
                 unsigned char* buffers)
{
    int message;
    int buffer_index = 0;
    int chunk;
    unsigned char* next_buffer;

    while (OSReceiveMessage(lbl_805E295C, &message, 0)) {
    }
    OSInitMessageQueue(lbl_805FA1F0, &lbl_8064D130, 2);

    if (remaining > 0x1000) {
        chunk = 0x1000;
        remaining -= 0x1000;
    } else {
        chunk = (remaining + 31) & ~31;
        remaining = 0;
    }
    fn_8015CDF0();
    while (!DVDReadAsyncPrio(file, buffers, chunk, offset, fn_8015D6A0, 2)) {
    }
    offset += chunk;

    while (remaining != 0) {
        OSReceiveMessage(lbl_805FA1F0, &message, 1);
        fn_8015CDF0();
        ARQPostRequest(lbl_805FA210, 6, 0, 0,
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
        while (!DVDReadAsyncPrio(file, next_buffer, chunk, offset,
                            fn_8015D6A0, 2)) {
        }
        offset += chunk;
        OSReceiveMessage(lbl_805E295C, &message, 1);
    }

    OSReceiveMessage(lbl_805FA1F0, &message, 1);
    ARQPostRequest(lbl_805FA210, 6, 0, 0,
                buffers + buffer_index * 0x1000, output, chunk,
                fn_8015D670);
    OSReceiveMessage(lbl_805E295C, &message, 1);
}
