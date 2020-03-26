#include <math.h>
#include <stdio.h>

double pi(int);
void print_pi(int);

int main() {
  print_pi(5);
  print_pi(9);
}

double pi(int precision) {
  double part = 0.0, next = 0.0;
  int i = 0;
  do {
    next = 8.0 / (4.0 * i + 1.0) / (4.0 * i + 3.0);
    part += next;
    ++i;
  } while (log10(next) > precision + 1);
  return part;
}

void print_pi(int precision) {
  printf("Pi = %.*f\n", precision, pi(precision));
  printf("Pi = %.*f\n", precision, M_PI);
}
