#include <stdio.h>
#include <gmp.h>
int main(){
    mpz_t n, p, q, e, phi, d, m, m_d, c, i, gcd, tmp;
    char message[1000], dec_message[1000];
    mpz_t encoded[1000];
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_inits(n, p, q, e, phi, d, m, m_d, c, i, gcd, tmp, NULL);
    printf("Enter the message(string):");
    fgets(message, sizeof(message), stdin);
    mpz_urandomb(p , state , 1024);
    mpz_nextprime(p, p);
    mpz_urandomb(q , state , 1024);
    mpz_nextprime(q, q);
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    mpz_init_set_ui(i, 2);
    while(mpz_cmp_ui(i, phi) < 0){
        mpz_urandomb(tmp , state , 100);        
        mpz_gcd(gcd, tmp, phi);
        if(mpz_cmp_ui(gcd, 1) == 0){
            mpz_set(e, tmp);
            break;
        }
        mpz_add_ui(i,i,1);
    }
    mpz_invert(d, e, phi);
    //now everything is ready
    //encode string to number
    int j=0, itr=0;
    printf("\nGiven Message = %s\nEncrypted Message = ",message);
    while(message[j] != '\0'){
        if (message[j] == ' '){
            j++;
            continue;
        }
        mpz_set_ui(encoded[itr],message[j]);
        mpz_powm(encoded[itr], encoded[itr], e, n);
        gmp_printf("%Zd",encoded[itr]);
        j++;
        itr++;    
    }

    j = 0;
    while(j < itr){
        mpz_powm(m_d, encoded[j], d, n);
        dec_message[j] = (char)mpz_get_ui(m_d);
        j++;
    }
    dec_message[j] = '\0';
    printf("\nDecrypted Message = %s\n",dec_message);
    mpz_clears(n, p, q, e, phi, d, m, m_d, c, i, gcd, tmp, NULL);
    return 0;
}
