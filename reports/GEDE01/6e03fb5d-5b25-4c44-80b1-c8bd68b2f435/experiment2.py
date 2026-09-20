from experiment import *
BASE=SRC.read_text()
variants={}
a='''        kind = *(u8*)(lbl_8030F540 + 0x1DA);
        descriptor = lbl_80241DE8;
        descriptor += kind;'''
b='''        descriptor = lbl_80241DE8;
        kind = *(u8*)(lbl_8030F540 + 0x1DA);
        descriptor += kind;'''
variants['base_before_kind']=BASE.replace(a,b)
variants['first_base_before_kind']=BASE.replace(a,b,1)
variants['int_transition']=BASE.replace('                    s16 transition;','                    int transition;')
variants['unsigned_adjustment']=BASE.replace('                    int adjustment;','                    unsigned int adjustment;')
variants['commute_counter2']=BASE.replace('= counter + adjustment;','= adjustment + counter;')
old='''                    transition = *(s16*)(lbl_8030F540 + 0x1D6);
                    adjustment = batch->adjustment - selected;
                    adjustment <<= 1;
                    counter = *(int*)(lbl_8030F540 + 0x1CC);
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter + adjustment;'''
for n,new in {
'assign_full':'''                    transition = *(s16*)(lbl_8030F540 + 0x1D6);
                    adjustment = (batch->adjustment - selected) << 1;
                    counter = *(int*)(lbl_8030F540 + 0x1CC);
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter + adjustment;''',
'read_counter_first':'''                    counter = *(int*)(lbl_8030F540 + 0x1CC);
                    transition = *(s16*)(lbl_8030F540 + 0x1D6);
                    adjustment = batch->adjustment - selected;
                    adjustment <<= 1;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter + adjustment;''',
'adjust_counter':'''                    transition = *(s16*)(lbl_8030F540 + 0x1D6);
                    adjustment = batch->adjustment - selected;
                    adjustment <<= 1;
                    counter = *(int*)(lbl_8030F540 + 0x1CC);
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    counter += adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;''',
'int_inplace':'''                    transition = *(s16*)(lbl_8030F540 + 0x1D6);
                    adjustment = batch->adjustment - selected;
                    adjustment <<= 1;
                    counter = *(int*)(lbl_8030F540 + 0x1CC);
                    transition -= adjustment;
                    counter += adjustment;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;''',
}.items():
 s=BASE.replace(old,new)
 if n=='int_inplace':s=s.replace('                    s16 transition;','                    int transition;')
 variants[n]=s
scores={n:run(n,s) for n,s in variants.items()}
(OUT/'experiments2.json').write_text(json.dumps(scores,indent=2)+'\n')
best=max(scores,key=scores.get); SRC.write_text(variants[best] if scores[best]>99.79876 else BASE); print('BEST',best)
