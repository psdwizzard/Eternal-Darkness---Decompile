typedef unsigned int u32;

typedef struct FSTEntry {
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
} FSTEntry;

extern FSTEntry *FstStart_8064D9E4;
extern char *FstStringStart_8064D9E8;

/* Copy a path component, without adding a terminator. */
static inline u32 copyComponent(char *dest, const char *src, u32 length)
{
    u32 remaining = length;
    while (remaining != 0 && *src != '\0') {
        *dest++ = *src++;
        remaining--;
    }
    return length - remaining;
}

u32 entryToPath(u32 entry, char *path, u32 maxLength)
{
    char *name;
    u32 length;

    if (entry == 0) {
        return 0;
    }
    name = FstStringStart_8064D9E8 +
           (FstStart_8064D9E4[entry].isDirAndStringOff & 0x00FFFFFF);
    length = entryToPath(FstStart_8064D9E4[entry].parentOrPosition,
                         path, maxLength);
    if (length == maxLength) {
        return length;
    }
    path[length++] = '/';
    length += copyComponent(path + length, name, maxLength - length);
    return length;
}
