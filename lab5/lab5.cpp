#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdexcept>

// Исключение для демонстрации
class InvalidBalanceException : public std::runtime_error {
public:
    InvalidBalanceException() : std::runtime_error("Недопустимый баланс!") {}
};

class User {
private:
    int id;
    std::string name;
    std::string login;
    std::string password;
    std::string created_date;
    float balance;

public:
    // Статическое поле
    static int userCount;

    User() : id(0), balance(0.0f) {
        userCount++;
    }

    User(int id, const std::string& name, const std::string& login, const std::string& password, float balance)
        : id(id), name(name), login(login), password(password) {
        if (balance < 0) {
            throw InvalidBalanceException(); // Инициализация исключения
        }
        this->balance = balance;
        userCount++;
    }

    // Конструктор копии
    User(const User& other)
        : id(other.id), name(other.name), login(other.login), password(other.password), balance(other.balance) {
        userCount++;
    }

    // Перегрузка оператора присваивания
    User& operator=(const User& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            login = other.login;
            password = other.password;
            balance = other.balance;
        }
        return *this;
    }
    int getId() const { return id; }
    const std::string& getName() const { return name; }
    float getBalance() const { return balance; }

    // Возврат значения через указатель
    float* getBalancePtr() {
        return &balance;
    }

    // Возврат значения через ссылку
    const std::string& getNameRef() const {
        return name;
    }

    // Дружественная функция
    friend void displayUserInfo(const User& user);

    static int getUserCount() { // Статический метод
        return userCount;
    }

    void setBalance(float balance) {
        if (balance < 0) {
            throw InvalidBalanceException(); // Инициализация исключения
        }
        this->balance = balance;
    }

    ~User() {
        userCount--;
    }
};

int User::userCount = 0;

void displayUserInfo(const User& user) {
    std::cout << "ID: " << user.id << ", Имя: " << user.name << ", Баланс: " << user.balance << std::endl;
}

class Slot {
private:
    int id;
    std::string name;
    int max_bet;
    int min_bet;
    float payout_ratio;

public:
    Slot() : id(0), max_bet(0), min_bet(0), payout_ratio(0.0f) {}

    Slot(int id, const std::string& name, int max_bet, int min_bet, float payout_ratio)
        : id(id), name(name), max_bet(max_bet), min_bet(min_bet), payout_ratio(payout_ratio) {}

    const std::string& getName() const { return name; }
    float getPayoutRatio() const { return payout_ratio; }

    void displaySlotInfo() const {
        std::cout << "Слот: " << name << ", Максимальная ставка: " << max_bet << ", Минимальная ставка: " << min_bet << std::endl;
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Slot& slot) {
        os << "Слот: " << slot.name << ", Максимальная ставка: " << slot.max_bet << ", Минимальная ставка: " << slot.min_bet;
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        std::cout << "Работа с классом User:\n";
        User user1(1, "Алексей", "alex123", "alexpass", 1500.0);
        displayUserInfo(user1); // Использование дружественной функции

        user1.setBalance(2000.0);
        std::cout << "Обновленный баланс: " << *user1.getBalancePtr() << std::endl; // Возврат значения через указатель

        user1.setBalance(-100); // Это вызовет исключение

    }
    catch (const InvalidBalanceException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    User user1;
    try {
        std::cout << "\nРабота с классом Slot:\n";
        Slot slot1(1, "Lucky 7", 100, 10, 2.5f);
        std::cout << slot1 << std::endl; // Перегрузка оператора вывода

        std::cout << "\nОбщее количество пользователей: " << User::getUserCount() << std::endl; // Статический метод

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
