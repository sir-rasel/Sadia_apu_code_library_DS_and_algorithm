int fastMax(int x, int y) { return (((y-x)>>(32-1))&(x^y))^y; }
if y < x, then (y — x) >> 31 = -1.
-1 & (x ^ y) = (x ^ y).
(x ^ y) ^ y = x.
if y >= x, then (y — x) >> 31 = 0.
0 & (x ^ y) = 0.
0 ^ y = y.
