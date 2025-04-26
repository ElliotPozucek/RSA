# RSA Cryptosystem Implementation - Python Version

This is the python version of the RSA cryptosystem implementation.

Project: RSA Cryptosystem Implementation in Python
1. Introduction
2. Project Structure
3. Requirements
4. Setup and Installation
5. Global Constants and Variables
6. Functions Overview
6.1 gcd(a, b)
6.2 modular_exponentiation(base, exp, n)
6.3 square_root_test(number)
6.4 prime(number)
6.5 generate_modulus_prime_factors()
6.6 compute_euler_totient(p, q)
6.7 generate_public_key(n, euler_totient)
6.8 generate_private_key(e, euler_totient)
6.9 encrypt(n, e, message, alphabet_to_index, index_to_alphabet)
6.10 decrypt(n, d, cipher, alphabet_to_index, index_to_alphabet)
6.11 rsa()
7. How to Generate Keys
8. How to Encrypt and Decrypt a Message
9. Iterations Counter (Complexity Tracking)
10. Limitations and Known Issues
11. Future Improvements
12. License