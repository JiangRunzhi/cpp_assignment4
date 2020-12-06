#include "Matrix.hpp"
using namespace std;
int main() {
    Matrix A();

    Matrix B(10,10);

    int m = 10;
    int n =10;
    float** mat = new float*[m];
    for(int i=0;i<m;i++){
        mat[i] = new float [n];
    }
    mat[m-1][n-2] = 1;

    Matrix C(m,n,mat);

    Matrix D(C);

    Matrix E = C;

    cout << E;

    Scalar a(10);
    Matrix F(10,1);
    a*B;
    B*C;
    F*a;

    return 0;
}
