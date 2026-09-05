typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RuntimeNode RuntimeNode;
struct RuntimeNode {
    RuntimeNode* next;
    u8 pad4[0x131C];
    void (*advance)(RuntimeNode*);
    void* state;
    u8 flags;
    u8 pad1329[3];
    u16 completed;
    u8 pad132E[2];
    u32 timer;
};

extern RuntimeNode* lbl_8064D094;
extern u32 lbl_8064BA10;
extern int fn_8015E4E8(void);
extern int fn_8015C628(void*);
extern unsigned int fn_8015C910(void);

void fn_8014B610(void)
{
    RuntimeNode* node = lbl_8064D094;
    int special = fn_8015E4E8();

    while (node != 0) {
        if ((special != 0 && (node->flags & 0x80) != 0) ||
            (special == 0 && ((node->flags & 5) != 0 || fn_8015C628(node->state) != 0) &&
             (fn_8015C910() == 0 || (node->flags & 8) == 0))) {
            u32 target;
            if (node->timer == 0 && node->completed != 0) {
                node->completed = 0;
                node->timer = 0x10000;
            }
            target = node->timer >> 16;
            if (target > node->completed) {
                int count = target - node->completed;
                int i;
                for (i = 0; i < count; i++) {
                    node->advance(node);
                    node->completed++;
                }
            }
            node->timer += lbl_8064BA10;
        }
        node = node->next;
    }
}
