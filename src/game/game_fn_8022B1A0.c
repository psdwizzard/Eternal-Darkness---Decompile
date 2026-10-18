typedef unsigned char u8;

typedef struct GXVtxDescList {
    int attr;
    int type;
} GXVtxDescList;

typedef struct GXVtxAttrFmtList {
    int attr;
    int count;
    int type;
    u8 frac;
} GXVtxAttrFmtList;

typedef struct Vec {
    float x, y, z;
} Vec;

/* GX descriptor and format save areas share the original BSS pool. */
static GXVtxDescList vcd[27];
static GXVtxAttrFmtList lbl_806424F0[27];
/* These preceding dodecahedron tables preserve the shared data-pool offsets. */
static int polygons[12][5] = {
    {0, 12, 10, 11, 16},
    {1, 17, 8, 9, 13},
    {2, 14, 9, 8, 18},
    {3, 19, 11, 10, 15},
    {4, 14, 2, 3, 15},
    {5, 12, 0, 1, 13},
    {6, 17, 1, 0, 16},
    {7, 19, 3, 2, 18},
    {8, 17, 6, 7, 18},
    {9, 14, 4, 5, 13},
    {10, 12, 5, 4, 15},
    {11, 19, 7, 6, 16},
};
static Vec lbl_802FF408[20] = {
    {-0.809015f, 0.0f, 0.309015f},
    {-0.809015f, 0.0f, -0.309015f},
    {0.809015f, 0.0f, -0.309015f},
    {0.809015f, 0.0f, 0.309015f},
    {0.309015f, -0.809015f, 0.0f},
    {-0.309015f, -0.809015f, 0.0f},
    {-0.309015f, 0.809015f, 0.0f},
    {0.309015f, 0.809015f, 0.0f},
    {0.0f, 0.309015f, -0.809015f},
    {0.0f, -0.309015f, -0.809015f},
    {0.0f, -0.309015f, 0.809015f},
    {0.0f, 0.309015f, 0.809015f},
    {-0.5f, -0.5f, 0.5f},
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {0.5f, 0.5f, 0.5f},
};
/* Unit octahedron vertices and counterclockwise triangle indices. */
static Vec lbl_802FF4F8[6] = {
    {1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, -1.0f},
};
static u8 lbl_802FF540[8][3] = {
    {0, 4, 2},
    {1, 2, 4},
    {0, 3, 4},
    {1, 4, 3},
    {0, 2, 5},
    {1, 5, 2},
    {0, 5, 3},
    {1, 3, 5},
};
extern void GXGetVtxDescv(GXVtxDescList *list);
extern void GXGetVtxAttrFmtv(int format, GXVtxAttrFmtList *list);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int attribute, int type);
extern void GXSetVtxAttrFmt(int format, int attribute, int count, int type, u8 fraction);
extern void Subdivide(u8 depth, const Vec *a, const Vec *b, const Vec *c);
extern void GXSetVtxDescv(const GXVtxDescList *list);
extern void GXSetVtxAttrFmtv(int format, const volatile GXVtxAttrFmtList *list);

/* Draw an octahedron, preserving the caller's vertex descriptors and format. */
void GXDrawOctahedron(void)
{
    int face;

    GXGetVtxDescv(vcd);
    GXGetVtxAttrFmtv(3, lbl_806424F0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(10, 1);
    GXSetVtxAttrFmt(3, 9, 1, 4, 0);
    GXSetVtxAttrFmt(3, 10, 0, 4, 0);
    for (face = 7; face >= 0; face--) {
        Subdivide(0,
            &lbl_802FF4F8[lbl_802FF540[(u8)face][0]],
            &lbl_802FF4F8[lbl_802FF540[(u8)face][1]],
            &lbl_802FF4F8[lbl_802FF540[(u8)face][2]]);
    }
    GXSetVtxDescv(vcd);
    GXSetVtxAttrFmtv(3, lbl_806424F0);
}
