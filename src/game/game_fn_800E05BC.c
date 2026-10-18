extern unsigned int rand(void);
#define rand() ((int)rand())

int fn_800E05BC(int first, int second)
{
    int active = first != 0 || second != 0;
    int choice;
    int result;

    if (active != 0) {
        choice = rand() % 6;
    } else {
        choice = rand() % 20;
    }

    switch (choice) {
    case 0:
        result = first != 0 ? -1 : 2;
        break;
    case 1:
        result = second != 0 ? -1 : 3;
        break;
    case 2:
        result = first != 0 ? -1 : 4;
        break;
    case 3:
        result = second != 0 ? -1 : 5;
        break;
    default:
        active = first != 0 || second != 0;
        result = active != 0 ? -1 : choice & 1;
        break;
    }
    return result;
}
