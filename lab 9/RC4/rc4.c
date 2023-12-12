#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define SIZE 256

void rc4_init(int *key, int key_length, mpz_t *S, mpz_t *T) {
    // Initialization phase, setting up S array and derived T array
    for (int i = 0; i < 256; i++) {
        mpz_inits(S[i], T[i], NULL);
        mpz_set_ui(S[i], i);
        mpz_set_ui(T[i], key[i % key_length]);
    }
}

void rc4_permute_s(mpz_t *S, mpz_t *T){
    int j = 0;
    mpz_t tmp;
    mpz_init(tmp);
    // Permutation phase
    for (int i = 0; i <= 255; i++){
        mpz_add(tmp, S[i], T[i]);
        j = (j + mpz_get_ui(tmp)) % 256;
        mpz_set(tmp, S[i]);
        mpz_set(S[i], S[j]);
        mpz_set(S[j], tmp);
    }
}

void rc4_encrypt(mpz_t *plaintext, mpz_t *ciphertext, int plaintext_length, mpz_t *S) {
    int i = 0;
    int j = 0;
    mpz_t tmp;
    mpz_init(tmp);

    printf("Encrypted Output:");

    for (int k = 0; k < plaintext_length; k++) {
        i = (i + 1) % 256;
        j = (j + mpz_get_ui(S[i])) % 256;
        mpz_set(tmp, S[i]);
        mpz_set(S[i], S[j]);
        mpz_set(S[j], tmp);

        int t = (mpz_get_ui(S[i]) + mpz_get_ui(S[j])) % 256;
        mpz_init(ciphertext[k]);
        mpz_xor(ciphertext[k], S[t], plaintext[k]);
        gmp_printf("%Zd", ciphertext[k]);
    }

    printf("\n");
}

void rc4_decrypt(mpz_t *ciphertext, mpz_t *decryptedtext, int ciphertext_length, mpz_t *S) {
    int i = 0;
    int j = 0;
    mpz_t tmp;
    mpz_init(tmp);

    printf("Decrypted Output:");

    for (int k = 0; k < ciphertext_length; k++) {
        i = (i + 1) % 256;
        j = (j + mpz_get_ui(S[i])) % 256;

        mpz_set(tmp, S[i]);
        mpz_set(S[i], S[j]);
        mpz_set(S[j], tmp);

        int t = (mpz_get_ui(S[i]) + mpz_get_ui(S[j])) % 256;

        mpz_init(decryptedtext[k]);
        mpz_xor(decryptedtext[k], S[t], ciphertext[k]);

        gmp_printf("%Zd", decryptedtext[k]);
    }

    printf("\n");
}

int main() {
    mpz_t S[256], T[256];
    int key[] = {2, 5, 7, 10, 14, 18, 19, 34};
    int key_length = sizeof(key) / sizeof(key[0]);

    rc4_init(key, key_length, S, T);
    rc4_permute_s(S, T);

    int plaintext_length;
    printf("Enter plaintext length:");
    scanf("%d", &plaintext_length);

    mpz_t plaintext[plaintext_length];
    mpz_t ciphertext[plaintext_length];

    for (int i = 0; i < plaintext_length; i++) {
        mpz_inits(plaintext[i], ciphertext[i], NULL);
        printf("Enter number %d:", i + 1);
        gmp_scanf("%Zd", plaintext[i]);
    }

    rc4_encrypt(plaintext, ciphertext, plaintext_length, S);

    // we reset the s array to get correct decrypted value
    rc4_init(key, key_length, S, T);
    rc4_permute_s(S, T);

    rc4_decrypt(ciphertext, plaintext, plaintext_length, S);

    // Clean the memory
    for (int i = 0; i < plaintext_length; i++) {
        mpz_clear(plaintext[i]);
        mpz_clear(ciphertext[i]);
    }

    return 0;
}

