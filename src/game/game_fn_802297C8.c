typedef unsigned char u8;
typedef unsigned long u32;

extern void fn_80229294(u32 tev_stage, u32 ind_stage, u32 format,
                        u32 bias_sel, u32 matrix_sel, u32 wrap_s,
                        u32 wrap_t, u8 add_prev, u8 utc_lod, u32 alpha_sel);

/* Disable indirect texturing for this TEV stage (GXSetTevDirect). */
void fn_802297C8(u32 tev_stage)
{
    fn_80229294(tev_stage, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
