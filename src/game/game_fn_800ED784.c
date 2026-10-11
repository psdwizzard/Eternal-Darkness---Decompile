/* Dequantizes a fixed-point s16 (GQR5 scale) into a float. */
float fn_800ED784(register short* source, register float* destination)
{
    register float value;

    /* ASM: psq_l with W=1 and GQR5 performs the hardware s16 dequantize;
     * C has no construct that makes MWCC emit a paired-single quantized load. */
    asm { psq_l value, 0(source), 1, 5 }
    *destination = value;
    return value;
}
