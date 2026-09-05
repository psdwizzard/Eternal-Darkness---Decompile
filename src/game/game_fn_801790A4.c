extern float lbl_80650860;
extern float lbl_80650868;

#pragma opt_common_subs off
float fn_801790A4(float x1, float y1, float x2, float y2)
{
    float dy;
    float dx = x2 - x1;
    float minimum;

    if (dx < lbl_80650860) {
        dx = -dx;
    }

    dy = y2 - y1;
    if (dy < lbl_80650860) {
        dy = -dy;
    }

    if (dx > dy) {
        minimum = dy;
    } else {
        minimum = dx;
    }

    return dx + dy - minimum * lbl_80650868;
}
#pragma opt_common_subs reset
