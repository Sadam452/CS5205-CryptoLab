#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main(){
    mpz_t p, g, a, b, x, y, ka, kb;
    mpz_inits(p, g, a, b, x, y, ka, kb, NULL);
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    //Alice and Bob get public numbers P, G
    mpz_urandomb(p, state, 1024);
    mpz_nextprime(p, p);
    mpz_urandomb(g, state, 1024);
    mpz_nextprime(g, g);
    gmp_printf("Public Numbers:\n\t P = %Zd \n\t g = %Zd\n", p, g);
    //Alice selected a private key a
    mpz_urandomb(a, state, 10);
    //Alice computes public value x
    mpz_powm(x, g, a, p);
    gmp_printf("Alice computes public value x = %Zd\n", x);
    
    //Bob selected a private key b
    mpz_urandomb(b, state, 10);
    //Bob computes public value y
    mpz_powm(y, g, b, p);
    gmp_printf("Bob computes public value y = %Zd\n", y);

    //Alice and Bob exchange public numbers x & y
    //Alice receives y, Bob receives x
    mpz_powm(ka, y, a, p);
    mpz_powm(kb, x, b, p);
    gmp_printf("Shared Key:\nAlice calculates: %Zd \nBob calculates: %Zd\n", ka, kb);
    
    mpz_clears(p, g, a, b, x, y, ka, kb, NULL);
    gmp_randclear(state);
    return 0;
}
