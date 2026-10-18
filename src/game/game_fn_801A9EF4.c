extern int rand(void);

int fn_801A9EF4(int low, int high)
{
    int random = rand();
    int range = high - low + 1;

    return low + random % range;
}
