# RSA Cryptosystem Implementation

This project is a C++ implementation of the RSA cryptosystem. It was done as a part of the course "Sécurité Informatique" at Avignon Université.

The implementation includes key generation, modular arithmetic, and primality testing using the Miller-Rabin algorithm.

Due to the complexity of the RSA algorithm, this implementation is not efficient for large key sizes (32 bits or more).

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [Functions](#functions)
- [Limitations](#limitations)
- [Contributing](#contributing)
- [License](#license)

## Overview

The RSA cryptosystem is an asymmetric encryption algorithm that uses a pair of keys: a public key for encryption and a private key for decryption. This project provides a basic implementation of RSA, including:

- Generation of prime numbers for key pairs.
- Computation of the modulus, Euler's totient, and keys.
- Modular exponentiation for encryption and decryption.
- Primality testing using the Miller-Rabin algorithm.

## Features

- **Prime Number Generation**: Generates large prime numbers for RSA key pairs.
- **Key Generation**: Computes public and private keys using the Extended Euclidean Algorithm.
- **Modular Exponentiation**: Efficiently computes large exponentiations modulo `n`.
- **Primality Testing**: Uses the Miller-Rabin test to check if a number is prime.
- **Customizable Parameters**: Allows adjustment of key size and other parameters.

## Dependencies

- **C++ Compiler**: A C++ compiler supporting C++11 or later (e.g., `g++`).
- **Standard Library**: Uses the C++ Standard Library (`<iostream>`, `<random>`, `<climits>`).

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/rsa-implementation.git
   cd rsa-implementation