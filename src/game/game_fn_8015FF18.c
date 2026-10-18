int luaG_getline(int* values, int target, int position, int* cursor)
{
    int offset;
    int index;
    int value;

    if (values == 0 || target == -1)
        return -1;

    if (cursor != 0)
        offset = *cursor;
    else
        offset = 0;

    index = offset;
    value = values[offset];
    if (value < 0) {
        position -= value;
        index++;
    }

    offset = index;
    while (values[offset] > target) {
        --offset;
        --position;
        value = values[offset];
        --index;
        if (value < 0) {
            position += value;
            --index;
            --offset;
        }
    }

    for (;;) {
        int next_position = position + 1;
        int next = index + 1;
        value = values[next];
        if (value < 0) {
            next_position -= value;
            ++next;
        }
        if (values[next] > target)
            break;
        position = next_position;
        index = next;
    }

    if (cursor != 0)
        *cursor = index;
    return position;
}
