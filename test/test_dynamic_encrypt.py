from rsa import encrypt, rsa, decrypt
from alphabet import alphabet_to_index_40, index_to_alphabet_40

def dynamic_test_encrypt():
    """
    Dynamic test for the encryption and decryption functions.
    This test asks the user to input a message and then encrypts and decrypts it.
    It checks if the decrypted message matches the original message, and also warns the user
    if the message is empty or contains invalid characters.
    """
    while True:
        message = input("Enter a message using the 40-character alphabet (A-Z [space] . ? $ 0-9): ").strip().upper()
        if message:
            break
        print("Message cannot be empty. Please try again.")

    # Check if the message contains only valid characters
    valid_chars = set(alphabet_to_index_40.keys())
    for c in message:
        if c not in valid_chars:
            print(f"Invalid character '{c}' in message. Only use the 40-character alphabet.")
            return

    # Encrypt and decrypt the message
    p, q, n, e, d = rsa()
    encrypted = encrypt(n, e, message, alphabet_to_index_40, index_to_alphabet_40)
    decrypted = decrypt(n, d, encrypted, alphabet_to_index_40, index_to_alphabet_40)
    
    # Clean the decrypted message to match the original length (remove padding)
    # NOTE : in a real-world scenario, the length of the original message should be stored in the encrypted message
    decrypted_clean = decrypted[:len(message)]

    print(f"Encrypted message: {encrypted}")
    print(f"Decrypted message: {decrypted_clean}")

    if decrypted_clean == message:
        print("Dynamic encryption/decryption test passed.\n")
    else:
        print("Dynamic encryption/decryption test failed.\n")