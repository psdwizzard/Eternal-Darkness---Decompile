typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State {
    void* object;
    u8 pad4[8];
    u8 timer;
    u8 state;
} State;

typedef struct Event {
    int unused;
    int type;
} Event;

extern void *fn_80201814();
extern void *fn_80201B8C();
extern int fn_80201B5C(void*);
extern u8 fn_8008C9BC(State*, void*);
extern u8 fn_8008CA28(void*, void*);
extern void *fn_80201BC8();
extern void fn_8011F114();
extern void fn_8008CBA4(State*);

int fn_8008C7F8(State* state, void* object, Vec3* position, void* owner,
                Event* event)
{
    int allowed = 1;
    void* ownerObject = fn_80201814(owner);
    void* objectState;
    int result = 0;

    objectState = fn_80201B8C(object);

    if (event != 0) {
        switch (event->type) {
        case 30:
        case 31:
        case 81:
        case 82:
            allowed = 0;
            break;
        }
    }
    if (allowed && fn_80201B5C(ownerObject) == 50)
        allowed = 0;
    if (allowed && fn_8008C9BC(state, objectState)) {
        void* currentOwner = fn_80201814(owner);
        if (fn_8008CA28(object, currentOwner)) {
            void* resource = currentOwner != 0 ? fn_80201BC8(currentOwner) : 0;
            if (resource != 0) {
                Vec3 source;
                fn_8011F114(&source, resource);
                *position = source;
                state->object = owner;
                fn_8008CBA4(state);
                result = 1;
            }
        }
    }
    return result;
}
