#include "Header.h"

int calculator(char a) {
    if (a == '*' || a == '/') {
        return 2;
    }
    else if (a == '+' || a == '-') {
        return 1;
    }
    else 
        return 0;
}

void change(string a) {
    stack<char> sk;
    string ans;
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] == ' ') {
            a.erase(i, 1);
        }
    }
    for (int i = 0; i < a.length(); ++i) {
        char c = a[i];
        if (c >= '0' && c <= '9') {
            ans += c;
        }
        else if (c == '(') {
            sk.push('(');
        }
        else if (c == ')') {
            while (!sk.empty() && sk.top() != '(') {
                char temp = sk.top();
                sk.pop();
                ans += temp;
            }
            sk.pop();
        }
        else {
            while (!sk.empty() && calculator(a[i]) <= calculator(sk.top())) {
                char tmp = sk.top();
                sk.pop();
                ans += tmp;
            }
            sk.push(c);
        }
    }
    while (!sk.empty()) {
        char tmp = sk.top();
        sk.pop();
        ans += tmp;
    }
    cout << "RPN: ";
    for (int i = 0; i < ans.length(); ++i) {
        cout << ans[i] << " ";
    }
}
