#include <iostream>
#include <vector>
using namespace std;

class MySet {
private:
    vector<int> elements; // Храним элементы в векторе

public:
    // Добавление элемента в множество
    void add(int num) {
        // Проверяем, есть ли уже такой элемент
        bool alreadyExists = false;
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i] == num) {
                alreadyExists = true;
                break;
            }
        }

        // Если элемента нет - добавляем
        if (!alreadyExists) {
            elements.push_back(num);
        }
    }

    // Оператор [] - доступ по индексу
    int& operator[](int index) {
        if (index < 0 || index >= elements.size()) {
            throw "Error: Index out of range!"; // Просто бросаем строку
        }
        return elements[index];
    }

    // Оператор () - получить размер множества
    int operator()() {
        return elements.size();
    }

    // Оператор + - объединение двух множеств
    MySet operator+(MySet other) {
        MySet result = *this; // Копируем текущее множество

        // Добавляем все элементы из второго множества
        for (int i = 0; i < other.elements.size(); i++) {
            result.add(other.elements[i]);
        }

        return result;
    }

    // Префиксный ++ (добавляем максимальный элемент + 1)
    MySet& operator++() {
        if (elements.empty()) {
            add(0); // Если множество пустое, добавляем 0
        }
        else {
            // Находим максимальный элемент
            int max = elements[0];
            for (int i = 1; i < elements.size(); i++) {
                if (elements[i] > max) {
                    max = elements[i];
                }
            }
            add(max + 1); // Добавляем max + 1
        }
        return *this;
    }

    // Постфиксный ++
    MySet operator++(int) {
        MySet temp = *this;
        ++(*this); // Используем префиксную версию
        return temp;
    }

    // Вывод множества на экран
    void print() {
        cout << "{ ";
        for (int i = 0; i < elements.size(); i++) {
            cout << elements[i] << " ";
        }
        cout << "}" << endl;
    }
};

int main() {
    try {
        // Создаем первое множество
        MySet set1;
        set1.add(1);
        set1.add(2);
        set1.add(3);
        cout << "Set1: ";
        set1.print();

        // Создаем второе множество
        MySet set2;
        set2.add(3);
        set2.add(4);
        set2.add(5);
        cout << "Set2: ";
        set2.print();

        // Объединение множеств
        MySet set3 = set1 + set2;
        cout << "Union (set1 + set2): ";
        set3.print();

        // Размер множества
        cout << "Size of set1: " << set1() << endl;

        // Доступ по индексу
        cout << "set1[1] = " << set1[1] << endl;
        set1[1] = 10;
        cout << "After set1[1] = 10: ";
        set1.print();

        // Префиксный ++
        ++set1;
        cout << "After ++set1: ";
        set1.print();

        // Постфиксный ++
        set2++;
        cout << "After set2++: ";
        set2.print();

        // Проверка ошибки
        cout << "Trying to access set1[100]..." << endl;
        cout << set1[100] << endl;
    }
    catch (const char* error) {
        cout << error << endl;
    }

    return 0;
}