/* MSL fflush */
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
} FileRecord;

enum { CLOSED_FILE = 0, DISK_FILE = 1 };
enum { READ_MODE = 1 };
enum { NEUTRAL = 0, WRITING = 1, READING = 2, REREADING = 3 };

int __flush_all(void); /* __flush_all */
unsigned int ftell(FileRecord *); /* ftell */
int __flush_buffer(FileRecord *, unsigned int *);

int fflush(FileRecord *file)
{
    unsigned int position;

    if (file == 0) {
        return __flush_all();
    }
    if (file->error || file->mode.file_kind == CLOSED_FILE) {
        return -1;
    }
    if (file->mode.io_mode == READ_MODE) {
        return 0;
    }
    if (file->state.io_state >= REREADING) {
        file->state.io_state = READING;
    }
    if (file->state.io_state == READING) {
        file->buffer_space = 0;
    }
    if (file->state.io_state != WRITING) {
        file->state.io_state = NEUTRAL;
        return 0;
    }
    if (file->mode.file_kind != DISK_FILE) {
        position = 0;
    } else {
        position = ftell(file);
    }
    if (__flush_buffer(file, 0)) {
        file->error = 1;
        file->buffer_space = 0;
        return -1;
    }
    file->state.io_state = NEUTRAL;
    file->position = position;
    file->buffer_space = 0;
    return 0;
}
