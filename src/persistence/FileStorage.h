#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "MyDoublyLinkedList.h"
#include "../models/Document.h"

class FileStorage {
private:
    std::string filePath;

    std::string trim(const std::string& value) {
        int start = 0;
        int end = (int)value.length() - 1;

        while (start <= end && value[start] == ' ') {
            start++;
        }

        while (end >= start && value[end] == ' ') {
            end--;
        }

        if (start > end) {
            return "";
        }

        return value.substr(start, end - start + 1);
    }

    int statusToInt(DocumentStatus status) {
        if (status == DocumentStatus::Available) {
            return 0;
        }

        if (status == DocumentStatus::Borrowed) {
            return 1;
        }

        if (status == DocumentStatus::Overdue) {
            return 2;
        }

        return 3;
    }

    DocumentStatus intToStatus(int value) {
        if (value == 0) {
            return DocumentStatus::Available;
        }

        if (value == 1) {
            return DocumentStatus::Borrowed;
        }

        if (value == 2) {
            return DocumentStatus::Overdue;
        }

        return DocumentStatus::Reserved;
    }

public:
    FileStorage(const std::string& filePath) {
        this->filePath = filePath;
    }

    bool load(MyDoublyLinkedList<Document>& list) {
        std::ifstream file(filePath);

        if (!file.is_open()) {
            return false;
        }

        list.clear();

        std::string line;

        // Bỏ dòng header
        getline(file, line);

        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);

            std::string documentId;
            std::string title;
            std::string borrowerId;
            std::string status;
            std::string dueDate;
            std::string priorityLevel;
            std::string registrationTime;
            std::string auditCategory;
            std::string conditionState;

            getline(ss, documentId, ',');
            getline(ss, title, ',');
            getline(ss, borrowerId, ',');
            getline(ss, status, ',');
            getline(ss, dueDate, ',');
            getline(ss, priorityLevel, ',');
            getline(ss, registrationTime, ',');
            getline(ss, auditCategory, ',');
            getline(ss, conditionState, ',');

            Document document;

            document.documentId = trim(documentId);
            document.title = trim(title);
            document.borrowerId = trim(borrowerId);

            int statusValue = std::stoi(trim(status));
            document.status = intToStatus(statusValue);

            document.dueDate = std::stoll(trim(dueDate));
            document.priorityLevel = std::stoi(trim(priorityLevel));
            document.registrationTime = std::stoll(trim(registrationTime));

            document.auditCategory = trim(auditCategory);
            document.conditionState = trim(conditionState);

            list.pushBack(document);
        }

        file.close();

        return true;
    }

    bool save(const MyDoublyLinkedList<Document>& list) {
        std::ofstream file(filePath);

        if (!file.is_open()) {
            return false;
        }

        file << "documentId,title,borrowerId,status,dueDate,priorityLevel,registrationTime,auditCategory,conditionState\n";

        for (int i = 0; i < list.getSize(); i++) {
            Document document;

            if (!list.get(i, document)) {
                continue;
            }

            file << document.documentId << ",";
            file << document.title << ",";
            file << document.borrowerId << ",";
            file << statusToInt(document.status) << ",";
            file << document.dueDate << ",";
            file << document.priorityLevel << ",";
            file << document.registrationTime << ",";
            file << document.auditCategory << ",";
            file << document.conditionState << "\n";
        }

        file.close();

        return true;
    }
};
