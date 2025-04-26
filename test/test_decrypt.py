from rsa import decrypt
from alphabet import alphabet_to_index_40, index_to_alphabet_40

def test_decrypt():
    """
    Hard-coded test for the decryption function with a known input and output.
    This test uses the RSA decryption algorithm with a specific modulus and exponent.
    It doesn't require the generation of keys or any randomness.
    
    It was used in a Test-Driven Development (TDD) approach.
    """
    n = 2047
    d = 411
    C = "AVOA25ALMA2PALPAR0ADC"
    expected = "ENVOYEZ 2500$."
    decrypted = decrypt(n, d, C, alphabet_to_index_40, index_to_alphabet_40)
    if decrypted == expected:
        print("Decryption test passed.\n")
    else:
        print("Decryption test failed.\n")
