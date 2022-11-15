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

int simplex(int m, int n, double a, double b, double c, double x, double y) {
    return xsimplex(m, n, a, b, c, x, y);
}