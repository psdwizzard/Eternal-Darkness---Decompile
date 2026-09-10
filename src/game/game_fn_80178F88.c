float fn_80178F88(float x1, float y1, float z1,
                  float x2, float y2, float z2)
{
    float y;
    float low;
    float x = x2 - x1;

    if (x < 0.0f) {
        x = -x;
    }

    y = y2 - y1;
    if (y < 0.0f) {
        y = -y;
    }

    {
        float z = z2 - z1;
        if (z < 0.0f) {
            z = -z;
        }

        if (x < y) {
            low = x;
        } else {
            low = y;
            y = x;
        }

        if (z < y) {
            x = y;
            y = z;
        } else {
            x = z;
        }

        return (low + y) / 4.0f + x;
    }
}
