#include <iostream>
#include <string>
#include <cctype>

double expression();

char token() {
    char ch;
    std::cin >> ch;
    return ch;
}

double factor() {
    double val = 0;
    char ch = token();
    if (ch == '(') {
        val = expression();
        ch = token();
        if (ch != ')') {
            std::string error = std::string("Expected ')', got: ") + ch;
            throw std::runtime_error(error.c_str());
        }
    }
    else if (isdigit(ch)) {
        std::cin.unget();
        std::cin >> val;
    }
    else throw std::runtime_error("Unexpected character");
    return val;
}

double term() {
    int ch;
    double val = factor();
    ch = token();
    if (ch == '*' || ch == '/') {
        double b = term();
        if (ch == '*')
            val *= b;
        else
            val /= b;
    }
    else std::cin.unget();
    return val;
}

double expression() {
    double val = term();
    char ch = token();
    if (ch == '-' || ch=='+') {
        double b = expression();
        if (ch == '+')
            val += b;
        else
            val -= b;
    }
    else std::cin.unget();
    return val;
}

int main() {
    try {
        std::cout << expression() << std::endl;
    }
    catch(std::exception &e) {
        std::cout << e.what();
    }
    return 0;
}
