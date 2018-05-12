int S[2*MAXN];
int N,lj,ljj;
int ord[MAXLG][2*MAXN],t[2*MAXN][2];
int A[2*MAXN], B[2*MAXN], C[2*MAXN], D[2*MAXN],id[MAXN];

void Build( void ){
    int i,j,k,jj;
    memset(A, 0, sizeof(A));
    for (i = 0; i < N; ++i) A[(int)S[i]] = 1;
    for (i = 1; i < 301; ++i) A[i] += A[i-1];
    for (i = 0; i < N; ++i) ord[0][i] = A[(int)S[i]];
    for (j = 0, jj = 1, k = 0; jj < N ; ++j, jj <<= 1){
        memset(A, 0, sizeof(A)); memset(B, 0, sizeof(B));
        for (i = 0; i < N; ++i){
            ++A[ t[i][0] = ord[j][i] ], ++B[ t[i][1] = (i+jj<N) ? ord[j][i+jj] : 0 ];
        }
        for (i = 1; i <= N; ++i) A[i] += A[i-1], B[i] += B[i-1];
        for (i = N-1; i >= 0; --i) C[--B[t[i][1]]] = i;
        for (i = N-1; i >= 0; --i) D[--A[t[C[i]][0]]] = C[i];
        ord[j+1][D[0]] = k = 1;
        for (i = 1; i < N; ++i){
            ord[j+1][D[i]] = (k += (t[D[i]][0] != t[D[i-1]][0] || t[D[i]][1] != t[D[i-1]][1]));
        }
    }
    lj = j; ljj = jj;
    for( i=0;i<N;i++ ) id[ord[lj][i]] = i;
}
int Lcp( int x, int y ){
    int k,j,jj, prf = 0;
    for (j = lj, jj = ljj; j >= 0; --j, jj >>= 1)
        if (x<N && y<N && ord[j][x] == ord[j][y]){
            x   += jj; y   += jj; prf += jj;
        }
    return prf;
}
