typedef unsigned char u8;
typedef unsigned int u32;

typedef struct NOTE NOTE;
struct NOTE {
    NOTE* next;
    NOTE* prev;
    u8 pad08[0xC];
};

typedef struct SEQ_INSTANCE {
    u8 pad000[0xE64];
    NOTE* noteUsed[2];
    NOTE* noteKeyOff;
} SEQ_INSTANCE;

extern NOTE* lbl_8064D384;
#define noteFree lbl_8064D384

void fn_801B244C(SEQ_INSTANCE* seq)
{
    NOTE* n;
    u32 i;
    for (i = 0; i < 2; i++) {
        if ((n = seq->noteUsed[i]) != 0) {
            for (; n->next != 0; n = n->next) {
            }

            if (noteFree != 0) {
                n->next = noteFree;
                noteFree->prev = n;
            }

            noteFree = seq->noteUsed[i];
            seq->noteUsed[i] = 0;
        }
    }

    if ((n = seq->noteKeyOff) != 0) {
        for (; n->next != 0; n = n->next) {
        }

        if (noteFree != 0) {
            n->next = noteFree;
            noteFree->prev = n;
        }

        noteFree = seq->noteKeyOff;
        seq->noteKeyOff = 0;
    }
}
