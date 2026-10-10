typedef struct Entry {
    int value;
    int object;
    int resource;
    int callback;
    int state;
    int index;
    unsigned short flags;
    unsigned short pad;
} Entry;

typedef struct Region {
    unsigned char pad00[0x3A];
    short first[2];
    short second[2];
    unsigned char pad42[0x26];
    unsigned int flags;
    short side;
    short angle;
    unsigned char pad70[4];
} Region;

typedef struct RegionSet {
    unsigned char pad00[0xB0];
    unsigned short count;
    unsigned short padB2;
    Region* regions;
} RegionSet;

extern Entry lbl_80332428[];
extern int lbl_8064D1BC;
extern void* fn_8015C28C(int selector);

int fn_8011E310(int object, int resource, int callback, int id,
                int value, int index, int flags)
{
    RegionSet* set;
    Region* regions;
    unsigned short i;

    switch (index) {
    case 2:
    case 4:
        if (id > 0 && value > lbl_80332428[index].value) {
            set = fn_8015C28C(2);
            regions = set->regions;
            for (i = 0; i < set->count; i++) {
                if (regions[i].flags & 1) {
                    switch (regions[i].side) {
                    case 0:
                        if ((id == regions[i].first[0] || id == regions[i].second[0] ||
                             (lbl_8064D1BC == 0 && lbl_8064D1BC == regions[i].first[0]) ||
                             lbl_8064D1BC == regions[i].second[0]) &&
                            regions[i].angle >= 90 && index == 2) {
                            return fn_8011E310(object, resource, callback, id, value, 4, flags);
                        }
                        break;
                    case 1:
                        if ((id == regions[i].first[1] || id == regions[i].second[1] ||
                             (lbl_8064D1BC == 0 && lbl_8064D1BC == regions[i].first[1]) ||
                             lbl_8064D1BC == regions[i].second[1]) &&
                            regions[i].angle >= 90 && index == 2) {
                            return fn_8011E310(object, resource, callback, id, value, 4, flags);
                        }
                        break;
                    }
                }
            }
            lbl_80332428[index].callback = callback;
            lbl_80332428[index].object = object;
            lbl_80332428[index].resource = resource;
            lbl_80332428[index].index = index;
            lbl_80332428[index].flags = flags;
            return index;
        }
        break;
    case 0:
    case 1:
    case 3:
    case 5:
        if (value >= lbl_80332428[index].value) {
            lbl_80332428[index].callback = callback;
            lbl_80332428[index].value = value;
            lbl_80332428[index].object = object;
            lbl_80332428[index].resource = resource;
            lbl_80332428[index].index = index;
            lbl_80332428[index].flags = flags;
            return index;
        }
        break;
    }
    return -1;
}
