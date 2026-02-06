#include <iostream> // for cin, cout, endl
#include <cstdlib>  // for exit()

using namespace std;

typedef unsigned int uint; //my coping mechanism for not being able to use size_t

int bin2d(string binstring);
string dec2bh(string sdec, char bh);
string dec2b(string sdec);
string dec2h(string sdec);

int main(int argc, char *argv[]) {
    if (argc != 3) { //must be 3 elements: program name, options and value
        cerr << "Usage: converter <options: d2b, d2h, b2d> <value>" << endl;
        exit(1);
    }

    //select type of conversion based on second element in argv (1st element is name of program)
    string fn_type = argv[1];
    if (fn_type == "d2b") {
        cout << dec2bh(argv[2], 'b') << endl;
    } else if (fn_type == "d2h") {
        cout << dec2bh(argv[2], 'h') << endl;
    } else if (fn_type == "b2d")  {
        int dec = bin2d(argv[2]);
        if (dec == -1) { //if bin2d found invalid inputs
            cerr << "Binary value contains non-binary digits." << endl;
            exit(1);
        }
        cout << dec << endl;
    } else { //if not one of the three options
        cerr << "Usage: converter <options: d2b, d2h, b2d> <value>" << endl;
        exit(1);
    }

    return 0;
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

//Pre-Conditions: takes in an int of the binary (assumes 0 or 1 else UB)
//Post-Conditions: casts to char
char int2bin(int val) {
    return val + '0';
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
        bin = int2bin(quotient % 2) + bin;
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

string fast_dec2bh(string sdec, char bh) {
    int quotient = sdec2d(sdec);

    if (!quotient) return "0";

    string based = "";

    int base_shift = (bh == 'b')? 1 : 4;
    int mod_mask = 2 << (base_shift - 1);

    while (quotient > 0) { 
        based = int2bin(quotient & mod_mask) + based;
        quotient >>= base_shift; 
    }

    return based;
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