typedef struct FileRecord {
    int handle;
    struct {
        unsigned short open_mode : 2;
        unsigned short io_mode : 3;
        unsigned short buffer_mode : 2;
        unsigned short file_kind : 3;
        unsigned short orientation : 2;
        unsigned short binary_io : 1;
        unsigned short reserved : 3;
    } mode;
    unsigned short reserved06;
    struct {
        unsigned char io_state : 3;
        unsigned char reserved : 5;
    } state;
    unsigned char eof;
    unsigned char error;
    unsigned char reserved0B[0xD];
    unsigned int position;
    unsigned char *buffer;
    unsigned int buffer_size;
    unsigned char *buffer_ptr;
    unsigned int buffer_space;
    unsigned int alignment_mask;
    char reserved30[4];
    unsigned int buffer_position;
    char reserved38[8];
    int (*write)(int, unsigned char *, unsigned int *, void *);
    char reserved44[4];
    void *ref;
} FileRecord;

int fwide(FileRecord *, int);
int fseek(FileRecord *, long, int);
void __stdio_atexit(void);
void __prep_buffer(FileRecord *);
int __flush_buffer(FileRecord *, unsigned int *);
void *__memrchr(const void *, int, unsigned long);
void *memcpy(void *, const void *, unsigned long);

unsigned long __fwrite(const void *ptr, unsigned long size,
                      unsigned long count, FileRecord *file)
{
    unsigned char *next;
    unsigned long remaining;
    unsigned long written;
    unsigned int chunk;
    unsigned char *newline;
    int buffered;

    if (fwide(file, 0) == 0)
        fwide(file, -1);
    remaining = size * count;
    if (!remaining || file->error || !file->mode.file_kind)
        return 0;
    if (file->mode.file_kind == 2)
        __stdio_atexit();

    buffered = !file->mode.binary_io || file->mode.buffer_mode == 2 ||
               file->mode.buffer_mode == 1;
    if (!file->state.io_state && (file->mode.io_mode & 2)) {
        if ((file->mode.io_mode & 4) && fseek(file, 0, 2))
            return 0;
        file->state.io_state = 1;
        __prep_buffer(file);
    }
    if (file->state.io_state != 1) {
        file->error = 1;
        file->buffer_space = 0;
        return 0;
    }

    next = (unsigned char *)ptr;
    written = 0;
    if (remaining && (file->buffer_ptr != file->buffer || buffered)) {
        file->buffer_space = file->buffer_size - (file->buffer_ptr - file->buffer);
        do {
            newline = 0;
            chunk = file->buffer_space;
            if (chunk > remaining)
                chunk = remaining;
            if (file->mode.buffer_mode == 1 && chunk) {
                newline = __memrchr(next, '\n', chunk);
                if (newline)
                    chunk = newline + 1 - next;
            }
            if (chunk) {
                memcpy(file->buffer_ptr, next, chunk);
                next += chunk;
                written += chunk;
                remaining -= chunk;
                file->buffer_ptr += chunk;
                file->buffer_space -= chunk;
            }
            if (!file->buffer_space || newline || !file->mode.buffer_mode) {
                if (__flush_buffer(file, 0)) {
                    file->error = 1;
                    file->buffer_space = 0;
                    remaining = 0;
                    break;
                }
            }
        } while (remaining && buffered);
    }
    /* Write binary, unbuffered data directly through the flush callback. */
    if (remaining && !buffered) {
        unsigned char *saved_buffer = file->buffer;
        unsigned int saved_size = file->buffer_size;
        file->buffer = next;
        file->buffer_size = remaining;
        file->buffer_ptr = next + remaining;
        if (__flush_buffer(file, &chunk)) {
            file->error = 1;
            file->buffer_space = 0;
        }
        written += chunk;
        file->buffer = saved_buffer;
        file->buffer_size = saved_size;
        __prep_buffer(file);
        file->buffer_space = 0;
    }
    if (file->mode.buffer_mode != 2)
        file->buffer_space = 0;
    return (written + size - 1) / size;
}
