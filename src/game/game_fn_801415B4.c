typedef unsigned char u8;
typedef signed short s16;

extern u8 lbl_8064D020;
extern s16 lbl_8064D022;
extern s16 lbl_8064D024;
extern float lbl_805B12B0[];

/* The retail routine expands all nine edge pairs in the active projection. */
#define EDGE_INTERSECTS(ax, ay, bx, by, cx, cy, dx, dy)                 \
    do {                                                               \
        float aex = (ax) - (bx);                                       \
        float aey = (ay) - (by);                                       \
        float bex = (cx) - (dx);                                       \
        float bey = (cy) - (dy);                                       \
        float rx = (dx) - (ax);                                        \
        float ry = (dy) - (ay);                                        \
        float det = bex * aey - bey * aex;                             \
        float ta = aex * ry - aey * rx;                                \
        if (((det > 0.0f && ta >= 0.0f && ta <= det) ||                \
             (det < 0.0f && ta <= 0.0f && ta >= det))) {               \
            float tb = bey * rx - bex * ry;                            \
            if ((det > 0.0f && tb >= 0.0f && tb <= det) ||             \
                (det < 0.0f && tb <= 0.0f && tb >= det))               \
                return 1;                                              \
        }                                                              \
    } while (0)

int fn_801415B4(const float* a0, const float* a1, const float* a2)
{
    unsigned int x = (unsigned short)lbl_8064D024;
    unsigned int y = (unsigned short)lbl_8064D022;
    float* b = lbl_805B12B0 + lbl_8064D020 * 3;
    float zero = 0.0f;
    float a0x = a0[x], a0y = a0[y];
    float a1x = a1[x], a1y = a1[y];
    float b0x = b[x], b0y = b[y];
    float b1x = b[6 + x], b1y = b[6 + y];

    EDGE_INTERSECTS(a0x,a0y,a1x,a1y,b0x,b0y,b1x,b1y);
    {
        float a2x = a2[x], a2y = a2[y];
        EDGE_INTERSECTS(a1x,a1y,a2x,a2y,b0x,b0y,b1x,b1y);
        EDGE_INTERSECTS(a2x,a2y,a0x,a0y,b0x,b0y,b1x,b1y);
        {
            float b2x = b[12 + x], b2y = b[12 + y];
            EDGE_INTERSECTS(a0x,a0y,a1x,a1y,b2x,b2y,b0x,b0y);
            EDGE_INTERSECTS(a1x,a1y,a2x,a2y,b2x,b2y,b0x,b0y);
            EDGE_INTERSECTS(a2x,a2y,a0x,a0y,b2x,b2y,b0x,b0y);
            EDGE_INTERSECTS(a0x,a0y,a1x,a1y,b1x,b1y,b2x,b2y);
            EDGE_INTERSECTS(a1x,a1y,a2x,a2y,b1x,b1y,b2x,b2y);
            EDGE_INTERSECTS(a2x,a2y,a0x,a0y,b1x,b1y,b2x,b2y);

            {
                float s0=(a1x-a0x)*(b1y-a0y)-(a1y-a0y)*(b1x-a0x);
                float s1=(a2x-a1x)*(b1y-a1y)-(a2y-a1y)*(b1x-a1x);
                float s2=(a0x-a2x)*(b1y-a2y)-(a0y-a2y)*(b1x-a2x);
                if (s0*s1 > zero && s0*s2 > zero) return 1;
            }
            {
                float s0=(b1x-b0x)*(a0y-b0y)-(b1y-b0y)*(a0x-b0x);
                float s1=(b2x-b1x)*(a0y-b1y)-(b2y-b1y)*(a0x-b1x);
                float s2=(b0x-b2x)*(a0y-b2y)-(b0y-b2y)*(a0x-b2x);
                if (s0*s1 > zero && s0*s2 > zero) return 1;
            }
            return 0;
        }
    }
}
