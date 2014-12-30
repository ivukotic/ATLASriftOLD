
f=file('8.wrl','r')
lines=f.readlines()

allShapes=[]
count=0
skip=0
shape=[]
for l in lines:
  l=l.strip('\r\n')
  if len(l)==0: continue
  if l.count("Shape"):
    shape.append(l)
    count+=1
    continue
  if count>0:
    shape.append(l)
    if l.count('{'): count+=1
    if l.count('}'): count-=1
    if l.count('IndexedLineSet') or l.count('_material3'): skip=1
    if count==0: 
      if skip==0:
          allShapes.append(shape)
          print len(allShapes)
      else:
          skip=0
      shape=[]
    
of=file('8MP.wrl','w')  
for s in allShapes:
    for l in s:
        of.write(l+'\n')
        