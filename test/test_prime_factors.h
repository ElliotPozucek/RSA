#ifndef TEST_PRIME_FACTORS_H
#define TEST_PRIME_FACTORS_H

#include "../rsa.h"

/**
 * Test the function generate_modulus_prime_factors(unsigned long &p, unsigned long &q)
 * The prime factors should be prime and not equal.
 * p and q should be spaced by at least 0.1 * max(p,q).
 * @param p the first prime factor
 * @param q the second prime factor
 */
void test_generate_modulus_prime_factors();

#endif