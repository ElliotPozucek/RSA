from rsa import decrypt
from alphabet import alphabet_to_index_40, index_to_alphabet_40

def test_decrypt():
    n = 2047
    d = 411
    C = "AVOA25ALMA2PALPAR0ADC"
    expected = "ENVOYEZ 2500$."
    decrypted = decrypt(n, d, C, alphabet_to_index_40, index_to_alphabet_40)
    if decrypted == expected:
        print("Decryption test passed.\n")
    else:
        print("Decryption test failed.\n")
