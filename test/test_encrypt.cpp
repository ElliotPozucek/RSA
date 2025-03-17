#include "test_encrypt.h"

void test_encrypt(unsigned long n, unsigned long e, string M, string expected) {
    string encrypted = encrypt(n, e, M);
    if (encrypted == expected) {
        cout << "Encryption test passed." << endl;
    } else {
        cout << "Encryption test failed." << endl;
    }
}