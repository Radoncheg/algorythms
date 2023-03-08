#include <iostream>
#include <cctype>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <sstream>

/*В строке текстового файла  задано  выражение  из  целых 
чисел и операций '+', '-', '*', '/', '^'.  Порядок  вычислений 
определяется приоритетом операций и круглыми скобками. Возможен
одноместный минус в начале  выражения  или  после  открывающей 
скобки. Преобразовать выражение в постфиксную  форму (алгоритм 
Дейкстры) и вычислить его значение. Показать этапы  выполнения
*/
//Ошаев Олег Visual Studio Code

//модуль стека


//Выражение подтягивается из файла

using namespace std;

template <typename T>
struct StackElement
{
    T data;
    StackElement<T>* next;
};

template <typename T>
class LStack
{
private:
    StackElement<T>* pTop;

public:
    LStack() {
        pTop = nullptr;
    }

    void push(T item)
    {
        StackElement<T>* p;

        try {
            p = new StackElement<T>;
        }
        catch (bad_alloc e)
        {
            return;
        }
        p->data = item;
        p->next = pTop;

        pTop = p;
    }

    void removeAll()
    {
        StackElement<T>* p;
        StackElement<T>* p2;

        p = pTop;
        while (p != nullptr)
        {
            p2 = p;
            p = p->next;
            delete p2;
        }
        pTop = nullptr;
    }

    ~LStack()
    {
        removeAll();
    }

    T pop()
    {
        if (pTop == nullptr)
            return 0;

        StackElement<T>* p2;
        T data;
        data = pTop->data;

        p2 = pTop;
        pTop = pTop->next;

        delete p2;

        return data;
    }

    T top()
    {
        if (pTop == nullptr)
            return 0; 
        else
            return pTop->data;
    }

    bool empty() {
        return (pTop == nullptr);
    }

};

//выражение подтягивается из файла

string readFileStreamIO(string aFileName) {
    string expression;
    ifstream readFile;
    readFile.open(aFileName, ifstream::in);
    if (readFile.is_open()) {
        while (getline(readFile, expression)) {
        }
    }
    readFile.close();
    return expression;
}

int64_t evaluate(const string & aExpression) {
        istringstream iss(aExpression);
        LStack<int64_t> stack;
        string token;
        int64_t tokenNum;
        int64_t secondOperand;
        int64_t firstOperand;
        while (iss >> token) {
            std::cout << token << " ";
            
            if (istringstream(token) >> tokenNum) {
                cout << "Push" <<endl;
                stack.push(tokenNum);
            }
            else {
                cout << "Operate" << endl;
                secondOperand = stack.pop();
                firstOperand = stack.pop();
                if (token == "*")
                    stack.push(firstOperand * secondOperand);
                else if (token == "/")
                    stack.push(firstOperand / secondOperand);
                else if (token == "-")
                    stack.push(firstOperand - secondOperand);
                else if (token == "+")
                    stack.push(firstOperand + secondOperand);
                else if (token == "^")
                    stack.push(pow(firstOperand, secondOperand));
                else { 
                    cerr << "Error" << std::endl;
                    exit(1);
                }
                cout << "Top " << stack.top() <<  endl;
            }
        }
        return stack.pop();
    }

// функция создает обратную польскую запись (постфиксная нотация)
string RPN(string aExpression)
{
    string result_pnotation;
    string::size_type index;
    
    // удаление пробелов из входной строки
    while ((index = aExpression.find(' ')) != string::npos) aExpression.erase(index, 1);
    cout << "Удаление пробелов... " << aExpression << endl;

    for (int i = 0; i < aExpression.size(); ++i) { // учёт отрицательных чисел
        if ((aExpression[i] == '+' || aExpression[i] == '-') 
            && (0 == i || (!isalnum(aExpression[i - 1]) 
            && aExpression[i - 1] != ')'))) {
                auto it = find_if(aExpression.begin() + i + 1, aExpression.end(), [](char const c) {return !isalnum(c); });
            aExpression.insert(it, ')');
            aExpression.insert(i, "(0");
            cout << "Обработка отрицательных чисел... " << aExpression << endl;
        }
    }

    map<char, size_t> map; // приоритеты операций
    map.insert(make_pair('^', 4));
    map.insert(make_pair('*', 3));
    map.insert(make_pair('/', 3));
    map.insert(make_pair('+', 2));
    map.insert(make_pair('-', 2));
    map.insert(make_pair('(', 1));
    
    LStack<char> char_stack;
    
    for (auto c : aExpression) {// формирование результирующей строки в обратной польской записи
        if (!isalnum(c)) {
            result_pnotation += ' ';
            if (')' == c) {
                while (char_stack.top() != '(') {
                    result_pnotation += char_stack.pop();
                }
                char_stack.pop();
            }
            else if ('(' == c) {
                char_stack.push(c);
            }
            else if (char_stack.empty() 
                || (map[char_stack.top()] <= map[c])) {
                char_stack.push(c);
            }
            else {
                do {
                    result_pnotation += char_stack.top();
                    char_stack.pop();
                } while (!(char_stack.empty() || (map[char_stack.top()] <= map[c])));
                char_stack.push(c);
            }
        }
        else {
            result_pnotation += c;
        }
    }
    while (!char_stack.empty()) {// остаток из стека добавляется в результ. строку
        result_pnotation += ' ';
        result_pnotation += char_stack.top();
        char_stack.pop();
    }

    return result_pnotation;
}

void test(string aFilename)
{
    string path = filesystem::current_path().string();
    string str = readFileStreamIO(path + "\\" + aFilename);
    cout << path << " Your data: " << str << endl;
    string expr = RPN(str);
    cout << "Выражение в польской нотации: " << expr << endl; // результат
    int mm = evaluate(expr);
    cout << "Решение: " << mm << endl; // результат
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    test("\\expression_1.txt");
    test("\\expression_2.txt");
    test("\\expression_3.txt");
    system("PAUSE");
    return 0;
}