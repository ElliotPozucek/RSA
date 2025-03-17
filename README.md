# RSA Cryptosystem Implementation

This project is a C++ implementation of the RSA cryptosystem. It was done as a part of the course "Sécurité Informatique" at Avignon Université.

The implementation includes key generation, modular arithmetic, and primality testing using the Miller-Rabin algorithm.

Due to the complexity of the RSA algorithm, this implementation is not efficient for large key sizes (32 bits or more).

KEY SIZE MAX SIZE: 32 bits (modulus 64 bits) 

## Table of Contents
- [Features](#features)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [Functions](#functions)
   - [Key Generation](#key-generation)
   - [Encryption and Decryption](#encryption-and-decryption)
   - [Utility Functions](#utility-functions)
   - [Test methods](#test-methods)
- [Alphabet Mapping](#alphabet-mapping)
- [Personalization](#personalization)
- [Limitations](#limitations)

## Features

- **Prime Number Generation**: Generates large prime numbers for RSA key pairs, using Miller-Rabin test.
- **Key Generation**: Generates public and private keys using the RSA algorithm.
- **Modular Arithmetic**: Implements fast modular exponentiation for efficient computations.
- **Encryption and Decryption**: Encrypts and decrypts messages using the generated keys.
- **Alphabet Mapping**: Supports custom alphabet mapping for message encryption and decryption.
- **Customizable Parameters**: Allows adjustment of key size and the number of Miller-Rabin tests.

## Dependencies

- **C++ Compiler**: A C++ compiler supporting C++11 or later (e.g., `g++`).
- **Standard Library**: Uses the C++ Standard Library (`<random>`, `<climits>`).

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/ElliotPozucek/RSA.git
   ```

2. Build the executable:
   ```bash
   make all
   ```

3. Run the executable:
   ```bash
   ./rsa.exe
   ```

4. Clean the build files:
   ```bash
   make clean
   ```

## Functions

### Key Generation

- bool **rsa**(): Main function that generates RSA keys.
- unsigned long **generate_modulus_prime_factors**(unsigned int &p, unsigned int &q, int &iterations, bool verbose = true): Generates two prime factors `p` and `q` for the modulus `n`.
- unsigned long **generate_public_key**(unsigned long n, unsigned long euler_totient, int &iterations): Generates the public key `e`.
- unsigned long **generate_private_key**(unsigned int e, unsigned long euler_totient, int &iterations): Generates the private key `d`.

### Encryption and Decryption

- string **encrypt**(unsigned long n, unsigned long e, string M, const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet, bool verbose = true): Encrypts a message `M` using the public key `(n, e)`. The alphabets are mapped to integers using the provided dictionaries in `alphabets.cpp`.
- string **decrypt**(unsigned long n, unsigned long d, string C, const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet, bool verbose = true): Decrypts a message `C` using the private key `(n, d)`.

### Utility Functions

- unsigned long **compute_euler_totient**(unsigned int p, unsigned int q): Computes Euler's totient function `φ(n)` = (`p`-1)(`q`-1).
- unsigned long **modular_exponentiation**(unsigned int base, unsigned int exp, unsigned long n): Computes `base`^`exp` mod `n` with fast modular exponentiation.
- bool **prime**(unsigned int number): Checks if a number is prime using the Miller-Rabin test (probabilistic).
- bool **square_root_test**(unsigned long number): Checks if a number is prime without using a probabilistic test (absolute certainty).

### Test methods

All test methods are located in `test/` directory. They should all pass.

- void **test_generate_modulus_prime_factors()**: Tests the `generate_modulus_prime_factors` function.
- void **test_prime()**: Tests the `prime` function.
- void **test_prime_factors**(): Tests the `prime_factors` function.
- void **test_encrypt**(): Tests the `encrypt` function.
- void **test_decrypt**(): Tests the `decrypt` function.

## Alphabet Mapping

The implementation supports custom alphabet mapping for message encryption and decryption. The alphabet mappings are defined in `alphabets.cpp`.
There are two dictionaries for each alphabet mapping: one for mapping characters to integers and another for mapping integers back to characters.

```cpp
// Alphabet dictionnary used for encryption/ decryption. 40 characters.
const std::unordered_map<char, int> alphabet_to_index_40 = {
    {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5},
    {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11},
    {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17},
    {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23},
    {'Y', 24}, {'Z', 25}, {'_', 26}, {'.', 27}, {'?', 28}, {'$', 29},
    {'0', 30}, {'1', 31}, {'2', 32}, {'3', 33}, {'4', 34}, {'5', 35},
    {'6', 36}, {'7', 37}, {'8', 38}, {'9', 39}
};

// Index dictionnary used for encryption / decryption. 40 characters.
const std::unordered_map<int, char> index_to_alphabet_40 = {
    {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'},
    {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'}, {10, 'K'}, {11, 'L'},
    {12, 'M'}, {13, 'N'}, {14, 'O'}, {15, 'P'}, {16, 'Q'}, {17, 'R'},
    {18, 'S'}, {19, 'T'}, {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'},
    {24, 'Y'}, {25, 'Z'}, {26, '_'}, {27, '.'}, {28, '?'}, {29, '$'},
    {30, '0'}, {31, '1'}, {32, '2'}, {33, '3'}, {34, '4'}, {35, '5'},
    {36, '6'}, {37, '7'}, {38, '8'}, {39, '9'}
};
```

## Personalization

The implementation can be personalized by adjusting the key size and the number of Miller-Rabin tests. The default values are set to `32` bits for the key size and `5` tests for the Miller-Rabin algorithm. They can be modified in the `rsa.h` file.

## Limitations

- **Key Size**: The implementation is not efficient for large key sizes (64 bits or more). This implementation does not support key sizes greater than 64 bits (prime factor size: 32 bits).
- **Miller-Rabin Test**: The Miller-Rabin test is probabilistic and may not always return correct results.

This project was done as a learning exercise and is not intended for real-world applications.