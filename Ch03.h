//
// Created by Francisco Soares on 2019-02-07.
//

#ifndef CRACKING_THE_CODING_INTERVIEW_CH03_H
#define CRACKING_THE_CODING_INTERVIEW_CH03_H

#include "DataStructures.h"
#include <vector>
#include <string>
#include <climits>
#include <exception>

// 3.1 Three in One: Describe how you could use a single array to implement three stacks.
// Solution 1: Fixed Division
class FixedMultiStack {
    int _numberOfStacks = 3;
    int _stackCapacity;
    int *_values;
    int *_sizes;

    int indexOfTop(int stackNum) {
        int offset = stackNum * _stackCapacity;
        int size = _sizes[stackNum];
        return offset + size - 1;
    }
public:
    FixedMultiStack(int stackSize) : _stackCapacity(stackSize) {
        _values = new int[stackSize * _numberOfStacks]();
        _sizes = new int[_numberOfStacks]();
    }

    void push(int stackNum, int value) {
        if (isFull(stackNum)) throw std::runtime_error("Stack is full");
        _sizes[stackNum]++;
        _values[indexOfTop(stackNum)] = value;
    }

    int pop(int stackNum) {
        if (isEmpty(stackNum)) throw std::runtime_error("Stack is empty");

        int topIndex = indexOfTop(stackNum);
        int value = _values[topIndex];
        _values[topIndex] = 0;
        _sizes[stackNum]--;
        return value;
    }

    int peek(int stackNum) {
        if (isEmpty(stackNum)) throw std::runtime_error("Stack is empty");
        return _values[indexOfTop(stackNum)];
    }

    bool isEmpty(int stackNum) {
        return _sizes[stackNum] == 0;
    }

    bool isFull(int stackNum) {
        return _sizes[stackNum] == _stackCapacity;
    }
};

// 3.2 Stack Min: How would you design a stack which, in addition to push and pop, has a function min which returns the
// minimum element? Push, pop and min should all operate in O(1) time
// Solution 1: Keep track of min element in class as a property, after every push, compare value with minimum value before
// and change if new value is smaller
template <typename Value>
class MinStack: Stack<Value> {
    Value *_min = nullptr;
public:
    Value min() {
        if (_min == nullptr) return Value();
        return *_min;
    }

    void push(ListNode<Value> *node) {
        auto data = node->data;
        if (_min == nullptr) _min = &data;
        else {
            if (*_min > data)
                _min = &data;
        }
        Stack<Value>::push(node);
    }

    void push(Value data) {
        if (_min == nullptr) _min = &data;
        else {
            if (*_min > data)
                _min = &data;
        }
        Stack<Value>::push(data);
    }
};

// 3.3 Stack of Plates: Imagine a (literal) stack of plates. If the stack gets too high, it might topple. Therefore,
// in real life, we would likely start a new stack when the previous stack exceeds some threshold. Implement a data
// structure SetOfStack that mimics this. SetOfStacks should be composed of several stacks and should create a new stack
// once the previous one exceeds capacity. SetOfStacks.push() and SetOfStacks.pop() should behave identically to a single
// stack (that is, pop() should return the same values as it would if there were just a single stack).
// FOLLOW-UP: Implement a function popAt(int index) which performs a pop operation on a specific sub-stack
// Solution 1:
template <class Value>
class SetOfStacks {
    std::vector< Stack<Value> *> _stacks;
    int _threshold;

public:
    SetOfStacks() : _threshold(4) {
        _stacks.reserve(10);
    }

    bool isEmpty() {
        return _stacks.size() == 0;
    }

    void push(Value value) {
        if (_stacks.size() == 0) {
            auto stack = new Stack<Value>();
            _stacks.push_back(stack);
        }

        Stack<Value> *last = _stacks.back();
        if (last->length() == _threshold) {
            auto stack = new Stack<Value>();
            _stacks.push_back(stack);
            last = _stacks.back();
        }

        last->push(value);
    }

    ListNode<Value> *pop() {
        if (_stacks.size() == 0) return new ListNode<Value>(Value());
        Stack<Value> *last = _stacks.back();
        auto value = last->pop();
        if (last->length() == 0)
            _stacks.pop_back();
        return value;
    }

    Value peek() {
        if (_stacks.size() == 0) return Value();
        Stack<Value> *last = _stacks.back();
        return last->peek();
    }

    ListNode<Value> *popAtIndex(int index) {
        if(index >= _stacks.size()) return new ListNode<Value>(Value());
        Stack<Value> *stack = _stacks[index];
        auto value = stack->pop();
        if (stack->isEmpty())
            _stacks.erase(_stacks.begin() + index);
        return value;
    }
};

// 3.4 Queue via Stacks: Implement a MyQueue class which implements a queue using two stacks
// Solution 1:
template <class Value>
class MyQueue {
    Stack<Value> *_stack;
    Stack<Value> *_tmpStack;
public:
    MyQueue() : _stack(new Stack<Value>()), _tmpStack(new Stack<Value>()) { }

    void add(Value item) {
        _stack->push(item);
    }

    ListNode<Value> *remove() {
        while (!_stack->isEmpty()) {
            _tmpStack->push(_stack->pop());
        }

        if (!_tmpStack->isEmpty()) {
            auto *node = _tmpStack->pop();
            while (!_tmpStack->isEmpty()) {
                _stack->push(_tmpStack->pop());
            }
            return node;
        }

        return new ListNode<Value>(Value());
    }

    Value peek() {
        while (!_stack->isEmpty()) {
            _tmpStack->push(_stack->pop());
        }

        if (!_tmpStack->isEmpty()) {
            auto value = _tmpStack->peek();
            while (!_tmpStack->isEmpty()) {
                _stack->push(_tmpStack->pop());
            }
            return value;
        }
        return Value();
    }

    bool isEmpty() {
        return _stack->isEmpty();
    }
};

// 3.5 Sort Stack: Write a program to sort a stack such that the smallest items are on the top. You can use an additional
// temporary stack, but you may not copy the elements into any other data structure (such as an array). The stack supports
// the following operations: push, pop, peek, and isEmpty.
// Solution 1: keep index of temporary stack, get biggest number in stack and add in the temporary stack, repeat until stack is empty, pop temporary into stak
void sortStack(Stack<int> *stack) {
    auto *tmp = new Stack<int>();
    while (!stack->isEmpty()) {
        int value = stack->pop()->data;
        while (!tmp->isEmpty() && tmp->peek() > value) {
            stack->push(tmp->pop());
        }
        tmp->push(value);
    }

    while (!tmp->isEmpty()) {
        stack->push(tmp->pop());
    }
}

// 3.6 Animal Shelter: An animal shelter, which holds only dogs and cats, operates on a strictly "first in, first out" basis.
// People must adopt either the "oldest" (based on arrival time) of all animals at the shelter, or they can select whether
// they would prefer a dog or a cat (and will receive the oldest animal of that type). They cannot select which specific
// animal they would like. Create the data structures to maintain this system and implement operations such as enqueue,
// dequeuAny, dequeueDog, and dequeueCat. You may use the built-in LinkedList data structure
class Animal {
    int order;
public:
    std::string name;
    Animal(const std::string &n) : name(n) { }
    void setOrder(int ord) { order = ord; }
    int getOrder() { return order; }

    bool isOlderThan(Animal *a) {
        return this->order < a->getOrder();
    }

    virtual Animal * clone() const {
        return new Animal(*this);
    }
};

class Dog: public Animal {
public:
    Animal * clone() const override {
        return new Dog(*this);
    }
};

class Cat: public Animal {
public:
    Animal * clone() const override {
        return new Cat(*this);
    }
};

class AnimalShelter {
    int order = 0;
public:
    Queue<Dog *> *dogs;
    Queue<Cat *> *cats;

    AnimalShelter() : dogs(new Queue<Dog *>()), cats(new Queue<Cat *>()) { }

    void enqueue(Animal *a) {
        a->setOrder(order);
        order++;

        if (auto *cat = dynamic_cast<Cat *>(a)) {
            cats->enqueue(cat);
        } else if (auto *dog = dynamic_cast<Dog *>(a)) {
            dogs->enqueue(dog);
        }
    }

    Animal *dequeueAny() {
        if (dogs->isEmpty()) return dequeueCats()->clone();
        else if (cats->isEmpty()) return dequeueDogs()->clone();

        auto *dog = dogs->peek();
        auto *cat = cats->peek();
        if (dog->isOlderThan(cat)) {
            return dequeueDogs()->clone();
        } else {
            return dequeueCats()->clone();
        }
    }

    Cat *dequeueCats() {
        auto *cat = cats->dequeue();
        return cat == nullptr ? nullptr : cat->data;
    }

    Dog *dequeueDogs() {
        auto *dog = dogs->dequeue();
        return dog == nullptr ? nullptr : dog->data;
    }
};

#endif //CRACKING_THE_CODING_INTERVIEW_CH03_H
