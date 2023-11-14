//let f(x) = anx^n + an-1x^n-1 + ....
//f(x) is irreducible according to Eisentein's Criterion if:
//p !/ an
//p / an-1, ..., a0
//p^2 !/ a0

#include <stdio.h>
#include <gmp.h>

int is_irreducible_eisenstein(const mpz_t* coeffs, size_t degree, const mpz_t* prime) {
    mpz_t a, b, result;
    mpz_inits(a, b, result, NULL);

    // Check if an(leading coefficient) is not divisible by the prime.
    mpz_set(a, coeffs[degree]);
    mpz_mod(b, a, *prime);
    if (mpz_sgn(b) == 0) {
        mpz_clears(a, b, result, NULL);
        return 0;  // Not irreducible
    }

    // Check if all other coefficients are divisible by the prime.
    for (size_t i = 0; i < degree; i++) {
        mpz_set(a, coeffs[i]);
        mpz_mod(b, a, *prime);
        if (mpz_sgn(b) != 0) {
            mpz_clears(a, b, result, NULL);
            return 0;  // Not irreducible
        }
    }

    // Check if the constant term is not divisible by the square of the prime.
    mpz_set(b, coeffs[0]);
    mpz_mul(result, *prime, *prime);
    if (mpz_divisible_p(b, result)) {
        mpz_clears(a, b, result, NULL);
        return 0;  // Not irreducible
    }

    mpz_clears(a, b, result, NULL);

    return 1;  // Irreducible
}

int main() {
    mpz_t prime;
    mpz_inits(prime, NULL);
    printf("Enter any prime number:");
    gmp_scanf("%Zd", prime);
    int degree = 0;
    printf("Enter degree of polynomial:");
    scanf("%d", &degree);
    //coefficients of polynomial.
    mpz_t coeffs[degree + 1];
    for(int i=0; i<=degree; i++){
    printf("Enter coefficient of polynomial term x^%d:", i);
    mpz_init(coeffs[i]);
    gmp_scanf("%Zd", coeffs[i]);
    }

    int irreducible = is_irreducible_eisenstein(coeffs, degree, &prime);
    if (irreducible) {
        printf("The polynomial is irreducible by Eisenstein's criterion.\n");
    } else {
        printf("The polynomial is reducible.\n");
    }

    mpz_clear(prime);
    for (int i = 0; i <= degree; i++) {
        mpz_clear(coeffs[i]);
    }

    return 0;
}
