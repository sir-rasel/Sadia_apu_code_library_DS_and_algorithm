struct seg
{
    int x1,y1,x2,y2;
} segs[MAXN];
pair < int , int > slopes[MAXN];
int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd (b, a%b);
}
int area(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
}
pair < int , int > slope(seg a)
{
    pair < int , int > ret;
    ret.first = a.y2 - a.y1;
    ret.second = a.x2 - a.x1;
    int g = gcd(ret.first, ret.second);
    ret.first /= g, ret.second /= g;
    if (ret.first < 0 && ret.second < 0)
    {
        ret.first = -ret.first;
        ret.second = -ret.second;
    }
    if ((ret.first < 0) + (ret.second < 0) == 1 && ret.first >= 0)
    {
        ret.first = -ret.first;
        ret.second = -ret.second;
    }
    return ret;
}
int sign(int x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
bool inseg(seg s, int x, int y)
{
    int x1 = MINI(s.x1,s.x2), x2 = MAXI(s.x1,s.x2);
    int y1 = MINI(s.y1,s.y2), y2 = MAXI(s.y1,s.y2);
    if (x1 <= x && x <= x2 && y1 <= y && y <= y2) return true;
    return false;
}
bool check(seg a, seg b)
{
    pair < int , int > sa = slope(a), sb = slope(b);
    int area1, area2;
    if (sa != sb)
    {
        area1 = area(a.x1,a.y1,a.x2,a.y2,b.x1,b.y1);
        if (area1 == 0 && inseg(a,b.x1,b.y1)) return true;
        area2 = area(a.x1,a.y1,a.x2,a.y2,b.x2,b.y2);
        if (area2 == 0 && inseg(a,b.x2,b.y2)) return true;
        if (area1 == 0 || area2 == 0) return false;
        if (sign(area1) == sign(area2)) return false;
        area1 = area(b.x1,b.y1,b.x2,b.y2,a.x1,a.y1);
        if (area1 == 0 && inseg(b,a.x1,a.y1)) return true;
        area2 = area(b.x1,b.y1,b.x2,b.y2,a.x2,a.y2);
        if (area2 == 0 && inseg(b,a.x2,a.y2)) return true;
        if (area1 == 0 || area2 == 0) return false;
        if (sign(area1) != sign(area2)) return true;
        return false;
    }
    area1 = area(a.x1,a.y1,a.x2,a.y2,b.x1,b.y1);
    area2 = area(a.x1,a.y1,a.x2,a.y2,b.x2,b.y2);
    if (area1 && area2) return false;
    if (inseg(a,b.x1,b.y1) || inseg(a,b.x2,b.y2)) return true;
    return false;
}
