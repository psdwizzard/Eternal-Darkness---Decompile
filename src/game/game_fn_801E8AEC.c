typedef struct Range { int first; int last; void* value; } Range;
void fn_801E8AEC(Range* range, int first, int count, void* value)
{
    int last = first - 1;
    range->first = first;
    last = count + last;
    if (last > first) first = last;
    range->last = first;
    range->value = value;
}
