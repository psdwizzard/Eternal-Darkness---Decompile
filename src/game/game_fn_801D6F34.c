typedef unsigned int u32;

typedef struct CandidateData {
    unsigned char pad00[8];
    int object_id;
    unsigned char pad0C[4];
    int owner;
    unsigned char pad14[0x10];
    unsigned char position[12];
} CandidateData;

typedef struct Candidate {
    unsigned char pad00[0x2C];
    CandidateData* data;
} Candidate;

extern void* fn_80201814(int);
extern int fn_80201EB8(void);
extern void* fn_80201B9C(void);
extern int fn_80201B5C(void*);
extern Candidate* fn_80201B8C(void*);
extern unsigned int fn_80179004(void*, void*);
extern void* fn_80201BC0(void*);

int fn_801D6F34(int object_id, void* position)
{
    int owner;
    int found;
    void* iterator;

    found = 0;
    if (fn_80201814(object_id) != 0) {
        owner = fn_80201EB8();
        iterator = fn_80201B9C();
        while (iterator != 0) {
            if (fn_80201B5C(iterator) == 25) {
                CandidateData* data = fn_80201B8C(iterator)->data;
                if (data->owner == owner && data->object_id == object_id &&
                    fn_80179004(position, data->position) < 100) {
                    found = 1;
                    break;
                }
            }
            iterator = fn_80201BC0(iterator);
        }
    }
    return found;
}
