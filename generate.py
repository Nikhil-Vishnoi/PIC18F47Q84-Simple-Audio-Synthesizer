import numpy as np 
import matplotlib.pyplot as pl 
x = np.linspace(0,49,50) 
values = np.sin(x/49*2*np.pi)*(255/2)+(255/2) 
# values = np.exp(x/49)*np.sin(x/49*2*np.pi)*(255/2)+(255/2)
values = [255]*25 
print(values)
for i in range(25): 
    values.append(0)
# for i in range(len(x)): 
#     if i < 25: 
#         values.append(x[i]*255/(24)) 
#     else: 
#         values.append(255 - (x[i] - 25) * 255 / 24)
# print(values)
s = "{"
for i in range(len(values)): 
    s = s + f"{int(values[i])}" 
    if i + 1 < len(values): 
        s = s + ", " 
s = s + '};'
print(s) 
pl.plot(x,values) 
pl.show()