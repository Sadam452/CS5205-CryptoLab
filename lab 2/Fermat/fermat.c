#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main() {
    mpz_t n, k, num, UPPER; // n will be the prime number to be checked, k the number of iterations
    mpz_t one, two;
    int flag = 0;
    
    mpz_init_set_ui(two, 2);
    mpz_init_set_ui(one, 1);
    
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    
    mpz_inits(n, k, num, UPPER, NULL);
    
    printf("Enter any number:");
    gmp_scanf("%Zd", n);
    
    printf("Enter k:");
    gmp_scanf("%Zd", k);
    mpz_t xt;
    mpz_init(xt);
    mpz_sub_ui(xt,n,1);
    
    if (mpz_cmp_ui(n, 1) <= 0 || mpz_cmp_ui(n, 4) == 0)
        printf("Not a prime\n");
    else if (mpz_cmp_ui(n, 3) <= 0)
        printf("It is prime\n");
    else {
        mpz_t result;
        mpz_init(result);
        
        mpz_sub(UPPER, n, two); // UPPER should be n-2
        
        while (mpz_cmp_ui(k, 0) > 0) {
            do {
                mpz_urandomb(num, state, mpz_sizeinbase(n, 2));
            } while (mpz_cmp_ui(num, 2) < 0 || mpz_cmp(num, UPPER) > 0);
            
           // gmp_printf("%Zd %Zd\n", k, num);
            
            mpz_powm(result, num, xt, n); // Calculate num^n mod n          
            
            if (mpz_cmp_ui(result, 1) != 0){
                printf("Given number is not prime\n");
                flag = 1;
                break;
                }
            
            mpz_sub(k, k, one);
        }
        
        mpz_clear(result);
    }
    if(flag == 0)
    	printf("Given number is probably Prime number\n");
    
    mpz_clears(n, k, num, UPPER, one, two, NULL);
    
    return 0;
}

