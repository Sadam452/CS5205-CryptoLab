#include <stdio.h>
#include <gmp.h>
int main(){
mpz_t n, m, result, k;
mpz_inits(n, m, result, k , NULL);
mpz_set_ui(m, 11); //mod 11 group
mpz_set_ui(k, 1);
printf("Enter value of N:");
gmp_scanf("%Zd",n);
gmp_printf("Multiplicative cyclic group formed by given %Zd with mod 11 is:\n1,", n);
while(mpz_cmp(k, m) < 0){
mpz_powm(result, n, k, m);
if(mpz_cmp_ui(result, 1) == 0){
break;
}
gmp_printf("%Zd,",result);
mpz_add_ui(k,k,1);
}
printf("\n");
mpz_clear(n);
return 0;
}
