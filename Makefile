all: rsa.exe

TEST_FOLDER = test

rsa.exe : rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o $(TEST_FOLDER)/test_encrypt.o $(TEST_FOLDER)/test_decrypt.o main.o
	g++ rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o $(TEST_FOLDER)/test_encrypt.o $(TEST_FOLDER)/test_decrypt.o main.o -o rsa.exe

rsa.o : rsa.cpp rsa.h
	g++ -c rsa.cpp

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