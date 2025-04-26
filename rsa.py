import math
import random
import time

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def modular_exponentiation(base, exp, n):
    res = 1
    b = base % n
    while exp > 0:
        if exp % 2 == 1:
            res = (res * b) % n
        b = (b * b) % n
        exp //= 2
    return res

def square_root_test(number):
    if number <= 2:
        return True
    if number % 2 == 0:
        return False
    root = int(math.isqrt(number))
    for i in range(3, root + 1, 2):
        if number % i == 0:
            return False
    return True

def prime(number):
    NUMBER_OF_ITERATIONS_PRIME_TEST = 8
    if number <= 1:
        return False
    if number == 2:
        return True
    if number % 2 == 0:
        return False
    d = number - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    random.seed(time.time())
    for _ in range(NUMBER_OF_ITERATIONS_PRIME_TEST):
        random_number = random.randint(2, number - 2)
        x = modular_exponentiation(random_number, d, number)
        if x == 1 or x == number - 1:
            continue
        for _ in range(s - 1):
            x = modular_exponentiation(x, 2, number)
            if x == number - 1:
                break
            if x == 1:
                return False
        else:
            return False
    return True

def generate_modulus_prime_factors():
    NB_BITS_PRIME_FACTORS = 64
    UPPER_BOUND_PRIME_FACTOR = (1 << NB_BITS_PRIME_FACTORS) - 1
    LOWER_BOUND_PRIME_FACTOR = 1 << (NB_BITS_PRIME_FACTORS - 4)
    PRIME_FACTOR_DISTANCE_THRESHOLD = 1 << (NB_BITS_PRIME_FACTORS // 2)
    random.seed(time.time())
    iterations = 0
    while True:
        p = random.randint(LOWER_BOUND_PRIME_FACTOR, UPPER_BOUND_PRIME_FACTOR)
        iterations += 1
        if prime(p):
            break
    while True:
        q = random.randint(LOWER_BOUND_PRIME_FACTOR, UPPER_BOUND_PRIME_FACTOR)
        iterations += 1
        if prime(q) and abs(p - q) > PRIME_FACTOR_DISTANCE_THRESHOLD:
            break
    return p, q, iterations, p * q

def compute_euler_totient(p, q):
    return (p - 1) * (q - 1)

def generate_public_key(n, euler_totient):
    random.seed(time.time())
    iterations = 0
    while True:
        e = random.randint(2, n - 1)
        iterations += 1
        if gcd(e, euler_totient) == 1:
            break
    return e, iterations

def generate_private_key(e, euler_totient):
    r, r1 = e, euler_totient
    u, v, u1, v1 = 1, 0, 0, 1
    while r1 != 0:
        q = r // r1
        r, r1 = r1, r - q * r1
        u, u1 = u1, u - q * u1
        v, v1 = v1, v - q * v1
    if u < 0:
        u += euler_totient
    return u

def encrypt(n, e, message, alphabet_to_index, index_to_alphabet):
    b = int(math.floor(math.log(n, len(alphabet_to_index))))
    if len(message) % b != 0:
        message += 'A' * (b - len(message) % b)
    converted_message = []
    for i in range(0, len(message), b):
        val = 0
        for j in range(b):
            val += alphabet_to_index[message[i + j]] * (len(alphabet_to_index) ** (b - j - 1))
        converted_message.append(val)
    encrypted_message = ''
    for val in converted_message:
        c = pow(val, e, n)
        for j in range(b + 1):
            encrypted_message += index_to_alphabet[c // (len(index_to_alphabet) ** (b + 1 - j - 1))]
            c %= len(index_to_alphabet) ** (b + 1 - j - 1)
    return encrypted_message

def decrypt(n, d, cipher, alphabet_to_index, index_to_alphabet):
    b = int(math.floor(math.log(n, len(alphabet_to_index)))) + 1
    if len(cipher) % b != 0:
        return ''
    converted_message = []
    for i in range(0, len(cipher), b):
        val = 0
        for j in range(b):
            val += alphabet_to_index[cipher[i + j]] * (len(alphabet_to_index) ** (b - j - 1))
        converted_message.append(val)
    decrypted_message = ''
    for val in converted_message:
        m = pow(val, d, n)
        for j in range(b - 1):
            decrypted_message += index_to_alphabet[m // (len(index_to_alphabet) ** (b - j - 2))]
            m %= len(index_to_alphabet) ** (b - j - 2)
    return decrypted_message

def rsa():
    p, q, iter, n = generate_modulus_prime_factors()
    euler_totient = compute_euler_totient(p, q)
    e, iter_pub = generate_public_key(n, euler_totient)
    d = generate_private_key(e, euler_totient)
    return p, q, n, e, d
