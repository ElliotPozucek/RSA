from rsa import encrypt
from alphabet import alphabet_to_index_40, index_to_alphabet_40


def test_encrypt():
    """
    Hard-coded test for the encryption function with a known input and output.
    This test uses the RSA encryption algorithm with a specific modulus and exponent.
    It doesn't require the generation of keys or any randomness.
    
    It was used in a Test-Driven Development (TDD) approach.
    """
    n = 2047
    e = 179
    M = "ENVOYEZ 2500$."
    expected = "AVOA25ALMA2PALPAR0ADC"
    encrypted = encrypt(n, e, M, alphabet_to_index_40, index_to_alphabet_40)
    if encrypted == expected:
        print("Encryption test passed.\n")
    else:
        print("Encryption test failed.\n")