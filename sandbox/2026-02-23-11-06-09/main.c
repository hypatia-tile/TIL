#include <stdio.h>
#include <stdlib.h>

int (*(*f[5])(double))[10];
int x = 0;
/*
 * ItoI is a type alias for a pointer to a function
 * that takes an int
 * and returns an int.
 */
typedef int (*ItoI)(int);
int add(int a) { return a + x; }
ItoI addn(int a) {
  x = a;
  return add;
}
int sum(int a, int b) { return addn(a)(b); }

int main() {
  // You don't read it left to right
  // You must start at the variable name 'x',
  // then spiral outward:
  // 1. 'x' is an array of 10 elements
  // 2. of pointers
  // 3. to int
  int *x[10];
  printf("%zd\n", sizeof(x));
  printf("before initialized: %p, %p\n", x[0], x[1]);
  x[0] = malloc(sizeof(int));
  x[1] = malloc(sizeof(int));
  *x[0] = 42; // The array subscript operator `[]` has higher precedence than
              // the dereference operator `*`
  *x[1] = 99;
  printf("first element: %p, %d\n", x[0], *x[0]);
  printf("second element: %p, %d\n", x[1], *x[1]);
  free(x[0]);
  free(x[1]);

  printf("addn(10)(20) = %d\n", addn(10)(20));
  return 0;
}
