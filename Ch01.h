//
// Created by Francisco Soares on 2019-02-03.
//

#ifndef CRACKING_THE_CODING_INTERVIEW_CH01_H
#define CRACKING_THE_CODING_INTERVIEW_CH01_H

#include <iostream>
#include <unordered_set>
#include <string>
#include <cstring>

// TODO(fssn): Implement generic Hash Table

// TODO(fssn): Implement generic ArrayList

// TODO(fssn): Implement StringBuilder

// 1.1 Is Unique: Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?

// Solution 1: Using Set
bool isUnique(const std::string &string) {
    auto length = string.length();
    auto str = string.c_str();
    std::unordered_set<char> set(str, str+length);
    return length == set.size();
}

// Solution 2: Without using Set
bool isUnique2(const std::string &string) {
    if (string.length() > 128) return false;
    int letters[128] = { 0 };

    for (auto c : string) {
        if (letters[c])
            return false;
        letters[c]++;
    }

    return true;
}

// 1.2 Check Permutation: Given two strings, write a method to decide if one is a permutation of the other
// Solution 1:
bool checkPermutation(const std::string &str1, const std::string &str2) {
    if (str1.length() != str2.length()) return false;
    int letters[128] = { 0 };

    for (auto c : str1) {
        letters[c]++;
    }

    for (auto c: str2) {
        letters[c]--;
        if (letters[c] < 0)
            return false;
    }

    return true;
}

// 1.3 URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the string has sufficient
// space at the end to hold the additional characters, and that you are given the "true" length of the string
void urlify(std::string &str, int trueLength) {
    int spaces = 0;
    for (int i = 0; i < trueLength; i++) {
        if (str[i] == ' ') spaces++;
    }

    int index = trueLength + spaces * 2;
    if (trueLength < str.length()) str[trueLength] = 0;
    for (int i = trueLength - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            str[index - 1] = '0';
            str[index - 2] = '2';
            str[index - 3] = '%';
            index -= 3;
        } else {
            str[index - 1] = str[i];
            index--;
        }
    }
}

// 1.4 Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palindrome.
// A palindrome is a word of phrase that is the same forwards and backwards. A permutation is a rearrangement of letters.
// The palindrome does not need to be limited to just dictionary words.
// Solution 1: Without bit vector
bool palindromePermutation(const std::string &str) {
    int letters[128] = { 0 };
    int size = 0;
    int count = 0;
    for (auto c : str) {
        int index = c;
        if (index == ' ') continue;
        if (index >= 'A' && index <= 'Z') index += 32;
        if (letters[index]) {
            count--;
            letters[index] = 0;
        } else {
            letters[index] = 1;
            count++;
        }
        size++;
    }

    if (size % 2 == 0) { // String is even
        return count == 0;
    } else { // String is odd
        return count == 1;
    };
}

// Solution 2: Using bit vector
char easytolower(char in) {
    if(in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

int getCharNumber(char c) {
    int indexOfA = 'a';
    int indexOfZ = 'z';
    int value = easytolower(c);
    if (indexOfA <= value && value <= indexOfZ) return value - indexOfA;
    return -1;
}

int toggle(int bitVector, int index) {
    if (index < 0) return bitVector;

    int mask = 1 << index;
    if ((bitVector & mask) == 0) {
        bitVector |= mask;
    } else {
        bitVector &= ~mask;
    }

    return bitVector;
}

int createBitVector(const std::string &str) {
    int bitVector = 0;
    for (auto c : str) {
        int x = getCharNumber(c);
        bitVector = toggle(bitVector, x);
    }
    return bitVector;
}

bool checkOneBitSet(int bitVector) {
    return (bitVector & (bitVector - 1)) == 0;
}

bool palindromePermutation2(const std::string &str) {
    int bitVector = createBitVector(str);
    return checkOneBitSet(bitVector) || bitVector == 0;
}

// 1.5 One Away: There are three types of edits that can be performed on strings: insert a character, remove a character,
// or replace a character. Given two strings, write a function to check if they are one edit (or zero edits) away.
// Solution 1:
bool oneInsert(const std::string &str1, const std::string &str2) {
    int index1 = 0;
    int index2 = 0;

    while (index1 < str1.size() && index2 < str2.size()) {
        if (str1[index1] != str2[index2]) {
            if (index1 != index2)
                return false;
            index2++;
        } else {
            index1++;
            index2++;
        }
    }

    return true;
}

bool oneAway(const std::string &str1, const std::string &str2) {
    if (str1.size() == str2.size()) {
        bool diff = false;
        for (int i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                if (diff)
                    return false;
                diff = true;
            }
        }
        return diff;
    } else if (str1.size() + 1 == str2.size()) {
        return oneInsert(str1, str2);
    } else if (str1.size() - 1 == str2.size()) {
        return oneInsert(str2, str1);
    }

    return false;
}

// 1.6 String Compression: Implement a method to perform basic string compression using the counts of repeated characters.
// For example, the string aabcccccaaa would become a2b1c5a3. If the "compressed" string would not become smaller than
// the original string, your method should return the original string. You can assume the string has only uppercase and
// lowercase letters (a-z)
// Solution 1: Using std::string
std::string stringCompression(const std::string &str) {
    std::string newString;
    char currentChar = str[0];
    int currentCharCounter = 0;
    for (auto c : str) {
        if (c == currentChar) {
            currentCharCounter++;
        } else {
            newString += currentChar;
            newString += std::to_string(currentCharCounter);
            currentChar = c;
            currentCharCounter = 1;
        }
    }

    newString += currentChar;
    newString += std::to_string(currentCharCounter);

    return newString.size() < str.size() ? newString : str;
}

// 1.7 Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, write a
// method to rotate the image by 90 degrees. Can you do this in place?
// Solution 1:
bool rotateMatrix(int **matrix, int numRows, int numCols) {
    if (numRows == 0 || numCols == 0 || numCols != numRows) return false;
    for (int layer = 0; layer < numRows / 2; layer++) {
        int first = layer;
        int last = numRows - 1 - layer;
        for (int i = first; i < last; i++) {
            int offset = i - first;
            int top = matrix[first][i];

            matrix[first][i] = matrix[last - offset][first];

            matrix[last - offset][first] = matrix[last][last - offset];

            matrix[last][last - offset] = matrix[i][last];

            matrix[i][last] = top;
        }
    }

    return true;
}

// 1.8 Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column are set to 0.
// Solution 1:
void zeroMatrix(int **matrix, int numCols, int numRows) {
    if (numCols * numRows == 0) return;
    int zeroRows[numRows];
    int zeroCols[numCols];
    int counter = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (!matrix[i][j]) {
                zeroRows[counter] = i;
                zeroCols[counter] = j;
                counter++;
            }
        }
    }

    for (int i = 0; i < counter; i++) {
        for (int j = 0; j < numRows; j++) {
            matrix[j][zeroCols[i]] = 0;
        }

        for (int j = 0; j < numCols; j++) {
            matrix[zeroRows[i]][j] = 0;
        }
    }
}

// 1.9 String Rotation: Assume you have a method isSubstring which checks if one word is a substring of another.
// Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring
// Solution 1:
bool stringRotation(const std::string &str1, const std::string &str2) {
    if (str1.size() != str2.size() || str1.empty()) return false;
    auto newStr = str1 + str1;
    auto pos = newStr.find(str2);
    return pos != std::string::npos;
}

#endif //CRACKING_THE_CODING_INTERVIEW_CH01_H
