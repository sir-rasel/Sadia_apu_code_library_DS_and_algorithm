inline int FastMax(int x, int y) { return (((y-x)>>(32-1))&(x^y))^y; }
inline int FastMin(int x, int y) { return (((y-x)>>(32-1))&(x^y))^x; }
