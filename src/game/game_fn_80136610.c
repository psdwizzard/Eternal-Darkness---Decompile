typedef struct Vec3s {
    short x;
    short y;
    short z;
} Vec3s;

typedef struct Vec3i {
    int x;
    int y;
    int z;
} Vec3i;

typedef struct Quad {
    float unk0;
    Vec3i pos;
    unsigned short idx[4];
    unsigned char unk18;
} Quad;

typedef struct QuadInfo {
    short unk0;
    unsigned char unk2;
    float x;
    float y;
    float z;
    float dist;
    Vec3i pos;
    float unk20;
    unsigned char unk24;
    char pad25[3];
    short unk28;
    unsigned short *indices;
    unsigned char unk30;
    int unk34;
} QuadInfo;

extern unsigned int fn_80178F14(int, int, int, int, int, int);
extern float lbl_80650290;

void fn_80136610(Quad *quad, QuadInfo *info, Vec3s *verts) {
    unsigned short *indices = quad->idx;

    info->unk0 = 0;
    info->unk2 = 0;
    info->x = (verts[indices[0]].x + verts[indices[1]].x + verts[indices[2]].x +
               verts[indices[3]].x) >> 2;
    info->y = (verts[indices[0]].y + verts[indices[1]].y + verts[indices[2]].y +
               verts[indices[3]].y) >> 2;
    info->z = (verts[indices[0]].z + verts[indices[1]].z + verts[indices[2]].z +
               verts[indices[3]].z) >> 2;
    info->dist = lbl_80650290 *
                 (float)fn_80178F14((int)info->x, (int)info->y, (int)info->z,
                                    verts[indices[0]].x, verts[indices[0]].y,
                                    verts[indices[0]].z);
    info->pos = quad->pos;
    info->unk20 = quad->unk0;
    info->unk24 = quad->unk18;
    info->unk28 = 4;
    info->indices = indices;
    info->unk30 = 0;
    info->unk34 = 0;
}
