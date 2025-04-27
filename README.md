# RSA Cryptosystem - Python Implementation

This repository contains a clean and documented implementation of the **RSA encryption and decryption algorithm**, developed as an academic assignment. This implementation can generate valide **keys up to 4096 bits** under a minute.

**WARNING:** This implementation is not intended for production use and should not be used for secure communications.  
To use RSA in a real-world application, well-established libraries should be used. 

## Overview

The RSA algorithm is a public-key cryptosystem that is widely used for secure data transmission. It is based on the mathematical properties of large prime numbers and modular arithmetic. The security of RSA relies on the difficulty of factoring the product of two large prime numbers.

Nowadays, RSA is used in various applications, including secure web browsing (HTTPS), email encryption, and digital signatures. RSA is still considered secure for most practical purposes, especially when using key sizes of 2048 bits or larger. However, it is important to note that the security of RSA is based on the assumption that factoring large numbers is computationally infeasible. As quantum computing technology advances, the security of RSA may be compromised in the future (as I write this in 2025).

See more about RSA [here](https://en.wikipedia.org/wiki/RSA_cryptosystem).


An alternative to RSA: [elliptic curve cryptography](https://en.wikipedia.org/wiki/Elliptic-curve_cryptography) 

In this project, the RSA algorithm is implemented in Python. Various functions are provided to generate keys, encrypt and decrypt messages dynamically. This project also includes a suit of dynamic tests for the user to explore the algorithm and its properties.

**NOTE** : this project was initially developed in C++ and then ported to Python. The reason for this porting is the lack of flexibility in big integer operations in C++. 
<br>Python's built-in support for arbitrary-precision integers makes it a more suitable choice for cryptographic applications.

## Table of Contents
- [Overview](#overview)
- [Project Structure](#project-structure)
- [Setup and Installation](#setup-and-installation)
- [Program Behavior](#program-behavior)
- [Functions Overview](#functions-overview)
- [Iterations Counter (Complexity Tracking)](#iterations-counter-complexity-tracking)
- [Performance](#performance)
- [Limitations and Known Issues](#limitations-and-known-issues)

## Project Structure

```bash
rsa.py                  # Main RSA algorithm implementation
main.py                 # User interface to run tests
test/
 ├── test_modular_expo.py        # Basic test used for TDD
 ├── test_prime.py               # Basic test used for TDD
 ├── test_encrypt.py             # Basic test used for TDD
 ├── test_decrypt.py             # Basic test used for TDD
 ├── test_generate_modulus.py    # Modulus generation
 ├── test_dynamic_encrypt.py     # Dynamic encryption
 └── test_rsa.py                 # Full RSA key generation
alphabet.py              # alphabet mapping (for message encoding)
```

## Setup and Installation

This project was developed and tested on **Python 3.12.3**.
<br>Only basic Python libraries are used (*time*, *random*), so **any recent Python 3 version should work** without any issues.  

I highly recommend using a **[virtual environment](https://docs.python.org/3/library/venv.html)** to avoid conflicts with other projects.

### 1. Clone the repository

```bash
git clone https://github.com/ElliotPozucek/RSA.git

cd RSA
```

### 2. Set up a virtual environment

#### Linux / MacOS

```bash
# Create a virtual environment
python3 -m venv <your_env_name>

# Activate the virtual environment
source <your_env_name>/bin/activate
```

#### Windows

```bash
# Create a virtual environment
python -m venv <your_env_name>

# Activate the virtual environment
<your_env_name>\Scripts\activate
```

### 3. Run project

```bash
# Run the main script
python3 main.py
```

## Program Behavior

Once you run `main.py`, you will be prompted to choose a **key size** in bits and if you want to run the tests with the public exponent **e** = 65537 or a random one.

Then, you will be able to choose which test you want to run:

### test_generate_modulus_prime_factors(key_size_bits):
- Generates **prime factors p and q** (p and q size: key_size_bits / 2)
- Generates **modulus n** = p * q
- Tests if p and q are valid

### test_rsa(key_size_bits, use_fixed_e):
- Generates **prime factors p and q** (p and q size: key_size_bits / 2)
- Generates **modulus n** = p * q
- Generates **euler totient** = (p-1) * (q-1)
- Generates **public key (n, e)**
    - If use_fixed_e is True, e = 65537
    - Otherwise, e is randomly generated
- Generates **private key (d)**
- Displays all the information about the keys and execution time 

### dynamic_test_encrypt(key_size_bits, use_fixed_e):
- Generates **prime factors p and q** (p and q size: key_size_bits / 2)
- Generates **modulus n** = p * q
- Generates **euler totient** = (p-1) * (q-1)
- Generates **public key (n, e)**
    - If use_fixed_e is True, e = 65537
    - Otherwise, e is randomly generated
- Generates **private key (d)**
- Asks for a **message** to encrypt
- **Encrypts** the message using the public key
- **Decrypts** the encrypted message using the private key
- Tests if the decrypted message is the same as the original message
- Displays **execution time**

The most interesting part of this project is the **dynamic encryption and decryption** (in `test_dynamic_encrypt.py`). You can test the algorithm with different messages and key sizes, and see how it works in real time. Note that the alphabet used for encoding the message is a custom 40-character alphabet. You can find the mapping in `alphabet.py`.
    
## Functions Overview

Below is a high-level overview of each function implemented in this project. More detailed explanations on the algorithm and its properties can be found within the code comments.

---

### `gcd(a, b)`
Computes the **greatest common divisor (GCD)** of two integers `a` and `b`.  
Used to ensure that two numbers are coprime, which is essential when choosing a valid public key `e` => gcd(e, euler_totient) = 1.

---

### `modular_exponentiation(base, exp, n)`
Efficiently computes \((base^{exp}) \mod n\) using **exponentiation by squaring**.  
Used during both encryption and decryption to handle very large exponentiations without performance issues.

---

### `square_root_test(number)`
Performs a **simple primality test** by checking divisibility up to the square root of the number.  
Mainly used as a secondary check in tests to validate the primes generated.

---

### `prime(number)`
Performs a **Miller-Rabin probabilistic primality test** on a given number.
Used to verify that randomly generated numbers are probably prime during key generation.  
It is possible to change the number of random tests to increase accuracy by modifying the global variable `NUMBER_OF_ITERATIONS_PRIME_TEST`. The probability of error for a Miller-Rabin test is 4^(-k), where k is the number of iterations.

---

### `generate_modulus_prime_factors(prime_factor_bits)`
Generates two distinct large prime numbers `p` and `q` of approximately the specified bit length.  
Returns `p`, `q`, and the modulus `n = p * q`.  
Ensures that `p` and `q` are not too close to each other to avoid cryptographic weaknesses.

---

### `compute_euler_totient(p, q)`
Computes **Euler's totient function** φ(n) = (p-1)(q-1), which represents the number of integers that are coprime with `n`.  
It is a key step in calculating the private key.

---

### `generate_public_key(n, euler_totient, use_fixed_e=False)`
Generates the public exponent `e` for RSA.  
- If `use_fixed_e` is True, uses the standard value 65537 in order to use fast encryption (see in encrypt function).  
- Otherwise, randomly picks an `e` that is coprime with the totient.  
Ensures fast encryption and good cryptographic properties.

---

### `generate_private_key(e, euler_totient)`
Computes the private exponent `d`, which is the **modular inverse** of `e` modulo the totient. Uses the Extended Euclidean Algorithm to find `d` such that d * e ≡ 1 (mod φ(n)).  
This allows decryption of messages encrypted with the public key.

---

### `encrypt(n, e, message, alphabet_to_index, index_to_alphabet)`
Encrypts a plaintext message using the public key `(n, e)`.  
- First, converts the message into numeric blocks based on a custom 40-character alphabet.
- Then applies modular exponentiation with `e` to encrypt each block (if e = 65537, uses the fast encryption method).
- Finally, reconstructs the cipher text from the encrypted numbers and returns it.

---

### `decrypt(n, d, cipher, alphabet_to_index, index_to_alphabet)`
Decrypts a cipher text using the private key `(n, d)`.  
- First, converts the cipher text into numeric blocks based on a custom 40-character alphabet.
- Then applies modular exponentiation with `d` to decrypt each numeric block.
- Reconstructs the original message from the decrypted numbers.

---

### `rsa(prime_factor_bits=128, use_fixed_e=False)`
High-level function that orchestrates **full RSA key generation**:
- Generates primes `p` and `q`
- Computes modulus `n`
- Computes totient \(\phi(n)\)
- Chooses public key `e`
- Computes private key `d`
- Tracks the number of iterations (basic operations)

Returns all important elements: `p, q, n, e, d, iterations`.

---

## Iterations Counter (Complexity Tracking)

The algorithm rougly tracks the number of iterations for each function. I defined as an iteration any basic operation (addition, multiplication, division, etc.) and sometimes comparisons.  
This is a basic way to track the complexity of the algorithm and see how the number of iterations grows exponentially with the key size. 

## Performance

In order to measure the execution time of the algorithm, I used the `time` module.  
The execution time is displayed after the tests that generate the keys and/or encrypt/decrypt messages.
For reference, on a *64-bit Ubuntu 24.04* machine with a *11th Gen Intel® Core™ i5-1135G7 × 8* with *16 GB RAM*, the execution times to generate the keys and encrypt/decrypt a message of 40 characters (using the custom alphabet) are as follows :

| Key Size (bits) | Message | Execution Time (seconds) | e = 65537 |
|-----------------|---------|--------------------------|-----------|
| 512    | BONSOIR | 0.03 ~ 0.05     | No
| 1024   | BONSOIR | 0.3 ~ 0.7       | No
| 2048   | BONSOIR | 3 ~ 5           | No
| 4096   | BONSOIR | 25 ~ 40         | No
| 8192   | BONSOIR | 300 ~ 400       | No

Going above 4096 bits is not recommended, as the execution time increases significantly and the algorithm may take several minutes to complete (and your machine might burn).

## Limitations and Known Issues

While this project provides a complete educational implementation of RSA, there are some important limitations to keep in mind:

---

### No Secure Padding for Encryption/Decryption

In real-world RSA, messages are padded with schemes like **OAEP** before encryption to prevent structural attacks.  
In the dynamic encryption test, the cypher text given by the `encrypt` function is padded with the character `A` because its numerical representation is 0 (no influence on the numerical representation of the message).  
So when the message is decrypted, the padding is removed by removing the trailing `A` characters using the original message length.  
In real-world applications, the original message length is not directly accessible. 

A more secure padding scheme would be to encrypt the message length and put it in the cypher text, so that the receiver can decrypt it and know how many `A` to remove to get the original message.

---

### Only supports a custom 40-character alphabet
The encryption and decryption functions assume that the input message uses a restricted set of characters (A-Z, space, dot, question mark, dollar, and digits 0-9).  
However, the alphabet is passed as a parameter to the functions, so a custom alphabet can easily be implemented.

It would also be possible to use UTF-8 encoding to support a wider range of characters.

--- 

### Performance with Large Key Sizes

Even though the algorithm is optimized for performance, the generation of large prime numbers and the encryption/decryption process can be slow for very large key sizes (depending on the machine, 4096 bits can take several minutes).  
However, I'm fairly satisfied with the performance of the algorithm on my machine with 4096-bit keys (real-world applications use 2048-bit or 4096-bit keys).

---

### No Error Handling

This project does not include satisfying error handling.
All the functions assume that the inputs are valid and do not check for exceptions, so it might be challenging to use the functions outside of the provided tests.

---

### No Cryptographic Security

This implementation is not intended for production use and should not be used for secure communications. RSA is the most widely known public-key cryptosystem, so a tremendous amount of research has been done on its flaws and vulnerabilities. A basic implementation like this one is not secure against modern attacks.