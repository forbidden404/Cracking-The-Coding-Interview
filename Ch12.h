//
// Created by Francisco Soares on 2019-02-07.
//

#ifndef CRACKING_THE_CODING_INTERVIEW_CH12_H
#define CRACKING_THE_CODING_INTERVIEW_CH12_H

#include <iostream>

#define NAME_SIZE 50 // Defines a macro

class Person {
    int id; // all members are private by default
    char name[NAME_SIZE];

public:
    Person(int a) : id(a) { }
    ~Person() = default;

    virtual void aboutMe() {
        std::cout << "I am a person.";
    }
};

class Student: Person {
public:
    void aboutMe() {
        std::cout << "I am a student.";
    }
};

#endif //CRACKING_THE_CODING_INTERVIEW_CH12_H
