//
// Created by max42 on 03.05.18.
//

#include "algebra.h"

int Inverses[P];

int Multiply(int a, int b)
{
    return a * b % P;
}

int Add(int a, int b)
{
    a += b;
    if (a >= P) {
        a -= P;
    }
    return a;
}

int Negate(int x)
{
    return (x == 0) ? 0 : P - x;
}

bool InversesInitialized = false;
void InitializeInverses()
{
    for (int i = 1; i < P; i++) {
        Inverses[i] = -1;
        for (int j = 0; j < P; j++) {
            if (Multiply(i, j) == 1) {
                Inverses[i] = j;
                break;
            }
        }
        assert(Inverses[i] != -1);
    }
    InversesInitialized = true;
}

int Inverse(int x)
{
    if (!InversesInitialized) {
        InitializeInverses();
    }
    return Inverses[x];
}

void SwapColumns(TMatrix& A, int i, int j)
{
    int n = A.size();
    for (int k = 0; k < n; k++) {
        std::swap(A[k][i], A[k][j]);
    }
}

void SwapRows(TMatrix& A, int i, int j)
{
    int n = A.size();
    for (int k = 0; k < n; k++) {
        std::swap(A[i][k], A[j][k]);
    }
}

void AddRow(TMatrix& A, int i, int j, int c)
{
    int n = A.size();
    for (int k = 0; k < n; k++) {
        A[i][k] = Add(A[i][k], Multiply(c, A[j][k]));
    }
}

void AddColumn(TMatrix& A, int i, int j, int c)
{
    int n = A.size();
    for (int k = 0; k < n; k++) {
        A[k][i] = Add(A[k][i], Multiply(c, A[k][j]));
    }
}

void MultiplyRow(TMatrix& A, int i, int c)
{
    int n = A.size();
    for (int j = 0; j < n; j++) {
        A[i][j] = Multiply(A[i][j], c);
    }
}

void MultiplyColumn(TMatrix& A, int i, int c)
{
    int n = A.size();
    for (int j = 0; j < n; j++) {
        A[j][i] = Multiply(A[j][i], c);
    }
}

TMatrix IdentityMatrix(int n)
{
    TMatrix result(n, TVector(n));
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    return result;
}

void CanonizeBilinearForm(TMatrix& A, TMatrix& L, TMatrix& R)
{
    TMatrix originalA = A;
    int n = A.size();
    L = IdentityMatrix(n);
    R = IdentityMatrix(n);
    for (int i = 0; i < n; i++) {
        int nonZeroRow = -1, nonZeroColumn = -1;
        for (int j = i; j < n; j++) {
            for (int k = i; k < n; k++) {
                if (A[j][k] != 0) {
                    nonZeroRow = j;
                    nonZeroColumn = k;
                }
            }
        }
        if (nonZeroColumn == -1) {
            break;
        }
        SwapRows(A, nonZeroRow, i);
        SwapRows(L, nonZeroRow, i);
        SwapColumns(A, nonZeroColumn, i);
        SwapRows(R, nonZeroColumn, i);
        {
            int c = A[i][i];
            MultiplyRow(A, i, Inverse(c));
            MultiplyRow(L, i, c);
        }
        for (int j = i + 1; j < n; j++) {
            int c = A[j][i];
            AddRow(A, j, i, Negate(c));
            AddRow(L, i, j, c);
        }
        for (int j = i + 1; j < n; j++) {
            int c = A[i][j];
            AddColumn(A, j, i, Negate(c));
            AddRow(R, i, j, c);
        }
    }
    int rank = 0;
    while (rank < n && A[rank][rank] > 0) {
        ++rank;
    }
    for (int i = rank; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = R[i][j] = 0;
        }
    }
}

TVector Multiply(TMatrix A, TVector B)
{
    TVector result(A.size());
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A.size(); j++) {
            result[i] = Add(result[i], Multiply(A[i][j], B[j]));
        }
    }
    return result;
}

int Dot(TVector A, TVector B)
{
    int result = 0;
    for (int i = 0; i < A.size(); ++i) {
        result = Add(result, Multiply(A[i], B[i]));
    }
    return result;
}
