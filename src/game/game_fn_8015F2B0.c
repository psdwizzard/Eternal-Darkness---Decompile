extern int luaK_getjump(void*, int);
extern void luaK_fixjump(void*, int, int);

void luaK_concat(void* object, int* head, int value)
{
    int index;

    if (*head == -1) {
        *head = value;
    } else {
        index = *head;
        while (1) {
            int next = luaK_getjump(object, index);
            if (next == -1) {
                luaK_fixjump(object, index, value);
                break;
            }
            index = next;
        }
    }
}
