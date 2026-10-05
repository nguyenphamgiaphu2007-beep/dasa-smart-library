#pragma once

#include "MyDoublyLinkedList.h"
#include "MyHashTable.h"
#include "../models/Document.h"

class DocumentStorage {
private:
    MyDoublyLinkedList<Document> list;
    MyHashTable hashTable;

public:
    bool add(const Document& document) {
        Document existing;

        if (hashTable.search(document.documentId, existing)) {
            return false;
        }

        if (!hashTable.insert(document)) {
            return false;
        }

        list.pushBack(document);

        return true;
    }

    bool findById(const std::string& id, Document& document) {
        return hashTable.search(id, document);
    }

    bool removeById(const std::string& id) {
        Document document;

        if (!hashTable.search(id, document)) {
            return false;
        }

        int index = -1;

        for (int i = 0; i < list.getSize(); i++) {
            Document current;

            if (list.get(i, current)) {
                if (current.documentId == id) {
                    index = i;
                    break;
                }
            }
        }

        if (index == -1) {
            return false;
        }

        if (!hashTable.remove(id)) {
            return false;
        }

        list.removeAt(index);

        return true;
    }

    void clear() {
        list.clear();
        hashTable.clear();
    }

    int getSize() const {
        return list.getSize();
    }

    const MyDoublyLinkedList<Document>& getList() const {
        return list;
    }

    MyHashTable& getHashTable() {
        return hashTable;
    }
};
