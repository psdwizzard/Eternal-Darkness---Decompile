typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef float Mtx[3][4];

typedef struct Vertex {
    s16 x, y, z;
} Vertex;

static inline void TransformVertex(register Vertex* input, register Vertex* output,
    register float column_x, register float x_z,
    register float column_y, register float y_z,
    register float column_z, register float z_z,
    register float translation, register float translation_z)
{
    register float input_xy, input_z;
    register float result_xy, result_z;
    /* ASM: psq_l dequantizes using GQR6; ps_madds0 and ps_madds1
     * select operand lanes for fused arithmetic on both output lanes.
     * C cannot request these lane selectors or GQR-dependent loads. */
    asm {
        psq_l input_xy, 0(input), 0, 6
        psq_l input_z, 4(input), 1, 6
        ps_madds0 result_xy, column_x, input_xy, translation
        ps_madds0 result_z, x_z, input_xy, translation_z
        ps_madds1 result_xy, column_y, input_xy, result_xy
        ps_madds1 result_z, y_z, input_xy, result_z
    }
    /* ASM: ps_madds0 finishes the fused transform; psq_st quantizes
     * through GQR6, including hardware saturation unavailable in C. */
    asm {
        ps_madds0 result_xy, column_z, input_z, result_xy
        ps_madds0 result_z, z_z, input_z, result_z
        psq_st result_xy, 0(output), 0, 6
        psq_st result_z, 4(output), 1, 6
    }
}

/* The matrix is stored as four consecutive xyz columns. GQR6 supplies
 * the input scale and signed packed-output conversion. The index table
 * contains byte offsets, terminated by an offset beyond flags' limit. */
void fn_80125104(Mtx matrix, Vertex* source, Vertex* destination,
                 u32 flags, u16* offsets)
{
    register float* m = (float*)matrix;
    register float column_y;
    register float y_z = m[5];
    register float column_z;
    register float translation;
    register float translation_z = m[11];
    register float column_x;
    register float z_z = m[8];
    register float x_z = m[2];
    register Vertex* input = source;
    register Vertex* output;
    u32 limit = flags >> 16;
    u32 count = flags & 0xFFFF;
    u32 offset;
    s16* indices = (s16*)offsets - 1;

    /* ASM: psq_l loads both matrix lanes; C scalar loads cannot preserve
     * the paired-single representation required by the transform. */
    asm {
        psq_l column_x, 0(m), 0, 0
        psq_l column_y, 12(m), 0, 0
        psq_l column_z, 24(m), 0, 0
        psq_l translation, 36(m), 0, 0
    }

    do {
        offset = *++indices;
        if (offset > limit)
            return;
        output = (Vertex*)((u8*)destination + offset);

        TransformVertex(input++, output, column_x, x_z, column_y, y_z,
                        column_z, z_z, translation, translation_z);
        if (--count == 0)
            break;
        offset = *++indices;
        if (offset > limit)
            return;
        output = (Vertex*)((u8*)destination + offset);
        TransformVertex(input++, output, column_x, x_z, column_y, y_z,
                        column_z, z_z, translation, translation_z);
    } while (--count != 0);
}
