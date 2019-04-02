//
// Created by Francisco Soares on 2019-02-04.
//

#ifndef CRACKING_THE_CODING_INTERVIEW_CH02_H
#define CRACKING_THE_CODING_INTERVIEW_CH02_H

#include <unordered_set>
#include "LinkedListNode.h"
#include "DataStructures.h"

class Node {
public:
    Node *next = nullptr;
    int data;

    explicit Node(int d) : data(d) { }

    void append(int d) {
        Node *end = new Node(d);
        Node *n = this;
        while (n->next != nullptr) {
            n = n->next;
        }
        n->next = end;
    }
};

Node *deleteNode(Node *head, int d) {
    Node *n = head;

    if (n->data == d) return head->next;

    while (n->next != nullptr) {
        if (n->next->data == d) {
            n->next = n->next->next;
            return head;
        }
        n = n->next;
    }

    return head;
}

// 2.1 Remove Dups: Write code to remove duplicates from an unsorted linked list. How would you solve this problem
// if a temporary buffer is not allowed?
// Solution 1: Using Hash Table
template <typename Value>
void removeDups(SinglyLinkedList<Value> *list) {
    auto *node = list->head;
    if (list->length == 0) return;
    std::unordered_set<int> hashTable;

    while (node != nullptr) {
        auto it = hashTable.find(node->data);
        if (it != hashTable.end()) {
            auto *tmp = list->remove(node);
            delete tmp;
        } else {
            hashTable.insert(node->data);
        }
        node = node->next;
    }
}

// Solution 2: Using two pointers when temporary buffer is not available
template <typename Value>
void removeDups2(SinglyLinkedList<Value> *list) {
    if (list->length == 0) return;
    auto *first = list->head;
    auto *second = first->next;

    while (first != nullptr) {
        while (second != nullptr) {
            if (second->data == first->data) {
                list->remove(second);
            }
            second = second->next;
        }
        first = first->next;
        if (!first) break;
        second = first->next;
    }
}

// 2.2 Return Kth to Last: Implement an algorithm to find the kth element to last element of a singly linked list
// Solution 1:
template <typename Value>
ListNode<Value> *returnKthToLast(SinglyLinkedList<Value> *list, int k) {
    size_t index = 0;
    size_t finalPosition = list->length - k - 1;
    auto *n = list->head;
    while (n != nullptr) {
        if (index == finalPosition) {
            return n;
        }
        index++;
        n = n->next;
    }
    return nullptr;
}

// Solution 2: Recursive
template <typename Value>
int returnKthToLastRecursive(SinglyLinkedList<Value> *list, int k) {
    if (list->length == 0) return 0;
    auto *head = list->head;
    int index = returnKthToLastRecursive(head->next, k) + 1;
    if (index == k) {
        std::cout << k << "th to last node is " << head->data << std::endl;
    }
    return index;
}

// Solution 3: C++
template <typename Value>
ListNode<Value> *nthToLast(SinglyLinkedList<Value> *list, int k, int &i) {
    if (list->length == 0) return nullptr;
    auto *head = list->head;
    auto *nd = nthToLast(head->next, k, i);
    i += 1;
    if (i == k)
        return head;
    return nd;
}

template <typename Value>
ListNode<Value> *nthToLast(SinglyLinkedList<Value> *head, int k) {
    int i = 0;
    return nthToLast(head, k, i);
}

// Solution 4: Iterative
template <typename Value>
ListNode<Value> *nthToLastIterative(ListNode<Value> *head, int k) {
    auto *first = head;
    auto *second = head;

    for (int i = 0; i < k; i++) {
        if (second == nullptr) return nullptr;
        second = second->next;
    }

    while (second != nullptr) {
        second = second->next;
        first = first->next;
    }
    return first;
}

// 2.3 Delete Middle Node: Implement an algorithm to delete a node in the middle of a singly linked list, given only access to that node.
// Solution 1:
template <typename Value>
void deleteMiddleNode(ListNode<Value> *node) {
    if (node->next == nullptr) {
        node = nullptr;
    } else {
        auto *next = node->next;
        node->data = next->data;
        node->next = next->next;
        next = nullptr;
    }
}

// 2.4 Partition: Write code to partition a linked list around a value x, such that all nodes less than x come before all
// nodes greater than or equal to x. If x is contained within the list, the values of x only need to be after the elements
// less than x. The partition element x can appear anywhere in the "right partition"; it does not need to appear between
// the left and right partitions.
void partition(Node *head, int x) {
    Node *beforeStart   = nullptr;
    Node *beforeEnd     = nullptr;
    Node *afterStart    = nullptr;
    Node *afterEnd      = nullptr;
    Node *node = head;

    node = node->next;
    while (node != nullptr) {
        Node *next = node->next;
        node->next = nullptr;
        if (node->data < x) {
            if (!beforeStart) {
                beforeStart = node;
                beforeEnd = beforeStart;
            } else {
                beforeEnd->next = node;
                beforeEnd = node;
            }
        } else {
            if (!afterStart) {
                afterStart = node;
                afterEnd = afterStart;
            } else {
                afterEnd->next = node;
                afterEnd = node;
            }
        }
        node = next;
    }

    if (!beforeStart) {
        head->next = afterStart;
    } else {
        beforeEnd->next = afterStart;
        head->next = beforeStart;
    }
}

// Solution 2: SinglyLinkedList
template <typename Value>
SinglyLinkedList<Value> *partition(SinglyLinkedList<Value> *list, int x) {
    auto *before = new SinglyLinkedList<Value>();
    auto *after = new SinglyLinkedList<Value>();

    auto *node = list->head;

    while (node != nullptr) {
        auto *next = node->next;
        node->next = nullptr;
        if (node->data < x) {
            before->insert(node);
        } else {
            after->insert(node);
        }
        node = next;
    }
    if (before->length == 0)
        return after;
    else {
        auto *cur = after->head;
        while (cur != nullptr) {
            auto *next = cur->next;
            before->appendAtTail(cur);
            cur = next;
        }
        return before;
    }

}

// 2.5 Sum Lists: You have two numbers represented by a linked list, where each node contains a single digit. The digit
// are stored in reverse order, such that the 1's digit is at the head of the list. Write a function that adds the two
// numbers and return the sum as a linked list.
// Solution 1:
SinglyLinkedList<int> *addLists(ListNode<int> *lhs, ListNode<int> *rhs, int carry) {
    if (lhs== nullptr && rhs == nullptr && carry == 0)
        return nullptr;

    auto *result = new SinglyLinkedList<int>();
    int value = carry;
    if (lhs != nullptr)
        value += lhs->data;
    if (rhs != nullptr)
        value += rhs->data;

    result->appendAtTail(value % 10);

    if (lhs != nullptr || rhs != nullptr) {
        auto *more = addLists(lhs->next == nullptr ? nullptr : lhs->next,
                              rhs->next == nullptr ? nullptr : rhs->next,
                              value >= 10 ? 1 : 0);
        if (more == nullptr) {
            return result;
        }
        auto *node = more->head;
        while (node != nullptr) {
            auto *next = node->next;
            result->appendAtTail(node);
            node = next;
        }
    }

    return result;
}

// Follow-up:
struct PartialSum {
    ListNode<int> *sum = nullptr;
    int carry = 0;
};

int length(ListNode<int> *head) {
    auto *node = head;
    int length = 0;
    while (node != nullptr) {
        node = node->next;
        length++;
    }

    return length;
}

ListNode<int> *insertBefore(ListNode<int> *head, int value) {
    auto *node = new ListNode<int>(value);
    if (head) {
        node->next = head;
    }
    return node;
}

ListNode<int> *padList(ListNode<int> *head, int padding) {
    auto *node = head;
    for (int i = 0; i < padding; i++) {
        head = insertBefore(head, 0);
    }
    return head;
}

PartialSum *addListsHelper(ListNode<int> *lhs, ListNode<int> *rhs) {
    if (lhs == nullptr && rhs == nullptr) {
        auto *sum = new PartialSum();
        return sum;
    }

    auto *sum = addListsHelper(lhs->next, rhs->next);

    int val = sum->carry + lhs->data + rhs->data;

    auto *fullResult = insertBefore(sum->sum, val % 10);

    sum->sum = fullResult;
    sum->carry = val / 10;
    return sum;
}

SinglyLinkedList<int> *addLists2(ListNode<int> *lhs, ListNode<int> *rhs) {
    int len1 = length(lhs);
    int len2 = length(rhs);

    // Pad the shorter list with zeros - see note
    if (len1 < len2) {
        lhs = padList(lhs, len2 - len1);
    } else {
        rhs = padList(rhs, len1 - len2);
    }

    auto *sum = addListsHelper(lhs, rhs);

    ListNode<int> *result = nullptr;
    if (sum->carry == 0) {
        result = sum->sum;
    } else {
        result = insertBefore(sum->sum, sum->carry);
    }

    auto *list = new SinglyLinkedList<int>();
    size_t length = 0;
    auto *node = result;
    while (node != nullptr) {
        if (node->next == nullptr)
            list->tail = node;
        node = node->next;
        length++;
    }
    list->length = length;
    list->head = result;
    return list;
}

// 2.6 Palindrome: Implement a function to check if a linked list is a palindrome
// Solution 1: O(n^2)
template <typename Value>
bool palindrome(SinglyLinkedList<Value> *head) {
    int limit = length(head) / 2;

    auto *n = head;
    for (int i = 1; i <= limit; i++) {
        if (n->data != nthToLastIterative(head, i)->data)
            return false;
    }

    return true;
}

// Solution 2:
template <typename Value>
LinkedListNode<Value> *reverseAndClone(LinkedListNode<Value> *node) {
    LinkedListNode<Value> *head = nullptr;
    while (node != nullptr) {
        LinkedListNode<Value> *n = new LinkedListNode<Value>(node->data);
        n->next = head;
        head = n;
        node = node->next;
    }
    return head;
}

template <typename Value>
bool isEqual(LinkedListNode<Value> *lhs, LinkedListNode<Value> *rhs) {
    while (lhs != nullptr && rhs != nullptr) {
        if (lhs->data != rhs->data) {
            return false;
        }
        lhs = lhs->next;
        rhs = rhs->next;
    }
    return lhs == nullptr && rhs == nullptr;
}

template <typename Value>
bool palindrome(LinkedListNode<Value> *head) {
    LinkedListNode<Value> *reversed = reverseAndClone(head);
    return isEqual(head, reversed);
}

// 2.7 Intersection: Given two (singly) linked lists, determine if the two lists intersect. Return the intersecting node.
// Note tha the intersection is defined based on reference, not value. That is, if the kth node of the first linked list
// is the exact same node (by reference) as the jth node of the second linked list, then they are intersecting
// Solution 1:
Node *intersection(Node *lhs, Node *rhs) {
    std::unordered_set<Node const*> hashTable;

    Node *n = lhs;
    while (n != nullptr) {
        hashTable.insert(n);
        n = n->next;
    }

    n = rhs;
    while (n != nullptr) {
        auto pos = hashTable.find(n);
        if (pos != hashTable.end())
            return n;
    }

    return nullptr;
}

// 2.8 Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the beginning of the loop
// Solution 1:
Node *loopDetection(Node *head) {
    Node *n = head;
    std::unordered_set<Node const*> hashTable;

    while (n != nullptr) {
        auto pos = hashTable.find(n);
        if (pos != hashTable.end())
            return n;
        hashTable.insert(n);
    }

    return nullptr;
}

#endif //CRACKING_THE_CODING_INTERVIEW_CH02_H
