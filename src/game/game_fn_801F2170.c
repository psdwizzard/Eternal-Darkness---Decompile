typedef struct Vec3 {
    float x, y, z;
    float pad[2];
} Vec3;

typedef struct PointOwner {
    unsigned char pad[0x10];
    Vec3* points;
} PointOwner;

extern float lbl_806513C8;
extern float fn_801F213C(Vec3*, Vec3*);

#pragma use_lmw_stmw on
void fn_801F2170(int output[8][4], PointOwner** owners, int count)
{
    int reverse[8][4];
    int forward[8][4];
    int group;
    int point;
    int candidate;

    for (group = 0; group < 8; group++) {
        for (point = 0; point < count; point++) {
            output[group][point] = -1;
            forward[group][point] = -1;
            reverse[group][point] = -1;
        }
        for (point = 0; point < count; point++) {
            float best = lbl_806513C8;
            for (candidate = 0; candidate < 4; candidate++) {
                if (reverse[group][candidate] == -1) {
                    Vec3* base_points = owners[0]->points;
                    Vec3* group_points = owners[group]->points;
                    float distance = fn_801F213C(&base_points[point],
                                                  &group_points[candidate]);
                    if (distance < best) {
                        best = distance;
                        reverse[group][forward[group][point]] = -1;
                        output[group][point] = candidate;
                        forward[group][point] = candidate;
                        reverse[group][candidate] = point;
                    }
                }
            }
        }
    }
}
