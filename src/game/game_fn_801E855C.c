typedef struct Node {
    int word0;
    void* word4;
    struct Node* next;
} Node;

extern Node* lbl_8064D5B0;

int fn_801E855C(int word0, void* word4, Node** result)
{
    Node* node = lbl_8064D5B0;
    int found = 0;

    while (node != 0) {
        if (node->word0 == word0 && node->word4 == word4) {
            if (result != 0) {
                *result = node;
            }
            found = 1;
            break;
        }
        node = node->next;
    }
    return found;
}
