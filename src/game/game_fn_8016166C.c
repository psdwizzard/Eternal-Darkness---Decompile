typedef struct Node Node;

typedef struct Row {
    Node* nodes[15];
    int unused;
} Row;

typedef struct Collection {
    char pad[0x48];
    Row* rows;
    int last_row;
} Collection;

#pragma use_lmw_stmw on

extern void markclosure(void*, Node*);

void marktagmethods(Collection* collection, void* list)
{
    int column;
    int row;

    for (column = 0; column < 15; column++) {
        for (row = 0; row <= collection->last_row; row++) {
            Node* node = collection->rows[row].nodes[column];
            if (node != 0)
                markclosure(list, node);
        }
    }
}
