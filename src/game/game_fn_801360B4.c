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
extern u8 fn_8017ABA0(const Vec3* left, const Vec3* right);
extern int fn_8013E028(const Vec3* a, const Vec3* b, const Vec3* c,
                       const Vec3* d, const Vec3* e, float* result);
extern u16 lbl_805AAE40[];
extern float lbl_80650288;
extern int lbl_8064D738;

int fn_801360B4(const Vec3* origin, const Vec3* direction, void* object,
                u16 descriptor_index, HitTriangle* triangle, float* distance,
                float max_distance)
{
    MeshInfo* info;
    short* vertices;
    u8* descriptor;
    u8* group;
    MeshIndex* indices;
    u16 group_count;
    int end;
    int first_index;
    int second_index;
    int third_index;
    int current;
    u16 group_index;
    int index;

    info = fn_8011F950(object);
    vertices = fn_8011FA6C(object, lbl_8064D738);
    descriptor = info->descriptors + descriptor_index * 0x114;
    group = info->groups + (*(u16*)(descriptor + 2) * 4);
    group_count = *(u16*)descriptor;
    indices = info->indices + *(u16*)(descriptor + 0xE);

    if (vertices != 0) {
        for (group_index = 0; group_index < group_count;
             group_index++, group += 4) {
            Vec3 first;
            Vec3 second;

            current = *(u16*)(group + 2);
            end = current + group[1];
            first_index = lbl_805AAE40[indices[current].vertex];
            fn_801380E0(vertices + first_index * 3, &first.x);
            fn_801380E0(vertices + first_index * 3 + 1, &first.y);
            fn_801380E0(vertices + first_index * 3 + 2, &first.z);
            second_index = lbl_805AAE40[indices[current + 1].vertex];
            fn_801380E0(vertices + second_index * 3, &second.x);
            fn_801380E0(vertices + second_index * 3 + 1, &second.y);
            fn_801380E0(vertices + second_index * 3 + 2, &second.z);

            for (index = current + 2; index < end; index++) {
                Vec3 third;

                third_index = lbl_805AAE40[indices[index].vertex];
                fn_801380E0(vertices + third_index * 3, &third.x);
                fn_801380E0(vertices + third_index * 3 + 1, &third.y);
                fn_801380E0(vertices + third_index * 3 + 2, &third.z);

                if (first_index != second_index && first_index != third_index &&
                    second_index != third_index &&
                    !fn_8017ABA0(&first, &second) &&
                    !fn_8017ABA0(&first, &third) &&
                    !fn_8017ABA0(&second, &third) &&
                    fn_8013E028(origin, direction, &first, &second, &third,
                                distance) &&
                    *distance <= max_distance && *distance >= lbl_80650288) {
                    triangle->a = first;
                    triangle->b = second;
                    triangle->c = third;
                    return 1;
                }
                first_index = second_index;
                second_index = third_index;
                first = second;
                second = third;
            }
        }
    }
    return 0;
}
