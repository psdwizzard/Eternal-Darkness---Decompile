typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ImageHeader {
    void* data;
    u16 width;
    u16 height;
    u8 horizontal_sampling;
    u8 vertical_sampling;
} ImageHeader;

void HVQM4InitSeqObj(ImageHeader* header, const u8* input)
{
    header->width = (input[0] << 8) | input[1];
    header->height = (input[2] << 8) | input[3];
    header->horizontal_sampling = input[4];
    header->vertical_sampling = input[5];
}
