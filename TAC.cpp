#include <iostream>
#include <vector>
using namespace std;

int main() {
    string expr;
    cout << "Enter expression: ";
    cin >> expr;

    vector<string> v;

    // Convert each character into string
    for (char ch : expr) {
        v.push_back(string(1, ch));
    }

    int temp = 1;

    // First handle * and /
    for (int i = 0; i < v.size(); i++) {

        if (v[i] == "*" || v[i] == "/") {

            string ans = "t" + to_string(temp);

            cout << ans << " = "
                 << v[i - 1] << " "
                 << v[i] << " "
                 << v[i + 1] << endl;

            // Replace a*b with t1
            v[i - 1] = ans;

            v.erase(v.begin() + i);     // remove operator
            v.erase(v.begin() + i);     // remove right operand

            temp++;
            i = 0;
        }
    }

    // Then handle + and -
    for (int i = 0; i < v.size(); i++) {

        if (v[i] == "+" || v[i] == "-") {

            string ans = "t" + to_string(temp);

            cout << ans << " = "
                 << v[i - 1] << " "
                 << v[i] << " "
                 << v[i + 1] << endl;

            v[i - 1] = ans;

            v.erase(v.begin() + i);
            v.erase(v.begin() + i);

            temp++;
            i = 0;
        }
    }

    cout << "Final Result: " << v[0];

    return 0;
}
