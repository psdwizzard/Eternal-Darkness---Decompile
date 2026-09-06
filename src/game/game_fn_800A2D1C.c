typedef unsigned char u8;

typedef struct Object800A2D1C {
    u8 pad000[0x160];
    void* handle;
} Object800A2D1C;

extern int fn_8017FEA4(void*);
extern void fn_8017FF14(void*, int);
extern void fn_80186A58(u8*, int);

void fn_800A2D1C(Object800A2D1C* object)
{
    if (object->handle != 0) {
        int runtime = fn_8017FEA4(object->handle);
        fn_8017FF14(object->handle, runtime + 0x3C);
        fn_80186A58(object->handle, 0);
        object->handle = 0;
    }
}
