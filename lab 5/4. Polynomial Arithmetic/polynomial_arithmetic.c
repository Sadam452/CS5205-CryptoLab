#include <stdio.h>
#include <string.h>

// Function to perform polynomial addition
void gf_add(const char* a, const char* b, char* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = (a[i] != b[i]) ? '1' : '0';
    }
    result[size] = '\0';
}

// Function to perform polynomial subtraction
void gf_subtract(const char* a, const char* b, char* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = (a[i] != b[i]) ? '1' : '0';
    }
    result[size] = '\0';
}

// Function to perform polynomial multiplication
void gf_multiply(const char* a, const char* b, const char* m, char* result) {
    int size = strlen(m);
    char partial_products[size][size];

    // Initialize the partial products to zero
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            partial_products[i][j] = '0';
        }
    }
    //a x 1 is a
    for(int i=0; i<size; i++){
    partial_products[0][i] = a[i];
    }

    // Calculate partial products
    for (int i = 1; i < size; i++) {
    int bit = partial_products[i-1][0]; //to check if 1st bit is 1, then xor with m(x) is needed
            for (int j = 0; j < size; j++) {
            if (j == size-1)
                partial_products[i][j] = '0';
            else
                partial_products[i][j] = partial_products[i-1][j+1];
            }
            //do xor if last bit left out was one
            if (bit == '1'){
            for (int j = 0; j < size; j++) {
            if((partial_products[i][j] == '1' && m[j] == '1') || (partial_products[i][j] == '0' && m[j] == '0'))
            partial_products[i][j] = '0';
            else
            partial_products[i][j] = '1';
            }
            }
    }

    // Initialize the result to zero
    for (int i = 0; i < size; i++) {
        result[i] = '0';
    }

    // Accumulate the partial products with XOR
    for (int i = 0; i < size; i++) {
        if(b[i] == '1'){
        for(int j=0; j<size; j++){
        if((partial_products[size-i-1][j] == '1' && result[j] == '1') || (partial_products[size-i-1][j] == '0' && result[j] == '0'))
            result[j] = '0';
            else
            result[j] = '1';
        }
    }
    }
    result[size] = '\0';
}

// Function to perform polynomial division
void gf_divide(const char* num, const char* mod, char* quotient, char* remainder, int size) {
    char dividend[size + 1];
    strcpy(dividend, num);

    for (int i = 0; i < size; i++) {
        quotient[i] = '0';
    }
    quotient[size] = '\0';

    for (int i = 0; i < size; i++) {
        if (dividend[0] == '0') {
            for (int j = 1; j <= size; j++) {
                dividend[j - 1] = dividend[j];
            }
            dividend[size] = '\0';
        } else {
            for (int j = 0; j <= size; j++) {
                quotient[j] = (dividend[j] == mod[j]) ? '0' : '1';
                dividend[j] = (dividend[j] == mod[j]) ? '0' : '1';
            }
        }
    }
    quotient[size] = '\0';
    strcpy(remainder, dividend);
}

int main() {
    int size = 8; // Size of the binary strings
    printf("Enter size of polynomial:");
    scanf("%d", &size);

    char m[size]; // generator
    char a[size];
    char b[size];
    char result[size];
    char quotient[size + 1];
    char remainder[size + 1];
    
    printf("Coefficients of a:");
    scanf("%s", a);
    printf("Coefficients of b:");
    scanf("%s", b);
    printf("Coefficients of m:");
    scanf("%s", m);

    // Addition
    gf_add(a, b, result, size);
    printf("Addition Result: %s\n", result);

    // Subtraction
    gf_subtract(a, b, result, size);
    printf("Subtraction Result: %s\n", result);

    // Multiplication
    gf_multiply(a, b, m, result);//, size);
    printf("Multiplication Result: %s\n", result);

    // Division
    gf_divide(a, m, quotient, remainder, size);
    printf("Division Result: Quotient: %s, Remainder: %s\n", quotient, remainder);

    return 0;
}

