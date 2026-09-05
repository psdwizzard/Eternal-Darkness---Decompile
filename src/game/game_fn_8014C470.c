typedef unsigned char u8;
typedef struct Resource {
    u8 pad0[0x29];
    u8 flags;
    u8 pad2A[3];
    u8 state;
    u8 pad2E[0x3E];
    void* owner;
} Resource;

extern int lbl_8064D18C;
extern void *fn_80156938();
extern Resource* fn_801FD6F4(void);
extern void* fn_80201ADC(void);
extern void *fn_80201BC8();
extern int fn_801FE25C(void*);
extern unsigned int fn_8015C910(void);
extern int fn_80047178(void);
extern int fn_8012FA54(void*, int);
extern int fn_8015E4E8(void);
extern int fn_8011FB4C(void*);
extern void fn_801FE110(void*);
extern int fn_801FE1EC(void*);
extern int fn_801FE52C(void*);
extern void fn_80156FF4(void*);

int fn_8014C470(void* object, void* unused, int active)
{
    void* runtime;
    Resource* resource;
    void* owner;
    int result = 0;

    if (active == 0)
        return 0;
    runtime = fn_80156938(object);
    resource = fn_801FD6F4();
    if (resource != 0) {
        if (fn_80201ADC() != 0) {
            owner = fn_80201BC8(fn_80201ADC());
        } else {
            owner = 0;
        }
        if (fn_801FE25C(runtime) != 0 && resource->owner != 0) {
            if (fn_8015C910() == 0 || !(resource->flags & 1)) {
                if ((fn_80047178() != 0 && fn_8012FA54(owner, 15) != 0) ||
                    !(resource->flags & 2)) {
                    if (fn_8015E4E8() == 0 || resource->state == 7) {
                        if (lbl_8064D18C == fn_8011FB4C(owner) ||
                            !(resource->flags & 0x10))
                            fn_801FE110(runtime);
                    }
                }
            }
        }
        if (fn_801FE1EC(runtime) != 0 || fn_801FE52C(runtime) != 0) {
            fn_80156FF4(object);
            result |= 4;
        }
    }
    return result;
}
