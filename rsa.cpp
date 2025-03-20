#include "rsa.h"

bool square_root_test(unsigned long number) {
    if (number <= 2) return true;
    if (number % 2 == 0) return false;
    unsigned long root = sqrt(number); //sqrt(number) < number/2
    for (unsigned long i = 3; i <= root; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}

bool prime(unsigned int number) {
    if (number <= 1) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    
    unsigned int d = number - 1;
    unsigned int s = 0;

    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    default_random_engine generator(time(0));
    uniform_int_distribution<unsigned int> distribution(2, number - 2);
    
    for (int i = 0; i < NUMBER_OF_ITERATIONS_PRIME_TEST; i++) {
        unsigned long random_number = distribution(generator);
        unsigned long x = modular_exponentiation(random_number, d, number);

        if (x == 1 || x == number - 1) continue;

        // Boolean flag to reduce the number of futile operations
        bool continue_loop = false;
        
        for (int j = 1; j < s; j++) {
            x = modular_exponentiation(x, 2, number);
            if (x == number - 1) {
                continue_loop = true;
                break;
            }
            if (x == 1) return false; // definitely composite
        }
        if (!continue_loop) return false; // definitely composite
    }
    return true;
}

unsigned long modular_exponentiation(unsigned int base, unsigned int exp, unsigned long n) {
    unsigned long res = 1;
    unsigned long b = base % n;

    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * b) % n; // multiply res by b if exp is odd
        }
        b = (b * b) % n;
        exp /= 2;
    }
    return res;
}

unsigned long generate_modulus_prime_factors(unsigned int &p, unsigned int &q, int &iterations, bool verbose) {
    if (verbose) cout << "Generating prime factors..." << "(" << NB_BITS_PRIME_FACTORS << " bits)" << endl;

    default_random_engine generator(time(0));
    uniform_int_distribution<unsigned int> distribution(LOWER_BOUND_PRIME_FACTOR, UPPER_BOUND_PRIME_FACTOR);

    // Generate first prime factor p
    do {
        p = distribution(generator);
        iterations++;
        if (verbose && iterations % 10 == 0) {
            cout << "Iterations : " << iterations << endl;
        }
    } while (!prime(p));

    // Generate second prime factor q
    // The distance between p and q must be greater than PRIME_FACTOR_DISTANCE_THRESHOLD
    do {
        q = distribution(generator);
        iterations++;
        if (verbose && iterations % 10 == 0) {
            cout << "Iterations : " << iterations << endl;
        }
    } while (!prime(q) || (p > q && p - q <= PRIME_FACTOR_DISTANCE_THRESHOLD) ||(q > p && q - p <= PRIME_FACTOR_DISTANCE_THRESHOLD)); 

    if (verbose) {
        cout << "p = " << p << endl << "q =  " << q << endl << "n = " << p * q << endl;
        cout << "Number of iterations for prime factors generation : " << iterations << endl;
    }

    // Convert p and q to long to avoid overflow
    return static_cast<unsigned long>(p) * q;
}

unsigned long compute_euler_totient(unsigned int p, unsigned int q) {
    return (p - 1) * (q - 1);
}

unsigned long generate_public_key(unsigned long n, unsigned long euler_totient, int &iterations) {
    cout << "Generating public key..." << endl;
    default_random_engine generator(time(0));
    uniform_int_distribution<unsigned long> distribution(2, n - 1);
    unsigned long e;
    while (true) {
        iterations++;
        e = distribution(generator);
        if (gcd(e, euler_totient) == 1) {
            break;
        }
    }
    cout << "Public key e = " << e << endl;
    return e;
}

unsigned long generate_private_key(unsigned int e, unsigned long euler_totient, int &iterations) {
    cout << "Generating private key..." << endl;
    // Extended Euclidean algorithm
    // e * d + k * euler_totient = 1
    // At the end of execution, d = u
    long r = e;
    long r1 = euler_totient;
    long u = 1, v = 0, u1 = 0, v1 = 1;
    long q, rs, us, vs;
    while (r1 != 0) {
        q = r / r1;
        rs = r; us = u; vs = v;
        r = r1; u = u1; v = v1;
        r1 = rs - q * r1;
        u1 = us - q * u1;
        v1 = vs - q * v1;
    }
    // ensure that u is positive
    if (u < 0) {
        u += euler_totient;
    }
    cout << "Private key d = " << u << endl;
    return u;
}

string encrypt(unsigned long n, unsigned long e, string M, 
    const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet,
    bool verbose) {
    if (verbose) cout << "Encrypting message..." << endl;
    // first we need to know the size of block
    // b < ln(n) / ln(L), with L the size of the alphabet
    int b = floor(log(n) / log(alphabet_to_index.size()));

    if (verbose) cout << "Block size : " << b << endl;
    if (verbose) cout << "Message : " << M << endl;

    // when the message is not a multiple of b, we add some padding ('A' -> 0)
    if (M.size() % b != 0) {
        M += string(b - M.size() % b, 'A');
    }

    // we display the message by block, with padding
    if (verbose) cout << "Message by block (with padding) : ";
    for (int i = 0; i < M.size() / b; i++) {
        if (verbose) cout << M.substr(i * b, b) << " ";
    }
    if (verbose) cout << endl;

    // we convert the message in its numerical representation (base 10)
    int* converted_message = new int[M.size() / b + 1]();
    if (verbose) cout << "Base 10 representation of the message : ";
    for (int i = 0; i < M.size() / b; i++) {
        converted_message[i] = 0;
        for (int j = 0; j < b; j++) {
            converted_message[i] += alphabet_to_index.at(M[i * b + j]) * pow(alphabet_to_index.size(), b - j - 1);
        }
        if (verbose) cout << converted_message[i] << " ";
    }
    if (verbose) cout << endl;

    // the encrypted message
    string encrypted_message = "";
    // encryption
    if (verbose) cout << "Base 10 representation of the encrypted message : ";
    for (int i = 0; i < M.size() / b; i++) {
        // C = M^e mod n
        unsigned long c = modular_exponentiation(converted_message[i], e, n);
        if (verbose) cout << c << " ";
        // we convert the number with the alphabet
        // the size of block for converting the encrypted message to its alphabet representation is b + 1
        for (int j = 0; j < b + 1; j++) {
            encrypted_message += index_to_alphabet.at(c / (unsigned long)pow(index_to_alphabet.size(), b + 1 - j - 1));
            c %= (unsigned long)pow(index_to_alphabet.size(), b + 1 - j - 1);
        }
    }
    if (verbose) cout << endl << "Encrypted message : " << encrypted_message << endl << endl;
    return encrypted_message;
}

string decrypt(unsigned long n, unsigned long d, string C, 
    const unordered_map<char, int>& alphabet_to_index, const unordered_map<int, char>& index_to_alphabet,
    bool verbose) {
    if (verbose) cout << "Decrypting message..." << endl;
    // first we need to know the size of block
    // b < ln(n) / ln(L) + 1, with L the size of the alphabet
    int b = floor(log(n) / log(alphabet_to_index.size())) + 1; 
    if (verbose) cout << "Block size : " << b << endl;

    if (C.size() % b != 0) {
        cout << "Error : the encrypted message must be padded." << endl;
        return "";
    }

    // we display the message by block
    if (verbose) cout << "Encrypted message by block : ";
    for (int i = 0; i < C.size() / b; i++) {
        if (verbose) cout << C.substr(i * b, b) << " ";
    }
    if (verbose) cout << endl;

    // we convert the message in its numerical representation (base 10)
    int* converted_message = new int[C.size() / b]();
    if (verbose) cout << "Base 10 representation of the encrypted message : ";
    for (int i = 0; i < C.size() / b; i++) {
        converted_message[i] = 0;
        for (int j = 0; j < b; j++) {
            converted_message[i] += alphabet_to_index.at(C[i * b + j]) * pow(alphabet_to_index.size(), b - j - 1);
        }
        if (verbose) cout << converted_message[i] << " ";
    }
    if (verbose) cout << endl;

    // the decrypted message
    string decrypted_message = "";

    // decryption
    if (verbose) cout << "Base 10 representation of the decrypted message : ";
    for (int i = 0; i < C.size() / b; i++) {
        // M = C^d mod n
        unsigned long m = modular_exponentiation(converted_message[i], d, n);
        if (verbose) cout << m << " ";
        // we convert the number with the alphabet
        // the size of block for converting the decrypted message to its alphabet representation is b - 1
        for (int j = 0; j < b - 1; j++) {
            decrypted_message += index_to_alphabet.at(m / (unsigned long)pow(index_to_alphabet.size(), b - j - 2));
            m %= (unsigned long)pow(index_to_alphabet.size(), b - j - 2);
        }
    }
    if (verbose) cout << endl << "Decrypted message : " << decrypted_message << endl << endl;
    return decrypted_message;
}

bool rsa() {
    unsigned int p, q;
    int iter = 0;
    unsigned long n = generate_modulus_prime_factors(p, q, iter, false);
    unsigned long euler_totient = compute_euler_totient(p, q);
    unsigned long e = generate_public_key(n, euler_totient, iter);
    unsigned long d = generate_private_key(e, euler_totient, iter);
    cout << endl << "RSA keys generated (" << NB_BITS_PRIME_FACTORS * 2 << " bits) :" << endl;
    cout << "Public key e = " << e << endl << "Private key d = " << d << endl << "Modulus n = " << n << endl << "Iterations : " << iter << endl;
    return true;
}