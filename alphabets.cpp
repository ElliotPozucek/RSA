#include <iostream>
#include <unordered_map>

// Alphabet dictionnary used for encryption/ decryption. 40 characters.
const std::unordered_map<char, int> alphabet_to_index_40 = {
    {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5},
    {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11},
    {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17},
    {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23},
    {'Y', 24}, {'Z', 25}, {'_', 26}, {'.', 27}, {'?', 28}, {'$', 29},
    {'0', 30}, {'1', 31}, {'2', 32}, {'3', 33}, {'4', 34}, {'5', 35},
    {'6', 36}, {'7', 37}, {'8', 38}, {'9', 39}
};

// Index dictionnary used for encryption / decryption. 40 characters.
const std::unordered_map<int, char> index_to_alphabet_40 = {
    {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'},
    {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'}, {10, 'K'}, {11, 'L'},
    {12, 'M'}, {13, 'N'}, {14, 'O'}, {15, 'P'}, {16, 'Q'}, {17, 'R'},
    {18, 'S'}, {19, 'T'}, {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'},
    {24, 'Y'}, {25, 'Z'}, {26, '_'}, {27, '.'}, {28, '?'}, {29, '$'},
    {30, '0'}, {31, '1'}, {32, '2'}, {33, '3'}, {34, '4'}, {35, '5'},
    {36, '6'}, {37, '7'}, {38, '8'}, {39, '9'}
};

// Alphabet dictionnary used for encryption/ decryption. Hexadecimal characters.
const std::unordered_map<char, int> alphabet_to_index_hexa = {
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
    {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11},
    {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
};

// Index dictionnary used for encryption / decryption. Hexadecimal characters.
const std::unordered_map<int, char> index_to_alphabet_hexa = {
    {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'},
    {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'a'}, {11, 'b'},
    {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'}
};