typedef int (*StreamCallback)(void* buffer, int count, int callback_arg);

extern int strncmp(const char*, const char*, unsigned long);
extern int fn_80146110(void*, void*, void*, int, int, unsigned char*);
extern const char lbl_8024EFE8[];

/* Check the stream signature before decoding into the supplied workspace. */
int fn_80147DD4(int size, StreamCallback read_callback, void* write_callback,
                int callback_arg, void* workspace)
{
    char signature[8];

    read_callback(signature, 8, callback_arg);
    if (strncmp(lbl_8024EFE8, signature, 8) == 0) {
        return fn_80146110(workspace, (void*)read_callback, write_callback,
                          callback_arg, size - 8,
                          (unsigned char*)workspace + 0x2AE0);
    }
    return -1;
}
