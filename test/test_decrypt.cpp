#include "test_decrypt.h"

void test_decrypt(unsigned long n, unsigned long d, string C, string expected, 
    const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet) {
    string decrypted = decrypt(n, d, C, alphabet_to_index, index_to_alphabet);
    if (decrypted == expected) {
        cout << "Decryption test passed." << endl << endl;
    } else {
        cout << "Decryption test failed." << endl << endl;
    }
}