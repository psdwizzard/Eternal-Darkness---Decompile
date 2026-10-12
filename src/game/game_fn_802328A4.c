#include "src/game/types.h"

extern double fn_80101988(double); /* cos */
extern double fn_80102360(double); /* exp */
extern double __frsqrte(double);
extern const float lbl_806517F8; /* pi */
extern const float lbl_806517FC; /* 2 */
extern const float lbl_80651804; /* 4 */
extern const double lbl_80651810; /* 0.5 */
extern const double lbl_80651818; /* 3 */

/* Evaluate the line spectral pairs at each mapped frequency, then apply
 * the resulting amplitude to all samples sharing that frequency. */
void fn_802328A4(float *curve, int *map, int count, int bins,
                float *lsp, int order, float amplitude, float offset)
{
    int i;
    float zero;
    float two;
    float frequencyScale = lbl_806517F8 / (float)bins;
    float p, q;

    i = 0;
    two = lbl_806517FC;
    for (; i < order; i++) {
        lsp[i] = two * (float)fn_80101988(lsp[i]);
    }

    two = 2.0f;
    zero = 0.0f;
    i = 0;
    while (i < count) {
        int k = map[i];
        int j;
        float w;
        float gain;

        p = 0.5f;
        q = p;
        w = two * (float)fn_80101988(frequencyScale * (float)k);

        for (j = 1; j < order; j += 2) {
            q *= w - lsp[j - 1];
            p *= w - lsp[j];
        }
        if (j == order) {
            q *= w - lsp[j - 1];
            p *= p * (lbl_80651804 - w * w);
            q *= q;
        } else {
            p *= p * (lbl_806517FC - w);
            q *= q * (lbl_806517FC + w);
        }
        /* Sum the two polynomial contributions and take their square root. */
        w = p + q;
        if (w > zero) {
            double estimate = __frsqrte(w);
            volatile float root;
            estimate = lbl_80651810 * estimate *
                       (lbl_80651818 - w * (estimate * estimate));
            estimate = lbl_80651810 * estimate *
                       (lbl_80651818 - w * (estimate * estimate));
            estimate = lbl_80651810 * estimate *
                       (lbl_80651818 - w * (estimate * estimate));
            root = w * estimate;
            w = root;
        }

        gain = (float)fn_80102360(0.11512925f * (amplitude / w - offset));
        curve[i] *= gain;
        while (map[++i] == k) {
            curve[i] *= gain;
        }
    }
}
