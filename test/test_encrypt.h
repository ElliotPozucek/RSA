#ifndef TEST_ENCRYPT_H
#define TEST_ENCRYPT_H

#include "../rsa.h"

/**
 * Tests the encryption of a message.
 * @param n the modulus
 * @param d the private key
 * @param M the message to encrypt
 * @param expected the expected encrypted message
 */
void test_encrypt(unsigned long n, unsigned long d, string M, string expected); 

#endif 