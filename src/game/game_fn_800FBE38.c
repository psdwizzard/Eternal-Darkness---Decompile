/* Heap sort, with byte-wise exchanges for arbitrary element sizes. */
typedef unsigned long size_t;
typedef int (*CompareProc)(const void*, const void*);

void qsort(void* base, size_t count, size_t size, CompareProc compare)
{
    if (count >= 2) {
        size_t root, end, child;
        signed char* root_ptr;
        signed char* end_ptr;
        signed char* parent_ptr;
        signed char* child_ptr;
        signed char* right_ptr;

        root = count / 2 + 1;
        end = count;
        root_ptr = (signed char*)base + size * (root - 1);
        end_ptr = (signed char*)base + size * (count - 1);

        for (;;) {
            if (root > 1) {
                root_ptr -= size;
                --root;
            } else {
                {
                    signed char* second = end_ptr - 1;
                    signed char* first = root_ptr - 1;
                    size_t remaining = size + 1;
                    int temp;
                    while (--remaining) {
                        temp = *++first;
                        *first = *++second;
                        *second = temp;
                    }
                }
                if (--end == 1)
                    return;
                end_ptr -= size;
            }

            child = root;
            child_ptr = (signed char*)base + size * (root - 1);
            while (child * 2 <= end) {
                parent_ptr = child_ptr;
                child *= 2;
                child_ptr = (signed char*)base + size * (child - 1);
                if (child < end) {
                    right_ptr = child_ptr + size;
                    if (compare(child_ptr, right_ptr) < 0) {
                        child_ptr = right_ptr;
                        ++child;
                    }
                }
                if (compare(parent_ptr, child_ptr) >= 0)
                    break;
                {
                    signed char* second = child_ptr - 1;
                    signed char* first = parent_ptr - 1;
                    size_t remaining = size + 1;
                    int temp;
                    while (--remaining) {
                        temp = *++first;
                        *first = *++second;
                        *second = temp;
                    }
                }
            }
        }
    }
}
