typedef unsigned char u8;
typedef unsigned long u32;

extern void fn_80229294(u32 tev_stage, u32 ind_stage, u32 format,
                        u32 bias_sel, u32 matrix_sel, u32 wrap_s,
                        u32 wrap_t, u8 add_prev, u8 utc_lod, u32 alpha_sel);

/* Configure indirect texturing with optional bias and zero wrapping. */
void fn_80229810(u32 tev_stage, u32 ind_stage, u8 bias, u8 wrap,
                 u32 matrix_sel)
{
    u32 wrap_sel = wrap ? 6 : 0;
    u32 bias_sel;

    if (bias) {
        bias_sel = 7;
    } else {
        bias_sel = 0;
    }

    fn_80229294(tev_stage, ind_stage, 0, bias_sel, matrix_sel,
                wrap_sel, wrap_sel, 0, 0, 0);
}
