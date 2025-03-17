// main.cpp - Elliot Pozucek - Security - TP1

#include "rsa.h"
#include "test/test_prime.h"
#include "test/test_prime_factors.h"
#include "test/test_encrypt.h"
#include "test/test_decrypt.h"
#include <cmath>


// sould return 51125
void test_modular_expo() {
    unsigned long long a = modular_exponentiation(12365, 165, 56625);
    cout << a << endl;
}

int main() {
    // cout << "UPPER_BOUND_PRIME_FACTOR: " << UPPER_BOUND_PRIME_FACTOR << endl;
    // cout << "LOWER_BOUND_PRIME_FACTOR: " << LOWER_BOUND_PRIME_FACTOR << endl;
    // cout << "PRIME_FACTOR_DISTANCE_THRESHOLD: " << PRIME_FACTOR_DISTANCE_THRESHOLD << endl;

    // test_modular_expo();
    // test_prime();
    // test_generate_modulus_prime_factors();

    // rsa();

    test_encrypt(2047, 179, "ENVOYEZ_2500$.", "AVOA25ALMA2PALPAR0ADC");
    test_decrypt(2047, 411, "AVOA25ALMA2PALPAR0ADC", "ENVOYEZ_2500$.");
    
    return 0;    
}

