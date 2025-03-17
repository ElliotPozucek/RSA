all: rsa.exe

CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lssl -lcrypto

hash_SHA-256.exe: alphabets.o hash_SHA-256.o rsa.o
	$(CXX) alphabets.o hash_SHA-256.o rsa.o -o hash_SHA-256.exe $(LDFLAGS)

hash_SHA-256.o: hash_SHA-256.cpp rsa.h
	$(CXX) $(CXXFLAGS) -c hash_SHA-256.cpp

TEST_FOLDER = test

rsa.exe : alphabets.o rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o $(TEST_FOLDER)/test_encrypt.o $(TEST_FOLDER)/test_decrypt.o main.o
	g++ alphabets.o rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o $(TEST_FOLDER)/test_encrypt.o $(TEST_FOLDER)/test_decrypt.o main.o -o rsa.exe

rsa.o : rsa.cpp rsa.h
	g++ -c rsa.cpp

alphabets.o : alphabets.cpp
	g++ -c alphabets.cpp

$(TEST_FOLDER)/test_prime.o : $(TEST_FOLDER)/test_prime.cpp
	g++ -c $(TEST_FOLDER)/test_prime.cpp -o $(TEST_FOLDER)/test_prime.o

$(TEST_FOLDER)/test_prime_factors.o : $(TEST_FOLDER)/test_prime_factors.cpp $(TEST_FOLDER)/test_prime_factors.h
	g++ -c $(TEST_FOLDER)/test_prime_factors.cpp -o $(TEST_FOLDER)/test_prime_factors.o

$(TEST_FOLDER)/test_encrypt.o : $(TEST_FOLDER)/test_encrypt.cpp $(TEST_FOLDER)/test_encrypt.h
	g++ -c $(TEST_FOLDER)/test_encrypt.cpp -o $(TEST_FOLDER)/test_encrypt.o

$(TEST_FOLDER)/test_decrypt.o : $(TEST_FOLDER)/test_decrypt.cpp $(TEST_FOLDER)/test_decrypt.h
	g++ -c $(TEST_FOLDER)/test_decrypt.cpp -o $(TEST_FOLDER)/test_decrypt.o

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o $(TEST_FOLDER)/*.o