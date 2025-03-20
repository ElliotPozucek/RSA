all: rsa.exe

CXX = g++

TEST_FOLDER = test

rsa.exe : alphabets.o rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o $(TEST_FOLDER)/test_encrypt.o $(TEST_FOLDER)/test_decrypt.o main.o
	$(CXX) alphabets.o rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o $(TEST_FOLDER)/test_encrypt.o $(TEST_FOLDER)/test_decrypt.o main.o -o rsa.exe

rsa.o : rsa.cpp rsa.h
	$(CXX) -c rsa.cpp

alphabets.o : alphabets.cpp
	$(CXX) -c alphabets.cpp

$(TEST_FOLDER)/test_prime.o : $(TEST_FOLDER)/test_prime.cpp
	$(CXX) -c $(TEST_FOLDER)/test_prime.cpp -o $(TEST_FOLDER)/test_prime.o

$(TEST_FOLDER)/test_prime_factors.o : $(TEST_FOLDER)/test_prime_factors.cpp $(TEST_FOLDER)/test_prime_factors.h
	$(CXX) -c $(TEST_FOLDER)/test_prime_factors.cpp -o $(TEST_FOLDER)/test_prime_factors.o

$(TEST_FOLDER)/test_encrypt.o : $(TEST_FOLDER)/test_encrypt.cpp $(TEST_FOLDER)/test_encrypt.h
	$(CXX) -c $(TEST_FOLDER)/test_encrypt.cpp -o $(TEST_FOLDER)/test_encrypt.o

$(TEST_FOLDER)/test_decrypt.o : $(TEST_FOLDER)/test_decrypt.cpp $(TEST_FOLDER)/test_decrypt.h
	$(CXX) -c $(TEST_FOLDER)/test_decrypt.cpp -o $(TEST_FOLDER)/test_decrypt.o

main.o : main.cpp
	$(CXX) -c main.cpp

clean:
	rm -f *.o $(TEST_FOLDER)/*.o rsa.exe