from rsa import modular_exponentiation

def test_modular_expo():
    a = modular_exponentiation(12365, 165, 56625)
    if a == 51125:
        print("Modular exponentiation test passed.\n")
    else:
        print("Modular exponentiation test failed.\n")
