#include "test_prime_factors.h"

void test_generate_modulus_prime_factors() {
    unsigned int p, q;
    int iter = 0;
    unsigned long n = generate_modulus_prime_factors(p, q, iter);

    cout << "p = " << p << endl << "q =  " << q << endl << "n = " << n << endl;
    unsigned long diff;
    if (p < q) {
        diff = q - p;
    }
    else {
        diff = p - q;
    }
    cout << "Difference between q and p : " << diff << endl;
    bool is_q_prime = square_root_test(q); // if q is prime
    bool is_p_prime = square_root_test(p); // if p is prime
    if (!is_p_prime && !is_q_prime) {
        cout << "p and q are not prime" << endl;
    }
    if (!is_p_prime) {
        cout << "p is not prime" << endl;
    }
    if (!is_q_prime) {
        cout << "q is not prime" << endl;
    }
    if (diff < PRIME_FACTOR_DISTANCE_THRESHOLD) {
        cout << "p and q are too close" << endl;
    }
    if (is_p_prime && is_q_prime && diff > PRIME_FACTOR_DISTANCE_THRESHOLD) {
        cout << "p and q are appropriate prime factors" << endl;
    }
}