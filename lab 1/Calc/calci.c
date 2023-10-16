#include <stdio.h>
#include <gmp.h>

int main(){
	mpf_t first_num, second_num, sum, sub, mul, div;
	//mpz for integers; format specifier %Zd
	//mpf for floating point numbers; Format specifier %Ff
	mpf_inits(first_num, second_num, sum, sub, mul, div, NULL);
	printf("%%%%%%%% Calculator Using GMP [Lab 1 @ 05/09/2023] %%%%%%%%");
	printf("\nEnter the value of first variable : ");
	gmp_scanf("%Ff", first_num);
	printf("Enter the value of second variable : ");
	gmp_scanf("%Ff", second_num);
	
	mpf_add(sum, first_num, second_num);
	mpf_sub(sub, first_num, second_num);
	mpf_mul(mul, first_num, second_num);
	mpf_div(div, first_num, second_num);
	
	gmp_printf("%Ff + %Ff = %Ff\n%Ff - %Ff = %Ff\n%Ff * %Ff = %Ff\n%Ff / %Ff = %Ff\n", first_num, second_num, sum, first_num, second_num, sub, first_num, second_num, mul, first_num, second_num, div);
	mpf_clears(first_num, second_num, sum, sub, mul, div, NULL);
	return 0;
}
