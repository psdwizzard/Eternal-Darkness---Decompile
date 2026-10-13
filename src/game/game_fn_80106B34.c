typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct DecoderComponent {
    u8* border;
    u8* interior;
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
} DecoderComponent;

/* The helper only needs the common image prefix. */
typedef struct ComponentInfo ComponentInfo;
typedef struct ImageInfo {
    ComponentInfo* components;
    u16 width;
    u16 height;
} ImageInfo;

typedef struct ImageHeader {
    ImageInfo info;
    u8 horizontal_sampling;
    u8 vertical_sampling;
} ImageHeader;

typedef struct WeightTree {
    u32 unused;
    int root;
    s16 zero[512];
    s16 one[512];
} WeightTree;

typedef struct WeightBits {
    u8* cursor;
    u32 unused04;
    u32 unused08;
    u8 byte;
    u8 mask;
    u8 padding[2];
    WeightTree* tree;
} WeightBits;

typedef struct ImageDecoder {
    DecoderComponent components[3];
    WeightTree trees[6];
    WeightBits coefficient_bits[3];
    WeightBits index_bits[3];
    WeightBits weight_bits[3];
    WeightBits control_bits[2];
    WeightBits offset_bits[2];
    u8 streams[0x30];
    WeightBits horizontal_bits[2];
    WeightBits vertical_bits[2];
    u16 horizontal_limit;
    u16 vertical_limit;
    u8 transposed;
    u8 workspace[0x3CD0 - 0x3261];
} ImageDecoder;

extern void fn_8010278C(ImageInfo* image, int component_index,
                       u8 horizontal, u8 vertical);

/* Set up component geometry, decoding trees, and padded block buffers. */
void fn_80106B34(register ImageHeader* image, register ImageDecoder* workspace)
{
    register ImageDecoder* decoder;
    register DecoderComponent* component;
    u8* next;
    u8* border;
    int i;
    int count;
    register int limit;
    register u32 height;
    register int transposed;
    register u32 width;
    register WeightTree* control_tree;
    register WeightTree* vertical_tree;
    register WeightTree* horizontal_tree;
    register WeightTree* weight_tree;
    register WeightTree* coefficient_tree;
    register WeightTree* offset_tree;

    /* ASM: addi preserves the retail argument-to-working-pointer copy;
     * MWCC generates mr for an ordinary C pointer assignment. */
    asm {
        addi decoder, workspace, 0
    }
    image->info.components = (ComponentInfo*)decoder->components;
    fn_8010278C(&image->info, 0, 1, 1);
    fn_8010278C(&image->info, 1, image->horizontal_sampling, image->vertical_sampling);
    fn_8010278C(&image->info, 2, image->horizontal_sampling, image->vertical_sampling);

    transposed = -1;
    width = image->info.width;
    height = image->info.height;
    /* ASM: subfc/subfze use carry for the orientation comparison;
     * this MWCC version emits a longer subtract/or/shift sequence in C. */
    asm {
        subfc height, height, width
        subfze transposed, transposed
    }
    decoder->transposed = transposed;
    if ((u8)transposed) {
        limit = 0x46;
        /* ASM: sth keeps the first limit store before loading the second
         * constant; MWCC otherwise schedules both loads before the stores. */
        asm { sth limit, 0x325c(decoder) }
        decoder->vertical_limit = 0x26;
    } else {
        limit = 0x26;
        /* ASM: sth keeps the first limit store before loading the second
         * constant; MWCC otherwise schedules both loads before the stores. */
        asm { sth limit, 0x325c(decoder) }
        decoder->vertical_limit = 0x46;
    }

    control_tree = &decoder->trees[3];
    /* ASM: stw fixes the first table-pointer store before the following
     * address calculations, which MWCC otherwise hoists across the store. */
    asm { stw control_tree, 0x31b0(decoder) }
    offset_tree = &decoder->trees[1];
    /* ASM: addi retains the address calculation before the next table store;
     * MWCC otherwise sinks this calculation past the store. */
    asm {
        addi coefficient_tree, decoder, 0xa8
    }
    decoder->control_bits[0].tree = control_tree;
    /* ASM: addi/addi retain the two table addresses before the next store;
     * MWCC's scheduler sinks these address calculations in C. */
    asm {
        addi weight_tree, decoder, 0x10b8
        addi horizontal_tree, decoder, 0x20c8
    }
    decoder->offset_bits[1].tree = offset_tree;
    /* ASM: addi/addi/stw retain the final table address, component copy,
     * and store order; MWCC reorders these and substitutes mr in C. */
    asm {
        addi vertical_tree, decoder, 0x28d0
        addi component, decoder, 0
        stw offset_tree, 0x31c4(decoder)
    }
    decoder->coefficient_bits[0].tree = decoder->coefficient_bits[1].tree =
        decoder->coefficient_bits[2].tree = coefficient_tree;
    decoder->index_bits[0].tree = decoder->index_bits[1].tree =
        decoder->index_bits[2].tree = offset_tree;
    decoder->weight_bits[0].tree = decoder->weight_bits[1].tree =
        decoder->weight_bits[2].tree = weight_tree;
    decoder->horizontal_bits[0].tree = decoder->horizontal_bits[1].tree = horizontal_tree;
    decoder->vertical_bits[0].tree = decoder->vertical_bits[1].tree = vertical_tree;

    next = (u8*)(decoder + 1);
    for (i = 0; i < 3; ++i, ++component) {
        component->border = next;
        component->interior = next + component->padded_width * 2 + 2;
        border = component->border;
        count = component->padded_width;
        next += count * component->padded_height * 2;
        /* The padded edges contain big-endian 0x7FFF values. */
        for (; count > 0; --count) {
            border[0] = 0x7F;
            border[1] = 0xFF;
            border += 2;
        }

        /* Bottom edge, filled backwards from the end of the buffer. */
        border = next;
        for (count = component->padded_width; count > 0; --count) {
            border -= 2;
            border[0] = 0x7F;
            border[1] = 0xFF;
        }

        /* Left and right edges exclude the two completed corner rows. */
        border = component->border + component->padded_width * 2;
        for (count = component->padded_height - 2; count > 0; --count) {
            border[0] = 0x7F;
            border[1] = 0xFF;
            border += component->padded_width * 2;
        }
        count = component->padded_height - 2;
        border = component->border + component->padded_width * 4 - 2;
        for (; count > 0; --count) {
            border[0] = 0x7F;
            border[1] = 0xFF;
            border += component->padded_width * 2;
        }
    }
}
