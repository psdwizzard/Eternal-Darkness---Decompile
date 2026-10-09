typedef unsigned char u8;
typedef unsigned int u32;

extern float lbl_80252F2C[];
extern float lbl_80253148[];
extern const float lbl_80650F8C;
extern const float lbl_80650F88;
extern const float lbl_80650F90;
extern const float lbl_80650FA0;
extern const float lbl_80650FA4;
extern const float lbl_80650FA8;
extern const float lbl_80650FAC;
extern long long fn_800F6318(double);
extern float fn_800F6264(long long);
extern u32 fn_800F5C54(double);

typedef struct PanInfo {
    u32 pan_i, pan_im, span_i, span_im, rpan_i, rpan_im;
    float pan_f, pan_fm, span_f, span_fm, rpan_f, rpan_fm;
} PanInfo;

static inline float wrap_unit(float value, float one)
{
    float product;
    float quotient;
    float absolute_one = __fabsf(one);
    float absolute_value = __fabsf(value);

    if (absolute_one > absolute_value) {
        return value;
    }
    quotient = value / one;
    product = one * fn_800F6264(fn_800F6318(quotient));
    return value - product;
}

/* Round the interpolation products separately to preserve the retail
 * multiply/add sequence instead of forming fused multiply-adds. */
static inline void calc_bus(float* fixed_table, float* volume_table,
                            float** upper_band, int initialize, float* output,
                            float vol, PanInfo* pi)
{
    float fraction, sample;
    u32 index;
    float scale = lbl_80650F88;

    index = fn_800F5C54(scale * vol);
    if (initialize) {
        *upper_band = fixed_table + 130;
    }
    fraction = (float)(scale * vol) - index;
    {
        float lo = volume_table[index];
        float inverse = 1.0f - fraction;
        float hi = volume_table[index + 1];

        sample = (float)(inverse * lo) + (float)(fraction * hi);
    }
    output[2] = lbl_80650F90 * (sample *
        ((float)((1.0f - pi->span_f) * fixed_table[pi->span_i + 129]) +
         (float)(pi->span_f * (*upper_band)[pi->span_i])));
    sample = sample *
        ((float)((1.0f - pi->span_fm) * fixed_table[pi->span_im + 129]) +
         (float)(pi->span_fm * (*upper_band)[pi->span_im]));
    output[1] = sample *
        ((float)((1.0f - pi->pan_f) * fixed_table[pi->pan_i + 129]) +
         (float)(pi->pan_f * (*upper_band)[pi->pan_i]));
    output[0] = sample *
        ((float)((1.0f - pi->pan_fm) * fixed_table[pi->pan_im + 129]) +
         (float)(pi->pan_fm * (*upper_band)[pi->pan_im]));
}

void fn_801C79C8(u8 curve, float* output, u32 packed_pan, u32 packed_span,
                 float volume, float aux_a, float aux_b, u32 narrow_pan,
                 u32 surround_layout)
{
    float* volume_table;
    float* fixed_table = lbl_80253148;
    float pan, span, reverse_pan, reverse_span;
    PanInfo pi;
    float rear_level, first, second;
    float scaled_volume, fraction_volume, sample_volume;
    u32 index_volume;

    volume_table = curve == 0 ? lbl_80253148 : lbl_80252F2C;
    /* The packed sentinel selects the full surround range. */
    if (packed_pan == 0x00800000) {
        packed_pan = 0;
        packed_span = 0x007F0000;
    }
    packed_pan = packed_pan <= 0x10000 ? 0 : packed_pan - 0x10000;
    packed_span = packed_span <= 0x10000 ? 0 : packed_span - 0x10000;
    pan = lbl_80650FA0 * packed_pan;
    span = lbl_80650FA0 * packed_span;

    if (surround_layout != 0) {
        pi.rpan_f = wrap_unit(pan, lbl_80650F8C);
        pi.rpan_i = fn_800F5C54(pan);
        reverse_pan = lbl_80650FA4 - pan;
        pi.rpan_fm = wrap_unit(reverse_pan, lbl_80650F8C);
        pi.rpan_im = fn_800F5C54(reverse_pan);
    }
    if (narrow_pan != 0) {
        first = lbl_80650FA8 * (pan - lbl_80650F8C);
        pan = lbl_80650F8C + first;
    }
    pi.pan_f = wrap_unit(pan, lbl_80650F8C);
    pi.pan_i = fn_800F5C54(pan);
    pi.span_f = wrap_unit(span, lbl_80650F8C);
    pi.span_i = fn_800F5C54(span);
    reverse_pan = lbl_80650FA4 - pan;
    reverse_span = lbl_80650FA4 - span;
    pi.pan_fm = wrap_unit(reverse_pan, lbl_80650F8C);
    pi.pan_im = fn_800F5C54(reverse_pan);
    pi.span_fm = wrap_unit(reverse_span, lbl_80650F8C);
    pi.span_im = fn_800F5C54(reverse_span);

    /* Output stores may alias the tables: reload bands between rows. */
    if (surround_layout == 0) {
        float* next_band;

        calc_bus(fixed_table, volume_table, &next_band, 1, output + 0, volume, &pi);
        calc_bus(fixed_table, volume_table, &next_band, 0, output + 3, aux_a, &pi);
        calc_bus(fixed_table, volume_table, &next_band, 0, output + 6, aux_b, &pi);
    } else {
        float* next_band;

        scaled_volume = lbl_80650F88 * volume;
        index_volume = fn_800F5C54(scaled_volume);
        next_band = fixed_table + 130;
        fraction_volume = scaled_volume - index_volume;
        sample_volume =
            (float)((1.0f - fraction_volume) * volume_table[index_volume]) +
            (float)(fraction_volume * volume_table[index_volume + 1]);
        rear_level = sample_volume *
            ((float)((1.0f - pi.span_f) * fixed_table[pi.span_i + 129]) +
             (float)(pi.span_f * next_band[pi.span_i]));
        sample_volume = sample_volume *
            ((float)((1.0f - pi.span_fm) * fixed_table[pi.span_im + 129]) +
             (float)(pi.span_fm * next_band[pi.span_im]));
        output[1] = sample_volume *
            ((float)((1.0f - pi.pan_f) * fixed_table[pi.pan_i + 129]) +
             (float)(pi.pan_f * next_band[pi.pan_i]));
        output[0] = sample_volume *
            ((float)((1.0f - pi.pan_fm) * fixed_table[pi.pan_im + 129]) +
             (float)(pi.pan_fm * next_band[pi.pan_im]));
        /* This layout uses the first sample for both outer channel pairs.
         * Its old-phase lower tap is at +0x214; the upper tap is +0x208. */
        first = (1.0f - pi.rpan_f) * fixed_table[pi.rpan_i + 133];
        second = pi.rpan_f * next_band[pi.rpan_i];
        output[7] = rear_level * (first + second);
        first = (1.0f - pi.rpan_fm) * fixed_table[pi.rpan_im + 133];
        second = pi.rpan_fm * next_band[pi.rpan_im];
        output[6] = rear_level * (first + second);

        calc_bus(fixed_table, volume_table, &next_band, 0, output + 3, aux_a, &pi);
        output[2] = lbl_80650FAC;
        output[8] = lbl_80650FAC;
    }
}
