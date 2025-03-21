#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <random>
#include <climits>
#include "alphabets.cpp"

// Number of bits for the prime factors of the modulus. The modulus will be twice this size.
// For example, with 32 bits, the key size will be 64 bits.
// WARNING: when using exactly 32 bits. It does not cause issue for exactly 32 bits.
// Prime factors greater than 2^32 - 1 (32 bits) will cause overflow and are not supported yet.
// The maximum supported key size is 64 bits (32 bits for each prime factors).
#define NB_BITS_PRIME_FACTORS 32
// Subtract 1 to avoid overflow when using exactly 32 bits
#define UPPER_BOUND_PRIME_FACTOR (1U << NB_BITS_PRIME_FACTORS) - 1
#define LOWER_BOUND_PRIME_FACTOR (1U << NB_BITS_PRIME_FACTORS - 4)
#define PRIME_FACTOR_DISTANCE_THRESHOLD (1U << NB_BITS_PRIME_FACTORS / 2)
// Used in the Miller-Rabin primality test. Must be at least 8.
#define NUMBER_OF_ITERATIONS_PRIME_TEST 8

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
 * @param verbose if true, display the steps of the prime factors generation
 * @return the modulus n = p.q (64 bits)
 */
unsigned long generate_modulus_prime_factors(unsigned int &p, unsigned int &q, int &iterations, bool verbose = true);

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
 * Return the result of (base^exp) % n using exponentiation by squaring.
 * Complexity: O(log(exp))
 * @param base the base 
 * @param exp the exponent
 * @param n the modulo
 * @return (base^exp) % n
 */ 
unsigned long modular_exponentiation(unsigned int base, unsigned int exp, unsigned long n);

/**
 * Check if a number is prime using the Miller-Rabin primality test.
 * Caps to 32-bits unsigned integers.
 * This test is probabilistic for large number.
 * The number of repetitions for the Miller-Rabin test is defined by NUMBER_OF_ITERATIONS_PRIME_TEST.
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

/**
 * Encrypt a message using the public key.
 * @param n the modulus
 * @param e the public key
 * @param message the message to encrypt
 * @param alphabet_to_index the alphabet dictionnary
 * @param index_to_alphabet the index dictionnary
 * @param verbose true to display the encryption steps, false otherwise
 * @return the encrypted message
 */
string encrypt(unsigned long n, unsigned long e, string M, 
    const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet,
    bool verbose = true);

/**
 * Decrypt a message using the private key.
 * @param n the modulus
 * @param d the private key
 * @param C the message to decrypt
 * @param alphabet_to_index the alphabet dictionnary
 * @param index_to_alphabet the index dictionnary
 * @param verbose if true, display the steps of the decryption
 * @return the decrypted message
 */
string decrypt(unsigned long n, unsigned long d, string C, 
    const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet,
    bool verbose = true);

#endif