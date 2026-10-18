typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKMessageSend(TRKBuffer *);
extern int TRKTestForPacket(void);
extern TRKBuffer *TRKGetBuffer(int);
extern int TRKSetBufferPosition(TRKBuffer *, u32);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern void TRKProcessInput(int);
extern void TRKReleaseBuffer(int);

/* Send a request, dispatch incoming commands, and validate the reply. */
int TRKRequestSend(TRKBuffer *request, register int *reply_id, int minimum_length,
                int retries, int use_timeout)
{
    u8 command;
    u8 status;
    int error;
    TRKBuffer *reply;
    u32 polls;
    int attempts;
    int invalid;

    attempts = retries + 1;
    error = 0;
    invalid = 1;
    *reply_id = -1;
    for (; attempts != 0 && *reply_id == -1 && error == 0; attempts--) {
        error = TRKMessageSend(request);
        if (error == 0) {
            if (use_timeout)
                polls = 0;
            for (;;) {
                do {
                    *reply_id = TRKTestForPacket();
                } while (*reply_id == -1 &&
                         (!use_timeout || ++polls < 0x04C4B3ECU));
                if (*reply_id != -1) {
                    invalid = 0;
                    reply = TRKGetBuffer(*reply_id);
                    TRKSetBufferPosition(reply, 0);
                    error = TRKReadBuffer1_ui8(reply, &command);
                    if (error == 0 && command < 0x80) {
                        TRKProcessInput(*reply_id);
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
                    error = TRKReadBuffer1_ui8(reply, &status);
                if (error == 0 && invalid == 0 &&
                    (command != 0x80 || status != 0))
                    invalid = 1;
                if (error != 0 || invalid != 0) {
                    TRKReleaseBuffer(*reply_id);
                    *reply_id = -1;
                }
            }
        }
    }
    if (*reply_id == -1)
        error = 0x800;
    return error;
}
