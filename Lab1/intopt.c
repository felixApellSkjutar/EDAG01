#include <stdio.h> 

int main() 
{
	printf("Hello World\n");
	int m,n;
	//&m = address of m
	scanf("%d %d", &m, &n);
	printf("m: %d\nn: %d\n", m, n);
	return 0;
}

double** make_matrix(int m, int n)
{
	double** a;
	int i;
	a = calloc(m, sizeof(double*));
	for (i = 0; i < m; i += 1)
		a[i] = calloc(n, sizeof(double));
	return a;
}