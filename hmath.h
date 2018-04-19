#pragma once
#ifndef _HMATH_H_
#define _HMATH_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include<stdio.h>
//#include"hmodel.h"
#define bool int
typedef double logdouble;
typedef void* Ptr;
typedef double* Vector;
typedef double** Matrix;
typedef int* IntVec;
typedef int** IntMat;

typedef Vector SVector;
typedef Matrix STriMat;
typedef Matrix SMatrix;

IntVec CreateIntVec(int n);
void FreeIntVec(IntVec v);
void ShowIntVec(IntVec v);
IntVec CreateIIntVec(int n, int label);
int IntVecSize(IntVec v);

IntMat CreateIntMat(int nrows, int ncols);
void FreeIntMat(IntMat m);
void ShowIntMat(IntMat m);

Vector CreateVector(int n);
int VectorSize(Vector v);
void ShowVector(Vector v);
void FreeVector(Vector v);

Vector CreateSVector(int n);
int SVectorSize(SVector v);
void ShowSVector(SVector v);
void FreeSVector(SVector v);

Matrix CreateMatrix(int nrows, int ncols);
int NumRows(Matrix m);
int NumCols(Matrix m);
void ShowMatrix(Matrix m);
void FreeMatrix(Matrix m);

SMatrix CreateSMatrix(int nrows, int ncols);
int NumRowsS(SMatrix m);
int NumColsS(SMatrix m);
void ShowSMatrix(SMatrix m);
void FreeSMatrix(SMatrix m);

Matrix CreateSTriMat(int size);
int STriMatSize(STriMat m);
void ShowSTriMat(STriMat m);
void FreeSTriMat(STriMat m);

Ptr GetHook(Ptr m);
void SetHook(Ptr m, Ptr ptr);
void SetUse(Ptr m, int n);

void ZeroVector(Vector v);
void ZeroSVector(SVector v);
void ZeroIntVec(IntVec v);
void ZeroMatrix(Matrix m);
void ZeroIntMat(IntMat m);
void ZeroSTriMat(STriMat m);
void CopyVector(Vector v1, Vector v2);
void CopySVector(SVector v1, SVector v2);
void CopyMatrix(Matrix m1, Matrix m2);
void CopySTriMat(STriMat m1, STriMat m2);
void CopyMatToTri(Matrix m1, STriMat m2);

void WriteMatrix(FILE* f,Matrix m);
void WriteSTriMat(FILE* f, STriMat m);
void WriteSVector(FILE* f,SVector v);
void WriteSVectorE(FILE* f, Vector v);
void WriteSVector2(FILE* f, SVector v);
void WriteIntVec2(FILE* f, IntVec v);

void LoadMatrix(FILE* f, Matrix m);
void LoadStriMat(FILE*f, STriMat m);
void LoadSVector(FILE* f, SVector v);
void LoadSVectorE(FILE* f, Vector v);


bool Choleski(STriMat A, Matrix L);
void MSolve(Matrix L, int i, Vector x, Vector y);
logdouble CovInvert(STriMat c, STriMat invc);
logdouble CovDet(STriMat c);



#ifdef __cplusplus
}
#endif // __cplusplus

#endif