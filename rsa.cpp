// rsa.cpp - Elliot Pozucek - Security - TP1

#include "rsa.h"

bool square_root_test(unsigned long number) {
    if (number <= 2) return true;
    if (number % 2 == 0) return false;
    unsigned long root = sqrt(number); //sqrt(number) < number/2
    for (unsigned long i = 3; i <= root; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}

unsigned long generate_modulus_prime_factors(unsigned int &p, unsigned int &q, int &iterations) {
    cout << "Generating prime factors..." << "(" << NB_BITS_PRIME_FACTORS << " bits)" << endl;
    default_random_engine generator(time(0));
    uniform_int_distribution<unsigned int> distribution(LOWER_BOUND_PRIME_FACTOR, UPPER_BOUND_PRIME_FACTOR);
    while (true) {
        iterations++;
        p = distribution(generator);
        if (prime(p)) {
            break;
        }
    }
    while (true) {
        iterations++;
        q = distribution(generator);
        if (prime(q)) {
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
        }
    }
    cout << "p = " << p << endl << "q =  " << q << endl;
    cout << "Number of iterations for prime factors generation : " << iterations << endl;
    return p * q;
}

unsigned long modular_exponentiation(unsigned int base, unsigned int exp, unsigned long n) {
    unsigned long temp = 1;
    for (unsigned long exp_cpt = 1; exp_cpt <= exp; exp_cpt++) {
        temp = base * temp % n;
    }
    return temp;
}


bool prime(unsigned int number) {
    if (number <= 2) return true;
    if (number % 2 == 0) return false;
    
    unsigned int d = number - 1;
    unsigned int s = 0;
    unsigned int x;

    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = NUMBER_OF_ITERATIONS_PRIME_TEST; i > 0; i--) {
        default_random_engine generator(time(0));
        uniform_int_distribution<unsigned int> distribution(2, number - 2);
        x = modular_exponentiation(distribution(generator), d, number);

        if (x == 1 || x == number - 1) continue;
        for (int j = 1; j < s; j++) {
            x = modular_exponentiation(x, 2, number);
            if (x == 1) return false;
            if (x == number - 1) break;
        }
        if (x != number - 1) return false;
    }
    return true;
}