//Özge KATIRCI 
//Melisa DEMÝRHAN

#include <iostream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;
int precedence(char);
bool isValid(string);

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string& s) {
    stack<char> ss;
    string result = "";
  
    if (isValid(s) == false)
    {
        cout << "ERROR! parentheses are not match.\n";
        exit(0);
    }

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-')
        {
            if (ss.empty()) {
                ss.push(s[i]);
                result += ' ';
            }
            else {
                if (precedence(s[i]) > precedence(ss.top())) {
                    ss.push(s[i]);
                    result += ' ';
                }
                else if (precedence(s[i]) == precedence(ss.top())) {
                    result += ' ';
                    result += ss.top();
                    result += ' ';
                    ss.pop();
                    ss.push(s[i]);
                }
                else if (precedence(s[i]) < precedence(ss.top())) {
                    while (!ss.empty() && precedence(s[i]) <= precedence(ss.top())) {
                        result += ' ';
                        result += ss.top();
                        result += ' ';
                        ss.pop();
                    }
                    ss.push(s[i]);
                }
            }
        }
        else if (s[i] == '(') {
            ss.push(s[i]);
        }
        else if (s[i] == ')') {
            while ((ss.top() != '(') && (!ss.empty())) {

                result += ' ';
                result += ss.top();
                result += ' ';
                ss.pop();
            }
            ss.pop();
        }
        else {
            result += s[i];
        }
    }
    while (!ss.empty()) {
        if (ss.top() != '(') {
            result += ' ';
            result += ss.top();
            result += ' ';
        }
        ss.pop();
    }

    return result;
} // end-Infix2Postfix
int precedence(char c) {
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
bool isValid(string s) {
    stack<char> S;
    int a = s.length();

    for (int i = 0; i < a; i++) {
        if (s[i] == '(')
        {
            S.push(s[i]);
           
        }
        else if (s[i] == ')') {

            if (S.empty()) return false;
            char top = S.top();
            S.pop();

            if (s[i] == ')' && top != '(') return false;
        }//end-else
    } //end-for

    if (S.empty()) return true;
    else           return false;
} //end-isValid

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
    stack<string> ss;
    string s2 = "";

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '*')
        {
            int a, b;
            a = stod(ss.top());
            ss.pop();
            b = stod(ss.top());
            ss.pop();
            stringstream c;
            c << a * b;
            string sc;
            c >> sc;
            ss.push(sc);
        }
        else if (s[i] == '/')
        {
            int a, b;
            a = stod(ss.top());
            ss.pop();
            b = stod(ss.top());
            ss.pop();
            stringstream c;
            c << b / a;
            string sc;
            c >> sc;
            ss.push(sc);
        }
        else if (s[i] == '+')
        {
            int a, b;
            a = stod(ss.top());
            ss.pop();
            b = stod(ss.top());
            ss.pop();
            stringstream c;
            c << a + b;
            string sc;
            c >> sc;
            ss.push(sc);
        }
        else if (s[i] == '-')
        {
            int a, b;
            a = stod(ss.top());
            ss.pop();
            b = stod(ss.top());
            ss.pop();
            stringstream c;
            c << b - a;
            string sc;
            c >> sc;
            ss.push(sc);
        }
        else if (s[i] != ' ')
        {
            s2 += s[i];
        }
        else if (s[i] == ' ' && !s2.empty()) {
            ss.push(s2);
            s2 = "";
        }
    }
    int result = stod(ss.top());

    return result;
} // end-EvaluatePostfixExpression


