
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
/* unified script-VM types reconstructed across the TU */
typedef struct Value {
    union {
        double first;
        int type;
    };
    union {
        void* pointer;
        void** pointer2;
        double number;
        double second;
        void* value;
    };
} Value;

typedef struct Entry {
    Value value;
    int next;
    int pad14;
} Entry;

typedef struct RefEntry {
    s16 id;
    u16 value2;
    u16 value4;
    u16 value6;
} RefEntry;

typedef struct Context {
    void* current;
    char pad04[4];
    void* end;
    char pad0C[0x40];
    union {
        int limit;
        char pad4C[4];
    };
    union {
        struct { Entry* entries; int count; int free; char pad5C[4]; int allocated_size; };
        struct { char pad50[0xC]; int limit_5C; char pad60[4]; };
    };
} Context;
