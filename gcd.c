#include <stdio.h>
#include <gmp.h>

int main() {
    mpz_t m, n, rem;
    mpz_inits(m, n, rem, NULL);

    printf("Enter first number: ");
    gmp_scanf("%Zd", m);

    printf("Enter second number: "); 
    gmp_scanf("%Zd", n);

    while (mpz_cmp_ui(n, 0) > 0) { // if n > 0
        mpz_mod(rem, m, n);
        mpz_set(m, n);
        mpz_set(n, rem);
    }

    gmp_printf("GCD is: %Zd\n", m);

    mpz_clears(m, n, rem, NULL);
    return 0;
}

