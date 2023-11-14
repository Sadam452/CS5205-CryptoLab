#include <stdio.h>
#include <gmp.h>

int main(){
	mpz_t n,result;
	mpz_inits(n, result, NULL); //result will contain square of i
	//n will contain the number entered by user whose prime factors will be calculated by program.
	printf("Enter any large number: ");
	gmp_scanf("%Zd",n);
	gmp_printf("Prime factors of %Zd are: ", n);
	// Print the number of 2s that divide n
	while (mpz_even_p(n)) {
        	printf("%s", "2, ");
        	mpz_divexact_ui(n, n, 2);
        }
        mpz_t i; //check other factors other than 2
        mpz_init_set_ui(i, 3); //initialize n with 3
        mpz_mul(result, i, i); //find i*i - May be we can optimise this line

        while (mpz_cmp(result,n) <= 0) { //if i*i < n
        // While i divides n, print i and divide n
        	while (mpz_divisible_p(n, i) != 0) { //if n%i == 0
            		gmp_printf("%Zd, ", i);
            		mpz_divexact(n, n, i); // n=n/i
        	}
        	mpz_add_ui(i, i, 2); // i=i+2
        	mpz_mul(result, i, i); //result = i*i
    	}

        // if number is still greater than 1, just print it.
   	 if (mpz_cmp_ui(n, 2) > 0)
        	gmp_printf("%Zd\n", n);
	mpz_clears(n,i,NULL);
	return 0;
}
