#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
//Boiler plate and general structure created using chatgpt, full implementation is original
class Parser {
public:
    // Constructor
    Parser(const std::string& expr) {}

    // Member function to evaluate the expression
    int evaluate(std::string expression) {
        size_t index=0;
        double result = parseNumber(expression, index);  // Get the first number

        while (index < expression.size()) {
            index++;
            char op = expression[index];  // Get the operator

            if (op == '+' || op == '-' || op == '*' || op == '/') {
                index++;  // Skip the operator
                int nextNumber = parseNumber(expression,index);
                switch (op) {
                    case '+':
                        result += nextNumber;
                        break;
                    case '-':
                        result -= nextNumber;
                        break;
                    case '*':
                        result *= nextNumber;
                        break;
                    case '/':
                        if (nextNumber != 0) {
                            result /= nextNumber;
                        } else {
                            std::cerr << "Error: Division by zero!" << std::endl;
                            return 0;  // or handle error as needed
                        }
                        break;
                }
            } else {
                break;  // No more valid operators
            }
        }

        return result;
    }

private:

    // Helper function to parse a number inside curly braces
    int parseNumber(std::string expression, size_t &index) {
        while (index < expression.size() && expression[index] != '{') {
            index++;  // Skip whitespace
        }

        if (expression[index] == '{') {
            index++;  // Skip opening '{'
            int result = 0;

            // Extract the number inside the curly braces
            while (index < expression.size() && std::isdigit(expression[index])) {
                result = result * 10 + (expression[index] - '0');
                index++;
            }

            if (expression[index] == '}') {
                index++;  // Skip closing '}'
            }
            return result;
        }

        std::cerr << "Error: Expected number inside {}" << std::endl;
        return 0;  // Return a default error value
    }
};

int main() {
    std::string expr = "{15} * {15}";
    Parser parser(expr);
    int result = parser.evaluate(expr);
    std::cout<<result<<std::endl;

    return 0;
}