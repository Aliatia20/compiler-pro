#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>

using namespace std;

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
            "auto", "break", "case", "char", "const", "continue", "default",
            "do", "double", "else", "enum", "extern", "float", "for", "goto",
            "if", "int", "long", "register", "return", "short", "signed",
            "sizeof", "static", "struct", "switch", "typedef", "union",
            "unsigned", "void", "volatile", "while"
    };
    int i, flag = 0;

    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

bool isOpeningBows(char c) {
    return (c == '(' || c == '{' || c == '[');
}

bool isClosingBows(char c) {
    return (c == ')' || c == '}' || c == ']');
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isPair(char opening, char closing) {
    return ((opening == '(' && closing == ')') ||
            (opening == '{' && closing == '}') ||
            (opening == '[' && closing == ']'));
}

// ...

bool isSyntaxCorrect(string input) {
    stack<char> BowsStack;

    for (char c : input) {
        if (isOpeningBows(c)) {
            BowsStack.push(c);
        } else if (isClosingBows(c)) {
            if (BowsStack.empty() || !isPair(BowsStack.top(), c)) {
                return false;
            }
            BowsStack.pop();
        }
    }

    return BowsStack.empty();
}


// ...


bool endsWithOperator(string input) {
    if (input.empty())
        return false;

    char lastChar = input.back();
    return isOperator(lastChar);
}

int main() {
    //lexical
    char ch, buffer[15], b[30], logical_op[] = "><", math_op[] = "+-*/=", numer[] = ".0123456789", other[] = ",;\\ (){}[]'':";
    int mark[1000] = {0};
    int i, j = 0, kc = 0, ic = 0, lc = 0, mc = 0, nc = 0, oc = 0, aaa = 0;
    vector<string> k;
    vector<char> id;
    vector<char> lo;
    vector<char> ma;
    vector<string> nu;
    vector<char> ot;

    cout << "Enter code (end with ';'):\n";
     string code;
    getline( cin,code);
//check for other
    for (char c : code) {
        for (i = 0; i < 12; ++i) {
            if (c == other[i]) {
                int aa = c;
                if (mark[aa] != 1) {
                    ot.push_back(c);
                    mark[aa] = 1;
                    ++oc;
                }
            }
        }
// check for math operator
        for (i = 0; i < 5; ++i) {
            if (c == math_op[i]) {
                int aa = c;
                if (mark[aa] != 1) {
                    ma.push_back(c);
                    mark[aa] = 1;
                    ++mc;
                }
            }
        }
//check for logical operator
        for (i = 0; i < 2; ++i) {
            if (c == logical_op[i]) {
                int aa = c;
                if (mark[aa] != 1) {
                    lo.push_back(c);
                    mark[aa] = 1;
                    ++lc;
                }
            }
        }
//check for numeric value
        if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.' || c == ' ' || c == '\n' || c == ';') {
            if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.') b[aaa++] = c;
            if ((c == ' ' || c == '\n' || c == ';') && (aaa != 0)) {
                b[aaa] = '\0';
                aaa = 0;
                char arr[30];
                strcpy(arr, b);
                nu.push_back(arr);
                ++nc;
            }
        }
//check for key word
        if (isalnum(c)) {
            buffer[j++] = c;
        } else if ((c == ' ' || c == '\n') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer) == 1) {
                k.push_back(buffer);
                ++kc;
            } else {
                if (buffer[0] >= 97 && buffer[0] <= 122) {
                    if (mark[buffer[0] - 'a'] != 1) {
                        id.push_back(buffer[0]);
                        ++ic;
                        mark[buffer[0] - 'a'] = 1;
                    }
                }
            }
        }
    }

    printf("Keywords: ");
    for (int f = 0; f < kc; ++f) {
        if (f == kc - 1) {
            cout << k[f] << "\n";
        } else {
            cout << k[f] << ", ";
        }
    }
    printf("Identifiers: ");
    for (int f = 0; f < ic; ++f) {
        if (f == ic - 1) {
            cout << id[f] << "\n";
        } else {
            cout << id[f] << ", ";
        }
    }
    printf("Math Operators: ");
    for (int f = 0; f < mc; ++f) {
        if (f == mc - 1) {
            cout << ma[f] << "\n";
        } else {
            cout << ma[f] << ", ";
        }
    }
    printf("Logical Operators: ");
    for (int f = 0; f < lc; ++f) {
        if (f == lc - 1) {
            cout << lo[f] << "\n";
        } else {
            cout << lo[f] << ", ";
        }
    }
    printf("Numerical Values: ");
    for (int f = 0; f < nc; ++f) {
        if (f== nc - 1) {
            cout << nu[f] << "\n";
        } else {
            cout << nu[f] << ", ";
        }
    }
    printf("Others: ");
    for (int f = 0; f < oc; ++f) {
        if (f == oc - 1) {
            cout << ot[f] << "\n";
        } else {
            cout << ot[f] << " ";
        }
    }

//    // Syntax checking


    if (endsWithOperator(code)) {
        cout << "Syntax is Incorrect, ends with an operator" << endl;
    } else if (code.back() == ';') {
        code.pop_back(); // Remove the semicolon from the input

        if (isSyntaxCorrect(code)) {
            cout << "Syntax is Correct" << endl;
        } else {
            cout << "Syntax is Incorrect, missing Closing Bows" << endl;
        }
    }
    else {
        cout << "Syntax is Incorrect, missing semicolon at the end" << endl;
    }

    return 0;
}


