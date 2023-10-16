#include <stdio.h>
#include <gmp.h>

void poly_add(mpz_t *result, mpz_t *p1, mpz_t *p2, int degree, mpz_t n) {
    for (int i = 0; i <= degree; i++) {
        mpz_add(result[i], p1[i], p2[i]);
        mpz_mod(result[i], result[i], n);
    }
}

void poly_subtract(mpz_t *result, mpz_t *p1, mpz_t *p2, int degree, mpz_t n) {
    for (int i = 0; i <= degree; i++) {
        mpz_sub(result[i], p1[i], p2[i]);
        mpz_mod(result[i], result[i], n);
    }
}

void poly_multiply(mpz_t *result, mpz_t *p1, mpz_t *p2, int degree, mpz_t n) {
    for (int i = degree+1; i <= 2 * degree; i++) {
        mpz_init(result[i]);
    }
    for (int i = 0; i <= 2 * degree; i++) {
        mpz_set_ui(result[i], 0);
    }
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            mpz_t temp;
            mpz_init(temp);
            
            mpz_mul(temp, p1[i], p2[j]); // Multiply coefficients
            mpz_mod(temp, temp, n);       // Take modulo n
            
            mpz_add(temp, result[2*degree -(i+j)], temp); // Add to result
            mpz_mod(result[2*degree -(i+j)], temp, n);

            mpz_clear(temp);
        }
    }
    int i, j;
    mpz_t tmp;

    for (i = 0, j = 2 * degree; i < j; i++, j--) {
        mpz_init(tmp);
        mpz_set(tmp, result[i]);
        mpz_set(result[i], result[j]);
        mpz_set(result[j], tmp);
        mpz_clear(tmp);
    }
}

void poly_divide(mpz_t *quotient, mpz_t *remainder, mpz_t *p1, mpz_t *p2, int degree, mpz_t n) {
    mpz_t temp[degree + 1], temp2[degree + 1], tmp;
    mpz_init(tmp);
    mpz_t res[2 * degree + 1];
    for(int k=0; k<=2*degree; k++)
    mpz_init(res[k]);

    for (int i = 0; i <= degree; i++) {
        mpz_inits(temp[i], quotient[i], remainder[i], temp2[i], NULL);
        mpz_set(remainder[i], p1[i]);
    }
    int flag = 0, index = 0;

    for (int j = 0; j <= degree; j++) {
    if (mpz_cmp_ui(remainder[j], 0) != 0 && flag == 0){
        flag = 1;
        index = j;
    }
    if (mpz_cmp_ui(p2[j], 0) != 0){
        if (flag == 1){
            mpz_invert(tmp, p2[j], n);
            mpz_mul(tmp, remainder[index], tmp);
            mpz_mod(tmp, tmp, n);
            mpz_set(temp[degree -(j-index)], tmp);
            for(int k=0; k<=degree; k++)
                mpz_add(quotient[k], quotient[k], temp[k]);
            poly_multiply(res, p2, temp, degree, n);
            for(int i=degree,k=0; i<=2*degree; i++,k++){
            mpz_set(temp2[k], res[i]);
            }
            poly_subtract(remainder, remainder, temp2, degree, n);
            //j = -1;
            flag = 0;
            for (int i = 0; i <= degree; i++) {
                mpz_set_ui(temp[i],0);
                }
            
        }
        else{
            break;
        }
        
    }
    }
}

//to check if remainder reachs zero or not
//return 1 if remainder != 0
int check(mpz_t *remainder, int degree){
    for(int i=0; i<=degree; i++){
        if(mpz_cmp_ui(remainder[i], 0) != 0)
        return 1;
    }
    return 0;
}
void poly_gcd(mpz_t *quotient, mpz_t *remainder, mpz_t *p1, mpz_t *p2, int degree, mpz_t n){
    mpz_t s1, s2, t1, t2;
    mpz_inits(s1, s2, t1, t2, NULL);
    mpz_init_set_ui(s1, 1);	
    mpz_init_set_ui(t2, 1);
    for(int i=0; i<=degree; i++){
    mpz_set_ui(quotient[i], 0);
    mpz_set_ui(remainder[i], 0);
    }
    do{
        poly_divide(quotient, remainder, p1, p2, degree, n);
        for(int i=0; i<=degree; i++){
	    mpz_set(p1[i], p2[i]);
	    mpz_set(p2[i], remainder[i]);
	}
    }while(check(remainder, degree) == 1);
    gmp_printf("x = %Zd y = %Zd",s2, s1);
}


int main() {
    int degree;
    printf("Enter the degree of polynomials:");
    scanf("%d", &degree);
    
    mpz_t n;
    mpz_init(n);
    printf("Enter the prime number 'n' GF(n): ");
    gmp_scanf("%Zd", n);

    mpz_t p1[degree + 1], p2[degree + 1], result[2 * degree + 1], quotient[degree + 1], remainder[degree + 1];

    printf("Enter the coefficients of p1(Higher to lower order terms):\n");
    for (int i = 0; i <= degree; i++) {
        mpz_inits(p1[i], result[i], NULL);
        gmp_scanf("%Zd", p1[i]);
    }

    printf("Enter the coefficients of p2(Higher to lower order terms):\n");
    for (int i = 0; i <= degree; i++) {
        mpz_init(p2[i]);
        gmp_scanf("%Zd", p2[i]);
    }

    // Perform polynomial addition, subtraction, and multiplication
    poly_add(result, p1, p2, degree, n);
    // Print the results
    printf("Addition result:\n");
    for (int i = 0; i <= degree; i++) {
        gmp_printf("%ZdX^%d", result[i], degree - i);
        if (i != degree)
            printf(" + ");
    }
    printf("\n");
    poly_subtract(result, p1, p2, degree, n);
    printf("Subtraction result:\n");
    for (int i = 0; i <= degree; i++) {
        gmp_printf("%ZdX^%d", result[i], degree - i);
        if (i != degree)
            printf(" + ");
    }
    printf("\n");
    poly_multiply(result, p1, p2, degree, n);
    printf("Multiplication result:\n");
    for (int i = 0; i <= 2 * degree; i++) {
        gmp_printf("%ZdX^%d", result[i], 2*degree-i);
        if (i != 2*degree)
            printf(" + ");
    }
    printf("\n");
    poly_divide(quotient, remainder, p1, p2, degree, n);
    printf("Division result:\nQuotient\t");
    for (int i = 0; i <= degree; i++) {
        gmp_printf("%ZdX^%d", quotient[i], degree - i);
        if (i != degree)
            printf(" + ");
    }
    printf("\nRemainder\t");
    for (int i = 0; i <= degree; i++) {
        gmp_printf("%ZdX^%d", remainder[i], degree - i);
        if (i != degree)
            printf(" + ");
    }
    printf("\n");
    printf("GCD result - Extended Euclidean Algorithm:\n");
    poly_gcd(quotient, remainder, p1, p2, degree, n);
    printf("\nGCD = \t");
    for (int i = 0; i <= degree; i++) {
        gmp_printf("%ZdX^%d", p1[i], degree - i);
        if (i != degree)
            printf(" + ");
    }
    printf("\n");
    return 0;
}

