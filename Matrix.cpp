// Matrix Class
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define MOD 1000000007
#define MAXI(a,b) ((a)>(b)?(a):(b))
#define MINI(a,b) ((a)<(b)?(a):(b))
class Matrix
{
public:
    int N;
    int matrix[SIZE][SIZE];
    Matrix(int n) {N = n;}
    int getDim() {return N;}
    void setZer() {memset(matrix, 0, sizeof(matrix));}
    void setOne()
    {
        int i;
        setZer();
        for (i=0; i<N; ++i) matrix[i][i] = 1;
    }
    void setVal(int array[][SIZE])
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
            for (j=0; j<N; ++j) ret.matrix[i][j] = (matrix[i][j] + A.matrix[i][j]) % MOD;
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
                    temp = (long long) matrix[i][k] * A.matrix[k][j];
                    ret.matrix[i][j] = (ret.matrix[i][j] + temp)%MOD;
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
} base(SIZE), ret(SIZE);
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
Matrix bigmodmat2(Matrix base, int K)
{
    ret = base;
    Matrix ans(base.N);
    ans.setOne();
    while (K)
    {
        if (K % 2) ans = ans * ret;
        K /= 2;
        ret = ret * ret;
    }
    return ans;
}
Matrix bigmod22(Matrix A, int K)
{
    Matrix ret = A;
    --K;
    while (K)
    {
        if (K&1) ret = ret * A;
        A = A * A;
        K >>= 1;
    }
    return ret;
}
int main()
{

    return 0;
}
