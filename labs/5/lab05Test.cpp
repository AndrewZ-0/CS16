// IMPORTANT NOTE TO USER: 
// The only parts of the program that you should change are:
// 1. The function definitions that are currently on lines 30-32.
// 2. The addition of more test cases in the main() function.
// PLEASE LEAVE ALL OTHER CODE (especially the ASSERT_EQUAL() functions) AS-IS!
//
#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>
#include <vector>
// YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER LIBRARY!!! (zero grade penalty)

using namespace std;

// FYI, templates are a way to make a variable type "flexible".
// We'll cover these at some point, but for now just leave these alone.
template <typename T>
void ASSERT_EQUAL(T, T);

template <typename T>
void ASSERT_EQUAL(const vector<T>&, const vector<T>&);

// FUNCTION DECLARATIONS: YOU MUST DEFINE AND USE THESE IN THE TESTS (do not remove):
vector<string> split(string target, string delimiter);
int bin2d(string binstring);
string dec2bh(string sdec, char bh);


//Pre-Condition: inp a target str which contains the substr as well as the delimiter as a str
//Post-Conditions: returns a vector of the substrings, not excluding empty strings
vector<string> split(string target, string delimiter) {
    uint end = target.length();

    vector<string> out;

    char delimit = delimiter[0]; //assuming that delimiter only has one char
    uint n; //number of characters since last_start
    uint last_start = 0; //keep track of the last element where the new substr should start (inc)
    for (uint i = 0; i < end; i++) {
        if (target[i] == delimit) {
            n = i - last_start; //get last_start->i (inc, exc)
            if (n) { 
                out.push_back(target.substr(last_start, n));
            }
            last_start = i + 1; //make last start the next element after the delimiter
        }
    }
    n = end - last_start;
    if (n) { //put last substr into the vec (since there might not be a delimiter at end of target)
        out.push_back(target.substr(last_start, end - last_start));
    }

    return out;
}


//Pre-Conditions: takes in a string (which should ideally contain only '0', or '1' chars)
//Post-Conditions: if not just bin chars, output -1, else compute the denary equiv to the bin and return said val
int bin2d(string binstring) {
    int acc = 0; //folds onto accumulator 
    for (char e: binstring) { //iter from lost significant to least significant bits
        acc *= 2; //left shift more significant digits so that least sigificant can be occupied by curr e
        if (e != '0' && e != '1') {
            return -1; //if not binary numeric chars
        }
        acc += e - '0'; //if '0', then results in 0, if '1', then results in 1
    }
    return acc;
}

//Pre-Conditions: takes in a string (ideally containing only '0' -> '9' chars and only +ve)
//Post-Conditions: if not just numeric chars, output -1, else convert the denary string into an int
int sdec2d(string sdec) { //basically the same algo as bin2d except with base 10
    int acc = 0;
    for (char e: sdec) { //really should be const char but I don't think Prof Matni has taught us that
        acc *= 10; //effectively moves all other digits to left to open up rightmost digit to be added
        if (e < '0' || e > '9') {
            return -1; //if not denary numeric chars
        }
        acc += e - '0'; //manual cast to an int (which assumes clean input, else UB)
    }
    return acc;
}

//Pre-Conditions: takes in a string of the denary (ideally containing only '0' -> '9' chars and only +ve)
//Post-Conditions: computes binary equiv of the str denary
string dec2b(string sdec) {
    int quotient = sdec2d(sdec); //get sdec as str

    if (!quotient) {
        return "0"; //if the original val is 0, special case: return 0 as str
    }

    //mod the denary val/quotient (from prev computes) to check if curr pow of 2 is (1 or 0)
    //add str ver of result to the front of the bin str (since we are going from least significant bit to most)
    //right shift the val/quotient to get remove influence of lowest power of 2.
    //continue iterating until quotient is 0 (until the most significant bit has been added to bin str)
    //(theoretically algorithm cannot produce -ve vals, but > operator is used just in case of a cosmic ray bit flip or smthing)
    string bin = "";
    while (quotient > 0) { 
        bin = to_string(quotient % 2) + bin;
        quotient /= 2; 
    }

    return bin;
}

//Pre-Conditions: takes in a denary val as int (assumes that val is within range 0->15 inc, otherwise UB)
//Post-Conditions: returns val in hex as a char
//   -> basically a manual cast of int -> hex where vals (strictly) greater than 9 are assigned upper letters in inc ord from 'A'
char int2hex(int val) {
    if (val < 10) { //0->9 inc
        return val + '0'; //manual ascii conversion of numerics
    } 

    return val - 10 + 'A'; //10-15 inc (and beyond which we don't care)
}

//Pre-Conditions: takes in the denary val as str (ideally containing only '0' -> '9' chars and only +ve)
//Post-Conditions: computes and returns the hex equiv to the denary as str 
string dec2h(string sdec) {
    int quotient = sdec2d(sdec); //get sdec as int

    //special case: if val is 0, return '0' 
    if (!quotient) { //otherwise while loop never runs and "" is returned which is ! intended
        return "0";
    }

    //exactly the same algo as for bin but just base 16
    string hex = "";
    while (quotient > 0) {
        hex = int2hex(quotient % 16) + hex; //uses bespoke int2hex conversion fn defined above
        quotient /= 16;
    }

    return hex;
}

//Pre-Conditions: takes in the denary val as str (ideally containing only '0' -> '9' chars and only +ve)
//   -> and a char 'b' or 'h' which indecates which base to conver into to
//   -> assuming that bh is always 'b' or 'h' due to options in calls hard coded
//Post-Conditions: computes and returns the bin/hex equiv to the denary as str 
string dec2bh(string sdec, char bh) {
    if (bh == 'b') { //for bin
        return dec2b(sdec);
    } else { //for hex
        return dec2h(sdec);
    }
}

int main() {
    cout << "Testing split..." << endl;    
    vector<string> answer;

    // Testing split function
    answer = {"Apples", "Bananas", "Cherries", "Dragon Fruits", "Elderberries"};
    ASSERT_EQUAL(answer, split("Apples,Bananas,Cherries,Dragon Fruits,Elderberries", ","));

    answer = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    ASSERT_EQUAL(answer, split("The quick brown fox jumps over the lazy dog", " "));

    answer = {"It w", "s r", "re, I w", "s there."};
    ASSERT_EQUAL(answer, split("It was rare, I was there.", "a"));

    answer = {"Can you hear me?", " - The Machine"};
    ASSERT_EQUAL(answer, split("\"Can you hear me?\" - The Machine", "\""));


    // Feel free to add additional test cases and edge cases
    // answer = {}
    // ASSERT_EQUAL(answer, split("", ""));


    cout << endl << "Testing bin2d..." << endl;
    // Testing binary to decimal
    ASSERT_EQUAL(0, bin2d("0"));
    ASSERT_EQUAL(2, bin2d("10"));
    ASSERT_EQUAL(9,bin2d("1001"));
    ASSERT_EQUAL(45,bin2d("101101"));
    ASSERT_EQUAL(246, bin2d("11110110"));

    cout << "Testing dec2hb..." << endl;
    // Testing decimal to binary
    ASSERT_EQUAL(string("1010"), dec2bh("10", 'b'));
    ASSERT_EQUAL(string("1111"), dec2bh("15", 'b'));
    ASSERT_EQUAL(string("1100100"), dec2bh("100", 'b'));

    // Testing decimal to hex conversion
    ASSERT_EQUAL(string("A"), dec2bh("10", 'h'));
    ASSERT_EQUAL(string("64"), dec2bh("100", 'h')); 

    // Feel free to add additional test cases and edge cases
    // ASSERT_EQUAL(string("64"), dec2bh("100", 'h')); 


    return 0;
}


// Template function to compare expected and actual values.
// If the values match, it prints a "PASSED" message; otherwise, a "FAILED" message.
template <typename T>
void ASSERT_EQUAL(T expected, T actual) {
    if (expected == actual) {
        cout << "PASSED: Expected and actual values are equal: " << expected << endl;
    } else {
        cout << "FAILED: Expected " << expected << " but got " << actual << endl;
    }
}

template <typename T>
void ASSERT_EQUAL(const vector<T>& expectation, const vector<T>& actuality) {
    T expect;
    T actual;
    if (expectation.size() != actuality.size()) {
	    cout << "FAILED: Expected vector of size " << expectation.size() << " but got " << actuality.size() << endl;
	    return;
    }
    for (size_t i = 0; i < min(expectation.size(), actuality.size()); i++) {
	    expect = expectation[i];
	    actual = actuality[i];
    	if (expect == actual) continue;
        cout << "FAILED: With index=" << i << ", Expected " << endl << "\t\"" << expect << "\"\n" << "\tbut got " << endl << "\t\"" << actual << "\"\n";
	    return;
    }

    cout << "PASSED: Expected and actual values are equal:";
    for (const T& expect: expectation) cout << endl << "\t" << expect;
    cout << endl << endl;    
}



