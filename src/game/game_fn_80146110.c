typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ArithmeticState {
    u16 value, high, low;
} ArithmeticState;

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

typedef struct StreamContext {
    u8 input[0x1000];
    u8 output[0x1000];
    int input_remaining;
    int input_offset;
    int output_offset;
    int input_limit;
    int input_unread;
    int output_count;
    ArithmeticState coder;
    u16 padding201e;
    u32 bits;
    int padding2024;
    DecodeModel model;
    int padding2a90[3];
    int window_size;
    int padding2aa0;
    int window_offset;
    u8 padding2aa8[0x20];
    u8* window;
    int callback_arg;
    void* write_callback;
    void* read_callback;
} StreamContext;

extern void fn_80145E6C(StreamContext*, void*, void*, int, int);
extern void fn_80145EDC(StreamContext*);
extern void fn_80145FCC(void*);
extern void fn_80145F54(StreamContext*);
extern void fn_80145774(u16*, int, int, int, int);

static inline int ReadByte(StreamContext* context)
{
    if (context->input_remaining > 0) {
        context->input_remaining--;
        return context->input[context->input_offset++];
    }
    fn_80145EDC(context);
    if (context->input_remaining > 0) {
        context->input_remaining--;
        return context->input[context->input_offset++];
    }
    return -1;
}

/* The low byte holds a sentinel followed by the remaining input bits. */
#define NEXT_BIT(context, buffer) \
    do { \
        (buffer) <<= 1; \
        if (((buffer) & 0xFF) == 0) { \
            int byte = ReadByte(context); \
            if (byte & 0x100) \
                (buffer) = 0x100; \
            else \
                (buffer) = (byte << 1) | 1; \
        } \
    } while (0)

static inline int GetCount(void* opaque, u32 total)
{
    StreamContext* context = opaque;
    int value = context->coder.value;
    int low = context->coder.low;
    int high = context->coder.high;
    return (int)(total * (value - low + 1) - 1) / (int)(high - low + 1);
}

/* Consume equal leading bits, then resolve arithmetic-coder underflow.
 * Packing the upper and lower bounds lets the underflow test use one mask. */
#define NORMALIZE_STATE(context_, high_, low_, value_, bits_) \
    do { \
        if (((high_ ^ low_) & 0x8000) == 0) { \
            do { \
                high_ <<= 1; \
                high_ |= 1; \
                low_ <<= 1; \
                value_ <<= 1; \
                NEXT_BIT(context_, bits_); \
                value_ |= (bits_ >> 8) & 1; \
            } while (((high_ ^ low_) & 0x8000) == 0); \
        } \
        high_ = (high_ << 16) | low_; \
        if ((int)(high_ & 0x40004000) == 0x4000) { \
            do { \
                high_ <<= 1; \
                high_ &= 0xFFFF7FFF; \
                high_ |= 0x80010000; \
                value_ = (value_ << 1) ^ 0x8000; \
                NEXT_BIT(context_, bits_); \
                value_ |= (bits_ >> 8) & 1; \
            } while ((int)(high_ & 0x40004000) == 0x4000); \
        } \
        context_->coder.low = high_; \
        context_->coder.high = (u32)high_ >> 16; \
        context_->coder.value = value_; \
        context_->bits = bits_; \
    } while (0)

static inline void DecodeInterval(StreamContext* context, int lower, int upper, int total)
{
    u32 high = context->coder.high;
    u32 bottom = context->coder.low;
    u32 bits = context->bits;
    u32 value = context->coder.value;
    int range = high - bottom + 1;
    high = range * upper / total + bottom;
    high--;
    bottom += range * lower / total;

    NORMALIZE_STATE(context, high, bottom, value, bits);
}

static inline void DecodeEndInterval(StreamContext* context, int lower)
{
    int total = lower + 1;
    u32 high = context->coder.high;
    u32 bottom = context->coder.low;
    u32 value = context->coder.value;
    u32 bits = context->bits;
    int range = high - bottom + 1;
    high = range * total / total + bottom;
    high--;
    bottom += range * lower / total;

    NORMALIZE_STATE(context, high, bottom, value, bits);
}

static inline void DecodeTreeInterval(StreamContext* context, int lower, int upper, int total)
{
    /* Reload the committed 16-bit state after the frequency-tree lookup. */
    ArithmeticState* state = (ArithmeticState*)((u8*)context + 0x2018);
    u32 high = state->high;
    u32 bottom = state->low;
    u32 value = state->value;
    u32 bits = context->bits;
    int range = high - bottom + 1;
    high = range * upper;
    high = (int)high / total;
    high += bottom;
    high--;
    bottom += range * lower / total;

    NORMALIZE_STATE(context, high, bottom, value, bits);
}

static inline void FindSymbol(u16* tree, int count, int level, long* symbol, long* cumulative)
{
    *symbol = 2;
    *cumulative = 0;
    for (;;) {
        int frequency = tree[*symbol];
        if (*cumulative + frequency <= count) {
            *cumulative += frequency;
            (*symbol)++;
        }
        if (*symbol >= level) {
            *symbol -= level;
            return;
        }
        *symbol <<= 1;
    }
}

static inline void ScaleTokens(DecodeModel* model, long history, long total)
{
    if (total >= 6000) {
        model->tokens[history].literal >>= 1;
        if (model->tokens[history].literal == 0)
            model->tokens[history].literal = 1;
        model->tokens[history].match >>= 1;
        if (model->tokens[history].match == 0)
            model->tokens[history].match = 1;
    }
}

static inline void WriteByte(StreamContext* context, int byte)
{
    context->output[context->output_offset++] = byte;
    if (context->output_offset == 0x1000)
        fn_80145F54(context);
}

/* Decode an adaptive arithmetic-coded stream into a circular LZ window. */
int fn_80146110(void* opaque, void* write_callback, void* read_callback,
                int callback_arg, int limit, u8* window)
{
    StreamContext* context = opaque;
    DecodeModel* model = &context->model;
    long available;
    long distance;
    long history;

    fn_80145E6C(context, write_callback, read_callback, callback_arg, limit);
    context->window_size = 0x79E0;
    context->window = window;
    context->window_offset = 0;
    fn_80145FCC(context);
    available = model->available;
    history = model->history;

    for (;;) {
        /* Two previous token kinds select the model; one count marks EOF. */
        long literal_frequency = model->tokens[history].literal;
        long token_total = literal_frequency + model->tokens[history].match;
        long count = GetCount(context, token_total + 1);

        if (literal_frequency > count) {
            long total, cumulative, count;
            long literal;
            DecodeInterval(context, 0, literal_frequency, token_total + 1);
            model->tokens[history].literal += 40;
            ScaleTokens(model, history, token_total);
            history = (history << 1) & 2;

            total = model->literals[1] + model->literal_escape;
            count = GetCount(context, total);
            if (count >= model->literals[1]) {
                long node, frequency, i, end;
                DecodeInterval(context, model->literals[1], total, total);
                total = model->new_literals[1];
                count = GetCount(context, total);
                FindSymbol(model->new_literals, count, 0x100, &literal, &cumulative);
                DecodeTreeInterval(context, cumulative,
                               cumulative + model->new_literals[literal + 0x100], total);

                /* Remove this literal from the unseen-symbol tree. */
                node = literal + 0x100;
                frequency = model->new_literals[node];
                while (node != 0) {
                    model->new_literals[node] -= frequency;
                    node >>= 1;
                }
                if (model->new_literals[1] != 0)
                    model->literal_escape++;
                else
                    model->literal_escape = 0;

                end = literal + 8;
                for (i = literal < 8 ? 0 : literal - 8;
                     i < (end < 255 ? end : 255); i++) {
                    if (model->new_literals[i + 0x100] != 0)
                        fn_80145774(model->new_literals, 0x100, 1000, 1, i);
                }
            } else {
                FindSymbol(model->literals, count, 0x100, &literal, &cumulative);
                DecodeTreeInterval(context, cumulative,
                               cumulative + model->literals[literal + 0x100], total);
            }
            fn_80145774(model->literals, 0x100, 1000, 1, literal);
            if (model->literals[literal + 0x100] == 3) {
                long decrement = model->literal_escape > 1 ? 1 : model->literal_escape - 1;
                model->literal_escape -= decrement;
            }
            context->window[context->window_offset] = literal;
            WriteByte(context, literal);
            if (++context->window_offset == context->window_size)
                context->window_offset = 0;
            if (available < 0x79E0)
                available++;
            continue;
        }
        if (token_total > count) {
            long total, count, cumulative;
            long length;
            DecodeInterval(context, literal_frequency, token_total, token_total + 1);
            model->tokens[history].match += 40;
            ScaleTokens(model, history, token_total);
            history = ((history << 1) | 1) & 3;

            while (available > model->distance_limit) {
                fn_80145774(model->distances, 16, 6000, 24, model->distance_bits++);
                model->distance_limit <<= 1;
            }
            total = model->distances[1];
            count = GetCount(context, total);
            FindSymbol(model->distances, count, 16, &distance, &cumulative);
            DecodeTreeInterval(context, cumulative,
                           cumulative + model->distances[distance + 16], total);
            fn_80145774(model->distances, 16, 6000, 24, distance);
            /* Expand the distance class with a uniformly coded residual. */
            if (distance > 1) {
                long power = 1;
                long i;
                long base, total, offset;
                for (i = distance; i != 0; i--)
                    power <<= 1;
                base = power >> 1;
                total = base;
                if (base == (model->distance_limit >> 1))
                    total = available - (model->distance_limit >> 1);
                offset = GetCount(context, total);
                DecodeInterval(context, offset, offset + 1, total);
                distance = offset + base;
            }

            total = model->lengths[1] + model->length_escape;
            count = GetCount(context, total);
            if (count >= model->lengths[1]) {
                long node, frequency, end;
                int i;
                DecodeInterval(context, model->lengths[1], total, total);
                total = model->new_lengths[1];
                count = GetCount(context, total);
                FindSymbol(model->new_lengths, count, 64, &length, &cumulative);
                DecodeTreeInterval(context, cumulative,
                               cumulative + model->new_lengths[length + 64], total);
                /* Remove this length from the unseen-symbol tree. */
                node = length + 64;
                frequency = model->new_lengths[node];
                while (node != 0) {
                    model->new_lengths[node] -= frequency;
                    node >>= 1;
                }
                if (model->new_lengths[1] != 0)
                    model->length_escape += 8;
                else
                    model->length_escape = 0;

                end = length + 4;
                for (i = length < 4 ? 0 : length - 4;
                     i < (end < 63 ? end : 63); i++) {
                    if (model->new_lengths[i + 64] != 0)
                        fn_80145774(model->new_lengths, 64, 6000, 1, i);
                }
            } else {
                FindSymbol(model->lengths, count, 64, &length, &cumulative);
                DecodeTreeInterval(context, cumulative,
                               cumulative + model->lengths[length + 64], total);
            }
            fn_80145774(model->lengths, 64, 6000, 8, length);
            if (model->lengths[length + 64] == 24) {
                long decrement = model->length_escape > 8 ? 8 : model->length_escape - 1;
                model->length_escape -= decrement;
            }
            if (length == 15) {
                length = 0x30F;
            } else if (length >= 16) {
                long offset = GetCount(context, 16);
                DecodeInterval(context, offset, offset + 1, 16);
                length = (length - 16) * 16 + (offset + 15);
            }
            if (available < 0x79E0) {
                available += length + 3;
                if (available > 0x79E0)
                    available = 0x79E0;
            }
            {
                long destination = context->window_offset;
                long remaining = length + 3;
                long size = context->window_size;
                u8* window = context->window;
                long source;
                if (destination > distance)
                    source = destination - 1 - distance;
                else
                    source = destination + (size - 1 - distance);
                while (remaining-- != 0) {
                    window[destination] = window[source];
                    WriteByte(context, window[source]);
                    if (++destination == size)
                        destination = 0;
                    if (++source == size)
                        source = 0;
                }
                context->window_offset = destination;
            }
            continue;
        }
        DecodeEndInterval(context, token_total);
        break;
    }
    fn_80145F54(context);
    return context->output_count;
}
