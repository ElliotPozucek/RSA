import math
import random
import time

# Number of bits for each prime factor (p and q)
# The key size will be 2 * NB_BITS_PRIME_FACTORS
# For example, if NB_BITS_PRIME_FACTORS = 1024, the key size will be 2048 bits.
NB_BITS_PRIME_FACTORS = 128

# Number of iterations for the Miller-Rabin primality test
# The more iterations, the more accurate the test, but also slower.
# For academic purposes, more than 10~15 iterations are not necessary.
# As a reminder, the probability of error (false positive) is 4^(-k), where k is the number of iterations.
# The probability of false positive for k = 8 is approximately 0.000015
NUMBER_OF_ITERATIONS_PRIME_TEST = 8

# Upper and lower bounds for the prime factors
# We want to generate prime that are always close to 2^NB_BITS_PRIME_FACTORS
UPPER_BOUND_PRIME_FACTOR = (1 << NB_BITS_PRIME_FACTORS) - 1
LOWER_BOUND_PRIME_FACTOR = 1 << (NB_BITS_PRIME_FACTORS - 4)

# Global variables
iterations = 0

# Random seed
random.seed(time.time())

def gcd(a: int, b: int) -> int:
    """
    Compute the greatest common divisor (GCD) of two integers using the Euclidean algorithm.

    Args:
        a (int): First integer.
        b (int): Second integer.

    Returns:
        int: The GCD of a and b.
    """
    global iterations
    while b != 0:
        iterations += 1
        temp = b
        b = a % b
        a = temp
    return a

def modular_exponentiation(base: int, exp: int, n: int) -> int:
    """
    Compute (base^exp) mod n using exponentiation by squaring.

    Args:
        base (int): The base.
        exp (int): The exponent.
        n (int): The modulus.

    Returns:
        int: Result of (base^exp) mod n.
    """
    global iterations
    res = 1
    b = base % n
    iterations += 2
    while exp > 0:
        iterations += 1
        if exp % 2 == 1:
            res = (res * b) % n
            iterations += 2
        b = (b * b) % n
        exp //= 2
        iterations += 2
    return res

def square_root_test(number: int) -> bool:
    """
    Perform a simple primality check by trial division up to the square root of the number.
    Is tremendously inefficient for large numbers, but is 100% accurate (deterministic).

    Args:
        number (int): Number to test for primality.

    Returns:
        bool: True if number is prime (100% accurate), False otherwise.
    """
    global iterations
    if number <= 2:
        return True
    if number % 2 == 0:
        return False
    root = int(math.isqrt(number))
    iterations += 1
    for i in range(3, root + 1, 2):
        iterations += 1
        if number % i == 0:
            return False
    return True

def prime(number: int) -> bool:
    """
    Perform Miller-Rabin probabilistic primality test.
    More about the algorithm: https://en.wikipedia.org/wiki/Miller–Rabin_primality_test
    The number of iterations of the test can be adjusted by changing NUMBER_OF_ITERATIONS_PRIME_TEST (global variable).
    
    Args:
        number (int): Number to test.

    Returns:
        bool: True if number is probably prime, False if definitely composite.
    """
    global iterations
    if number <= 1:
        return False
    if number == 2:
        return True
    if number % 2 == 0:
        return False
    d = number - 1
    s = 0
    iterations += 2
    while d % 2 == 0:
        d //= 2
        s += 1
        iterations += 2
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

def generate_modulus_prime_factors() -> tuple[int, int, int]:
    """
    Generate two distinct prime numbers and their modulus (n = p * q).

    Returns:
        Tuple[int, int, int]: Tuple containing the prime factors p & q, and the modulus n.
    """
    global iterations
    while True:
        p = random.randint(LOWER_BOUND_PRIME_FACTOR, UPPER_BOUND_PRIME_FACTOR)
        iterations += 1
        if prime(p):
            break
    while True:
        q = random.randint(LOWER_BOUND_PRIME_FACTOR, UPPER_BOUND_PRIME_FACTOR)
        iterations += 1
        if prime(q):
            if NB_BITS_PRIME_FACTORS <= 32:
                if p != q:
                    break
            else:
                if abs(p - q) > (NB_BITS_PRIME_FACTORS // 32):
                    break
    return p, q, p * q

def compute_euler_totient(p: int, q: int) -> int:
    """
    Compute Euler's totient function phi(n) = (p-1)*(q-1).

    Args:
        p (int): First prime factor.
        q (int): Second prime factor.

    Returns:
        int: The value of Euler's totient function.
    """
    global iterations
    iterations += 2
    return (p - 1) * (q - 1)

def generate_public_key(n: int, euler_totient: int) -> int:
    """
    Generate a random public key e coprime with euler_totient.

    Args:
        n (int): Modulus.
        euler_totient (int): Euler's totient of the modulus.

    Returns:
        int: The public key e.
    """
    global iterations
    while True:
        e = random.randint(2, n - 1)
        iterations += 1
        if gcd(e, euler_totient) == 1:
            break
    return e

def generate_private_key(e: int, euler_totient: int) -> int:
    """
    Compute the private key d such that e * d ≡ 1 (mod phi(n)) using Extended Euclidean Algorithm.
    e must be coprime with euler_totient.

    Args:
        e (int): Public key.
        euler_totient (int): Euler's totient of the modulus.

    Returns:
        int: The private key d.
    """
    global iterations
    r, r1 = e, euler_totient
    u, v, u1, v1 = 1, 0, 0, 1
    iterations += 6
    while r1 != 0:
        q = r // r1
        r, r1 = r1, r - q * r1
        u, u1 = u1, u - q * u1
        v, v1 = v1, v - q * v1
        iterations += 6
    if u < 0:
        u += euler_totient
        iterations += 1
    return u

def encrypt(n: int, e: int, message: str, alphabet_to_index: dict[str, int], index_to_alphabet: dict[int, str]) -> str:
    """
    Encrypt a message using RSA encryption.
    The message is converted to a numerical representation based on the provided alphabet mapping.
    The encryption is performed using the public key (n, e).
    The message is cut into blocks so that the numerical representation of the message is less than n. 

    Args:
        n (int): Modulus.
        e (int): Public key.
        message (str): Message to encrypt.
        alphabet_to_index (dict): Mapping from characters to indices.
        index_to_alphabet (dict): Mapping from indices to characters.

    Returns:
        str: Encrypted message.
    """
    global iterations
    b = int(math.floor(math.log(n, len(alphabet_to_index))))
    iterations += 1
    if len(message) % b != 0:
        message += 'A' * (b - len(message) % b)
    converted_message = []
    for i in range(0, len(message), b):
        val = 0
        for j in range(b):
            val += alphabet_to_index[message[i + j]] * (len(alphabet_to_index) ** (b - j - 1))
            iterations += 2
        converted_message.append(val)
    encrypted_message = ''
    for val in converted_message:
        c = pow(val, e, n)
        iterations += 1
        for j in range(b + 1):
            encrypted_message += index_to_alphabet[c // (len(index_to_alphabet) ** (b + 1 - j - 1))]
            c %= len(index_to_alphabet) ** (b + 1 - j - 1)
            iterations += 2
    return encrypted_message

def decrypt(n: int, d: int, cipher: str, alphabet_to_index: dict[str, int], index_to_alphabet: dict[int, str]) -> str:
    """
    Decrypt an RSA encrypted message.
    The ciphertext is converted back to a numerical representation based on the provided alphabet mapping.
    The decryption is performed using the private key (n, d).
    The message is cut into blocks so that the numerical representation of the message is less than n.
    The block size is always the same as the one used in encryption incremented by 1.

    Args:
        n (int): Modulus.
        d (int): Private key.
        cipher (str): Ciphertext to decrypt.
        alphabet_to_index (dict): Mapping from characters to indices.
        index_to_alphabet (dict): Mapping from indices to characters.

    Returns:
        str: Decrypted message.
    """
    global iterations
    b = int(math.floor(math.log(n, len(alphabet_to_index)))) + 1
    iterations += 1
    if len(cipher) % b != 0:
        return ''
    converted_message = []
    for i in range(0, len(cipher), b):
        val = 0
        for j in range(b):
            val += alphabet_to_index[cipher[i + j]] * (len(alphabet_to_index) ** (b - j - 1))
            iterations += 2
        converted_message.append(val)
    decrypted_message = ''
    for val in converted_message:
        m = pow(val, d, n)
        iterations += 1
        for j in range(b - 1):
            decrypted_message += index_to_alphabet[m // (len(index_to_alphabet) ** (b - j - 2))]
            m %= len(index_to_alphabet) ** (b - j - 2)
            iterations += 2
    return decrypted_message

def rsa() -> tuple[int, int, int, int, int, int]:
    """
    Generate RSA keys: two prime factors (p, q), modulus (n), public key (e), and private key (d).

    Returns:
        tuple[int, int, int, int, int, int]: p, q, n, e, d, and total basic operations performed.
    """
    global iterations
    iterations = 0
    p, q, n = generate_modulus_prime_factors()
    euler_totient = compute_euler_totient(p, q)
    e = generate_public_key(n, euler_totient)
    d = generate_private_key(e, euler_totient)
    return p, q, n, e, d, iterations