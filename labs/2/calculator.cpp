#include <iostream>
#include <cstdlib>
using namespace std;

int compute(int a, int b, char op) {
    switch (op) { //match the operator char to one of 4 known operators, else pannic 
        case '+': 
            return a + b;
        case '-':
            return a - b;
        case 'x':
            return a * b;
        case '%':
            if (!b) { //if b is 0, then div by zero err
                cerr << "Cannot divide by zero." << endl;
                exit(1); //as much as I hate exiting from the middle of a code block, this is by far the simplest solution I can think of.
            }
            return a % b; //else, eval as usual
        default:
            cerr << "Bad operation choice." << endl;
            exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Number of arguments is incorrect." << endl;
        exit(1); //this says a lot about society...
    }

    int a = atoi(argv[1]); //char* -> int 
    int b = atoi(argv[3]);
    char op = *argv[2]; //deref the operator char* into a char. Pretty sure this will break if argv[2] is more than one char. But that's not extactly a criteria so. 

    int result = compute(a, b, op);

    cout << result << endl;

    return 0;
}