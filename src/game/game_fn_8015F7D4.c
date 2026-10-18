typedef struct OuterObject {
    char pad0[0x28];
    void* object;
} OuterObject;

typedef struct Command {
    int type;
    int first;
    int second;
} Command;

typedef struct Pair {
    int first;
    int second;
} Pair;

extern Pair codes[];
extern void discharge1(void*, Command*);
extern void luaK_concat(void*, int*, int);
extern void luaK_tostack(OuterObject*, Command*, int);
extern int luaK_code1(void*, int, int);

void luaK_posfix(OuterObject* outer, int type, Command* output,
                 Command* input)
{
    void* object = outer->object;

    switch (type) {
    case 12:
        discharge1(object, input);
        output->first = input->first;
        luaK_concat(object, &output->second, input->second);
        break;
    case 13:
        discharge1(object, input);
        output->second = input->second;
        luaK_concat(object, &output->first, input->first);
        break;
    default:
        luaK_tostack(outer, input, 1);
        luaK_code1(object, codes[type].first,
                    codes[type].second);
        break;
    }
}
