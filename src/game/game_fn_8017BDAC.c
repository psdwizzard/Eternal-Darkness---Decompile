typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long long s64;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
    u8 pad_0D[0x23];
    u32 flags;
    int unk_34;
    s64 time;
    u16 attempts;
    u16 pad_42;
    void (*callback)(struct Request*);
} Request;

extern s64 OSGetTime(void);
extern s64 fn_800F5ECC(s64, s64);
extern int CARDGetResultCode(u8);
extern int fn_8017BD78(Request*);
extern void fn_8017AF78(void);
extern void fn_8017B440(u8);
extern void fn_8017BA54(void);
extern void fn_8017C108(Request*);
extern void fn_8017C1C8(Request*);
extern void fn_8017C2B0(Request*);
extern void fn_8017C32C(Request*);
extern void fn_8017C3C0(Request*);
extern void fn_8017C47C(Request*);
extern void fn_8017C584(Request*);
extern void fn_8017C67C(Request*);
extern void fn_8017C724(Request*);
extern void fn_8017C810(Request*);
extern void fn_8017C8E0(Request*);
extern void fn_8017C964(Request*);
extern void fn_8017CA0C(Request*);
extern void fn_8017CB20(Request*);
extern void fn_8017CBCC(Request*);

int fn_8017BDAC(Request* request)
{
    switch (request->state) {
    case 3:
        if (fn_800F5ECC(OSGetTime() - request->time,
                (*(volatile u32*)0x800000F8 >> 2) / 1000) > 800) {
            request->flags &= 0xFFFFFFFEU;
            request->state = 0;
        }
        break;
    case 0:
        switch (request->kind) {
        case 1: fn_8017C108(request); break;
        case 2: fn_8017C1C8(request); break;
        case 3: fn_8017C2B0(request); break;
        case 4: fn_8017C32C(request); break;
        case 5: fn_8017C3C0(request); break;
        case 6: fn_8017C47C(request); break;
        case 7: fn_8017C584(request); break;
        case 8: fn_8017C67C(request); break;
        }
        switch (request->state) {
        case 0:
            request->attempts++;
            if (request->attempts >= fn_8017BD78(request)) {
                if (request->kind == 2) fn_8017AF78();
                if (request->callback != 0) request->callback(request);
                return 1;
            }
            break;
        case 1:
            if (request->kind != 1) {
                fn_8017B440(request->value);
                fn_8017BA54();
            }
            break;
        case 2:
            if (request->flags & 2) {
                request->flags &= 0xFFFFFFFDU;
                request->state = 4;
                request->time = OSGetTime();
            } else {
                if (request->callback != 0) request->callback(request);
                return 1;
            }
            break;
        }
        break;
    case 1:
        request->result = CARDGetResultCode(request->value);
        switch (request->kind) {
        case 1: fn_8017C724(request); break;
        case 3: fn_8017C810(request); break;
        case 4: fn_8017C8E0(request); break;
        case 5: fn_8017C964(request); break;
        case 6: fn_8017CA0C(request); break;
        case 7: fn_8017CB20(request); break;
        case 8: fn_8017CBCC(request); break;
        }
        if (request->state == 2) {
            if (request->flags & 2) {
                request->flags &= 0xFFFFFFFDU;
                request->state = 4;
                request->time = OSGetTime();
            } else {
                if (request->callback != 0) request->callback(request);
                return 1;
            }
        }
        break;
    case 4:
        if (fn_800F5ECC(OSGetTime() - request->time,
                (*(volatile u32*)0x800000F8 >> 2) / 1000) > 600) {
            if (request->callback != 0) request->callback(request);
            return 1;
        }
        break;
    }
    return 0;
}
