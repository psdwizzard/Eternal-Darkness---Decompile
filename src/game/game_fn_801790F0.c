/* fn_801790F0: atan2(y, x) evaluated with Euler's arctangent series. */

extern const float lbl_80650860;
extern const float lbl_8065086C; /* pi */
extern const float lbl_80650870; /* pi/2 */
extern const float lbl_80650874; /* -pi/2 */
extern const float lbl_80650878; /* 1.0f */
extern const float lbl_8065087C; /* pi/4 */
extern const float lbl_80650880; /* -3pi/4 */
extern const float lbl_80650884; /* -1.0f */
extern const float lbl_80650888; /* -pi/4 */
extern const float lbl_8065088C; /* 3pi/4 */
extern const float lbl_80650890; /* -3pi/2 */
extern const float lbl_80650894; /* 2.0f */
extern const float lbl_80650898; /* 3.0f */
extern const float lbl_8065089C; /* -0.01f */
extern const float lbl_806508A4; /* -pi */

/* Reciprocal table: lbl_80250D00[n] == 1.0f / n */
extern const float lbl_80250D00[100];

float fn_801790F0(float y, float x)
{
    float sum;
    float ratio;
    float term;
    float scale;
    float factor;
    float square;
    int i;

    if (lbl_80650860 == y) {
        if (x > lbl_80650860) {
            return lbl_80650860;
        }
        return lbl_8065086C;
    }
    if (lbl_80650860 == x) {
        if (y > lbl_80650860) {
            return lbl_80650870;
        }
        return lbl_80650874;
    }

    ratio = y / x;
    sum = lbl_80650878;
    if (sum == ratio) {
        if (y > lbl_80650860) {
            return lbl_8065087C;
        }
        return lbl_80650880;
    }
    if (lbl_80650884 == ratio) {
        if (x > lbl_80650860) {
            return lbl_80650888;
        }
        return lbl_8065088C;
    }

    if (ratio > sum || ratio < lbl_80650884) {
        float result = fn_801790F0(x, y);
        if (x > lbl_80650860) {
            return lbl_80650870 - result;
        }
        if (y > lbl_80650860) {
            return lbl_80650870 - result;
        }
        return lbl_80650890 - result;
    }

    /* Euler's series: atan(r) = r/(1+r^2) * sum of (2n)!!/(2n+1)!! * (r^2/(1+r^2))^n */
    square = ratio * ratio;
    scale = sum / (sum + square);
    factor = square * scale;
    term = lbl_80650894 * factor / lbl_80650898;
    for (i = 4; i < 100; i += 2) {
        sum += term;
        if (term >= lbl_8065089C && term <= 0.01f) {
            break;
        }
        term *= factor * i * lbl_80250D00[i + 1];
    }
    sum *= ratio * scale;

    if (x > 0.0f) {
        return sum;
    }
    if (y > 0.0f) {
        return lbl_8065086C + sum;
    }
    return lbl_806508A4 + sum;
}
