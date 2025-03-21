#ifndef TEST_DECRYPT_H
#define TEST_DECRYPT_H

#include "../rsa.h"

/**
 * Tests the decryption of a crypted message.
 * @param n the modulus
 * @param e the public key
 * @param C the message to decrypt
 * @param expected the expected message
 */
void test_decrypt(unsigned long n, unsigned long e, string C, string expected, 
    const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet); 

#endif 