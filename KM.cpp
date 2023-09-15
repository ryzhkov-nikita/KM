#include <iostream>
#include <set>
#include <stack>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

// Структура для множеств или операций
struct Set {
    char name; // Название множества
    set<int> elements; // Элементы множества
};

// Массив множеств
vector<Set> setsArray;

// Функция для объединения множеств
void Union(stack<Set>& setStack) {
    // Берем два множества из стека и выполняем объединение
    Set set2 = setStack.top();
    setStack.pop();
    Set set1 = setStack.top();
    setStack.pop();

    // Создаем новое множество с объединением элементов
    Set newSet;
    newSet.name = '+';
    set_union(set1.elements.begin(), set1.elements.end(), set2.elements.begin(), set2.elements.end(), inserter(newSet.elements, newSet.elements.begin()));

    // Помещаем новое множество обратно в стек
    setStack.push(newSet);
}

// Функция для разности множеств
void Difference(stack<Set>& setStack) {
    // Берем два множества из стека и выполняем разность
    Set set2 = setStack.top();
    setStack.pop();
    Set set1 = setStack.top();
    setStack.pop();

    // Создаем новое множество с разностью элементов
    Set newSet;
    newSet.name = '-';
    set_difference(set1.elements.begin(), set1.elements.end(), set2.elements.begin(), set2.elements.end(), inserter(newSet.elements, newSet.elements.begin()));

    // Помещаем новое множество обратно в стек
    setStack.push(newSet);
}

// Функция для пересечения множеств
void Intersection(stack<Set>& setStack) {
    // Берем два множества из стека и выполняем пересечение
    Set set2 = setStack.top();
    setStack.pop();
    Set set1 = setStack.top();
    setStack.pop();

    // Создаем новое множество с пересечением элементов
    Set newSet;
    newSet.name = '*';
    set_intersection(set1.elements.begin(), set1.elements.end(), set2.elements.begin(), set2.elements.end(), inserter(newSet.elements, newSet.elements.begin()));

    // Помещаем новое множество обратно в стек
    setStack.push(newSet);
}

// Функция для симметрической разности множеств
void SymmetricDifference(stack<Set>& setStack) {
    // Берем два множества из стека и выполняем симметрическую разность
    Set set2 = setStack.top();
    setStack.pop();
    Set set1 = setStack.top();
    setStack.pop();

    // Создаем новое множество с симметрической разностью элементов
    Set newSet;
    newSet.name = '/';
    set_symmetric_difference(set1.elements.begin(), set1.elements.end(), set2.elements.begin(), set2.elements.end(), inserter(newSet.elements, newSet.elements.begin()));

    // Помещаем новое множество обратно в стек
    setStack.push(newSet);

    // Добавляем новое множество в массив множеств
    setsArray.push_back(newSet);
}

// Функция для проверки наличия множества в массиве множеств
bool IsSetInArray(char setName) {
    for (const auto& set : setsArray) {
        if (set.name == setName) {
            return true;
        }
    }
    
    return false;
}
Set CopySet(char setName) {
    Set newSet;
    for (const auto& set : setsArray) {
        if (set.name == setName) {
            newSet.name = set.name;
            for (const auto& element : set.elements) {
                newSet.elements.insert(element);
            }
            cout << endl;
        }
    }
    return newSet;
}
// Функция для ввода элементов множества
void EnterSetElements(Set& set) {
    int numElements;
    cout << "Введите количество элементов множества " << set.name << ": ";
    cin >> numElements;

    int element;
    for (int i = 0; i < numElements; i++) {
        cout << "Введите элемент множества " << set.name << ": ";
        cin >> element;
        set.elements.insert(element);
    }
}

int main() {
    setlocale(0, "");

    // Создание стека для множеств
    stack<Set> setStack;

    // Создание стека для операций
    stack<char> operationStack;

    // Ввод строки
    string input;
    cout << "Введите строку калькулятора множеств: ";
    getline(cin, input);

    // Переменная для хранения текущего символа
    char currentChar;

    // Проход по строке
    for (int i = 0; i < input.length(); i++) {
        currentChar = input[i];

        // Если текущий символ - буква, добавляем множество в стек
        if (isalpha(currentChar)) {
            // Проверяем, есть ли уже данное множество в массиве множеств
            Set newSet;
            if (IsSetInArray(currentChar)) {
                
                newSet = CopySet(currentChar);
                setStack.push(newSet);
            }
            else {
                newSet.name = currentChar;
                EnterSetElements(newSet);
                setStack.push(newSet);
                setsArray.push_back(newSet);
            }
        }
        // Если текущий символ - операция, добавляем ее в стек операций
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            operationStack.push(currentChar);
        }
        // Если текущий символ - открывающая скобка, ничего не делаем
        else if (currentChar == '(') {
            continue;
        }
        // Если текущий символ - закрывающая скобка, выполняем операцию
        else if (currentChar == ')') {
            // Получаем операцию
            char operation = operationStack.top();
            operationStack.pop();

            // Выполняем операцию над множествами в стеке
            if (operation == '+') {
                Union(setStack);
            }
            else if (operation == '-') {
                Difference(setStack);
            }
            else if (operation == '*') {
                Intersection(setStack);
            }
            else if (operation == '/') {
                SymmetricDifference(setStack);
            }
        }
    }

    // Вывод результатов для каждой операции
    while (!setStack.empty()) {
        Set setResult = setStack.top();
        setStack.pop();
        cout << "Множество " << setResult.name << ": ";
        for (auto it = setResult.elements.begin(); it != setResult.elements.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }

    return 0;
}