all: rsa.exe

TEST_FOLDER = test

rsa.exe : rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o main.o
	g++ rsa.o $(TEST_FOLDER)/test_prime.o $(TEST_FOLDER)/test_prime_factors.o main.o -o rsa.exe

rsa.o : rsa.cpp rsa.h
	g++ -c rsa.cpp

$(TEST_FOLDER)/test_prime.o : $(TEST_FOLDER)/test_prime.cpp
	g++ -c $(TEST_FOLDER)/test_prime.cpp -o $(TEST_FOLDER)/test_prime.o

$(TEST_FOLDER)/test_prime_factors.o : $(TEST_FOLDER)/test_prime_factors.cpp $(TEST_FOLDER)/test_prime_factors.h
	g++ -c $(TEST_FOLDER)/test_prime_factors.cpp -o $(TEST_FOLDER)/test_prime_factors.o

main.o : main.cpp
	g++ -c main.cpp