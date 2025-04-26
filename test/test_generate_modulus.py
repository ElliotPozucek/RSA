from rsa import generate_modulus_prime_factors, square_root_test, prime

def test_generate_modulus_prime_factors(miller_rabin = True):
    """
    Test the generation of the modulus prime factors.
    This test checks if the generated prime factors p and q are indeed prime,
    if they are sufficiently far apart, and if the modulus n is correctly calculated.
    
    It was used in a Test-Driven Development (TDD) approach.

    :param miller_rabin: If True, use Miller-Rabin primality test, otherwise use simple square root test.
    Note that the square root test is 100% accurate (as opposed to Miller-Rabin which is probabilistic), but astronomically slow for large numbers.
    """
    p, q, iter, n = generate_modulus_prime_factors()
    print("Testing prime factors generation...")
    print(f"p = {p}\nq = {q}\nn = {n}")
    diff = abs(p - q)
    print(f"Difference between q and p: {diff}")
    
    if miller_rabin:
        is_q_prime = prime(q)
        is_p_prime = prime(p)
    else:
        is_q_prime = square_root_test(q)
        is_p_prime = square_root_test(p)
    
    if not is_p_prime and not is_q_prime:
        print("p and q are not prime")
    if not is_p_prime:
        print("p is not prime")
    if not is_q_prime:
        print("q is not prime")
    if diff < (1 << (64 // 2)):
        print("p and q are too close")
    if is_p_prime and is_q_prime and diff > (1 << (64 // 2)):
        print("p and q are appropriate prime factors.")