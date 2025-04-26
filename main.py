from test.test_modular_expo import test_modular_expo
from test.test_prime import test_prime
from test.test_generate_modulus import test_generate_modulus_prime_factors
from test.test_encrypt import test_encrypt
from test.test_decrypt import test_decrypt
from test.test_dynamic_encrypt import dynamic_test_encrypt
from rsa import rsa

if __name__ == "__main__":
    test_modular_expo()
    test_prime()
    test_generate_modulus_prime_factors()
    p, q, n, e, d = rsa()
    test_encrypt()
    test_decrypt()
    dynamic_test_encrypt()
