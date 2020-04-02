#include <math.h>
#include <stdio.h>

double pi(int);
void print_pi(int);

int main() {
  print_pi(5);
  print_pi(7);
}

double pi(int precision) {
  double part = 0.0, next = 0.0;
  int i = 0;
  do {
    next = 4.0/(2.0*i+1);
    if (i % 2 == 1)
        next *= -1.0;
    part += next;
    ++i;
  } while ((next >= 0.5) || fabs(log10(fabs(next))) < precision + 1);
  return part;
}

void print_pi(int precision) {
  printf("Pi = %.*f\n", precision, pi(precision));
  printf("Pi = %.*f\n", precision, M_PI);
}
