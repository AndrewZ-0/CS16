#include <iostream>
#include <string>
using namespace std;

void clean_str(string &str);
void alpha_count_zeros();
bool is_anagram(string &str1, string &str2);

int main() {
	string str1, str2;
    cout << "Enter first string:" << endl; 
    getline(cin, str1);

    cout << "Enter second string:" << endl; 
    getline(cin, str2);
    
    clean_str(str1);
    clean_str(str2);

    if (is_anagram(str1, str2)) {
        cout << "The strings are anagrams." << endl;
    } else {
        cout << "The strings are not anagrams." << endl;
    }

    return 0;
}

void clean_str(string &str) { //call by reference to modify the string in place (to avoid having to declare new str)
    int len = str.length(); //store the len prior to using it in the while loop (avoids calling .length every iter)

    char c; //moved declration outside loop to avoid redoing it every iter
    int j = 0; //declaration is outside so j is in scope when using substr
    for (int i = 0; i < len; i++) { 
        c = str[i];
        if (isalpha(c)) { //check first if char is alpha
            str[j] = tolower(c); //then lower if upper 
            j++; //count valid characters
        } 
    }
    str = str.substr(0, j); //get the clean substr which has been moved forward, taking the spot of invalid chars
}

int alpha_count[26];
void alpha_count_zeros() {
    for (int i = 0; i < 26; i++) {
        alpha_count[i] = 0; 
    }
}

int str1_len;
bool running_is_anagram;
bool is_anagram(string &str1, string &str2) { //call by ref: even though the values are not modified, ref is almost always more efficient
    alpha_count_zeros(); //reset the alpha count arr before starting in case is_anagrams is run multiple times

    str1_len = str1.length();
    if (str1_len != str2.length()) {
        //base case: if the two strs are different in length, we know for certain that the counts won't match
        //this condition must be enforced because the algo only iterates up to str1_len for both 
        //so if str2 is longer, then not all chars are counted, if str2 is shorter, you are summing noise from ram
        return 0;
    }

    //first string adds count and second subtracts
    //if by the end, both counts sum to 0 (equilbrium), that means that counts are equal.
    //if this is true for all letters of the alphabet, then the two are anagrams
    for (int i = 0; i < str1_len; i++) {
        alpha_count[str1[i] - 'a']++; //convert chars to indicies 0->a and 25->z by exploiting ascii and auto typecast
        alpha_count[str2[i] - 'a']--;
    }

    running_is_anagram = 0; //cumulative boolean flag for checking if all characters have reached equilibrium
    for (int i = 0; i < 26; i++) {
        running_is_anagram = running_is_anagram || alpha_count[i]; //logial or retains 0's by the end only if every element is 0
    }

    return !running_is_anagram; //if all zeros, then is anagram so return 1 else return 0.
}

//gigachad alternative: 
// -> doesn't care if strings are not cleaned 
// -> does everything with fewest number of loops
// -> no new memory allocation inside fn whatsoever
// -> zero selection so zero branch prediction therefore max speed
// -> no helper or built in functions (aside from length)
// -> causes hella memory corruption if user inputs big UTF chars (i.e punishes user if they type wierd stuff)
unsigned char c;
size_t idx, len, len1, len2; //reused global vars like a boss
bool acc;
int8_t tiny_alpha_count[26]; //cache friendly arr to reduce cache misses
bool is_dirty_str_anagram(string &str1, string &str2) {
    for (idx = 0; idx < 26; tiny_alpha_count[idx++] = 0);

    len1 = str1.length();
    len2 = str2.length();
    len = len1 ^ ((len1 ^ len2) & -(len1 < len2)); //branchless max fn equiv

    for (idx = 0; idx < len; idx++) {
        c = str1[idx] | 32; //force lower by bitmask
        tiny_alpha_count[c - 'a'] += (c >= 'a' && c <= 'z'); //branchless range check and possible mem corruption if idx out of bounds

        c = str2[idx] | 32;
        tiny_alpha_count[c - 'a'] -= (c >= 'a' && c <= 'z');
    }

    acc = 0; 
    for (idx = 0; idx < 26; idx++) acc |= tiny_alpha_count[idx];
    return !acc;
}