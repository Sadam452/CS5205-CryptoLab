#include <stdio.h>
#include <gmp.h>
#include <time.h>

#define BITS 1024

int main() {
    gmp_randstate_t state;
    mpz_t num;
    
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    //time(NULL) returns the current time in seconds since the epoch (January 1, 1970). Making random number more unpredictable
    mpz_init(num);

    // Generate a random 1024-bit number
    mpz_urandomb(num, state, BITS);

    // To Ensure that the number is odd
    mpz_setbit(num, 0);

    // To Ensure the number is at least 1024 bits by setting the most significant bit
    mpz_setbit(num, BITS - 1);

    // Next prime greater than or equal to num
    mpz_nextprime(num, num);

    // Print the prime number
    gmp_printf("Generated 1024-bit prime is: %Zd\n", num);

    mpz_clear(num);
    gmp_randclear(state);

    return 0;
}

