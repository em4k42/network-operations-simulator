#include <iostream>
#include <limits>
#include <string>

const int MAX_INCIDENTS = 100;

struct Incident {
    int id;
    std::string source;
    std::string category;
    std::string severity;
    bool resolved;
};

bool isDuplicateId(const Incident incidents[], int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (incidents[i].id == id) {
            return true;
        }
    }
    return false;
}

bool isValidCategory(const std::string& category) {
    return category == "SIGNAL" ||
           category == "OVERLOAD" ||
           category == "DEVICE_OFFLINE" ||
           category == "DATA_ERROR";
}

bool isValidSeverity(const std::string& severity) {
    return severity == "INFO" ||
           severity == "WARNING" ||
           severity == "CRITICAL";
}

bool validateIncident(const Incident& inc, const Incident incidents[], int count) {
    if (inc.id <= 0) {
        std::cout << "Validation error: ID must be a positive integer.\n";
        return false;
    }
    if (isDuplicateId(incidents, count, inc.id)) {
        std::cout << "Validation error: Incident with this ID already exists.\n";
        return false;
    }
    if (inc.source.empty()) {
        std::cout << "Validation error: Source cannot be empty.\n";
        return false;
    }
    if (!isValidCategory(inc.category)) {
        std::cout << "Validation error: Invalid category. Allowed: SIGNAL, OVERLOAD, DEVICE_OFFLINE, DATA_ERROR.\n";
        return false;
    }
    if (!isValidSeverity(inc.severity)) {
        std::cout << "Validation error: Invalid severity. Allowed: INFO, WARNING, CRITICAL.\n";
        return false;
    }
    return true;
}

bool readIncident(Incident& inc) {
    std::cout << "Enter incident ID (integer > 0): ";
    if (!(std::cin >> inc.id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input error: Expected an integer for ID.\n";
        return false;
    }

    std::cout << "Enter source (e.g., router-1): ";
    std::cin >> inc.source;

    std::cout << "Enter category (SIGNAL / OVERLOAD / DEVICE_OFFLINE / DATA_ERROR): ";
    std::cin >> inc.category;

    std::cout << "Enter severity (INFO / WARNING / CRITICAL): ";
    std::cin >> inc.severity;

    inc.resolved = false;
    return true;
}

int main() {
    Incident incidents[MAX_INCIDENTS];
    int incidentCount = 0;
    int choice = -1;

    std::cout << "=== Incident Manager (Input & Validation Module) ===\n";

    while (true) {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Add new incident\n";
        std::cout << "0. Exit\n";
        std::cout << "Select an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error: Please enter 1 or 0.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Exiting Incident Manager. Total incidents stored: "
                      << incidentCount << ".\n";
            break;
        } else if (choice == 1) {
            if (incidentCount >= MAX_INCIDENTS) {
                std::cout << "Storage error: Maximum limit of "
                          << MAX_INCIDENTS << " incidents reached.\n";
                continue;
            }

            Incident tempIncident;
            if (readIncident(tempIncident)) {
                if (validateIncident(tempIncident, incidents, incidentCount)) {
                    incidents[incidentCount] = tempIncident;
                    ++incidentCount;
                    std::cout << "Incident validated and added successfully (total: "
                              << incidentCount << ").\n";
                }
            }
        } else {
            std::cout << "Invalid option. Please enter 1 or 0.\n";
        }
    }

    return 0;
}