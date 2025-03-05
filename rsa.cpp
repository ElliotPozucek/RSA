// rsa.cpp - Elliot Pozucek - Security - TP1

#include "rsa.h"

unsigned long long generate_modulus_prime_factors(unsigned long &p, unsigned long &q) {
    default_random_engine generator;
    uniform_int_distribution<unsigned long> distribution(LOWER_BOUND_ULONG, UPPER_BOUND_ULONG);
    while (true) {
        p = distribution(generator);
        if (prime(p)) {
            break;
        }
    }
    while (true) {
        q = distribution(generator);
        if (prime(q)) {
            // we cast into signed numbers
            if (p > q) {
                if (p - q > PRIME_FACTOR_DISTANCE_THRESHOLD) {
                    break;
                }
            }
            else {
                if (q - p > PRIME_FACTOR_DISTANCE_THRESHOLD) {
                    break;
                }
            }
            // if (abs(static_cast<unsigned long>(p) - static_cast<unsigned long>(q)) > PRIME_FACTOR_DISTANCE_THRESHOLD) {
            //     break;
            // }
        }
    }
    return p * q;
}

unsigned long long modular_exponentiation(unsigned long base, unsigned long exp, unsigned long long n) {
    unsigned long long temp = 1;
    for (unsigned long long exp_cpt = 1; exp_cpt <= exp; exp_cpt++) {
        temp = base * temp % n;
    }
    return temp;
}

// is not efficient
bool prime(unsigned long number) {
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    unsigned long root = sqrt(number); //sqrt(number) < number/2
    for (unsigned long i = 3; i <= root; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}