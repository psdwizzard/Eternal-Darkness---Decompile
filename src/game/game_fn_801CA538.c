typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

void salCrossProduct(Vec3* output, Vec3* left, Vec3* right)
{
    output->x = left->y * right->z - left->z * right->y;
    output->y = left->z * right->x - left->x * right->z;
    output->z = left->x * right->y - left->y * right->x;
}
