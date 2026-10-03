#pragma once

#include <iostream>

template <typename T>
class MyDoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;

public:
    MyDoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~MyDoublyLinkedList() {
        clear();
    }

    bool empty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void pushFront(const T& value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        size++;
    }

    void pushBack(const T& value) {
        Node* newNode = new Node(value);

        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    bool popFront(T& value) {
        if (head == nullptr) {
            return false;
        }

        Node* temp = head;
        value = temp->data;

        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete temp;
        size--;

        return true;
    }

    bool popBack(T& value) {
        if (tail == nullptr) {
            return false;
        }

        Node* temp = tail;
        value = temp->data;

        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete temp;
        size--;

        return true;
    }

    bool get(int index, T& value) const {
        if (index < 0 || index >= size) {
            return false;
        }

        Node* current;

        if (index < size / 2) {
            current = head;

            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;

            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }

        value = current->data;
        return true;
    }

    bool removeAt(int index) {
        if (index < 0 || index >= size) {
            return false;
        }

        Node* current;

        if (index < size / 2) {
            current = head;

            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;

            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        delete current;
        size--;

        return true;
    }

    void clear() {
        Node* current = head;

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void print() const {
        Node* current = head;

        while (current != nullptr) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
};
