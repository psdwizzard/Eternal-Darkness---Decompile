typedef unsigned char u8;
typedef int s32;

typedef struct AudioRequest {
    s32 type;
    char source[0x50];
    u8* buffer;
    s32 arg;
} AudioRequest;

typedef struct AudioQueue {
    u8 state[0x20];
} AudioQueue;

extern AudioQueue lbl_806481D8;
extern s32 lbl_8064DC4C;

extern int fn_8020D318(void*, void**, int);
extern u8* fn_80236AF8(u8*, s32);
extern void fn_80237224(s32);

void fn_80236D60(void) {
    void* message;
    AudioRequest* request;

    for (;;) {
        register AudioQueue* queueAddress = &lbl_806481D8;
        register AudioQueue* queue;

        /* ASM: or (mr) keeps the retail register copy where C emits addi. */
        asm { or queue, queueAddress, queueAddress }
        fn_8020D318(queue, &message, 1);
        request = (AudioRequest*)message;
        switch (request->type) {
        case 3: {
            u8* buffer = request->buffer;
            lbl_8064DC4C = 0;
            fn_80236AF8(buffer, request->arg);
            fn_80237224((s32)request->source);
            break;
        }
        }
    }
}
