typedef unsigned char u8;
typedef void (*Callback)(void*, void*);

int fn_80129C2C(void* owner, u8* entry, int value, int flags, int kind)
{
    int reject;
    unsigned short old_kind;
    int result = 0;
    if ((*(unsigned short*)(entry + 0xFC) & 4) != 0) {
        int same = **(int**)(entry + 0xB8) == value;
        old_kind = *(unsigned short*)(entry + 0xFA);
        reject = 0;
        if ((unsigned short)kind > old_kind ||
            (same && (flags & 0x10) != 0) ||
            ((unsigned short)kind == old_kind && !same && (flags & 0x20) != 0)) {
            reject = 1;
        }
        if (reject) {
            Callback callback = *(Callback*)(entry + 0xA8);
            if (callback != 0) {
                *(Callback*)(entry + 0xA8) = 0;
                callback(owner, *(void**)(entry + 0xAC));
            }
            result = 1;
        }
    } else {
        result = 1;
    }
    return result;
}
