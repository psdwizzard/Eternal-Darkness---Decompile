typedef struct Value {
    int type;
    int pad04;
    union {
        void* pointer;
        double number;
        unsigned int word;
    } data;
} Value;

int luaO_equalObj(Value* left, Value* right)
{
    if (left->type != right->type) {
        return 0;
    }

    switch (left->type) {
    case 2:
        return left->data.number == right->data.number;
    case 0:
    case 3:
        return left->data.pointer == right->data.pointer;
    case 4:
        return left->data.pointer == right->data.pointer;
    case 5:
        return left->data.pointer == right->data.pointer;
    default:
        return 1;
    }
}
