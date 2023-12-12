#include <stdio.h>
#include <gmp.h>
#include <openssl/sha.h>
#include <string.h>

// Struct to hold both message and digital signature
struct MessageAndSignature {
    unsigned char message[256];
    mpz_t ds;
};

// Function to verify the digital signature sent by B
void verify_signature_B(const struct MessageAndSignature *combined, mpz_t e, mpz_t n){
    printf("\n--------------------------------\n%%%%%%%% USER C %%%%%%%% \nUSER C received message from USER B\nUSER C verifies the signature using public key of B(Remember this is signature of A, so this should fail)\n");
    //gmp_printf("%s %Zd %Zd %Zd",combined->message, combined->ds, e, n);
    mpz_t tmpi, ds;
    mpz_inits(tmpi, ds, NULL);
    unsigned char hash[20];

    printf("Received message: %s\n", combined->message);
    SHA1(combined->message, strlen((char *)combined->message), hash);

    mpz_powm(ds, combined->ds, e, n);

    // Create a null-terminated hexadecimal string
    char hexString[41];
    for (int i = 0; i < 20; i++) {
        snprintf(hexString + (i * 2), 3, "%02x", hash[i]);
    }

    mpz_set_str(tmpi, hexString, 16);

    if (mpz_cmp(ds, tmpi) == 0) {
        printf("Authentication Successful\n");
    } else {
        printf("Authentication Unsuccessful\n");
    }
}

// Function to verify the digital signature sent by A
void verify_signature_A(const struct MessageAndSignature *combined, mpz_t e, mpz_t n) {
    //gmp_printf("%s %Zd %Zd %Zd",combined->message, combined->ds, e, n);
    mpz_t tmpi, ds;
    mpz_inits(tmpi, ds, NULL);
    unsigned char hash[20];
    printf("--------------------------------\n%%%%%%%% USER B %%%%%%%% \nUSER B received message from USER A\nUSER B verifies the signature using public key of A\n");
    printf("Received message: %s\n", combined->message);
    SHA1(combined->message, strlen((char *)combined->message), hash);

    mpz_powm(ds, combined->ds, e, n);

    // Create a null-terminated hexadecimal string
    char hexString[41];
    for (int i = 0; i < 20; i++) {
        snprintf(hexString + (i * 2), 3, "%02x", hash[i]);
    }

    mpz_set_str(tmpi, hexString, 16);

    if (mpz_cmp(ds, tmpi) == 0) {
        printf("Authentication Successful\n");
    } else {
        printf("Authentication Unsuccessful\n");
    }
    printf("\nAnother scenario: Now let us say B forwards same message to USER C");
    //we will pass public key of B here.....
    //lets generate public key for B first
    mpz_t p, q, phi, d, tmp, n_;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_inits(n_, p, q, e, phi, d, tmp, NULL);

    mpz_urandomb(p, state, 200);
    mpz_nextprime(p, p);
    mpz_urandomb(q, state, 200);
    mpz_nextprime(q, q);
    mpz_mul(n_, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);

    mpz_init_set_ui(tmp, 2);
    while (mpz_cmp_ui(tmp, phi) < 0) {
        mpz_urandomb(d, state, 100);
        mpz_gcd(e, d, phi);
        if (mpz_cmp_ui(e, 1) == 0) {
            mpz_set(e, d);
            break;
        }
        mpz_add_ui(tmp, tmp, 1);
    }
    //note that we passed the e generated in B itself. Means it is key of B not of A.
    verify_signature_B(combined, e, n);
}

int main() {
    struct MessageAndSignature combined;
    //strcpy(combined.message, "Launch Mission");
    printf("Enter a message: ");
    fgets(combined.message, sizeof(combined.message), stdin);
    combined.message[strlen(combined.message) - 1] = '\0';  // Remove the newline character

    unsigned char hash[20];
    printf("%%%%%%%% USER A %%%%%%%% \nGiven message: %s\n", combined.message);
    SHA1(combined.message, strlen((char *)combined.message), hash);

    //printf("Hash: ");
    //for (int i = 0; i < 20; i++) {
    //    printf("%02x", hash[i]);
    //}
    //printf("\n");

    mpz_t n, p, q, e, phi, d, tmp, ds;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_inits(n, p, q, e, phi, d, tmp, combined.ds, NULL);

    mpz_urandomb(p, state, 100);
    mpz_nextprime(p, p);
    mpz_urandomb(q, state, 100);
    mpz_nextprime(q, q);
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);

    mpz_init_set_ui(tmp, 2);
    while (mpz_cmp_ui(tmp, phi) < 0) {
        mpz_urandomb(d, state, 100);
        mpz_gcd(e, d, phi);
        if (mpz_cmp_ui(e, 1) == 0) {
            mpz_set(e, d);
            break;
        }
        mpz_add_ui(tmp, tmp, 1);
    }
    mpz_invert(d, e, phi);

    // Create a null-terminated hexadecimal string
    char hexString[41];
    for (int i = 0; i < 20; i++) {
        snprintf(hexString + (i * 2), 3, "%02x", hash[i]);
    }

    mpz_set_str(tmp, hexString, 16);
    mpz_powm(combined.ds, tmp, d, n);

    //mpz_set_ui(combined.ds,ds);

    printf("USER A sends message to USER B\n");
    verify_signature_A(&combined, e, n);

    return 0;
}
