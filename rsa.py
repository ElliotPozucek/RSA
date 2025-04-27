import math
import random
import time


# Number of iterations for the Miller-Rabin primality test
# The more iterations, the more accurate the test, but also slower.
# For academic purposes, more than 10~15 iterations are not necessary.
# As a reminder, the probability of error (false positive) is 4^(-k), where k is the number of iterations.
# The probability of false positive for k = 8 is approximately 0.000015
NUMBER_OF_ITERATIONS_PRIME_TEST = 8

# Upper and lower bounds for the prime factors
# We want to generate prime that are always close to 2^NB_BITS_PRIME_FACTORS
# UPPER_BOUND_PRIME_FACTOR = (1 << NB_BITS_PRIME_FACTORS) - 1
# LOWER_BOUND_PRIME_FACTOR = 1 << (NB_BITS_PRIME_FACTORS - 4)

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

    Every bit of the exponent is processed separately.
    To know more about the algorithm, see: https://en.wikipedia.org/wiki/Exponentiation_by_squaring
    Time complexity: O(log(exp))

    Args:
        base (int): The base.
        exp (int): The exponent.
        n (int): The modulus.

    Returns:
        int: Result of (base^exp) mod n.
    """
    global iterations
    res = 1                             # Neutral element for multiplication
    b = base % n                        # Prevent overflow
    iterations += 2

    # Exponentiation by squaring
    while exp > 0:
        iterations += 1
        # If exp is odd (least significant bit is 1)
        if exp % 2 == 1:
            # Multiply current result by base mod n
            res = (res * b) % n
            iterations += 2
        # Square the base mod n
        b = (b * b) % n
        # Divide exp by 2 (shift right in binery, i.e., remove the least significant bit)
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

    # Test divisibility by all odd numbers from 3 to sqrt(number)
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
    The probability of error (false positive) is 4^(-k), where k is the number of iterations.
    
    Args:
        number (int): Number to test.

    Returns:
        bool: True if number is probably prime, False if definitely composite.
    """
    global iterations

    # Basic primality tests
    if number < 0:
        raise ValueError("Negative numbers in prime() method are not allowed.")
    if number == 1 or number == 0 or number == 2:
        return True
    if number % 2 == 0:
        return False
    
    d = number - 1
    s = 0
    iterations += 2

    # Decompose number - 1 (even number) into d * 2^s
    while d % 2 == 0:
        d //= 2
        s += 1          # Count the number of times we can divide by 2
        iterations += 2

    # Perform NUMBER_OF_ITERATIONS_PRIME_TEST iterations of the Miller-Rabin test
    for _ in range(NUMBER_OF_ITERATIONS_PRIME_TEST):
        # Pick a random base in the range [2, number - 2]
        random_number = random.randint(2, number - 2)

        x = modular_exponentiation(random_number, d, number)

        # If x is 1 or number - 1, proceed to the next iteration
        if x == 1 or x == number - 1:
            continue

        # Otherwise, repeatedly square x, up to s - 1 times (s is the number of times we divided the number to test - 1 by 2)
        for _ in range(s - 1):
            x = modular_exponentiation(x, 2, number)
            # If x is number - 1, the test passes
            if x == number - 1:
                break
            # If x is 1, the number is definitely composite
            if x == 1:
                return False
        # If we reached the end of the loop without finding x == number - 1, the number is definitely composite
        else:
            return False
    # If all iterations passed, the number is probably prime
    return True

def generate_modulus_prime_factors(key_size_bits: int) -> tuple[int, int, int]:
    """
    Generate two distinct prime numbers and their modulus (n = p * q).
    The prime factors will be generated randomly witthin the defined bounds

    Args:
        key_size_bits (int): Size of the key in bits.

    Returns:
        Tuple[int, int, int]: Tuple containing the prime factors p & q, and the modulus n.
    """
    global iterations

    # bounds for the prime factors
    upper_bound = (1 << key_size_bits//2) - 1
    lower_bound = 1 << (key_size_bits//2 - 4)

    # Generate first prime factor p
    # We pick a random candidate between the defined bounds, and check if it is prime.
    # Loop until we find a prime number within the bounds.
    while True:
        p = random.randint(lower_bound, upper_bound)
        iterations += 1
        if prime(p):
            break
    
    # Generate second prime factor q
    # We will do the same as for p, but we will ensure each prime factor is sufficiently distinct.
    while True:
        q = random.randint(lower_bound, upper_bound)
        iterations += 1
        if prime(q):
            # Ensure p and q are sufficiently distinct
            if key_size_bits//2 <= 32:
                if p != q:
                    break
            else:
                if abs(p - q) > ((key_size_bits//2) // 32):
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

def generate_public_key(n: int, euler_totient: int, use_fixed_e: bool = False) -> int:
    """
    Generate a random public key e coprime with euler_totient.
    Optionally, use the fixed value 2^16 + 1 for e (fast encryption).

    Args:
        n (int): Modulus.
        euler_totient (int): Euler's totient of the modulus.
        use_fixed_e (bool): If True, use 2^16 + 1 as the public key e.

    Returns:
        int: The public key e.
    """
    global iterations

    if use_fixed_e:
        # Use the standard fast public exponent
        e = 2**16 + 1
        iterations += 1
        # 65537 must be coprime with euler_totient
        if gcd(e, euler_totient) == 1:
            return e
        else:
            raise ValueError("2^16 + 1 is not coprime with Euler's totient.")
    
    # We pick a random candidate between 2 and n - 1, and loop until we find a number coprime with euler_totient.
    while True:
        e = random.randint(2, n - 1)
        iterations += 1
        if gcd(e, euler_totient) == 1:
            break

    return e

def generate_private_key(e: int, euler_totient: int) -> int:
    """
    Compute the private key d such that e * d ≡ 1 (mod phi(n)) using Extended Euclidean Algorithm.
    e must be coprime with euler_totient (not verified in this function).
    To know more about the Extended Euclidean Algorithm, see: https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide_étendu

    Args:
        e (int): Public key (must be coprime with euler_totient).
        euler_totient (int): Euler's totient of the modulus.

    Returns:
        int: The private key d.
    """
    global iterations

    # Initialize the first remainder (r) and second remainder (r1)
    r, r1 = e, euler_totient

    # Initialize the coefficients for Bézout's identity
    # We want to find integers u and v such that e * u + euler_totient * v = gcd(e, euler_totient) = 1
    # u is the modular inverse of e, so u is the private key d.
    u, v, u1, v1 = 1, 0, 0, 1
    iterations += 6


    while r1 != 0:
        # quotient of the division of r by r1
        q = r // r1

        # Update the remainders: r becomes r1, r1 becomes the remainder of previous r divided by r1
        r, r1 = r1, r - q * r1

        # Update the Bézout coefficients
        u, u1 = u1, u - q * u1
        v, v1 = v1, v - q * v1
        iterations += 6

    # If e was coprime with euler_totient, r should be 1 (gcd(e, euler_totient) = 1)

    # If u is negative, we add euler_totient to it to get the positive equivalent
    if u < 0:
        u += euler_totient
        iterations += 1

    # u is the private key d
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
        str: Encrypted message (ciphertext, string of characters from the alphabet).
    """
    global iterations

    # Determine block size: b < log(n) / log(len(alphabet_to_index))
    b = int(math.floor(math.log(n, len(alphabet_to_index))))
    iterations += 1

    # Pad the message with 'A' (numerical representation of 'A' is 0) until its length is a multiple of b
    if len(message) % b != 0:
        message += 'A' * (b - len(message) % b)

    converted_message = []
    # Convert each block of b characters to a numerical representation
    for i in range(0, len(message), b):
        val = 0
        # Convert each character in the block to its numerical representation
        for j in range(b):
            val += alphabet_to_index[message[i + j]] * (len(alphabet_to_index) ** (b - j - 1))
            iterations += 2
        converted_message.append(val)
    
    encrypted_message = ''
    # Encrypt each character (numerical representation) using modular exponentiation and the public key
    for val in converted_message:

        # If e is 65537, use the fast exponentiation method
        if e == 65537:
            iterations += 1
            val_pow = val
            # Square sixteen times (val^(2^16))
            for _ in range(16):
                val_pow = (val_pow * val_pow) % n
                iterations += 2

            # Multiply once more to get val^(2^16 + 1)
            c = (val_pow * val) % n
            iterations += 2

        # Standard encryption (works for any e): c = val^e mod n
        else:
            c = modular_exponentiation(val, e, n)
            iterations += 1

        # Convert the numerical representation of the encrypted message back to characters
        # We must use a block size of b + 1 because exponentiation increases the size of each numerical representation
        for j in range(b + 1):
            encrypted_message += index_to_alphabet[c // (len(index_to_alphabet) ** (b + 1 - j - 1))]
            c %= len(index_to_alphabet) ** (b + 1 - j - 1)
            iterations += 2

    # The encrypted message, which is a string of characters from the alphabet
    return encrypted_message

def decrypt(n: int, d: int, cipher: str, alphabet_to_index: dict[str, int], index_to_alphabet: dict[int, str]) -> str:
    """
    Decrypt an RSA encrypted message.
    The ciphertext is converted back to a numerical representation based on the provided alphabet mapping.
    The decryption is performed using the private key (n, d).
    The message is cut into blocks so that the numerical representation of the message is less than n.
    The block size is always the same as the one used in encryption incremented by 1. This is because the exponentiation
    increases the size of each numerical representation.

    Args:
        n (int): Modulus.
        d (int): Private key.
        cipher (str): Ciphertext to decrypt.
        alphabet_to_index (dict): Mapping from characters to indices.
        index_to_alphabet (dict): Mapping from indices to characters.

    Returns:
        str: Decrypted message (plaintext, string of characters from the alphabet).
    """
    global iterations

    # Determine block size: b < log(n) / log(len(alphabet_to_index)) + 1 for decryption
    b = int(math.floor(math.log(n, len(alphabet_to_index)))) + 1
    iterations += 1

    # If the ciphertext length is not a multiple of b, it is not valid
    if len(cipher) % b != 0:
        return ''
    
    converted_message = []
    # Convert each block of b characters to a numerical representation
    for i in range(0, len(cipher), b):
        val = 0
        # Convert each character in the block to its numerical representation
        for j in range(b):
            val += alphabet_to_index[cipher[i + j]] * (len(alphabet_to_index) ** (b - j - 1))
            iterations += 2
        converted_message.append(val)

    # Decrypt each character (numerical representation) using modular exponentiation and the private key
    decrypted_message = ''
    for val in converted_message:
        m = modular_exponentiation(val, d, n)
        iterations += 1

        # Convert the numerical representation of the decrypted message back to characters
        # We use the original block size b, for we are working with the original message
        for j in range(b - 1):
            decrypted_message += index_to_alphabet[m // (len(index_to_alphabet) ** (b - j - 2))]
            m %= len(index_to_alphabet) ** (b - j - 2)
            iterations += 2

    # The decrypted message, which is a string of characters from the alphabet
    return decrypted_message

def rsa(key_size_bits: int = 128, use_fixed_e: bool = False) -> tuple[int, int, int, int, int, int]:
    """
    Generate RSA keys: two prime factors (p, q), modulus (n), public key (e), and private key (d).

    Args:
        key_size_bits (int): Size of the key in bits.
        use_fixed_e (bool): If True, generate_public_key() will use the fixed value 2^16 + 1 for e (fast encryption).
        
    Returns:
        tuple[int, int, int, int, int, int]: p, q, n, e, d, and total basic operations performed.
    """
    global iterations
    iterations = 0
    p, q, n = generate_modulus_prime_factors(key_size_bits)
    euler_totient = compute_euler_totient(p, q)
    e = generate_public_key(n, euler_totient, use_fixed_e)
    d = generate_private_key(e, euler_totient)
    return p, q, n, e, d, iterations