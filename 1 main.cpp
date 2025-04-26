#include <iostream>
#include <vector>
using namespace std;

class MySet {
private:
    vector<int> elements; // ������ �������� � �������

public:
    // ���������� �������� � ���������
    void add(int num) {
        // ���������, ���� �� ��� ����� �������
        bool alreadyExists = false;
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i] == num) {
                alreadyExists = true;
                break;
            }
        }

        // ���� �������� ��� - ���������
        if (!alreadyExists) {
            elements.push_back(num);
        }
    }

    // �������� [] - ������ �� �������
    int& operator[](int index) {
        if (index < 0 || index >= elements.size()) {
            throw "Error: Index out of range!"; // ������ ������� ������
        }
        return elements[index];
    }

    // �������� () - �������� ������ ���������
    int operator()() {
        return elements.size();
    }

    // �������� + - ����������� ���� ��������
    MySet operator+(MySet other) {
        MySet result = *this; // �������� ������� ���������

        // ��������� ��� �������� �� ������� ���������
        for (int i = 0; i < other.elements.size(); i++) {
            result.add(other.elements[i]);
        }

        return result;
    }

    // ���������� ++ (��������� ������������ ������� + 1)
    MySet& operator++() {
        if (elements.empty()) {
            add(0); // ���� ��������� ������, ��������� 0
        }
        else {
            // ������� ������������ �������
            int max = elements[0];
            for (int i = 1; i < elements.size(); i++) {
                if (elements[i] > max) {
                    max = elements[i];
                }
            }
            add(max + 1); // ��������� max + 1
        }
        return *this;
    }

    // ����������� ++
    MySet operator++(int) {
        MySet temp = *this;
        ++(*this); // ���������� ���������� ������
        return temp;
    }

    // ����� ��������� �� �����
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
        // ������� ������ ���������
        MySet set1;
        set1.add(1);
        set1.add(2);
        set1.add(3);
        cout << "Set1: ";
        set1.print();

        // ������� ������ ���������
        MySet set2;
        set2.add(3);
        set2.add(4);
        set2.add(5);
        cout << "Set2: ";
        set2.print();

        // ����������� ��������
        MySet set3 = set1 + set2;
        cout << "Union (set1 + set2): ";
        set3.print();

        // ������ ���������
        cout << "Size of set1: " << set1() << endl;

        // ������ �� �������
        cout << "set1[1] = " << set1[1] << endl;
        set1[1] = 10;
        cout << "After set1[1] = 10: ";
        set1.print();

        // ���������� ++
        ++set1;
        cout << "After ++set1: ";
        set1.print();

        // ����������� ++
        set2++;
        cout << "After set2++: ";
        set2.print();

        // �������� ������
        cout << "Trying to access set1[100]..." << endl;
        cout << set1[100] << endl;
    }
    catch (const char* error) {
        cout << error << endl;
    }

    return 0;
}