from rsa import generate_modulus_prime_factors, square_root_test

def test_generate_modulus_prime_factors():
    p, q, iter, n = generate_modulus_prime_factors()
    print("Testing prime factors generation...")
    print(f"p = {p}\nq = {q}\nn = {n}")
    diff = abs(p - q)
    print(f"Difference between q and p: {diff}")
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