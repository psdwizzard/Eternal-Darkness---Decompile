typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int fn_800EF2A0(TRKBuffer *);
extern int fn_800EFFBC(void);
extern TRKBuffer *TRKGetBuffer(int);
extern int fn_800EFC6C(TRKBuffer *, u32);
extern int fn_800EF86C(TRKBuffer *, u8 *);
extern void fn_800EFED4(int);
extern void fn_800EFCDC(int);

/* Send a request, dispatch incoming commands, and validate the reply. */
int fn_800F3054(TRKBuffer *request, register int *reply_id, int minimum_length,
                int retries, int use_timeout)
{
    u8 command;
    u8 status;
    int error;
    TRKBuffer *reply;
    u32 polls;
    int attempts;
    int invalid;
    register int no_buffer;

    attempts = retries + 1;
    error = 0;
    invalid = 1;
    no_buffer = -1;
    /* ASM: stw prevents MWCC from moving this store ahead of the local
     * register initializations, as it does for the equivalent C assignment. */
    asm {
        stw no_buffer, 0(reply_id)
    }
    for (; attempts != 0 && *reply_id == -1 && error == 0; attempts--) {
        error = fn_800EF2A0(request);
        if (error == 0) {
            if (use_timeout)
                polls = 0;
            for (;;) {
                do {
                    *reply_id = fn_800EFFBC();
                } while (*reply_id == -1 &&
                         (!use_timeout || ++polls < 0x04C4B3ECU));
                if (*reply_id != -1) {
                    invalid = 0;
                    reply = TRKGetBuffer(*reply_id);
                    fn_800EFC6C(reply, 0);
                    error = fn_800EF86C(reply, &command);
                    if (error == 0 && command < 0x80) {
                        fn_800EFED4(*reply_id);
                        *reply_id = -1;
                        continue;
                    }
                }
                break;
            }
            if (*reply_id != -1) {
                if (reply->length < (u32)minimum_length)
                    invalid = 1;
                if (error == 0 && invalid == 0)
                    error = fn_800EF86C(reply, &status);
                if (error == 0 && invalid == 0 &&
                    (command != 0x80 || status != 0))
                    invalid = 1;
                if (error != 0 || invalid != 0) {
                    fn_800EFCDC(*reply_id);
                    *reply_id = -1;
                }
            }
        }
    }
    if (*reply_id == -1)
        error = 0x800;
    return error;
}
