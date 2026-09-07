extern float lbl_80651018;

void fn_801CA59C(float* output, float* input)
{
    float negative_inverse;
    float inverse;
    float c0;
    float c1;
    float determinant;
    float c2;

    c0 = input[4] * input[8] - input[7] * input[5];
    c1 = -(input[3] * input[8] - input[6] * input[5]);
    c2 = input[3] * input[7] - input[6] * input[4];
    determinant = input[0] * c0 + input[1] * c1 + input[2] * c2;
    inverse = lbl_80651018 / determinant;
    negative_inverse = -inverse;

    output[0] = inverse * c0;
    output[3] = inverse * c1;
    output[6] = inverse * c2;
    output[1] = negative_inverse *
                (input[1] * input[8] - input[7] * input[2]);
    output[4] = inverse *
                (input[0] * input[8] - input[6] * input[2]);
    output[7] = negative_inverse *
                (input[0] * input[7] - input[6] * input[1]);
    output[2] = inverse *
                (input[1] * input[5] - input[4] * input[2]);
    output[5] = negative_inverse *
                (input[0] * input[5] - input[3] * input[2]);
    output[8] = inverse *
                (input[0] * input[4] - input[3] * input[1]);
    output[9] = -input[9] * output[0] - input[10] * output[1] -
                input[11] * output[2];
    output[10] = -input[9] * output[3] - input[10] * output[4] -
                 input[11] * output[5];
    output[11] = -input[9] * output[6] - input[10] * output[7] -
                 input[11] * output[8];
}
