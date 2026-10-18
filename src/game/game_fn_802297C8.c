typedef unsigned char u8;
typedef unsigned long u32;

extern void GXSetTevIndirect(u32 tev_stage, u32 ind_stage, u32 format,
                        u32 bias_sel, u32 matrix_sel, u32 wrap_s,
                        u32 wrap_t, u8 add_prev, u8 utc_lod, u32 alpha_sel);

/* Disable indirect texturing for this TEV stage (GXSetTevDirect). */
void GXSetTevDirect(u32 tev_stage)
{
    GXSetTevIndirect(tev_stage, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
