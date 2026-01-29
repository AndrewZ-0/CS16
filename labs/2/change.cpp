#include <iostream>
using namespace std;

int quarters, dimes, pennies; //decided to raise qdp to global scope to avoid boilerplate. 

//calculate the number of quarters, dimes and pennies (qdp) required to satisfy "amount"
void calc_qdp(int amount) {
    int quarter_remainder; //temp variable for storing remainder from calculating no. quarters

    quarters = amount / 25;
    quarter_remainder = amount % 25;
    dimes = quarter_remainder / 10;
    pennies = quarter_remainder % 10;
}

//print functions for singular and plural forms of quarters, dimes and pennies
void printq() {
    cout << quarters << " quarter";
    if (quarters > 1) {
        cout << "s"; //print extra "s" on the end to pluralise
    }
}
void printd() {
    cout << dimes << " dime";
    if (dimes > 1) {
        cout << "s"; //print extra "s" on the end to pluralise
    }
}
void printp() {
    cout << pennies << " penn";
    if (pennies > 1) {
        cout << "ies"; //pluralise
    } else {
        cout << "y"; //singular
    }
}
void printc(int c) {
    cout << " cent";
    if (c > 1) {
        cout << "s"; //pluralise
    }
}

//calculate qdp and print formatted results (w. commas when necessary)
void compute_coins(int amount) {
    calc_qdp(amount);

    cout << amount;
    printc(amount);
    cout << " can be given in ";

    bool has_comma = 0; //bool flag which tracks if there is already something printed earlier: in which case there needs to be a comma
    if (quarters) { //q is always first so doesn't need comma
        has_comma = 1; //if q is printed, then next will always need a comma
        printq();
    }
    if (dimes) {
        if (has_comma) {
            cout << ", "; //has_comma is already 1 so no need to set it again
        } else {
            has_comma = 1; //bc. (d==1 && !has_comma) == 1 so need comma for next regardless
        }
        printd();
    }
    if (pennies) {
        if (has_comma) {
            cout << ", "; //no need for else here bc. p is the last one
        }
        printp();
    }

    cout << "." << endl;
}

int main() {
    int amount; //declared amount here bc. model version of compute_coins has amount passed in as param. Though this could be in global scope for consistancy.

    while (1) { //trust in the process bro... 
        cout << "Enter number of cents (or zero to quit):" << endl; 
        cin >> amount; 

        if (!amount) {
            break; //amount is 0 so break from while loop; 
        }
        if (amount > 0 && amount < 100) { //in range: compute_coins then run loop again
            compute_coins(amount);
        } else { //out of range error, run loop again
            cout << "Amount is out of bounds. Must be between 1 and 99." << endl;
        }
    }

    return 0;
}