#include <iostream>
using namespace std;

int q, d, p;

void calc_qdp(int amount) {
    int qr;

    q = amount / 25;
    qr = amount % 25;
    d = qr / 10;
    p = qr % 10;
}

void printq() {
    cout << q << " quarter";
    if (q > 1) cout << "s"; 
}
void printd() {
    cout << d << " dime";
    if (d > 1) cout << "s";
}
void printp() {
    cout << p << " penn";
    if (p > 1) cout << "ies";
    else cout << "y";
}

void compute_coins(int amount) {
    calc_qdp(amount);

    cout << amount << " cents can be given in ";

    bool has_comma = 0;
    if (q) {
        has_comma = 1; 
        printq();
    }
    if (d) {
        if (has_comma) cout << ", ";
        else has_comma = 1;
        printd();
    }
    if (p) {
        if (has_comma) cout << ", ";
        printp();
    }

    cout << "." << endl;
}

int main() {
    int amount;

    while (1) {
        cout << "Enter number of cents (or zero to quit):" << endl; 
        cin >> amount; 

        if (!amount) break;
        if (amount > 0 && amount < 100) compute_coins(amount);
        else cout << "Amount is out of bounds. Must be between 1 and 99" << endl;
    }

    return 0;
}
