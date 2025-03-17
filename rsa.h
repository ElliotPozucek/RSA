// rsa.h - Elliot Pozucek - Security - TP1

#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <random>
#include <climits>
#include <unordered_map>

// warning when using exactly 32 bits (overflow). Use 28 bits for quick tests.
#define NB_BITS_PRIME_FACTORS 25
// subtract 1 to avoid overflow when using exactly 32 bits
#define UPPER_BOUND_PRIME_FACTOR (1U << NB_BITS_PRIME_FACTORS)
#define LOWER_BOUND_PRIME_FACTOR (1U << NB_BITS_PRIME_FACTORS - 4)
#define PRIME_FACTOR_DISTANCE_THRESHOLD (1U << NB_BITS_PRIME_FACTORS / 2)
#define NUMBER_OF_ITERATIONS_PRIME_TEST 15
#define ALPHABET_SIZE 40

// alphabet used for encryption
const std::unordered_map<char, int> alphabet_to_index = {
    {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5},
    {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11},
    {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17},
    {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23},
    {'Y', 24}, {'Z', 25}, {'_', 26}, {'.', 27}, {'?', 28}, {'$', 29},
    {'0', 30}, {'1', 31}, {'2', 32}, {'3', 33}, {'4', 34}, {'5', 35},
    {'6', 36}, {'7', 37}, {'8', 38}, {'9', 39}
};

// index used for encryption
const std::unordered_map<int, char> index_to_alphabet = {
    {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'},
    {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'}, {10, 'K'}, {11, 'L'},
    {12, 'M'}, {13, 'N'}, {14, 'O'}, {15, 'P'}, {16, 'Q'}, {17, 'R'},
    {18, 'S'}, {19, 'T'}, {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'},
    {24, 'Y'}, {25, 'Z'}, {26, '_'}, {27, '.'}, {28, '?'}, {29, '$'},
    {30, '0'}, {31, '1'}, {32, '2'}, {33, '3'}, {34, '4'}, {35, '5'},
    {36, '6'}, {37, '7'}, {38, '8'}, {39, '9'}
};

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

/**
 * Encrypt a message using the public key.
 * @param n the modulus
 * @param e the public key
 * @param message the message to encrypt
 * @return the encrypted message
 */
string encrypt(unsigned long n, unsigned long e, string M);

/**
 * Decrypt a message using the private key.
 * @param n the modulus
 * @param d the private key
 * @param C the message to decrypt
 * @return the decrypted message
 */
string decrypt(unsigned long n, unsigned long d, string C);

#endif