// main.cpp - Elliot Pozucek - Security - TP1

#include "rsa.h"
#include <cmath>

/**
 * @param number number to test
 * @return true if number is prime, false otherwise
 */
bool square_root_test(unsigned long long number) {
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    unsigned long root = sqrt(number); //sqrt(number) < number/2
    for (unsigned long i = 3; i <= root; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}

/**
 * Test the function generate_modulus_prime_factors.
 * The prime factors should be prime, not equal.
 * p and q should be spaced by at least 0.1 * max(p,q).
 * @param p the first prime factor
 * @param q the second prime factor
 * 
 */
bool test_generate_modulus_prime_factors() {
    unsigned long p, q;
    unsigned long long n = generate_modulus_prime_factors(p, q);

    cout << "p: " << p << " q: " << q << " n: " << n << endl;
    unsigned long diff;
    if (p < q) {
        diff = q - p;
    }
    else {
        diff = p - q;
    }
    cout << "diff: " << diff << endl;
    bool is_q_prime = square_root_test(q); // if q is prime
    bool is_p_prime = square_root_test(p); // if p is prime
    if (!is_p_prime && !is_q_prime) {
        cout << "p and q are not prime" << endl;
        return false;
    }
    if (!is_p_prime) {
        cout << "p is not prime" << endl;
        return false;
    }
    if (!is_q_prime) {
        cout << "q is not prime" << endl;
        return false;
    }
    if (diff < PRIME_FACTOR_DISTANCE_THRESHOLD) {
        cout << "p and q are too close" << endl;
        return false;
    }
    return true;
}

void test_modular_expo() {
    unsigned long long a = modular_exponentiation(15, 7, 53);
    cout << a << endl;
}

int main() {
    // unsigned long p, q;
    // cout<< "Enter p: ";
    // cin >> p;
    // cout << "Enter q: ";
    // cin >> q;
    if (!test_generate_modulus_prime_factors()) {
        cout << "Test failed" << endl;
        return 1;
    } else {
        cout << "Test passed" << endl;
    }
    test_modular_expo();
    
    return 0;    
}

