// rsa.cpp - Elliot Pozucek - Security - TP1

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
    if (number <= 2) return true;
    if (number % 2 == 0) return false;
    
    unsigned int d = number - 1;
    unsigned int s = 0;
    unsigned int x;

    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = NUMBER_OF_ITERATIONS_PRIME_TEST; i > 0; i--) {
        default_random_engine generator(time(0));
        uniform_int_distribution<unsigned int> distribution(2, number - 2);
        x = modular_exponentiation(distribution(generator), d, number);

        if (x == 1 || x == number - 1) continue;
        for (int j = 1; j < s; j++) {
            x = modular_exponentiation(x, 2, number);
            if (x == 1) return false;
            if (x == number - 1) break;
        }
        if (x != number - 1) return false;
    }
    return true;
}

unsigned long modular_exponentiation(unsigned int base, unsigned int exp, unsigned long n) {
    unsigned long temp = 1;
    for (unsigned long exp_cpt = 1; exp_cpt <= exp; exp_cpt++) {
        temp = base * temp % n;
    }
    return temp;
}

unsigned long generate_modulus_prime_factors(unsigned int &p, unsigned int &q, int &iterations) {
    cout << "Generating prime factors..." << "(" << NB_BITS_PRIME_FACTORS << " bits)" << endl;
    default_random_engine generator(time(0));
    uniform_int_distribution<unsigned int> distribution(LOWER_BOUND_PRIME_FACTOR, UPPER_BOUND_PRIME_FACTOR);
    while (true) {
        iterations++;
        p = distribution(generator);
        if (prime(p)) {
            break;
        }
    }
    while (true) {
        iterations++;
        q = distribution(generator);
        if (prime(q)) {
            if (p > q) {
                if (p - q > PRIME_FACTOR_DISTANCE_THRESHOLD) {
                    break;
                }
            }
            else {
                if (q - p > PRIME_FACTOR_DISTANCE_THRESHOLD) {
                    break;
                }
            }
        }
    }
    cout << "p = " << p << endl << "q =  " << q << endl << "n = " << p * q << endl;
    cout << "Number of iterations for prime factors generation : " << iterations << endl;
    return p * q;
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

string encrypt(unsigned long n, unsigned long e, string M) {
    // first we need to know the size of block
    // b < ln(n) / ln(L), with L the size of the alphabet
    int b = floor(log(n) / log(ALPHABET_SIZE));
    cout << "Block size : " << b << endl;
    cout << "Message : " << M << endl;

    // when the message is not a multiple of b, we add some padding ('A' -> 0)
    if (M.size() % b != 0) {
        M += string(b - M.size() % b, 'A');
    }

    // we display the message by block, with padding
    cout << "Message by block (with padding) : ";
    for (int i = 0; i < M.size() / b; i++) {
        cout << M.substr(i * b, b) << " ";
    }
    cout << endl;

    // we convert the message in its numerical representation (base 10)
    int* converted_message = new int[M.size() / b + 1]();
    cout << "Base 10 representation of the message : ";
    for (int i = 0; i < M.size() / b; i++) {
        converted_message[i] = 0;
        for (int j = 0; j < b; j++) {
            converted_message[i] += alphabet_to_index.at(M[i * b + j]) * pow(ALPHABET_SIZE, b - j - 1);
        }
        cout << converted_message[i] << " ";
    }
    cout << endl;

    // the encrypted message
    string encrypted_message = "";
    // encryption
    cout << "Base 10 representation of the encrypted message : ";
    for (int i = 0; i < M.size() / b; i++) {
        // C = M^e mod n
        unsigned long c = modular_exponentiation(converted_message[i], e, n);
        cout << c << " ";
        // we convert the number with the alphabet
        // the size of block for converting the encrypted message to its alphabet representation is b + 1
        for (int j = 0; j < b + 1; j++) {
            encrypted_message += index_to_alphabet.at(c / (unsigned long)pow(ALPHABET_SIZE, b + 1 - j - 1));
            c %= (unsigned long)pow(ALPHABET_SIZE, b + 1 - j - 1);
        }
    }
    cout << endl << "Encrypted message : " << encrypted_message << endl;
    return encrypted_message;
}

bool rsa() {
    unsigned int p, q;
    int iter = 0;
    unsigned long n = generate_modulus_prime_factors(p, q, iter);
    unsigned long euler_totient = compute_euler_totient(p, q);
    unsigned long e = generate_public_key(n, euler_totient, iter);
    unsigned long d = generate_private_key(e, euler_totient, iter);
    cout << endl << "RSA keys generated (" << NB_BITS_PRIME_FACTORS * 2 << " bits) :" << endl;
    cout << "Public key : " << e << endl << "Private key : " << d << endl << "Modulus : " << n << endl << "Iterations : " << iter << endl;
    return true;
}