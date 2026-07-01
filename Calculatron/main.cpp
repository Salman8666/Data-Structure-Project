#include <iostream>
#include <vector>
#include "Queue.h"
#include "Stack.h"

using namespace std;


 // Returns precedence of operators

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}


 // Checks if character is an operator

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}


  //Removes all spaces from an expression

string removeSpaces(const string& exp) {
    string cleaned = "";
    for (char c : exp) {
        if (c != ' ')
            cleaned += c;
    }
    return cleaned;
}


 // Converts Infix expression to Postfix

string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";

    for (char c : infix) {

        // If operand, add to postfix
        if (isdigit(c)) {
            postfix += c;
        }

        // If opening bracket, push to stack
        else if (c == '(') {
            s.push(c);
        }

        // If closing bracket, pop until '('
        else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(')
                postfix += s.pop();
            s.pop(); // Remove '('
        }

        // If operator
        else if (isOperator(c)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(c))
                postfix += s.pop();
            s.push(c);
        }
    }

    // Pop remaining operators
    while (!s.isEmpty())
        postfix += s.pop();

    return postfix;
}


 // Evaluates a Postfix expression

int evaluatePostfix(string postfix) {
    vector<int> stk;

    for (char c : postfix) {

        // If digit, push to stack
        if (isdigit(c)) {
            stk.push_back(c - '0');
        }

        // If operator, apply operation
        else {
            int b = stk.back(); stk.pop_back();
            int a = stk.back(); stk.pop_back();

            switch (c) {
                case '+': stk.push_back(a + b); break;
                case '-': stk.push_back(a - b); break;
                case '*': stk.push_back(a * b); break;
                case '/':
                    if (b == 0) throw runtime_error("Division by zero");
                    stk.push_back(a / b);
                    break;
                case '%':
                    if (b == 0) throw runtime_error("Modulo by zero");
                    stk.push_back(a % b);
                    break;
            }
        }
    }
    return stk.back();
}

/*--------------------------------------------------
  Main Driver Function
--------------------------------------------------*/
int main() {

    Queue expressionQueue;      // Stores incoming expressions
    vector<int> results;        // Stores evaluated results
    string longestExpression = "";

    int choice;

    do {
        cout << "\n--- calculaTRON Menu ---\n";
        cout << "1. Add Expression\n";
        cout << "2. Process Expression\n";
        cout << "3. Display Queue\n";
        cout << "4. Display Longest Expression\n";
        cout << "5. Show Results\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        // Add new expression
        if (choice == 1) {
            string exp;
            cout << "Enter expression: ";
            cin.ignore();
            getline(cin, exp);

            exp = removeSpaces(exp);   // REMOVE ALL SPACES
            expressionQueue.enqueue(exp);

            if (exp.length() > longestExpression.length())
                longestExpression = exp;
        }

        // Process next expression
        else if (choice == 2) {
            if (expressionQueue.isEmpty()) {
                cout << "Queue is empty!\n";
            } else {
                try {
                    string infix = expressionQueue.dequeue();
                    string postfix = infixToPostfix(infix);
                    int ans = evaluatePostfix(postfix);
                    results.push_back(ans);

                    cout << "Processed: " << infix << " = " << ans << endl;
                }
                catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
            }
        }

        // Display queue
        else if (choice == 3) {
            cout << "Current Queue: ";
            expressionQueue.display();
        }

        // Display longest expression
        else if (choice == 4) {
            cout << "Longest Expression: " << longestExpression << endl;
        }

        // Display all results
        else if (choice == 5) {
            cout << "Results: ";
            for (int r : results)
                cout << r << " ";
            cout << endl;
        }

    } while (choice != 0);

    return 0;
}
