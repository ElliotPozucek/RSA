from test.test_modular_expo import test_modular_expo
from test.test_prime import test_prime
from test.test_generate_modulus import test_generate_modulus_prime_factors
from test.test_encrypt import test_encrypt
from test.test_decrypt import test_decrypt
from test.test_dynamic_encrypt import dynamic_test_encrypt
from test.test_rsa import test_rsa
from rsa import rsa

def main():
    print("\n" + "=" * 80)
    print(f"{'RSA PROJECT TEST SUITE':^80}")
    print("=" * 80)

    try:
        key_size_bits = int(input("\nEnter the desired RSA key size (in bits, e.g., 256, 512, 1024): "))
        if key_size_bits < 16 or key_size_bits % 2 != 0:
            print("Key size must be an even number >= 16. Defaulting to 128 bits.")
            key_size_bits = 128
    except ValueError:
        print("Invalid input. Defaulting to 128 bits.")
        key_size_bits = 128

    # Ask user if they want to use fixed e = 65537
    use_fixed_e_input = input("Use fixed public exponent e = 65537? (y/n) [default: y]: ").strip().lower()
    use_fixed_e = (use_fixed_e_input != 'n')

    print("\n" + "=" * 80)
    print(f"Starting RSA tests with {key_size_bits}-bit key ({key_size_bits//2}-bit prime factors)...")
    print("=" * 80)

    # Test used for TDD, not interesting for the user with current implementation
    # test_modular_expo()
    # test_encrypt()
    # test_decrypt()

    if input("Run prime number tests? (y/n) [default: n]: ").strip().lower() == 'y':
        test_prime()

    if input("Run modulus generation tests? (y/n) [default: n]: ").strip().lower() == 'y':
        test_generate_modulus_prime_factors(key_size_bits)

    if input("Run dynamic encryption tests? (y/n) [default: n]: ").strip().lower() == 'y':
        dynamic_test_encrypt(key_size_bits, use_fixed_e)

    if input("Run RSA keys generation test ? (y/n) [default: y]: ").strip().lower() != 'n':
        test_rsa(key_size_bits, use_fixed_e)

if __name__ == "__main__":
    main()