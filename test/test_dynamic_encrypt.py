from rsa import encrypt, rsa, decrypt
from alphabet import alphabet_to_index_40, index_to_alphabet_40
import time

def dynamic_test_encrypt(key_size_bits: int = 128, use_fixed_e: bool = False):
    """
    Dynamic test for the encryption and decryption functions.
    This test asks the user to input a message and then encrypts and decrypts it.
    It checks if the decrypted message matches the original message, and also warns the user
    if the message is empty or contains invalid characters.

    Args:
        key_size_bits (int): The size of the key in bits. Default is 128 bits.
        use_fixed_e (bool): If True, use a fixed public exponent e = 65537. Default is False.
    """

    print("\n" + "=" * 80)
    print(f"{'DYNAMIC ENCRYPTION/DECRYPTION TEST':^80}")
    print("=" * 80)

    while True:
        message = input("\nEnter a message using the 40-character alphabet (A-Z [space] . ? $ 0-9): ").strip().upper()
        if message:
            break
        print("Message cannot be empty. Please try again.")

    # Check if the message contains only valid characters
    valid_chars = set(alphabet_to_index_40.keys())
    for c in message:
        if c not in valid_chars:
            print(f"\n[FAILED] Invalid character '{c}' in message. Only use the 40-character alphabet.")
            print("=" * 80)
            print(f"{'End of Dynamic Test':^80}")
            print("=" * 80 + "\n")
            return
        
    print("\n[ Key Generation ]\n")
    if use_fixed_e:
        print("Using fixed public exponent e = 65537.")
    else:
        print("Using random public exponent e.")
    print(f"Key Size (bits) : {key_size_bits} bits\n")

    start_time = time.time()

    # Generate RSA keys
    p, q, n, e, d, iterations = rsa(key_size_bits, use_fixed_e)
    # Encrypt and decrypt the message

    generation_end_time = time.time()
    generation_elapsed_time = generation_end_time - start_time
    print(f"Key Generation Execution Time : {generation_elapsed_time:.6f} seconds")
    print(f"Number of basic operations (iterations) : {iterations}")

    print("\n[ Encryption/Decryption ]\n")

    encrypted = encrypt(n, e, message, alphabet_to_index_40, index_to_alphabet_40)
    decrypted = decrypt(n, d, encrypted, alphabet_to_index_40, index_to_alphabet_40)

    encrypt_decrypt_end_time = time.time()
    elapsed_time = encrypt_decrypt_end_time - generation_end_time
    
    # Clean the decrypted message to match the original length (remove padding)
    # NOTE : in a real-world scenario, the length of the original message should be stored in the encrypted message
    decrypted_clean = decrypted[:len(message)]

    print(f"Original message                     : {message}")
    print(f"Encrypted message                    : {encrypted}")
    print(f"Decrypted message                    : {decrypted_clean}")
    print(f"Encryption/Decryption Execution Time : {elapsed_time:.6f} seconds")
    print(f"Total execution time                 : {elapsed_time + generation_elapsed_time:.6f} seconds")

    if decrypted_clean == message:
        print(f"\n[PASSED] Dynamic encryption/decryption test passed. Messages match.\n")
    else:
        print(f"\n[FAILED] Dynamic encryption/decryption test failed. Messages do not match.\n")

    print("=" * 80)
    print(f"{'End of Dynamic Test':^80}")
    print("=" * 80 + "\n")