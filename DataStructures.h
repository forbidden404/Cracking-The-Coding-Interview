//
// Created by Francisco Soares on 2019-02-07.
//

#ifndef CRACKING_THE_CODING_INTERVIEW_DATASTRUCTURES_H
#define CRACKING_THE_CODING_INTERVIEW_DATASTRUCTURES_H

#include <tuple>
#include <vector>
#include <functional>
#include <iostream>

template <typename Value>
class ListNode {
public:
    ListNode<Value> *prev;
    ListNode<Value> *next;
    Value data;

    explicit ListNode<Value>(Value d) : data(d) { }
};

template <typename Value>
class SinglyLinkedList {
public:
    ListNode<Value> *head;
    ListNode<Value> *tail;
    size_t length;

    SinglyLinkedList<Value>() : head(nullptr), tail(nullptr), length(0) { }
    ~SinglyLinkedList() {
        auto *cur = head;
        while (cur != nullptr) {
            auto *next = cur->next;
            delete cur;
            cur = cur->next;
        }
    }

    void print() {
        if (length != 0) {
            ListNode<Value> *cur = head;
            while(cur != nullptr) {
                std::cout << cur->data << " ";
                cur = cur->next;
            }
            std::cout << std::endl;
        }
    }

    void insert(Value data, ListNode<Value> *after) {
        auto *node = new ListNode<Value>(data);
        insert(node, after);
    }

    void insert(ListNode<Value> *node, ListNode<Value> *after) {
        if (length == 0) {
            head = node;
            tail = node;
            node->next = nullptr;
        } else {
            if (after == tail) {
                tail->next = node;
                node->next = nullptr;
                tail = node;
            } else if (!after) { // Insert before head
                node->next = head;
                head = node;
            } else {
                node->next = after->next;
                after->next = node;
            }
        }
        length++;
    }

    void insert(Value data) {
        insert(data, nullptr);
    }

    void insert(ListNode<Value> *node) {
        insert(node, nullptr);
    }

    void appendAtTail(Value data) {
        insert(data, tail);
    }

    void appendAtTail(ListNode<Value> *node) {
        insert(node, tail);
    }

    ListNode<Value> *remove(ListNode<Value> *node) {
        if (length == 0) return nullptr;
        if (length == 1 && node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
            length = 0;
        } else {
            if (node == head) {
                head = node->next;
            } else {
                ListNode<Value> *cur = head;
                while (cur->next != node && cur->next != nullptr) {
                    cur = cur->next;
                }
                if (node == tail) {
                    tail = cur;
                    cur->next = nullptr;
                } else {
                    cur->next = node->next;
                }
            }
            length--;
        }

        return node;
    }

    ListNode<Value> *remove(Value data) {
        ListNode<Value> *cur = head;
        while (cur != nullptr && cur->data != data) {
            cur = cur->next;
        }
        if (cur != nullptr && cur->data == data)
            return remove(cur);
        return nullptr;
    }

    ListNode<Value> *removeAtIndex(int index) {
        if (index > length) return nullptr;

        ListNode<Value> *cur = head;
        int counter = 0;
        while (cur != nullptr && counter != index) {
            cur = cur->next;
            counter++;
        }
        if (cur != nullptr)
            return remove(cur);
        return nullptr;
    }
};

template <typename Value>
class DoublyLinkedList {
    ListNode<Value> *head;
    ListNode<Value> *tail;
    size_t length;

    DoublyLinkedList<Value>() : head(nullptr), tail(nullptr), length(0) { }
    ~DoublyLinkedList() {
        auto *cur = head;
        while (cur != nullptr) {
            auto *next = cur->next;
            delete cur;
            cur = cur->next;
        }
    }

    void print() {
        if (length != 0) {
            ListNode<Value> *cur = head;
            while(cur != nullptr) {
                std::cout << cur->data << " ";
                cur = cur->next;
            }
            std::cout << std::endl;
        }
    }

    void insert(Value data, ListNode<Value> *after) {
        auto *node = new ListNode<Value>(data);
        insert(node, after);
    }

    void insert(ListNode<Value> *node, ListNode<Value> *after) {
        if (length == 0) {
            head = node;
            tail = node;
            node->next = nullptr;
            node->prev = nullptr;
        } else {
            if (after == tail) {
                tail->next = node;
                node->prev = tail;
                node->next = nullptr;
                tail = node;
            } else if (!after) { // Insert before head
                node->next = head;
                head->prev = node;
                head = node;
            } else {
                node->next = after->next;
                node->prev = after;
                after->next = node;
            }
        }
        length++;
    }

    void insert(Value data) {
        insert(data, nullptr);
    }

    void insert(ListNode<Value> *node) {
        insert(node, nullptr);
    }

    void appendAtTail(Value data) {
        insert(data, tail);
    }

    void appendAtTail(ListNode<Value> *node) {
        insert(node, tail);
    }

    ListNode<Value> *remove(ListNode<Value> *node) {
        if (length == 0) return nullptr;
        if (length == 1 && node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
            length = 0;
        } else {
            if (node == head) {
                head = node->next;
                head->prev = nullptr;
            } else {
                if (node == tail) {
                    tail = node->prev;
                    tail->next = nullptr;
                } else {
                    node->next->prev = node->prev;
                    node->prev->next = node->next;
                }
            }
            length--;
        }

        return node;
    }

    ListNode<Value> *remove(Value data) {
        ListNode<Value> *cur = head;
        while (cur != nullptr && cur->data != data) {
            cur = cur->next;
        }
        if (cur != nullptr && cur->data == data)
            return remove(cur);
        return nullptr;
    }

    ListNode<Value> *removeAtIndex(int index) {
        if (index > length) return nullptr;

        ListNode<Value> *cur = head;
        int counter = 0;
        while (cur != nullptr && counter != index) {
            cur = cur->next;
            counter++;
        }
        if (cur != nullptr)
            return remove(cur);
        return nullptr;
    }
};

template <typename Value>
class Stack {
public:
    size_t length() {
        return _stack->length;
    };

    Stack<Value>() : _stack(new SinglyLinkedList<Value>()) { }
    ~Stack() {
        delete _stack;
    }

    void print() {
        _stack->print();
    }

    Value peek() {
        if (_stack->length == 0) return Value();
        return _stack->head->data;
    }

    bool isEmpty() {
        return _stack->length == 0;
    }

    ListNode<Value> *pop() {
        if (_stack->length == 0) return nullptr;
        return _stack->remove(_stack->head);
    }

    virtual void push(ListNode<Value> *node) {
        _stack->insert(node);
    }

    virtual void push(Value data) {
        _stack->insert(data);
    }
private:
    SinglyLinkedList<Value> *_stack;
};

template <typename Value>
class Queue {
public:
    size_t length() {
        return _queue->length;
    }

    Queue<Value>() : _queue(new SinglyLinkedList<Value>()) { }
    ~Queue() {
        delete _queue;
    }

    void print() {
        _queue->print();
    }

    bool isEmpty() {
        return _queue->length == 0;
    }

    ListNode<Value> *dequeue() {
        if (_queue->length == 0) return nullptr;
        return _queue->remove(_queue->tail);
    }

    Value peek() {
        if (_queue->length == 0)
            return Value();
        return _queue->tail->data;
    }

    void enqueue(ListNode<Value> *node) {
        _queue->insert(node);
    }

    void enqueue(Value data) {
        _queue->insert(data);
    }
private:
    SinglyLinkedList<Value> *_queue;
};

template <typename Key, typename Value>
struct Bucket {
    SinglyLinkedList< std::tuple<Key, Value> > *items;
    Bucket() : items(new SinglyLinkedList< std::tuple<Key, Value> >()) { }
    ~Bucket() { delete items; }
};

template <typename Key, typename Value>
class HashTable {
    Bucket<Key, Value> **_buckets;
    int _bucketSize;
    double _loadFactor;
    int _numOfRecords;
    int _bucketListSizeThreshold;

    size_t hash(Key key) {
        std::hash<Key> h;
        return h(key);
    }

    void resize() {
        int oldSize = _bucketSize;
        _bucketSize *= 2;
        auto *oldBuckets = _buckets;
        auto *newBuckets = new Bucket<Key, Value>*[_bucketSize];
        for (int index = 0; index < _bucketSize; index++)
            newBuckets[index] = new Bucket<Key, Value>();
        _buckets = newBuckets;
        _numOfRecords = 0;
        _loadFactor = 0.0;
        for (int i = 0; i < oldSize; i++) {
            auto *bucket = oldBuckets[i];
            if (bucket != nullptr) {
                auto *item = bucket->items->head;
                for (int j = 0; j < bucket->items->length; j++, item = item->next) {
                    if (item != nullptr)
                        insert(std::get<0>(item->data), std::get<1>(item->data));
                }
            }
            delete bucket;
        }
    }

public:
    explicit HashTable<Key, Value>() : _bucketSize(128), _loadFactor(0.0), _numOfRecords(0), _bucketListSizeThreshold(8) {
        _buckets = new Bucket<Key, Value>*[_bucketSize];
        for (int index = 0; index < _bucketSize; index++)
            _buckets[index] = new Bucket<Key, Value>();
    }

    ~HashTable() {
        for (int i = 0; i < _bucketSize; i++) {
            if (_buckets[i])
                delete _buckets[i];
        }
        delete _buckets;
    }

    void insert(Key key, Value value) {
        auto hashCode = hash(key);
        auto index = hashCode % _bucketSize;
        if (_buckets[index]->items->length != 0) {
            auto *cur = _buckets[index]->items->head;
            while (cur != nullptr && std::get<0>(cur->data) != key) {
                cur = cur->next;
            }

            if (cur == nullptr) {
                _buckets[index]->items->insert(std::make_tuple(key, value));
                _numOfRecords++;
            } else {
                cur->data = std::make_tuple(key, value);
            }
        } else {
            _buckets[index]->items->insert(std::make_tuple(key, value));
            _numOfRecords++;
        }

        _loadFactor = (1.0 *_numOfRecords) / _bucketSize;
        if (_loadFactor > 0.7 || _buckets[index]->items->length > _bucketListSizeThreshold) {
            resize();
        }
    }

    Value get(Key key) {
        auto hashCode = hash(key);
        auto index = hashCode % _bucketSize;
        if (_buckets[index] == nullptr)
            return Value();
        if (_buckets[index]->items->length != 0) {
            auto *cur = _buckets[index]->items->head;
            while (cur != nullptr && std::get<0>(cur->data) != key) {
                cur = cur->next;
            }

            if (cur == nullptr) {
                return Value();
            } else {
                return std::get<1>(cur->data);
            }
        }

        return Value();
    }
};

template <class Value>
class Tree {
public:
    class Node {
    public:
        Value data;
        Node *left;
        Node *right;

        explicit Node(Value data, Node *left = nullptr, Node *right = nullptr) : data(data), left(left), right(right) { }
    };

    template <class F>
    static void inOrderTraversal(Node *node, F visit) {
        if (node != nullptr) {
            Tree::inOrderTraversal(node->left, visit);
            visit(*node);
            Tree::inOrderTraversal(node->right, visit);
        }
    }

    template <class F>
    static void preOrderTraversal(Node *node, F visit) {
        if (node != nullptr) {
            visit(*node);
            Tree::preOrderTraversal(node->left, visit);
            Tree::preOrderTraversal(node->right, visit);
        }
    }

    template <class F>
    static void postOrderTraversal(Node *node, F visit) {
        if (node != nullptr) {
            Tree::postOrderTraversal(node->left, visit);
            Tree::postOrderTraversal(node->right, visit);
            visit(*node);
        }
    }
};

#endif //CRACKING_THE_CODING_INTERVIEW_DATASTRUCTURES_H
