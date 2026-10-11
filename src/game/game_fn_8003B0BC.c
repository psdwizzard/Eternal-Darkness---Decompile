typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct QueryResult { unsigned int normal[3]; Vec3 position; } QueryResult;
extern void fn_8004914C(int);
extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern void fn_8011F114(Vec3*, int);
extern unsigned int fn_80179004(Vec3*, unsigned int*);
extern void fn_801A7610(int, unsigned int*, float, float, int, int, int);
extern void fn_801A76F4(unsigned int*, int);
extern void fn_80211A48(unsigned int*, Vec3*, unsigned int*);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern void fn_80211AAC(Vec3*, Vec3*);
extern float lbl_8064E25C;
void fn_8003B0BC(void* object, Vec3* normal_out, Vec3* position_out, int context, int transform, int use_transform) {
    QueryResult result;
    unsigned int query;
    unsigned int id;
    Vec3 direction;
    Vec3 normal;
    Vec3 first;
    Vec3 second;
    Vec3 third;
    Vec3 fourth;
    if (object != 0) {
        fn_8004914C(context);
        if (fn_8011F6A4(object, 4, -1, -1, &query, 1) != -1) {
            if (use_transform != 0) {
                fn_8011F114(&direction, transform);
                id = fn_80179004(&direction, result.normal);
                direction.x = lbl_8064E25C * result.position.x;
                direction.y = lbl_8064E25C * result.position.y;
                direction.z = lbl_8064E25C * result.position.z;
                normal.x = *(float*)&result.normal[0];
                normal.y = *(float*)&result.normal[1];
                normal.z = *(float*)&result.normal[2];
                fn_80211AAC(&direction, &direction);
                fn_80211A90(&direction, &direction, (float)id);
                fn_80211A48((unsigned int*)&normal, &direction, (unsigned int*)&normal);
            } else {
                normal.x = *(float*)&result.normal[0];
                normal.y = *(float*)&result.normal[1];
                normal.z = *(float*)&result.normal[2];
            }
            *position_out = result.position;
            *normal_out = normal;
            first = normal; second = result.position; third = normal; fourth = result.position;
            fn_801A7610(context, (unsigned int*)&third, second.y, second.x, (int)second.z, (int)second.y, (int)normal.x);
        }
    } else {
        fn_801A76F4((unsigned int*)&first, context);
        *position_out = second;
        *normal_out = first;
    }
}
