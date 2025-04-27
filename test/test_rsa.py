from rsa import rsa
import time

def test_rsa(key_size_bits: int = 128, use_fixed_e: bool = False):
    """
    Test the RSA key generation process.
    Will print all the generated values, the execution time, and the number of basic operations (iterations).

    Args:
        key_size_bits (int): The size of the key in bits. Default is 128 bits.
        use_fixed_e (bool): If True, use a fixed public exponent e = 65537. Default is False.
    """

    print("\n" + "=" * 80)
    print(f"{'RSA KEY GENERATION TEST':^80}")
    print("=" * 80)

    print(f"Key Size (bits)                         : {key_size_bits} bits\n")

    start_time = time.time()

    p, q, n, e, d, total_iterations = rsa(key_size_bits, use_fixed_e)

    end_time = time.time()
    elapsed_time = end_time - start_time

    print(f"Prime p                                 : {p}\n")
    print(f"Prime q                                 : {q}\n")
    print(f"Modulus n (p * q)                       : {n}\n")
    print(f"Public Exponent e                       : {e}\n")
    print(f"Private Exponent d                      : {d}\n")

    print(f"Number of basic operations (iterations) : {total_iterations}")
    print(f"Key Generation Execution Time           : {elapsed_time:.6f} seconds")

    print("\n" + "=" * 80)
    print(f"{'End of RSA Key Generation Test':^80}")
    print("=" * 80 + "\n")
