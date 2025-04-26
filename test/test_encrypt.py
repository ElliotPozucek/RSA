from rsa import encrypt, rsa, decrypt
from alphabet import alphabet_to_index_40, index_to_alphabet_40

def test_encrypt():
    n = 2047
    e = 179
    M = "ENVOYEZ 2500$."
    expected = "AVOA25ALMA2PALPAR0ADC"
    encrypted = encrypt(n, e, M, alphabet_to_index_40, index_to_alphabet_40)
    if encrypted == expected:
        print("Encryption test passed.\n")
    else:
        print("Encryption test failed.\n")

def dynamic_test_encrypt():
    message = input("Enter a message using the 40-char alphabet (A-Z [space] . ? $ 0-9): ").strip().upper()
    valid_chars = set(alphabet_to_index_40.keys())
    if any(c not in valid_chars for c in message):
        print("Invalid characters in message. Only use the 40-character alphabet.")
        return

    p, q, n, e, d = rsa()
    encrypted = encrypt(n, e, message, alphabet_to_index_40, index_to_alphabet_40)
    decrypted = decrypt(n, d, encrypted, alphabet_to_index_40, index_to_alphabet_40)
    
    decrypted_clean = decrypted[:len(message)]  # Take only the original message length

    print(f"Encrypted message: {encrypted}")
    print(f"Decrypted message: {decrypted_clean}")

    if decrypted_clean == message:
        print("Dynamic encryption/decryption test passed.\n")
    else:
        print("Dynamic encryption/decryption test failed.\n")