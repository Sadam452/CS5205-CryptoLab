#include <stdio.h>
#include <string.h>
#include <time.h>
#include <gmp.h>

int main(){
    mpz_t p, q, r, upper, g, res_r, res_q, key_x, key_y, k, c1, c2, yk;
    mpz_inits(p, q, r, upper, g, res_q, res_r, key_x, key_y, k, c1, c2, yk, NULL);
    char message[100], dec_message[100];
    mpz_t encode[100];
    printf("Enter message:");
    fgets(message, sizeof(message), stdin);
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
    int flag = 0;
    mpz_set_ui(r, 2);
    while(flag == 0){
    mpz_urandomb(q, state, 128);
    mpz_nextprime(q, q);
    mpz_mul(p, q, r);
    mpz_add_ui(p, p, 1);
    //gmp_printf("%Zd",p);
    if(mpz_probab_prime_p(p, 10) != 0){
    	flag = 1;
    }
    }
    flag = 0;
    mpz_sub_ui(upper, p, 1);
    //find generator
    while(flag == 0){
    	mpz_urandomm(g, state, upper);
    	if(mpz_cmp_ui(g, 2) < 0)
    		mpz_add_ui(g, g, 2);
    	mpz_powm(res_q, g, q, p);
    	mpz_powm(res_r, g, r, p);
    	if(mpz_cmp_ui(res_q, 1) != 0 && mpz_cmp_ui(res_r, 1) != 0)
    		flag = 1;
    }
    //now p, q, r, g(generator) are calculated above.
    //now choose key x [2 to p-2]
    mpz_sub_ui(upper, p, 2);
    do{
    mpz_urandomm(key_x, state, upper);
    }while(mpz_cmp_ui(key_x, 1) < 0);
    //now generate key_y: y = g power x mod p
    mpz_powm(key_y, g, key_x, p);
    //choose k - any random number
    mpz_urandomm(k, state, p);
    //calculate C1= gPowerKmod p
    mpz_powm(c1, g, k, p);
    //start encyption now:
    mpz_powm(c2, key_y, k, p);
    for(int i=0; i<sizeof(message); i++){
    	mpz_init(encode[i]);
    	mpz_set_ui(encode[i], message[i]);
    	mpz_mul(encode[i], encode[i], c2);
    }
    //print encrypted string
    printf("Encrypted Message: ");
    for(int i=0; i<sizeof(message); i++){
    	gmp_printf("%Zd", encode[i]);
    }
    printf("\n");
    //now decrypt the message
    mpz_powm(yk, c1, key_x, p);
    mpz_invert(yk, yk, p);
    for(int i=0; i<sizeof(message); i++){
    	mpz_mul(encode[i], encode[i], yk);
    	mpz_mod(encode[i], encode[i], p);
    	dec_message[i] = (char)mpz_get_ui(encode[i]);
    }
    //print decrypted string
    printf("Decrypted Message: ");
    puts(dec_message);
    printf("\n");
    mpz_clears(p, q, r, upper, g, res_q, res_r, key_x, key_y, k, c1, c2, NULL);
    gmp_randclear(state);
    return 0;
}
