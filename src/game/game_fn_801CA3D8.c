typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

void salApplyMatrix(float* matrix, Vec3* input, Vec3* output)
{
    output->x = matrix[0] * input->x + matrix[1] * input->y +
                matrix[2] * input->z + matrix[9];
    output->y = matrix[3] * input->x + matrix[4] * input->y +
                matrix[5] * input->z + matrix[10];
    output->z = matrix[6] * input->x + matrix[7] * input->y +
                matrix[8] * input->z + matrix[11];
}
