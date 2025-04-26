from rsa import prime, square_root_test

def test_prime():
    """
    Test the prime() method.
    This test checks if the prime() method correctly identifies prime numbers.
    prime() is a probabilistic test, and square_root_test() is a deterministic test.
    
    It was used in a Test-Driven Development (TDD) approach.
    """
    test_numbers = [2, 6113, 505639, 127123, 865121, 11, 1, 2000629, 4200007793, 1000002161, 29]
    print("Testing prime number verification...")
    for number in test_numbers:
        print(f"Testing number: {number}", end='')
        if prime(number) and square_root_test(number):
            print(" is prime and should be prime.")
        else:
            print(" is not prime and should be prime.")
