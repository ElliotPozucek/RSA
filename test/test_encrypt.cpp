#include "test_encrypt.h"

void test_encrypt(unsigned long n, unsigned long e, string M, string expected, 
    const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet) {
    string encrypted = encrypt(n, e, M, alphabet_to_index, index_to_alphabet);
    if (encrypted == expected) {
        cout << "Encryption test passed." << endl << endl;
    } else {
        cout << "Encryption test failed." << endl << endl;
    }
}