typedef unsigned char u8;
typedef signed char s8;

typedef struct EventRequest {
    u8 pad_00[8];
    int status;
    u8 value;
} EventRequest;

typedef struct State {
    unsigned int type;
    u8 base[0x1AC];
    u8 order[6];
    u8 pad[2];
} State;

extern int fn_800B6908(void);
extern void fn_800B25AC(void);
extern int fn_800B1944(void);
extern void fn_800BBC40(State *);
extern void fn_800B6960(int, int);
extern void fn_800B35AC(int, int, int);
extern void fn_800B933C(void);
extern void fn_800B6024(int, int);
extern void fn_800BBF6C(void *, void *);
extern void fn_8017B864(int);
extern void fn_8017B914(int);
extern void fn_800B261C(void *);
extern void fn_800B2624(int, int, const char *, int, int);
extern void fn_800B566C(EventRequest *);

extern State lbl_80320738;
extern State lbl_80320978;
extern const char lbl_80247434[];
extern s8 lbl_8064CA30;
extern s8 lbl_8064CA31;
extern int lbl_8064CA60;
extern int lbl_8064CA64;

void fn_800B52C0(EventRequest *request)
{
    fn_800B6908();
    fn_800B25AC();
    switch (fn_800B1944()) {
    case 0:
        if (request->status == 0) {
            fn_800BBC40(&lbl_80320738);
            fn_800B6960(0, 1);
            fn_800B35AC(request->value, 0, 0);
            lbl_8064CA30 = 3;
        } else {
            if ((s8)lbl_8064CA31 != 0) {
                fn_800B933C();
                lbl_8064CA31 = 0;
                lbl_8064CA30 = 1;
            }
            fn_800B6024(request->value, request->status);
            lbl_8064CA60 = 20;
        }
        break;
    case 1:
    case 2:
    case 3:
        if (request->status == 0) {
            fn_800BBC40(&lbl_80320978);
            fn_800BBF6C((void *)(unsigned int)request->value, &lbl_80320978);
            fn_8017B864(0x2000);
            fn_8017B914(0);
            fn_800B261C(0);
            lbl_8064CA31 += 1;
            lbl_8064CA64 = 1;
            lbl_8064CA60 = 0;
            fn_800B2624(6, request->value, lbl_80247434, 2, (int)&fn_800B566C);
        } else {
            if ((s8)lbl_8064CA31 != 0) {
                fn_800B933C();
                lbl_8064CA31 = 0;
                lbl_8064CA30 = 1;
            }
            fn_800B6024(request->value, request->status);
            lbl_8064CA60 = 20;
        }
        break;
    }
}
