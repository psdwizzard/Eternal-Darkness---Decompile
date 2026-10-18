typedef unsigned short u16;

typedef struct FileRecord {
    char pad0[4];
    u16 mode;
    char pad6[0x46];
    struct FileRecord *next;
} FileRecord;

extern FileRecord __files[];
extern int fflush(FileRecord *);

int __flush_all(void)
{
    int result = 0;
    FileRecord *file = __files;

    while (file != 0) {
        if (((file->mode >> 6) & 7) != 0 && fflush(file) != 0) {
            result = -1;
        }
        file = file->next;
    }
    return result;
}
