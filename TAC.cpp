#include <bits/stdc++.h>
using namespace std;

int main() {
    string expr;
    cout << "Enter expression: ";
    cin >> expr;

    int tempCount = 1;

    // Process * and /
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '*' || expr[i] == '/') {
            char op = expr[i];
            char left = expr[i - 1];
            char right = expr[i + 1];

            cout << "t" << tempCount << " = " << left << " " << op << " " << right << endl;

            // Replace in expression
            expr.replace(i - 1, 3, "t" + to_string(tempCount));
            tempCount++;
            i = 0; // restart scanning
        }
    }

    // Process + and -
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '+' || expr[i] == '-') {
            char op = expr[i];
            char left = expr[i - 1];
            char right = expr[i + 1];

            cout << "t" << tempCount << " = " << left << " " << op << " " << right << endl;

            expr.replace(i - 1, 3, "t" + to_string(tempCount));
            tempCount++;
            i = 0;
        }
    }

    cout << "Final Result: " << expr << endl;

    return 0;
}