#include <iostream>
#include <vector>
using namespace std;

// Простой класс для ошибки выхода за границы
class OutOfRangeError {
public:
    string message;
    OutOfRangeError() : message("Index is out of range!") {}
};

// Простой класс для ошибки пустого множества
class EmptySetError {
public:
    string message;
    EmptySetError() : message("Set is empty!") {}
};

class MySet {
private:
    vector<int> elements;

public:
    void add(int num) {
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i] == num) {
                return; // Элемент уже есть - ничего не делаем
            }
        }
        elements.push_back(num);
    }

    int& operator[](int index) {
        if (index < 0 || index >= elements.size()) {
            throw OutOfRangeError(); // Бросаем объект ошибки
        }
        return elements[index];
    }

    int operator()() {
        return elements.size();
    }

    MySet operator+(MySet other) {
        MySet result = *this;
        for (int i = 0; i < other.elements.size(); i++) {
            result.add(other.elements[i]);
        }
        return result;
    }

    MySet& operator++() {
        if (elements.empty()) {
            throw EmptySetError();
        }

        int max = elements[0];
        for (int i = 1; i < elements.size(); i++) {
            if (elements[i] > max) {
                max = elements[i];
            }
        }
        add(max + 1);
        return *this;
    }

    MySet operator++(int) {
        MySet temp = *this;
        ++(*this);
        return temp;
    }

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
        MySet set1;
        set1.add(1);
        set1.add(2);
        set1.add(3);
        cout << "Set1: ";
        set1.print();

        MySet set2;
        set2.add(3);
        set2.add(4);
        set2.add(5);
        cout << "Set2: ";
        set2.print();

        MySet set3 = set1 + set2;
        cout << "Union (set1 + set2): ";
        set3.print();

        cout << "Size of set1: " << set1() << endl;

        cout << "set1[1] = " << set1[1] << endl;
        set1[1] = 10;
        cout << "After set1[1] = 10: ";
        set1.print();

        ++set1;
        cout << "After ++set1: ";
        set1.print();

        set2++;
        cout << "After set2++: ";
        set2.print();

        // Проверка ошибки с пустым множеством
        MySet emptySet;
        cout << "Trying ++ on empty set..." << endl;
        ++emptySet;
    }
    catch (OutOfRangeError e) {
        cout << "ERROR: " << e.message << endl;
    }
    catch (EmptySetError e) {
        cout << "ERROR: " << e.message << endl;
    }

    return 0;
}