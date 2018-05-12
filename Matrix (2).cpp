#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define MOD 1000000007
#define MAXI(a,b) ((a)>(b)?(a):(b))
#define MINI(a,b) ((a)<(b)?(a):(b))
#define MATSIZE 4
class Matrix
{
    int N;
public:
    int matrix[MATSIZE][MATSIZE];
    Matrix(int n) {N = n;}
    int getDim() {return N;}
    void setVal(int array[][MATSIZE])
    {
        int i,j;
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j) matrix[i][j] = array[i][j];
        }
    }
    Matrix operator+ (Matrix &A)
    {
        Matrix ret(N);
        int i,j;
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j) ret.matrix[i][j] = (matrix[i][j] + A.matrix[i][j])%MOD;
        }
        return ret;
    }
    Matrix operator* (Matrix &A)
    {
        Matrix ret(N);
        int i,j,k;
        long long temp;
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j)
            {
                ret.matrix[i][j] = 0;
                for (k=0; k<N; ++k)
                {
                    temp = (long long) matrix[i][k]*A.matrix[k][j];
                    ret.matrix[i][j] = (ret.matrix[i][j] + temp%MOD)%MOD;
                }
            }
        }
        return ret;
    }
    void printMatrix()
    {
        int i,j;
        puts("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j) printf("%3d ", matrix[i][j]);
            puts("");
        }
        puts("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    }
} base(MATSIZE), ret(MATSIZE);
Matrix bigmod(Matrix A, int K)
{
    if (K==1) return base;
    if (K&1)
    {
        ret = bigmod(A, K-1);
        ret = ret * base;
        return ret;
    }
    ret = bigmod(A, K>>1);
    ret = ret*ret;
    return ret;
}
int main()
{

    return 0;
}
