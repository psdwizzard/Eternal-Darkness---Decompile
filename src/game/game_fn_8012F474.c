typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef float Matrix34[3][4];

typedef struct QueryResult {
    u8 pad_0[8];
    Vec3 position;
    Vec3 direction;
    u8 pad_20[8];
} QueryResult;

typedef struct QueryVectors {
    Vec3 position;
    Vec3 direction;
} QueryVectors;

extern void fn_80127FD8(void*, int, Matrix34);
extern void PSVECSubtract(const Vec3*, const Vec3*, Vec3*);
extern float PSVECMag(const Vec3*);
extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern void PSVECNormalize(const Vec3*, Vec3*);
extern void PSVECScale(const Vec3*, Vec3*, float);
extern void PSVECAdd(const Vec3*, const Vec3*, Vec3*);

/* The queried key pair is required to produce a valid result. */
void fn_8012F474(void* object, int transform_index, int second, int first,
                 const Vec3* target, Vec3* start, Vec3* end)
{
    Matrix34 matrix;
    QueryResult query;
    QueryVectors query_vectors;
    Vec3 direction;
    Vec3 translation;
    Vec3 delta;
    float distance;

    fn_80127FD8(object, transform_index, matrix);
    translation.x = matrix[0][3];
    translation.y = matrix[1][3];
    translation.z = matrix[2][3];
    PSVECSubtract(target, &translation, &delta);
    distance = PSVECMag(&delta);
    fn_8011F6A4(object, first, second, -1, &query, 1);
    query_vectors.position = query.position;
    query_vectors.direction = query.direction;
    *start = query_vectors.position;
    direction = query_vectors.direction;
    PSVECNormalize(&direction, &direction);
    PSVECScale(&direction, &direction, distance);
    PSVECAdd(start, &direction, end);
}
