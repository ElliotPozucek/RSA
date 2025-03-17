// rsa.h - Elliot Pozucek - Security - TP1

#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <random>
#include <climits>

// warning when using exactly 32 bits (overflow). Use 28 bits for quick tests.
#define NB_BITS_PRIME_FACTORS 25
// subtract 1 to avoid overflow when using exactly 32 bits
#define UPPER_BOUND_PRIME_FACTOR (1U << NB_BITS_PRIME_FACTORS)
#define LOWER_BOUND_PRIME_FACTOR (1U << NB_BITS_PRIME_FACTORS - 4)
#define PRIME_FACTOR_DISTANCE_THRESHOLD (1U << NB_BITS_PRIME_FACTORS / 2)
#define NUMBER_OF_ITERATIONS_PRIME_TEST 15

using namespace std;

/**
 * Generate the RSA keys.
 * @return true if the keys were successfully generated, false otherwise
 */
bool rsa();

/**
 * Generate the two prime factors of the modulus.
 * p et q are passed by reference and will be modified.
 * Number of iterations needed to generate the prime factors is also passed by reference.
 * 
 * @param p the first prime factor (modified, 32 bits)
 * @param q the second prime factor (modified, 32 bits)
 * @param iterations the number of iterations needed to generate the prime factors (modified)
 * @return the modulus n = p.q (64 bits)
 */
unsigned long generate_modulus_prime_factors(unsigned int &p, unsigned int &q, int &iterations);

/**
 * Generate the public key e.
 * e must be within [2, n-1] and coprime with φ(n).
 * @param n the modulus (64 bits)
 * @param euler_totient the euler totient of n (64 bits)
 * @return the public key e (64 bits)   
 */
unsigned long generate_public_key(unsigned long n, unsigned long euler_totient, int &iterations);

/**
 * Generate the private key d such as e.d + k.φ(n) = 1.
 * This function implements the extended Euclidean algorithm.
 * @param e the public key (64 bits)
 * @param euler_totient the euler totient of n (64 bits)
 * @return the private key d (64 bits)
 */
unsigned long generate_private_key(unsigned int e, unsigned long euler_totient, int &iterations);

/**
 * Compute the euler_totient φ(n) = (p-1)(q-1).
 * @param p the first prime factor
 * @param q the second prime factor
 * @return φ(n) = (p-1)(q-1)
 */
unsigned long compute_euler_totient(unsigned int p, unsigned int q);

/**
 * Return the result of base^exp mod n, using a fast algorithm.
 * @param base the base 
 * @param exp the exponent
 * @param n the modulo
 * @return base^exp mod n
 */ 
unsigned long modular_exponentiation(unsigned int base, unsigned int exp, unsigned long n);

/**
 * Check if a number is prime. Caps to 32 bits unsigned integers.
 * This function implement the Miller-Rabin primality test.
 * @param number number to test
 * @return true if n is probably prime, false if definitely composite (not prime)
 */
bool prime(unsigned int number);

 /**
  * Is used to test the function prime(unsigned int number) from rsa.cpp
 * @param number number to test
 * @return true if number is prime, false otherwise
 */
bool square_root_test(unsigned long number);


#endif