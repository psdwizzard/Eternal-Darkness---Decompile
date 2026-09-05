typedef struct Bucket {
    int state;
    int count;
} Bucket;

#pragma opt_propagation off
int fn_801A63A0(Bucket* buckets)
{
    int state;
    int count;

    count = 0;
    state = -1;

    if (buckets[0].count >= count) {
        state = buckets[0].state;
        count = buckets[0].count;
    }
    if (buckets[1].count >= count) {
        state = buckets[1].state;
        count = buckets[1].count;
    }
    if (buckets[2].count >= count) {
        state = buckets[2].state;
        count = buckets[2].count;
    }
    if (buckets[3].count >= count) {
        state = buckets[3].state;
        count = buckets[3].count;
    }
    if (buckets[4].count >= count) {
        state = buckets[4].state;
    }
    return state;
}
#pragma opt_propagation reset
