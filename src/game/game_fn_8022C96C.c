/* Compare signed characters, treating either string ending as equal. */
signed char fn_8022C96C(const char *left, const char *right)
{
    do {
        if ((signed char)*left < (signed char)*right) {
            return 1;
        }
        if ((signed char)*left > (signed char)*right) {
            return -1;
        }
        ++left;
        ++right;
    } while ((signed char)*left != 0 && (signed char)*right != 0);
    return 0;
}
