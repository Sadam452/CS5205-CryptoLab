#include <stdio.h>
#include <gmp.h>
int main(){
    mpz_t n, p, q, e, phi, d, m, c, m_d, i, gcd, tmp;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_inits(n, p, q, e, phi, d, m, c, m_d, i, gcd, tmp,NULL);
    printf("Enter the message(number):");
    gmp_scanf("%Zd", m);
    mpz_urandomb(p , state , 2048);
    mpz_nextprime(p, p);
    mpz_urandomb(q , state , 2048);
    mpz_nextprime(q, q);
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    mpz_init_set_ui(i, 2);
    while(mpz_cmp_ui(i, phi) < 0){
        mpz_urandomb(tmp , state , 100);        
        mpz_gcd(gcd, tmp, phi);
        if(mpz_cmp_ui(gcd, 1) == 0){
            mpz_set(e, tmp);
            break;
        }
        mpz_add_ui(i,i,1);
    }
    mpz_invert(d, e, phi);
    //now everything is ready
    //lets encrypt and decrypt
    mpz_powm(c, m, e, n);
    mpz_powm(m_d, c, d, n);
    //gmp_printf("%Zd %Zd %Zd\n",phi,e, d);
    gmp_printf("Actual Message = %Zd \t Encrypted Message = %Zd \tDecrypted Message = %Zd\n",m,c, m_d);
    mpz_clears(n, p, q, e, phi, d, m, c, m_d, i, gcd, NULL);
    return 0;
}
