#include "rsa.h"
#include "test/test_prime.h"
#include "test/test_prime_factors.h"
#include "test/test_encrypt.h"
#include "test/test_decrypt.h"
#include <cmath>


// sould return 51125
void test_modular_expo() {
    unsigned long long a = modular_exponentiation(12365, 165, 56625);
    cout << "Modular exponentiation test: a = 12365^165 mod 56625 = " << a << endl; 
    if (a == 51125) {
        cout << "Modular exponentiation test passed." << endl;
    } else {
        cout << "Modular exponentiation test failed." << endl;
    }
}

int main() {
    cout << "NB_BITS_PRIME_FACTORS: " << NB_BITS_PRIME_FACTORS << endl;
    cout << "UPPER_BOUND_PRIME_FACTOR: " << UPPER_BOUND_PRIME_FACTOR << endl;
    cout << "LOWER_BOUND_PRIME_FACTOR: " << LOWER_BOUND_PRIME_FACTOR << endl;
    cout << "PRIME_FACTOR_DISTANCE_THRESHOLD: " << PRIME_FACTOR_DISTANCE_THRESHOLD << endl;

    cout << endl;

    test_modular_expo();
    cout << endl;
    test_prime();
    cout << endl;
    test_generate_modulus_prime_factors();
    cout << endl;

    cout << "--------------------------------------------------------------------" << endl;
    rsa();
    cout << "--------------------------------------------------------------------" << endl << endl;

    test_encrypt(2047, 179, "ENVOYEZ_2500$.", "AVOA25ALMA2PALPAR0ADC", alphabet_to_index_40, index_to_alphabet_40);
    test_decrypt(2047, 411, "AVOA25ALMA2PALPAR0ADC", "ENVOYEZ_2500$.", alphabet_to_index_40, index_to_alphabet_40);
    
    return 0;    
}

