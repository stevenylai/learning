lA = [0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2]
lB = [0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2]

l = []
a, b, c = 5, 1, 2

for x in lA:
    for y in lB:
        PA = (a-b*(x+y)-c)*x
        PB = (a-b*(x+y)-c)*y
        tup = (PA, PB)
        l.append(tup)
    
n = len(lA)        
output=[l[i:i + n] for i in range(0, len(l), n)]
for o in output:
    print(o)
'''
Q1: 25
Q2: 20 20
Q4: 1
'''

'''
[(0, 0),        (0.0, 0.6875),   (0.0, 1.25),     (0.0, 1.6875),   (0, 2),         (0.0, 2.1875),   (0.0, 2.25),       (0.0, 2.1875),     (0, 2)]
[(0.6875, 0.0), (0.625, 0.625),  (0.5625, 1.125), (0.5, 1.5),      (0.4375, 1.75), (0.375, 1.875),  (0.3125, 1.875),   (0.25, 1.75),      (0.1875, 1.5)]

[(1.25, 0.0),   (1.125, 0.5625), (1.0, 1.0),      (0.875, 1.3125), (0.75, 1.5),    (0.625, 1.5625), (0.5, 1.5),        (0.375, 1.3125),   (0.25, 1.0)]

[(1.6875, 0.0), (1.5, 0.5),      (1.3125, 0.875), (1.125, 1.125),  (0.9375, 1.25), (0.75, 1.25),    (0.5625, 1.125),   (0.375, 0.875),    (0.1875, 0.5)]
[(2, 0),        (1.75, 0.4375),  (1.5, 0.75),     (1.25, 0.9375),  (1, 1),         (0.75, 0.9375),  (0.5, 0.75),       (0.25, 0.4375),    (0, 0)]
[(2.1875, 0.0), (1.875, 0.375),  (1.5625, 0.625), (1.25, 0.75),    (0.9375, 0.75), (0.625, 0.625),  (0.3125, 0.375),   (0.0, 0.0),        (-0.3125, -0.5)]

[(2.25, 0.0),   (1.875, 0.3125), (1.5, 0.5),      (1.125, 0.5625), (0.75, 0.5),    (0.375, 0.3125), (0.0, 0.0),        (-0.375, -0.4375), (-0.75, -1.0)]

[(2.1875, 0.0), (1.75, 0.25),    (1.3125, 0.375), (0.875, 0.375),  (0.4375, 0.25), (0.0, 0.0),      (-0.4375, -0.375), (-0.875, -0.875),  (-1.3125, -1.5)]
[(2, 0),        (1.5, 0.1875),   (1.0, 0.25),     (0.5, 0.1875),   (0, 0),         (-0.5, -0.3125), (-1.0, -0.75),     (-1.5, -1.3125),   (-2, -2)]

'''
