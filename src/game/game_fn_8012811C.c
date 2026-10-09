typedef struct VertexData {
    char data[0xE];
    signed char active;
    char pad_F;
} VertexData;

typedef struct VertexAttribute {
    unsigned int words[4];
} VertexAttribute;

void fn_8012811C(register VertexData* input, register VertexAttribute* output)
{
    register float first;
    register float second;

    /* ASM: psq_l/psq_lu/psq_st/psq_stu convert four components using GQR7's
     * quantization settings; C cannot express paired-single quantized transfers. */
    asm {
        psq_l first, 0(input), 0, 7
        psq_lu second, 4(input), 0, 7
        psq_st first, 0(output), 0, 0
        psq_stu second, 8(output), 0, 0
    }
}
