#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of TAC statements: ";
    cin >> n;
    cin.ignore();

    vector<string> code(n);

    cout << "Enter TAC statements:\n";
    for (int i = 0; i < n; i++) {
        getline(cin, code[i]);
    }

    cout << "\nOptimized Code:\n";

    for (auto line : code) {
        string lhs, eq, op1, oper, op2;
        stringstream ss(line);

        ss >> lhs >> eq >> op1 >> oper >> op2;

        // Constant Folding
        if (isdigit(op1[0]) && isdigit(op2[0])) {
            int a = stoi(op1);
            int b = stoi(op2);

            if (oper == "+") cout << lhs << " = " << a + b << endl;
            else if (oper == "-") cout << lhs << " = " << a - b << endl;
            else if (oper == "*") cout << lhs << " = " << a * b << endl;
            else if (oper == "/") cout << lhs << " = " << a / b << endl;
        }
        // Algebraic Simplification
        else if (oper == "*" && op2 == "1") {
            cout << lhs << " = " << op1 << endl;
        }
        else if (oper == "+" && op2 == "0") {
            cout << lhs << " = " << op1 << endl;
        }
        else {
            cout << line << endl;
        }
    }

    return 0;
}