#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

size_t          smallest_factor(size_t n);
void            factorize(size_t n);

int
main(int argc, char const * const argv[argc]) {
    if (argc == 1) {
        return 0;
    }
    for (int i = 0; i < argc; ++i){
        if (argv[i]) {
            size_t val = strtoull(argv[i], 0, 0); 
            if (val > 0) {
            factorize(val);
            }
        }
    }
    return 0;
}

size_t
smallest_factor(size_t n) {
    if (n < 4) {
        return n;
    }
    for (size_t i = 2; i < n; ++i) {
        if (!(n % i)) {
            return i;
        }
    }
    return n;
}

void
factorize(size_t n) {
    printf("%zu: ", n);
    if (n == 1) {
        puts("1");
        return;
    }
    while (n > 1) {
        size_t fac = smallest_factor(n);
        printf("%zu ", fac);
        while (!(n % fac)) {
            n /= fac;
        }     
    }
    puts("");
}
