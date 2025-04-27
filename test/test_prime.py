from rsa import prime, square_root_test

def test_prime():
    """
    Test the prime() method.
    This test checks if the prime() method correctly identifies prime numbers.
    prime() is a probabilistic test, and square_root_test() is a deterministic test.
    
    It was used in a Test-Driven Development (TDD) approach.
    """
    test_numbers = [2, 6113, 505639, 127123, 865121, 11, 1, 2000629, 4200007793, 1000002161, 29]

    print("\n" + "=" * 80)
    print(f"{'PRIME VERIFICATION TEST':^80}")
    print("=" * 80)

    print("\n[ Testing Prime Numbers ]\n")
    for number in test_numbers:
        result = prime(number)
        ground_truth = square_root_test(number)

        if result and ground_truth:
            status = "PASSED"
            message = f"Number {number:<20} is prime and correctly identified."
        else:
            status = "FAILED"
            message = f"Number {number:<20} is NOT prime but should be prime."

        print(f"[{status:^7}] {message}")

    print("\n" + "=" * 80)
    print(f"{'End of Prime Test':^80}")
    print("=" * 80 + "\n")

