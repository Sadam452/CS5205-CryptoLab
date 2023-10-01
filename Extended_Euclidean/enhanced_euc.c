#include <stdio.h>
#include <gmp.h>
int main()
{	
	mpz_t a, b, x, y, rem, s1, s2, t1, t2, q, q1, temp;	
	mpz_inits(a, b, x, y, rem, s1, s2, t1, t2, q, q1, temp, NULL);	
	mpz_init_set_ui(s1, 1);	
	mpz_init_set_ui(t2, 1);	//mpz_set(s1, 1);	//mpz_set(t2, 1);	
	printf("Enter value of a:");	
	gmp_scanf("%Zd", a);	
	printf("Enter value of b:");	
	gmp_scanf("%Zd", b);		
	while(mpz_cmp_ui(b, 0) > 0){		
		mpz_fdiv_q(q, a, b);		
		mpz_fdiv_q(q1, a, b);		//gmp_printf("q is : %Zd %Zd\n", q, q1);		
		mpz_mod(rem, a, b);		
		mpz_set(a, b);		
		mpz_set(b, rem);		
		if(mpz_cmp_ui(rem, 0)>0){		
			mpz_set(temp, s2);		
			mpz_mul(q, q, s2);		
			mpz_sub(s2, s1, q);		
			mpz_set(s1, temp);	
				//		
			mpz_set(temp, t2);		
			mpz_mul(q1, q1, t2);		
			mpz_sub(t2, t1, q1);		
			mpz_set(t1, temp);}			
			}	
		gmp_printf("GCD = %Zd x = %Zd y = %Zd\n", a, s2, t2);	
		mpz_clears(a, b, x, y, rem, s1, s2, t1, t2, q, q1, temp, NULL);	
	return 0;
}
