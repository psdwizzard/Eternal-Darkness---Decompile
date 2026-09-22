typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct HitTriangle {
    Vec3 a, b, c;
} HitTriangle;

typedef struct MeshIndex {
    u16 vertex;
    u16 pad;
} MeshIndex;

typedef struct MeshInfo {
    u8 pad0[0x28];
    u8* descriptors;
    u8 pad2C[0x14];
    u8* groups;
    MeshIndex* indices;
} MeshInfo;

extern MeshInfo* fn_8011F950(void* object);
extern short* fn_8011FA6C(void* object, int index);
extern void fn_801380E0(short* value, float* out);
extern u8 fn_8017ABE0(Vec3* a, Vec3* b);
extern u8 fn_801420F8(Vec3* a, Vec3* b, Vec3* c, int side);
extern void fn_8013C894(Vec3* a, Vec3* b, Vec3* c, Vec3* out);
extern float fn_80178F88(float, float, float, float, float, float);
extern u16 lbl_805AAE40[];
extern float lbl_80650278;
extern int lbl_8064D738;

int fn_80135A40(Vec3* point, void* object, u16 descriptor_index,
                HitTriangle* triangle, Vec3* hit_point, u8 stop_early)
{
    MeshInfo* info;
    short* vertices;
    u8* descriptor;
    u8* group;
    MeshIndex* indices;
    u16 group_count;
    u16 group_index;
    int end;
    int first_index;
    int second_index;
    int third_index;
    int found;
    int current;
    float best;

    info = fn_8011F950(object);
    vertices = fn_8011FA6C(object, lbl_8064D738);
    descriptor = info->descriptors + descriptor_index * 0x114;
    group_count = *(u16*)descriptor;
    group = info->groups + (*(u16*)(descriptor + 2) * 4);
    indices = info->indices + *(u16*)(descriptor + 0xE);
    found = 0;
    best = lbl_80650278;

    if (vertices != 0) {
        for (group_index = 0; group_index < group_count;
             group_index++, group += 4) {
            Vec3 first;
            Vec3 second;

            current = *(u16*)(group + 2);
            end = current + group[1];
            first_index = lbl_805AAE40[indices[(u16)current].vertex];
            fn_801380E0(vertices + first_index * 3, &first.x);
            fn_801380E0(vertices + first_index * 3 + 1, &first.y);
            fn_801380E0(vertices + first_index * 3 + 2, &first.z);
            second_index = lbl_805AAE40[indices[current + 1].vertex];
            fn_801380E0(vertices + second_index * 3, &second.x);
            fn_801380E0(vertices + second_index * 3 + 1, &second.y);
            fn_801380E0(vertices + second_index * 3 + 2, &second.z);
            current += 2;

            while (current < end) {
                Vec3 third;
                Vec3 candidate;

                third_index = lbl_805AAE40[indices[current].vertex];
                fn_801380E0(vertices + third_index * 3, &third.x);
                fn_801380E0(vertices + third_index * 3 + 1, &third.y);
                fn_801380E0(vertices + third_index * 3 + 2, &third.z);

                if (first_index != second_index && first_index != third_index &&
                    second_index != third_index &&
                    !fn_8017ABE0(&first, &second) &&
                    !fn_8017ABE0(&first, &third) &&
                    !fn_8017ABE0(&second, &third) &&
                    (fn_801420F8(&first, &second, &third, 0) ||
                     fn_801420F8(&first, &second, &third, 1))) {
                    float distance;
                    found = 1;
                    if (stop_early) {
                        return 1;
                    }
                    fn_8013C894(&first, &second, &third, &candidate);
                    distance = fn_80178F88(point->x, point->y, point->z,
                                           candidate.x, candidate.y, candidate.z);
                    if (distance < best) {
                        best = distance;
                        triangle->a.x = first.x;
                        triangle->a.y = first.y;
                        triangle->a.z = first.z;
                        triangle->b.x = second.x;
                        triangle->b.y = second.y;
                        triangle->b.z = second.z;
                        triangle->c.x = third.x;
                        triangle->c.y = third.y;
                        triangle->c.z = third.z;
                        hit_point->x = candidate.x;
                        hit_point->y = candidate.y;
                        hit_point->z = candidate.z;
                    }
                }
                first_index = second_index;
                second_index = third_index;
                first.x = second.x;
                first.y = second.y;
                first.z = second.z;
                second.x = third.x;
                second.y = third.y;
                second.z = third.z;
                current++;
            }
        }
    }
    return found;
}
