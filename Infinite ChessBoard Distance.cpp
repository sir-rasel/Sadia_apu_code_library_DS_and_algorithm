Infinite chessboard distance between 2 cells.
int f(int x1, int y1, int x2, int y2)
{
  int dx=abs(x2-x1);
  int dy=abs(y2-y1);
  int lb=(dx+1)/2;
  lb>?=(dy+1)/2;
  lb>?=(dx+dy+2)/3;
  while ((lb%2)!=(dx+dy)%2) lb++;
  if (abs(dx)==1 && dy==0) return 3;
  if (abs(dy)==1 && dx==0) return 3;
  if (abs(dx)==2 && abs(dy)==2) return 4;
  return lb;
}
