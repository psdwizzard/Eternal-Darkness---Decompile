typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ComponentInfo {
    u16 unk00[4];
    u16 block_width;
    u16 block_height;
    u16 padded_width;
    u16 padded_height;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u32 unk18;
    u32 row_stride;
    u32 row_stride_plus_four;
    u32 unk24;
    u16 sample_width;
    u16 sample_height;
    u32 sample_count;
    u8 horizontal_shift;
    u8 vertical_shift;
    u8 horizontal_scale;
    u8 vertical_scale;
    u8 scale;
    u8 pad35[3];
} ComponentInfo;

typedef struct ImageInfo {
    ComponentInfo* components;
    u16 width;
    u16 height;
} ImageInfo;

void setHVQPlaneDesc(ImageInfo* image, int component_index, u8 horizontal,
                 u8 vertical)
{
    ComponentInfo* component = &image->components[component_index];
    int horizontal_shift;
    int vertical_shift;
    int padded_width;
    int row_stride;

    if (horizontal == 2) {
        horizontal_shift = 1;
    } else {
        horizontal_shift = 0;
    }
    component->horizontal_shift = horizontal_shift;
    component->sample_width = image->width >> component->horizontal_shift;
    if (vertical == 2) {
        vertical_shift = 1;
    } else {
        vertical_shift = 0;
    }
    component->vertical_shift = vertical_shift;
    component->sample_height = image->height >> component->vertical_shift;
    component->sample_count = component->sample_width * component->sample_height;
    component->horizontal_scale = 2 >> component->horizontal_shift;
    component->vertical_scale = 2 >> component->vertical_shift;
    component->scale = component->horizontal_scale * component->vertical_scale;
    component->block_width = image->width / (horizontal << 2);
    component->block_height = image->height / (vertical << 2);
    component->padded_width = component->block_width + 2;
    component->padded_height = component->block_height + 2;
    component->unk10 = 0;
    component->unk16 = 1;
    padded_width = component->padded_width;
    component->unk12 = padded_width;
    component->unk14 = padded_width + 1;
    component->unk18 = 0;
    component->unk24 = 4;
    row_stride = component->sample_width << 2;
    component->row_stride = row_stride;
    component->row_stride_plus_four = row_stride + 4;
}
