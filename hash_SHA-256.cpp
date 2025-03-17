#include <openssl/evp.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "rsa.h"

using namespace std;

/**
 * Compute the SHA-256 hash of a file.
 * Entirely made with AI.
 * @param file_path the path to the file
 * @return the SHA-256 hash
 */
string sha256_hash_file(const string& file_path) {
    ifstream file(file_path, ios::binary);
    if (!file) {
        throw runtime_error("Could not open file: " + file_path);
    }

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (!context) {
        throw runtime_error("Failed to create EVP_MD_CTX");
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to initialize SHA-256 context");
    }

    vector<char> buffer(1024);
    while (file.good()) {
        file.read(buffer.data(), buffer.size());
        if (EVP_DigestUpdate(context, buffer.data(), file.gcount()) != 1) {
            EVP_MD_CTX_free(context);
            throw runtime_error("Failed to update SHA-256 hash");
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length;
    if (EVP_DigestFinal_ex(context, hash, &hash_length) != 1) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to finalize SHA-256 hash");
    }

    EVP_MD_CTX_free(context);

    stringstream ss;
    for (unsigned int i = 0; i < hash_length; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();
}

int main() {
    try {
        // Valid RSA keys
        unsigned long n = 2047;
        unsigned long e = 179;
        unsigned long d = 411;

        string hash = sha256_hash_file("test.txt");
        cout << "SHA-256 Hash: " << hash << endl;

        // Sign the hash using the private key, with encrypt method
        string signature = encrypt(n, d, hash, alphabet_to_index_hexa, index_to_alphabet_hexa, false); 
        cout << "Signature: " << signature << endl;

        // Verify the signature using public key, with decrypt method
        string signature_decrypted = decrypt(n, e, signature, alphabet_to_index_hexa, index_to_alphabet_hexa, false); 
        cout << "Decrypted Signature: " << signature_decrypted << endl;
        if (hash != signature_decrypted) {
            cout << "Signature verification failed. Hash does not match decrypted signature." << endl;
        } else {
            cout << "Signature verification passed. Hash matches decrypted signature." << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}