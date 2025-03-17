#include "test_decrypt.h"

void test_decrypt(unsigned long n, unsigned long d, string C, string expected) {
    string decrypted = decrypt(n, d, C);
    if (decrypted == expected) {
        cout << "Decryption test passed." << endl << endl;
    } else {
        cout << "Decryption test failed." << endl << endl;
    }
}