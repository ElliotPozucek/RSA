// rsa.h - Elliot Pozucek - Security - TP1

#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <random>
#include <climits>

#define UPPER_BOUND_ULONG ULONG_MAX
#define LOWER_BOUND_ULONG ULONG_MAX/2
#define PRIME_FACTOR_DISTANCE_THRESHOLD (1UL << 24)

using namespace std;

/**
 * Generate the two prime factors of the modulus.
 * p et q are passed by reference and will be modified.
 * @param p the first prime factor (modified, 32 bits)
 * @param q the second prime factor (modified, 32 bits)
 * @return the modulus n = p.q (64 bits)
 */
unsigned long long generate_modulus_prime_factors(unsigned long &p, unsigned long &q);

/**
 * Generate the public key e.
 * e must be within [2, n-1] and coprime with φ(n).
 * @param n the modulus (64 bits)
 * @param euler_totient the euler totient of n (64 bits)
 * @return the public key e (64 bits)   
 */
unsigned long long generate_public_key(unsigned long long n, unsigned long long euler_totient);

/**
 * Generate the private key d such as e.d + k.φ(n) = 1.
 * This function implements the extended Euclidean algorithm.
 * @param e the public key (64 bits)
 * @param euler_totient the euler totient of n (64 bits)
 * @return the private key d (64 bits)
 */
unsigned long long generate_private_key(unsigned long e, unsigned long long euler_totient);

/**
 * Compute the euler_totient φ(n) = (p-1)(q-1).
 * @param p the first prime factor
 * @param q the second prime factor
 * @return φ(n) = (p-1)(q-1)
 */
unsigned long long compute_euler_totient(unsigned long p, unsigned long q);

/**
 * Return the result of base^exp mod n, using a fast algorithm.
 * @param base the base 
 * @param exp the exponent
 * @param n the modulo
 * @return base^exp mod n
 */ 
unsigned long long modular_exponentiation(unsigned long base, unsigned long exp, unsigned long long n);

/**
 * Check if a number is prime.
 * This function implement the Solovay-Strassen primality test.
 * @param number number to test
 * @return true if n is prime, false otherwise
 */
bool prime(unsigned long number);

#endif