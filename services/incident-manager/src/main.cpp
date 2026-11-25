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
        std::cout << "Помилка валідації: id має бути додатним цілим числом.\n";
        return false;
    }
    if (isDuplicateId(incidents, count, inc.id)) {
        std::cout << "Помилка валідації: інцидент із таким id вже існує.\n";
        return false;
    }
    if (inc.source.empty()) {
        std::cout << "Помилка валідації: джерело (source) не може бути порожнім.\n";
        return false;
    }
    if (!isValidCategory(inc.category)) {
        std::cout << "Помилка валідації: неприпустима категорія. Дозволені: SIGNAL, OVERLOAD, DEVICE_OFFLINE, DATA_ERROR.\n";
        return false;
    }
    if (!isValidSeverity(inc.severity)) {
        std::cout << "Помилка валідації: неприпустимий рівень (severity). Дозволені: INFO, WARNING, CRITICAL.\n";
        return false;
    }
    return true;
}

bool readIncident(Incident& inc) {
    std::cout << "Введіть ID інциденту (ціле число > 0): ";
    if (!(std::cin >> inc.id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка введення: очікувалося ціле число для ID.\n";
        return false;
    }

    std::cout << "Введіть джерело (source, наприклад router-1): ";
    std::cin >> inc.source;

    std::cout << "Введіть категорію (SIGNAL / OVERLOAD / DEVICE_OFFLINE / DATA_ERROR): ";
    std::cin >> inc.category;

    std::cout << "Введіть рівень (INFO / WARNING / CRITICAL): ";
    std::cin >> inc.severity;

    inc.resolved = false;
    return true;
}

int main() {
    Incident incidents[MAX_INCIDENTS];
    int incidentCount = 0;

    std::cout << "=== Incident Manager (базовий модуль валідації) ===\n";
    Incident tempIncident;

    if (readIncident(tempIncident)) {
        if (validateIncident(tempIncident, incidents, incidentCount)) {
            if (incidentCount < MAX_INCIDENTS) {
                incidents[incidentCount] = tempIncident;
                ++incidentCount;
                std::cout << "Інцидент успішно пройшов валідацію та доданий (всього: "
                          << incidentCount << ").\n";
            }
        }
    }

    return 0;
}