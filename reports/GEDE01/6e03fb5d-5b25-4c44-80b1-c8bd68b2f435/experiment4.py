from experiment import *
BASE=SRC.read_text()
old='''                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    counter += adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;'''
variants={}
for name,seq in {
'counter_before_store':'''                    counter += adjustment;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;''',
'result_reuse':'''                    transition -= adjustment;
                    adjustment = counter + adjustment;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition;
                    *(int*)(lbl_8030F540 + 0x1CC) = adjustment;''',
'new_result':'''                    { int result = counter + adjustment;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = result; }''',
'assign_result_after':'''                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    { int result = counter + adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = result; }''',
'counter_subtract_negative':'''                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    counter -= -adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;''',
'output_before_transition':'''                    *(int*)(lbl_8030F540 + 0x1CC) = counter + adjustment;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;''',
}.items():
 for typ in ['s16','int']:
  s=BASE.replace(old,seq).replace('                    s16 transition;','                    '+typ+' transition;')
  variants[name+'_'+typ]=s
scores={n:run(n,s) for n,s in variants.items()}
(OUT/'experiments4.json').write_text(json.dumps(scores,indent=2)+'\n');best=max(scores,key=scores.get);SRC.write_text(variants[best] if scores[best]>99.96904 else BASE); print('BEST',best)
