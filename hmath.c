#include "hmath.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
IntVec CreateIntVec(int n)
{
	int *i;int t;
	IntVec v = (int*)malloc(sizeof(int)*(n + 1));
	i = (int *)v; *i = n; for (t = 1; t <= n; t++)v[t] = 0;
	return v;
}
void FreeIntVec(IntVec v) { free(v); }

void ShowIntVec(IntVec v)
{
	int i;
	for (i = 1; i <= VectorSize(v); i++)printf("%d\t", v[i]);
	printf("\n");
}

IntVec CreateIIntVec(int n, int label)
{
	int *i;int t;
	IntVec v = (int*)malloc(sizeof(int)*(n + 1));
	i = (int *)v; *i = n; for (t = 1; t <= n; t++)v[t] = 0; v[label] = 1;
	return v;
}

int IntVecSize(IntVec v)
{
	return *((int*)v);
}

IntMat CreateIntMat(int nrows, int ncols)
{
	size_t vsize;
	int *i, j;
	IntVec *m;
	char *p;//ʹ��char����Ϊ���ǵ����ֽ�
	p = (char*)malloc(sizeof(int)*((ncols + 1)*nrows) + (nrows + 1) * sizeof(IntVec));
	//���е�һ����������,�����Ϊ����,������ĵ�һ�д�������
	i = (int *)p; *i = nrows;
	vsize = (ncols + 1) * sizeof(int);
	m = (IntVec *)p;
	p += (nrows + 1) * sizeof(IntVec);
	for (j = 1; j <= nrows; j++, p += vsize) {
		i = (int *)p; *i = ncols;
		m[j] = (IntVec)p;
	}
	return m;
}

void FreeIntMat(IntMat m) { free(m); }

void ShowIntMat(IntMat m)
{
	int i,j;
	int r = NumRows(m), c = NumCols(m);
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++)printf("%d\t", m[i][j]);
		printf("\n");
	}
}

Vector CreateVector(int n)
{
	int *i;int t;
	Vector v = (double*)malloc(sizeof(double)*(n + 1));
	i = (int *)v; *i = n; for (t = 1; t <= n; t++)v[t] = 0.0;
	return v;
}

int VectorSize(Vector v){
//	printf("%d\n", *((int*)v));
	return *((int*)v);
}

void ShowVector(Vector v)
{
	int i;
	for (i = 1; i <= VectorSize(v); i++)printf("%f\t", v[i]);
	printf("\n");
}

void FreeVector(Vector v) { free(v); }

Vector CreateSVector(int n)
{
	SVector v;
	Ptr *p;
	int *i;
	p = (Ptr *)malloc(sizeof(double)*(n+1)+sizeof(Ptr)*2);
	v = (SVector)(p + 2);
	i = (int *)v; *i = n;
	SetHook(v, NULL);
	SetUse(v, 0);
	return v;
}

int SVectorSize(SVector v)
{
	int *i;
	i = (int *)v;
	return *i;
}

void ShowSVector(SVector v)
{
	int i;
	for (i = 1; i <= SVectorSize(v); i++)printf("%f\t", v[i]);
	printf("\n");
}

void FreeSVector(SVector v)
{
	Ptr* ptr= (Ptr*)v - 2;
	free(ptr);
}

Ptr GetHook(Ptr m)
{
	Ptr *p = (Ptr*)m; p -= 2;
	return *p;//interesting
	//m-=2;return m;
}

void SetHook(Ptr m, Ptr ptr)
{
	Ptr *p = (Ptr*)m; p -= 2; *p = ptr;
}

void SetUse(Ptr m, int n)
{
	Ptr* p = (Ptr*)m; --p; *((int *)p) = n;
}

Matrix CreateMatrix(int nrows, int ncols)
{
	size_t vsize;
	int *i, j;
	Vector *m;
	char *p;//ʹ��char����Ϊ���ǵ����ֽ�
	p = (char*)malloc(sizeof(double)*((ncols + 1)*nrows) + (nrows + 1) * sizeof(Vector));
	//���е�һ����������,�����Ϊ����,������ĵ�һ�д�������
	i = (int *)p; *i = nrows;
	vsize = (ncols+1)*sizeof(double);
	m = (Vector *)p;
	p += (nrows + 1) * sizeof(Vector);
	for (j = 1; j <= nrows; j++, p += vsize) {
		i = (int *)p; *i = ncols;
		m[j] = (Vector)p;
	}
	return m;
}

int NumRows(Matrix m)
{
	int *nrows;
	nrows = (int *)m;
	return *nrows;
}

int NumCols(Matrix m)
{
	int *ncols;
	ncols = (int *)m[1];
	return *ncols;
}

void ShowMatrix(Matrix m)
{
	int r = NumRows(m), c = NumCols(m);
	int i,j;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++)printf("%f\t", m[i][j]);
		printf("\n");
	}
}

void FreeMatrix(Matrix m) { free(m); }

SMatrix CreateSMatrix(int nrows, int ncols)
{
	size_t vsize;
	int *i, j;
	Vector *m;
	char *p;

	p = (char*)malloc(sizeof(double)*((ncols + 1)*nrows) + (nrows + 3) * sizeof(Vector))+2 * sizeof(Ptr *);
	i = (int *)p; *i = nrows;
	vsize = (ncols + 1) * sizeof(double);
	m = (Vector *)p;
	p += (nrows + 1) * sizeof(Vector);
	for (j = 1; j <= nrows; j++, p += vsize) {
		i = (int *)p; *i = ncols;
		m[j] = (Vector)p;
	}
	SetHook(m, NULL);
	SetUse(m, 0);
	return m;
}

int NumRowsS(SMatrix m)
{
	int *nrows;
	nrows = (int *)m;
	return *nrows;
}

int NumColsS(SMatrix m)
{
	int *ncols;
	ncols = (int *)m[1];
	return *ncols;
}

void ShowSMatrix(SMatrix m)
{
	int r = NumRows(m), c = NumCols(m);
	int i,j;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++)printf("%f\t", m[i][j]);
		printf("\n");
	}
}

void FreeSMatrix(SMatrix m)
{
	Ptr* ptr = (Ptr*)m - 2;
	free(ptr);
}

Matrix CreateSTriMat(int size)
{
	int *i, j;
	Vector *m;
	char *p;
	p = (char *)malloc(size*(sizeof(double) * 2 + (size + 1) * sizeof(double)) / 2+ (size + 1) * sizeof(Vector) + 2 * sizeof(Ptr)) + 2 * sizeof(Ptr *);
	i = (int *)p; *i = size;
	m = (Vector *)p;
	p += (size + 1) * sizeof(Vector);
	for (j = 1; j <= size; j++) {
		i = (int *)p; *i = j;
		m[j] = (Vector)p; p += sizeof(double)*(j+1);
	}
	SetHook(m, NULL);
	SetUse(m, 0);
	return m;
}

int STriMatSize(STriMat m)
{
	int *nrows;
	nrows = (int *)m;
	return *nrows;
}

void ShowSTriMat(STriMat m)
{
	int i,j;
	for (i = 1; i <= STriMatSize(m); i++) {
		for (j = 1; j <= i; j++)printf("%f\t", m[i][j]);
		printf("\n");
	}
}


void FreeSTriMat(STriMat m)
{
	Ptr* ptr = (Ptr*)m - 2;
	free(ptr);
}

void CopySTriMat(STriMat m1, STriMat m2)
{
	int i, size;
	size = STriMatSize(m1);
	if (size != STriMatSize(m2))printf("dim dismatch when copying stri");
	for (i = 1; i <= size; i++)
		CopyVector(m1[i], m2[i]);
}

void CopyMatToTri(Matrix m1, STriMat m2)
{
	int i,j;
	if (NumRows(m1) != STriMatSize(m2))printf("dismatch when copying mat to trimat\n");
	for (i = 1; i <= STriMatSize(m2); i++) {
		for (j = 1; j <= i; j++)m2[i][j] = m1[i][j];
	}
}

void WriteMatrix(FILE * f, Matrix m)
{
	int i,j;
	for (i = 1; i <= NumRows(m); i++) {
		for (j = 1; j <= NumCols(m); j++)fprintf(f, "%f\t", m[i][j]);
		fprintf(f, "\n");
	}
}

void WriteSTriMat(FILE * f, STriMat m)
{
	int i,j;double t;
	int size = STriMatSize(m);
	for (i = 1; i <= size; i++) {
		for (j = 1; j <= i; j++) { t = m[i][j]; fprintf(f, "%f\t",t); }
		fprintf(f, "\n");
	}
}


void WriteSVector(FILE * f, SVector v)
{
	int i;
	for (i = 1; i <= SVectorSize(v); i++)fprintf(f, "%f\t", v[i]);
	fprintf(f, "\n");
}

void WriteSVectorE(FILE * f, Vector v)
{
	int i;
	for (i = 1; i <= SVectorSize(v); i++)fprintf(f, "%e\t", v[i]);
	fprintf(f, "\n");
}

/*for dnn read*/
void WriteSVector2(FILE * f, SVector v)
{
	int i;
	fprintf(f,"\n  ");
	for (i = 1; i <= SVectorSize(v); i++)fprintf(f, "%f ", v[i]);
}

void WriteIntVec2(FILE * f, IntVec v)
{
	int i;
	fprintf(f, "\n  ");
	for (i = 1; i <=IntVecSize(v); i++)fprintf(f, "%d ", v[i]);
}

void LoadMatrix(FILE * f, Matrix m)
{
	int i,j;
	for (i = 1; i <= NumRows(m); i++) {
		for (j = 1; j <= NumCols(m); j++)fscanf(f, "%lf\t", &m[i][j]);
		fscanf(f, "\n");
	}
}

void LoadStriMat(FILE * f, STriMat m)
{
	int size = STriMatSize(m);int i,j;
	for (i = 1; i <= size; i++) {
		for (j = 1; j <= i; j++) { fscanf(f, "%lf\t", &m[i][j]); }
		fscanf(f, "\n");
	}
}

void LoadSVector(FILE * f, SVector v)
{
	int size = VectorSize(v);int i;
	for (i = 1; i <= size; i++)fscanf(f, "%lf\t", &v[i]);
}

void LoadSVectorE(FILE * f, Vector v)
{
	int size = VectorSize(v);int i;
	for (i = 1; i <= size; i++)fscanf(f, "%le\t", &v[i]);
}


bool Choleski(STriMat A, Matrix L)
{
	int size, i, j, k;
	double sum;

	size = STriMatSize(A);
	for (i = 1; i <= size; i++)
		for (j = 1; j <= i; j++) {
			sum = A[i][j];
			for (k = 1; k < j; k++) {
				sum -= (L[i][k] * L[j][k]);
			}
			if ((i == j) && (sum <= 0.0))
				return 0;
			else if (i == j)
				sum = sqrt(sum);
			else if (L[j][j] == 0.0)
				return 0;
			else
				sum /= L[j][j];
			L[i][j] = sum;
		}
	for (i = 1; i <= size; i++)
		for (j = i + 1; j <= size; j++)
			L[i][j] = 0.0;
	return 1;
}

void MSolve(Matrix L, int i, Vector x, Vector y)
{
	int nr, j, k;
	double sum;

	nr = NumRows(L);
	for (j = 1; j<i; j++) y[j] = 0.0;  /* forward sub */
	y[i] = 1.0 / L[i][i];
	for (j = i + 1; j <= nr; j++) {
		sum = 0.0;
		for (k = i; k<j; k++)
			sum -= L[j][k] * y[k];
		y[j] = sum / L[j][j];
	}
	x[nr] = y[nr] / L[nr][nr];         /* backward sub */
	for (j = nr - 1; j >= 1; j--) {
		sum = y[j];
		for (k = j + 1; k <= nr; k++)
			sum -= L[k][j] * x[k];
		x[j] = sum / L[j][j];
	}
}

logdouble CovInvert(STriMat c, STriMat invc)
{
	Matrix l;     /* Lower Tri Choleski Matrix */
	Vector x, y;   /* for f/b substitution */
	logdouble ldet = 0.0;
	int i, j, n;
	bool isTri=1;
	for (i = 1; i <= STriMatSize(c); i++)c[i][i] += 0.000001;

	n = STriMatSize(c); 
	x = CreateVector( n);
	y = CreateVector( n);
	l = CreateMatrix(n, n);
	if (Choleski(c, l)) {
		for (j = 1; j <= n; j++) {
			MSolve(l, j, x, y);
			for (i = isTri ? j : 1; i <= n; i++)
				invc[i][j] = x[i];
			ldet += log(l[j][j]);
		}
	}
	else {
		FILE* fcov = fopen("cov.dat", "w");
		WriteSTriMat(fcov, c);
		fclose(fcov);
		printf("the matrix is not inversible\n");
	}
	FreeVector(x); FreeVector(y);
	FreeMatrix( l);    /* cut back stack to entry state */
	return 2.0*ldet;
}

logdouble CovDet(STriMat c)
{
	Matrix l;  /* Lower Tri Choleski Matrix */
	logdouble ldet = 0.0;
	int j, n;

	n = STriMatSize(c);
	l = CreateMatrix( n, n);
	if (Choleski(c, l)) {
		for (j = 1; j <= n; j++)
			ldet += log(l[j][j]);
	}
	else
		printf("the matrix is not inversible\n");
	FreeMatrix( l);
	return 2.0*ldet;
}

void ZeroVector(Vector v)
{
	int i, n;
	n = VectorSize(v);
	for (i = 1; i <= n; i++) v[i] = 0.0;
}

void ZeroSVector(SVector v)
{
	int i, n;
	n = SVectorSize(v);
	for (i = 1; i <= n; i++) v[i] = 0.0;
}

void ZeroIntVec(IntVec v)
{
	int i, n;
	n = VectorSize(v);
	for (i = 1; i <= n; i++) v[i] = 0;
}

void ZeroMatrix(Matrix m)
{
	int r = NumRows(m); int c = NumCols(m);int r0,c0;
	for (r0 = 1; r0 <= r; r0++)for (c0 = 1; c0 <= c; c0++)m[r0][c0] = 0.0;
}

void ZeroIntMat(IntMat m)
{
	int r = NumRows(m); int c = NumCols(m);int r0,c0;
	for (r0 = 1; r0 <= r; r0++)for (c0 = 1; c0 <= c; c0++)m[r0][c0] = 0;
}

void ZeroSTriMat(STriMat m)
{
	int i, j, size;
	size = STriMatSize(m);
	for (i = 1; i <= size; i++)
		for (j = 1; j <= i; j++) m[i][j] = 0.0;
}

void CopyVector(Vector v1, Vector v2)
{
	int i;
	if (VectorSize(v1) != VectorSize(v2)) {
		printf("v1 and v2 size dismatch when copying vector\n"); 	system("pause"); exit(-1);}
	for (i = 1; i <= VectorSize(v1); i++)v2[i] = v1[i];
}

