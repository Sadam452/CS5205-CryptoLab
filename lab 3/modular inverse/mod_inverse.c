#include <stdio.h>
#include <gmp.h>
int main()
{
    mpz_t n, a, r, t1, t2, t3, q, inv, n_tmp, a_tmp;
    mpz_inits(n, a, r, t1, t2, t3, q, inv, n_tmp, a_tmp, NULL);
    mpz_init_set_ui(t2, 1);
    //mpz_init_set_ui(n, 7); //
    printf("Enter n:");
    gmp_scanf("%Zd",n);
    printf("Enter a:");
    gmp_scanf("%Zd",a);
    //mpz_init_set_ui(a, 3); 
    mpz_set(n_tmp, n);
    mpz_set(a_tmp, a);
    
    while(mpz_cmp_ui(a, 0) != 0){
        mpz_fdiv_q(q, n, a);
        mpz_mod(r, n, a);
        mpz_set(n, a);
        mpz_set(a, r);
        if(mpz_cmp_ui(r, 0)>0){
            //t3 = t1 - q*t2
            mpz_mul(q, q, t2);
            mpz_sub(t3, t1, q);
            mpz_set(t1, t2);
            mpz_set(t2, t3);
        }
    }
    if(mpz_cmp_ui(n, 1) == 0){
        mpz_mod(inv, t2, n_tmp);
        gmp_printf("%%%%%%%%%%%%%%%%%%%%\nMultiplicative inverse of %Zdmod%Zd is %Zd\n%%%%%%%%%%%%%%%%%%%%\n",a_tmp, n_tmp, inv);
    }
    else
        gmp_printf("%%%%%%%%%%%%%%%%%%%%\nMultiplicative inverse of %Zdmod%Zd doesn't exist\na and n must be coprime\n%%%%%%%%%%%%%%%%%%%%\n",a_tmp, n_tmp);
    
    
    mpz_clears(n, a, r, t1, t2, t3, q, inv, n_tmp, a_tmp, NULL);
    return 0;
}
