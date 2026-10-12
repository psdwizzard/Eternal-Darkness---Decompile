typedef unsigned short u16;

typedef struct TokenFrequencies {
    u16 literal, match;
} TokenFrequencies;

typedef struct DecodeModel {
    u16 lengths[0x80];
    u16 new_lengths[0x80];
    u16 distances[0x20];
    u16 literals[0x200];
    u16 new_literals[0x200];
    TokenFrequencies tokens[4];
    int available;
    int distance_limit;
    int distance_bits;
    int literal_escape;
    int length_escape;
    int history;
} DecodeModel;

extern void fn_80145774(u16*, int, int, int, int);

void fn_801458C4(DecodeModel* model)
{
    int i;

    model->literal_escape = 1;
    model->length_escape = 8;
    model->available = 0;
    model->history = 0;
    model->distance_limit = 1;
    model->distance_bits = 1;
    for (i = 0; i < 4; i++) {
        model->tokens[i].literal = model->tokens[i].match = 40;
    }

    for (i = 0x40; i < 0x80; i++)
        model->lengths[i] = 0;
    for (i = 0x3F; i > 0; i--)
        model->lengths[i] = model->lengths[i * 2] + model->lengths[i * 2 + 1];

    for (i = 0x40; i < 0x80; i++)
        model->new_lengths[i] = 1;
    for (i = 0x3F; i > 0; i--)
        model->new_lengths[i] = model->new_lengths[i * 2] + model->new_lengths[i * 2 + 1];

    for (i = 0x100; i < 0x200; i++)
        model->literals[i] = 0;
    for (i = 0xFF; i > 0; i--)
        model->literals[i] = model->literals[i * 2] + model->literals[i * 2 + 1];

    for (i = 0x100; i < 0x200; i++)
        model->new_literals[i] = 1;
    for (i = 0xFF; i > 0; i--)
        model->new_literals[i] = model->new_literals[i * 2] + model->new_literals[i * 2 + 1];

    for (i = 0x10; i < 0x20; i++)
        model->distances[i] = 0;
    for (i = 0xF; i > 0; i--)
        model->distances[i] = model->distances[i * 2] + model->distances[i * 2 + 1];

    fn_80145774(model->distances, 16, 6000, 24, 0);
}
