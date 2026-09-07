typedef struct {
    unsigned char pad[0x68];
    void* object;
} Data;

extern unsigned char fn_80157AB8(void*);

void fn_801A7934(Data* data) { fn_80157AB8(data->object); }
