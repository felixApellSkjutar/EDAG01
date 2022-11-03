#include <stdio.h> 
#include <stdlib.h> 

double** make_matrix(int m, int n);
int scanMatrix(double** matrix, int m, int n);
int printMatrix(double** matrix, int m, int n);
int main() 
{
	int m,n;
	//&m = address of m
//	scanf("%d %d", &m, &n);
//	printf("m: %d\nn: %d\n", m, n);
	scanf("%d %d", &m, &n);
	double** linearMatrix = make_matrix(m,n);
	scanMatrix(linearMatrix, m, n);
	printMatrix(linearMatrix, m, n);
	return 0;
}

double** make_matrix(int m, int n)
{
	double** a;
	int i;
	int mm = m+2;
	a = calloc(mm, sizeof(double*));
	for (i = 0; i < mm; i += 1)
		a[i] = calloc(n, sizeof(double));
	return a;
}

int scanMatrix(double** matrix, int m, int n)
{
	int i;
	for(i = 0; i < m+2; i++) {
		for(int j = 0; j < n ; j++) {
			scanf("%lf", &(matrix[i][j]));
		}
	}
	return 0;
}

int printMatrix(double** matrix, int m, int n)
{
	printf("max z = ");
	int i;
	for(i = 0; i < m+2; i++) {
		
		for(int j = 0; j < n ; j++) {
			if(i == 0)
			{
				if(j == n-1)	printf("%lf\n\n", matrix[i][j]);
				else 			printf("%lf + ", matrix[i][j]);
			}
			else if (i < m+1)
			{
				if (j == n-1) printf("%lf <= %lf\n",matrix[i][j], matrix[m+1][i-1]); 
				else printf("%lf + ",matrix[i][j] );
			}
			
		}
	}
	return 0;	
}