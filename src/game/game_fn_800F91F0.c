/* MSL fclose. */
struct FileRecord;

typedef struct CloseFileRecord {
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
        unsigned char free_buffer : 1;
        unsigned char reserved : 4;
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
    unsigned char reserved30[4];
    unsigned int buffer_position;
    unsigned char reserved38[0xC];
    int (*close)(int);
} CloseFileRecord;

int fflush(struct FileRecord *file);
void free(void *ptr);

int fclose(CloseFileRecord *file)
{
    int flush_result;
    int close_result;

    if (file == 0) {
        return -1;
    }
    if (file->mode.file_kind == 0) {
        return 0;
    }
    flush_result = fflush((struct FileRecord *)file);
    close_result = file->close(file->handle);
    file->mode.file_kind = 0;
    file->handle = 0;
    if (file->state.free_buffer) {
        free(file->buffer);
    }
    return (flush_result || close_result) ? -1 : 0;
}
