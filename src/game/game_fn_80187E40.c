typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_8064C278;
extern double lbl_80650A40;
extern volatile float lbl_80650A58;
extern float lbl_80650A5C;
extern void* fn_8015C910(void*);
extern u8 fn_8018E26C(void*, void*);
extern void fn_8018E230(void*, void*, int, u8, u8, int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int fn_80187E40(u8* self)
{
    u8* self_local = self;
    u8* entry = *(u8**)(self_local + 0x4C);
    float value;
    float bound;

    if (*(int*)(self_local + 0xA8) == 0 ||
        fn_8015C910(self_local) == 0) {
      if (entry[0] != 0 && fn_8018E26C(entry, entry + 0x2B) == 0) {
          *(u16*)(self_local + 0x22) = 8;
      } else {
        if (*(int*)(self_local + 0xA4) != 0) {
            fn_8018E230(entry, entry + 0x2B, 1, self_local[2],
                        self_local[4], 0);
            *(int*)(self_local + 0xA4) = 0;
        }

        if (*(int*)(self_local + 0x9C) != 0) {
            value = *(volatile float*)(self_local + 0xAC) +
                    *(volatile float*)(self_local + 0xB8);
            bound = lbl_80650A58;
            if (value > bound) {
                bound = value;
            }
            if (lbl_80650A5C < bound) {
                value = lbl_80650A5C;
            } else {
                bound = lbl_80650A58;
                if (value > bound) {
                    bound = value;
                }
                value = bound;
            }
            *(float*)(self_local + 0xB8) = value;

            bound = lbl_80650A58;
            value = *(volatile float*)(self_local + 0xB0);
            value += *(volatile float*)(self_local + 0xBC);
            if (value > bound) {
                bound = value;
            }
            if (lbl_80650A5C < bound) {
                value = lbl_80650A5C;
            } else {
                bound = lbl_80650A58;
                if (value > bound) {
                    bound = value;
                }
                value = bound;
            }
            *(float*)(self_local + 0xBC) = value;

            bound = lbl_80650A58;
            value = *(volatile float*)(self_local + 0xB4);
            value += *(volatile float*)(self_local + 0xC0);
            if (value > bound) {
                bound = value;
            }
            if (lbl_80650A5C < bound) {
                value = lbl_80650A5C;
            } else {
                bound = lbl_80650A58;
                if (value > bound) {
                    bound = value;
                }
                value = bound;
            }
            *(float*)(self_local + 0xC0) = value;

            entry[0x28] = *(float*)(self_local + 0xB8);
            entry[0x29] = *(float*)(self_local + 0xBC);
            entry[0x2A] = *(float*)(self_local + 0xC0);
            ++*(u16*)(self_local + 0xE0);
        }

          value = *(float*)(self_local + 0xC8) +
                  *(float*)(self_local + 0xC4);
          *(float*)(self_local + 0xC8) =
              MIN(value, (float)self_local[0x8D]);
          entry[0x21] = *(float*)(self_local + 0xC8);
      }

      ++*(u16*)(self_local + 0xA);
    } else {
      *(u32*)(self_local + 0x44) -= lbl_8064C278;
    }
    return 0;
}
