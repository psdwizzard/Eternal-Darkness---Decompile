from experiment import *
BASE=SRC.read_text()
old='''                    counter += adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;'''
variants={
'last_reuse_adjustment':BASE.replace(old,'''                    adjustment = counter + adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = adjustment;'''),
'last_adjustment_compound':BASE.replace(old,'''                    adjustment += counter;
                    *(int*)(lbl_8030F540 + 0x1CC) = adjustment;'''),
'last_counter_reverse':BASE.replace(old,'''                    counter = adjustment + counter;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;'''),
'last_signed_counter':BASE.replace('                    int counter;','                    unsigned int counter;'),
}
scores={n:run(n,s) for n,s in variants.items()}
(OUT/'experiments3.json').write_text(json.dumps(scores,indent=2)+'\n');best=max(scores,key=scores.get);SRC.write_text(variants[best] if scores[best]>99.96904 else BASE); print('BEST',best)
