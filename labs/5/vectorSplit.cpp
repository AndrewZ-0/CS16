#include <iostream> // for cin, cout
#include <vector>   // for vector
#include <string>   // for getline()

using namespace std;

typedef unsigned int uint; //my coping mechanism for not being able to use size_t

vector<string> split(string target, string delimiter);

//Pre-Conditions: inputs str vec to be printed (with at least one element and printable chars)
//Post-Conditions: prints every element in vec with double quotes around each and comma as delimeters (exc last)
void print_vec(vector<string> v) {
    string *p = &v[0]; //curr ptr set to first element
    string *end = p + v.size() - 1;
    for ( ; p < end; p++) { //inc curr pointer up to last element
        cout << "\"" << *p << "\", "; //print val under curr ptr p with double quotes around 
    }
    cout << "\"" << *p << "\"" << endl; //print last element without comma delimiter
}

int main() {
    string target, delimiter; //prealloc space for userinput
    cout << "Enter string to split:" << endl;
    getline(cin, target);

    cout << "Enter delimiter string:" << endl;
    getline(cin, delimiter);

    vector<string> splitted = split(target, delimiter);

    if (splitted.size() < 1) { //if splitted has only one element, then no substrings have been produced
        cout << "No substrings." << endl;
    } else {
        cout << "The substrings are: ";
        print_vec(splitted); //splitted is guarenteed to have at least one element by selection
    }

    return 0;
}

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