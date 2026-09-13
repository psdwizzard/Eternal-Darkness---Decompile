typedef unsigned char u8;

void fn_801F4FC8(u8* source, int* red, int* green, int* blue)
{
    int component;

    *red = (1164 * (source[0] - 16) + 1596 * (source[2] - 128) + 500) / 1000;
    *green = (1164 * (source[0] - 16) - 813 * (source[2] - 128) -
              391 * (source[1] - 128) + 500) / 1000;
    *blue = (1164 * (source[0] - 16) + 2018 * (source[1] - 128) + 500) / 1000;

    component = *red;
    component = component > 255 ? 255 : (component < 0 ? 0 : component);
    *red = (u8)component;

    component = *green;
    component = component > 255 ? 255 : (component < 0 ? 0 : component);
    *green = (u8)component;

    component = *blue;
    component = component > 255 ? 255 : (component < 0 ? 0 : component);
    *blue = (u8)component;
}
