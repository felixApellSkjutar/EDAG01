#include <stdlib.h>
#include <math.h>


typedef struct simplex_t simplex_t;

struct simplex_t {
    int m ; /* Constraints. */
    int n ; /* Decision variables. */
    int *var; /* 0..n  1 are nonbasic. */
    double *a ; /* A. */
    double *b ; /* b. */
    double *x ; /* x. */
    double *c ; /* c. */
    double *y ; /* y. */
}; 


int xsimplex(int m, int n, double* a, double* b, double c, double x, double y, int* var, int h)
{
    simplex_t* s;
    int i, row, col;
    if (!initial(&s, m, n, a, b, c, x, y, var))
    {
        free(s->var);
        return NAN;
    }
    while((col = select_nonbasic(&s))>= 0 )
    {
        row -= 1;
        int i;
        for(i = 0; i < m; i+=1)
        {
            if((&a)[i][col] > pow(10,-6) && (row < 0 || b[i]/(&a)[i][col] < b[row]/(&a)[row][col])) {
                row = i;
            }
        }
        if (row < 0)
        {
            free(s->var);
            return INFINITY;
        }
        pivot(&s, row, col);
    }

}

int simplex(int m, int n, double* a, double* b, double c, double x, double y) {
    return xsimplex(m, n, a, b, c, x, y, NULL, 0);
}