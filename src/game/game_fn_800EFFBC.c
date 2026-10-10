typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex;
    u32 in_use;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

typedef struct TRKFramingState {
    int buffer_id;
    TRKBuffer *buffer;
    u8 state;
    u8 pad9[3];
    int is_escape;
    u8 fcs;
} TRKFramingState;

extern TRKFramingState lbl_80329FC4;
extern int fn_800F555C(u8 *);
extern int fn_800EFD6C(int *, TRKBuffer **);
extern void fn_800EFCDC(int);
extern void fn_800F2B28(TRKBuffer *, int, int);

static inline void TRKDiscardFrame(void)
{
    if (lbl_80329FC4.buffer_id != -1) {
        fn_800EFCDC(lbl_80329FC4.buffer_id);
        lbl_80329FC4.buffer_id = -1;
    }
    lbl_80329FC4.buffer = 0;
    lbl_80329FC4.state = 0;
}

static inline int TRKFinishFrame(TRKBuffer *buffer)
{
    if (buffer->length < 2) {
        fn_800F2B28(buffer, 0xFF, 2);
        TRKDiscardFrame();
        return 0;
    }
    buffer->position = 0;
    buffer->length--;
    return 1;
}

static inline int TRKAppendByte(TRKBuffer *buffer, u8 c)
{
    if (buffer->position >= 0x880) {
        return 0x301;
    }
    buffer->data[buffer->position++] = c;
    buffer->length++;
    return 0;
}

int fn_800EFFBC(void)
{
    int err = 0;
    int result;
    signed char c;

    for (result = fn_800F555C((u8 *)&c); result == 0 && err == 0; result = fn_800F555C((u8 *)&c)) {
        if (lbl_80329FC4.state != 2) {
            lbl_80329FC4.is_escape = 0;
        }
        switch (lbl_80329FC4.state) {
        case 0:
            if ((int)c == 0x7E) {
                err = fn_800EFD6C(&lbl_80329FC4.buffer_id, &lbl_80329FC4.buffer);
                lbl_80329FC4.fcs = 0;
                lbl_80329FC4.state = 1;
            }
            break;
        case 1:
            if ((int)c == 0x7E) {
                break;
            }
            lbl_80329FC4.state = 2;
        case 2:
            if (c == 0x7E) {
                if (lbl_80329FC4.is_escape) {
                    fn_800F2B28(lbl_80329FC4.buffer, 0xFF, 4);
                    TRKDiscardFrame();
                    break;
                }
                if (TRKFinishFrame(lbl_80329FC4.buffer)) {
                    int id = lbl_80329FC4.buffer_id;
                    lbl_80329FC4.buffer_id = -1;
                    lbl_80329FC4.buffer = 0;
                    lbl_80329FC4.state = 0;
                    return id;
                }
                lbl_80329FC4.state = 0;
                break;
            }
            if (lbl_80329FC4.is_escape) {
                c ^= 0x20;
                lbl_80329FC4.is_escape = 0;
            } else if (c == 0x7D) {
                lbl_80329FC4.is_escape = 1;
                break;
            }
            err = TRKAppendByte(lbl_80329FC4.buffer, c);
            lbl_80329FC4.fcs += c;
            break;
        case 3:
            if ((int)c == 0x7E) {
                TRKDiscardFrame();
            }
            break;
        }
    }
    return -1;
}
