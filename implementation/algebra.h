#pragma once

#include "common.h"

#include <vector>
#include <cassert>
#include <algorithm>
#include <utility>

const int P = 10427;

int Multiply(int a, int b);
int Add(int a, int b);
int Negate(int x);

void InitializeInverses();
int Inverse(int x);

using TMatrix = std::vector<std::vector<int>>;
using TVector = std::vector<int>;

void SwapRows(TMatrix& A, int i, int j);
void SwapColumns(TMatrix& A, int i, int j);

void AddRow(TMatrix& A, int i, int j, int c);
void AddColumn(TMatrix& A, int i, int j, int c);

void MultiplyRow(TMatrix& A, int i, int c);
void MultiplyColumn(TMatrix& A, int i, int c);

TMatrix IdentityMatrix(int n);

TVector Multiply(TMatrix A, TVector B);

int Dot(TVector A, TVector B);

// Build such matrices L and R that that for any vectors u, v
// u^T * A * v = (Lu)^T * (Rv).
void CanonizeBilinearForm(TMatrix& A, TMatrix& L, TMatrix& R);
