typedef struct TokenStream {
    char pad0[0x18];
    unsigned int* tokens;
    int pad1;
    short initial_depth;
    short add_one;
} TokenStream;

typedef struct TokenInfo {
    unsigned char unused;
    unsigned char run;
    unsigned char back;
} TokenInfo;

extern const TokenInfo luaK_opproperties[];
extern int pushpc(int*, int, int, int);

unsigned int luaG_symbexec(TokenStream* stream, int limit, int selected)
{
    int positions[250];
    unsigned int* tokens = stream->tokens;
    int cursor = 0;
    int depth = stream->initial_depth;

    if (stream->add_one)
        depth++;

    while (cursor < limit) {
        unsigned int token = tokens[cursor++];
        unsigned int type = token & 0x3f;
        int amount;

        switch (type) {
        case 1:
            depth = token >> 6;
            break;
        case 3:
            depth = (token >> 6) & 0x1ff;
            break;
        case 2:
            amount = (token >> 6) & 0x1ff;
            if (amount == 255)
                amount = 1;
            depth = pushpc(positions, cursor, token >> 15, amount);
            break;
        case 4:
            depth = pushpc(positions, cursor, depth, token >> 6);
            break;
        case 5:
            depth -= token >> 6;
            break;
        case 20:
        case 21:
            depth -= (token >> 6) & 0x1ff;
            break;
        case 22:
            depth -= (token >> 5) & 0x7fffffe;
            break;
        case 29:
            depth -= token >> 6;
            positions[depth++] = cursor - 1;
            break;
        case 48:
            depth -= (token >> 6) & 0x1ff;
            positions[depth++] = cursor - 1;
            break;
        case 40:
        case 41: {
            int next = (int)(token >> 6) - 0x2000000 + cursor + 1;
            if (cursor < next && next <= limit) {
                positions[depth - 1] = cursor - 1;
                cursor = next;
            } else {
                depth--;
            }
            break;
        }
        default:
            depth -= luaK_opproperties[type].back;
            depth = pushpc(positions, cursor, depth,
                               luaK_opproperties[type].run);
            break;
        }
    }

    return tokens[positions[selected]];
}
