//Project Contributors   
// 1. Momna Abbasi(468297)
// 2. Kainat Ali (468287)

#include <iostream>
#include <stack>
#include <string>
#include <bitset>
#include <cctype>

// Function to convert a binary string to an integer
int binaryToInt(const std::string& binStr) {
    return std::bitset<32>(binStr).to_ulong();  // Converts binary string to an unsigned long
}

// Function to convert an integer to a binary string
std::string intToBinary(int num) {
    return std::bitset<32>(num).to_string();  // Convert integer to a binary string (32 bits)
}

// Function to perform binary operations
int performOperation(int operand1, int operand2, char op) {
    switch(op) {
        case '+': return operand1 + operand2;        // Addition
        case '&': return operand1 & operand2;        // AND
        case '|': return operand1 | operand2;        // OR
        case '^': return operand1 ^ operand2;       // XOR
        default: return 0;
    }
}

// Function to evaluate the binary expression using a stack
std::string evaluateExpression(const std::string& expression) {
    std::stack<int> operands;  // Stack to store operands
    std::stack<char> operators; // Stack to store operators

    // This will process the expression character by character
    std::string token = "";
    for (size_t i = 0; i < expression.length(); ++i) {
        char currentChar = expression[i];
        
        if (std::isdigit(currentChar)) {
            // If the character is a digit, we are reading a binary number
            token += currentChar;
        } else if (currentChar == '+' || currentChar == '&' || currentChar == '|' || currentChar == '^') {
            // If we reach an operator, process the token
            if (!token.empty()) {
                // Convert the token (binary number) to an integer and push to the operand stack
                int operand = binaryToInt(token);
                operands.push(operand);
                token.clear();  // Clear the current token for the next operand
            }
            // Push the operator onto the operator stack
            operators.push(currentChar);
        }
    }

    // Finally, we need to process the last operand
    if (!token.empty()) {
        int operand = binaryToInt(token);
        operands.push(operand);
    }

    // Evaluate the expression by performing operations using the stack
    while (!operators.empty()) {
        int operand2 = operands.top(); operands.pop();
        int operand1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();

        int result = performOperation(operand1, operand2, op);
        operands.push(result);  // Push the result back onto the stack
    }

    // Final result should be the only element in the stack
    return intToBinary(operands.top());
}

int main() {
    std::string expression;

    while (true) {
        std::cout << "Enter a binary expression (e.g., 1010+0110) or 'exit' to quit: ";
        std::getline(std::cin, expression);

        if (expression == "exit") {
            break;  // Exit the loop if the user types 'exit'
        }

        // Check if the input is empty
        if (expression.empty()) {
            std::cout << "Invalid input! Please enter a valid binary expression." << std::endl;
            continue;  // Skip to the next iteration if input is empty
        }

        // Process the expression and get the result
        std::string result = evaluateExpression(expression);
        std::cout << "Result: " << result << std::endl;
    }

    std::cout << "Exiting program." << std::endl;
    return 0;
}
