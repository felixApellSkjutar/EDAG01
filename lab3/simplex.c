#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct simplex_t simplex_t;
double epsilon = 0.0000001;
int glob;

struct simplex_t
{
    int m;      /* Constraints. */
    int n;      /* Decision variables. */
    int *var;   /* 0..n  1 are nonbasic. */
    double **a; /* A. */
    double *b;  /* b. */
    double *x;  /* x. */
    double *c;  /* c. */
    double y;   /* y. */
};

int init(simplex_t *s, int m, int n, double** a, double* b, double* c, double* x, double y, int* var)
{
    int i, k;
    s->m = m;
    s->n = n;
    s->a = a;
    s->b = b;
    s->c = c;
    s->x = x;
    s->y = y;
    s->var = var;
    if(s->var == NULL)
    {
        s->var = calloc(m+n+1, sizeof(int)); //Kanske fel
        for(i = 0; i < m+n; i+=1)
        {
            s->var[i] = i;
        }
    }
    for(k = 0, i = 1; i < m; i+=1)
    {
        if (b[i] < b[k])
        {
            k = i;
        }
    }
    return k;
}


int select_nonbasic(simplex_t *s) 
{
    int i;
    for(i = 0; i < s->n; i +=1) 
    {
        if(s->c[i] > epsilon)
        {
            return i;
        }
    }
    return -1;
}

void pivot(simplex_t *s, int row, int col)
{
    double **a = s->a;
    double *b = s->b;
    double *c = s->c;

    int m = s->m;
    int n = s->n;
    int i, j, t;

    t = s->var[col];
    s->var[col] = s->var[n + row];
    s->var[n + row] = t;
    s->y = s->y + (c[col] * b[row] / a[row][col]);

    for (i = 0; i < n; i += 1)
    {
        if (i != col)
        {
            c[i] = c[i] - c[col] * a[row][i] / a[row][col];
        }
    }
    c[col] = -c[col] / a[row][col];
    for (i = 0; i < m; i += 1)
    {
        if (i != row)
        {
            b[i] = b[i] - a[i][col] * b[row] / a[row][col];
        }
    }
    for (i = 0; i < m; i += 1)
    {
        if (i != row)
        {
            for (j = 0; j < n; j += 1)
            {
                if (j != col)
                {
                    a[i][j] = a[i][j] - a[i][col] * a[row][j] / a[row][col];
                }
            }
        }
    }
    for (i = 0; i < m; i += 1)
    {
        if (i != row)
        {
            a[i][col] = -a[i][col] / a[row][col];
        }
    }
    for (i = 0; i < n; i += 1)
    {
        if (i != col)
        {
            a[row][i] = a[row][i] / a[row][col];
        }
    }
    b[row] = b[row] / a[row][col];
    a[row][col] = 1 / a[row][col];
}

void prepare(simplex_t *s, int k)
{
    int m = s->m;
    int n = s->n;
    int i;

    for(i = m+n; i>n; i = i-1)
    {
        s->var[i] = s->var[i-1];
    }
    s->var[n] = m+n;
    n = n+1;
    for(i = 0; i<m; i = i+1)
    {
        s->a[i][n-1] = -1;
    }
    s->x = calloc(m+n, sizeof(double));
    s->c = calloc(n, sizeof(double));
    s->c[n-1] = -1;
    s->n = n;
    pivot(s, k, n-1); 
}

int initial(simplex_t *s, int m, int n, double **a, double *b, double* c, double *x, double y, int *var) 
{
    int i, j, k;
    double w;
    k = init(s, m, n, a, b, c, x, y, var);
    if(b[k] >= 0) 
    {
        return 1;
    }
    prepare(s, k);
    /*
    n = s->n;
    s->y = xsimplex (m, n, s->a, s->b, s->c, s->x, 0, s->var, 1);

    for(i =0; i < m + n; i +=1) 
    {
        if(s->var[i] == m+n - 1)
        {
            if(s->x[i] > pow(10, -6))
            {
                free(s->x);
                free(s->c);
                return 0;
            }
            else
            {
                break;
            }
        }
    }
    return 0;
    */
}



double xsimplex(int m, int n, double **a, double *b, double* c, double *x, double y, int *var, int h)
{
    simplex_t s;
    int i, row, col;
    if (!initial(&s, m, n, a, b, c, x, y, var))
    {
        free(s.var);
        return NAN;
    }
    while ((col = select_nonbasic(&s)) >= 0)
    {
        row = -1;
        for (i = 0; i < m; i += 1)
        {
            if (a[i][col] > epsilon && (row < 0 || b[i] / a[i][col] < b[row] / a[row][col]))
            {
                row = i;
            }
        }
        if (row < 0)
        {
            free(s.var);
            return INFINITY;
        }
        pivot(&s, row, col);
    }
    if (h == 0)
    {
        for (i = 0; i < n; i += 1)
        {
            if (s.var[i] < n)
            {
                x[s.var[i]] = 0;
            }
        }
        for (i = 0; i < m; i += 1)
        {
            if (s.var[n + i] < n)
            {
                x[s.var[n + i]] = s.b[i];
            }
        }
        free(s.var);
    }
    else
    {
        for (i = 0; i < n; i += 1)
        {
            x[i] = 0;
        }
        for (i = n; i < n + m; i += 1)
        {
            x[i] = s.b[i - n];
        }
    }
    return s.y;
}

double simplex(int m, int n, double **a, double *b, double *c, double *x, double y)
{
    return xsimplex(m, n, a, b, c, x, y, NULL, 0);
}

int main()
{

    int m, n;
    double *c, *b, **a, **t, *x;
    scanf("%d %d", &m, &n);
    //c = calloc(n, sizeof(double));
    //b = calloc(m, sizeof(double));
    a = calloc(m, sizeof(double*)); //för att a är en matris
    t = calloc(m+2, sizeof(double*));//temp
    x = calloc(m, sizeof(double));
    int i;


    for(i = 0; i < m; i+=1) 
    {
        a[i] = calloc(n, sizeof(double));
    }
    for(i = 0; i < m+2; i+=1) {
        t[i] = calloc(n, sizeof(double));
		for(int j = 0; j < n ; j+=1) {
			scanf("%lf", &(t[i][j]));
            if(i > 0 && i < m+1)
            {
                a[i-1][j] = t[i][j];
            }
		}
	}
    c = t[0];
    b = t[m+1];

    printf("%lf", simplex(m, n, a, b, c, x, 0));

    for(i = 0; i < m; i +=1)
    {
        free(a[i]);     //invalid free()
    }

    for(i = 0; i < m + 2; i += 1) 
    {
        free(t[i]);
    }

//    free(c);
//    free(b);    //invalid free()
    free(a);
    free(t);
    free(x);
    return 0;
}


	
	