from rsa import generate_modulus_prime_factors, square_root_test, prime

def test_generate_modulus_prime_factors(key_size_bits: int = 128, miller_rabin = True):
    """
    Test the generation of the modulus prime factors.
    This test checks if the generated prime factors p and q are indeed prime,
    if they are sufficiently far apart, and if the modulus n is correctly calculated.

    It was used in a Test-Driven Development (TDD) approach.

    Args:
        key_size_bits (int): The size of the key in bits. Default is 128 bits.
        miller_rabin: If True, use Miller-Rabin primality test, otherwise use simple square root test.
        Note that the square root test is 100% accurate (as opposed to Miller-Rabin which is probabilistic), but astronomically slow for large numbers.
    """

    print("\n" + "=" * 80)
    print(f"{'MODULUS PRIME FACTORS GENERATION TEST':^80}")
    print("=" * 80)

    p, q, n = generate_modulus_prime_factors(key_size_bits)

    print(f"Prime p: ({key_size_bits//2} bits)\n{p}\n")
    print(f"Prime q: ({key_size_bits//2} bits)\n{q}\n")
    
    print(f"Modulus n ({key_size_bits} bits)\n{n}\n")

    diff = abs(p - q)
    
    if miller_rabin:
        print("Using Miller-Rabin primality test...")
        is_p_prime = prime(p)
        is_q_prime = prime(q)
    else:
        print("Using Square Root primality test (slow but deterministic)...")
        is_p_prime = square_root_test(p)
        is_q_prime = square_root_test(q)
    
    if not is_p_prime and not is_q_prime:
        print(f"[FAILED] Both p and q are not prime.\n")
        return
    if not is_p_prime:
        print(f"[FAILED] Prime p is not prime.\n")
        return
    if not is_q_prime:
        print(f"[FAILED] Prime q is not prime.\n")
        return
    print(f"[PASSED] Both primes p and q are prime.\n")

    if (key_size_bits // 2) <= 32:
        if p == q:
            print(f"[FAILED] Primes p and q are equal, which is invalid.\n")
            return
    else:
        if diff <= ((key_size_bits // 2) // 32):
            print(f"[FAILED] Primes p and q are too close.\n")
            return
    print(f"[PASSED] Primes p and q are appropriately distant.\n")

    print("=" * 80)
    print(f"{'End of Prime Factors Test':^80}")
    print("=" * 80 + "\n")