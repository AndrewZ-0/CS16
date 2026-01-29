#include <iostream>
#include <string>
using namespace std;

void clean_str(string &str);
void alpha_count_zeros();
bool is_anagram(string str1, string str2);

int main() {
	string str1, str2;
    cout << "Enter first string:" << endl; 
    getline(cin, str1);

    cout << "Enter first string:" << endl; 
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

void clean_str(string &str) {
    int len = str.length();

    char c;
    int i = 0, j = 0;
    while (j < len) {
        c = tolower(str[j]);
        if (isalpha(c)) {
            str[i] = c;
            i++;
        } 
        j++;
    }
    str = str.substr(0, i);
}

int alpha_count[26];
void alpha_count_zeros() {
    for (int i = 0; i < 26; i++) {
        alpha_count[i] = 0;
    }
}

int str1_len;
bool running_is_anagram;
bool is_anagram(string str1, string str2) {
    alpha_count_zeros();

    str1_len = str1.length();
    if (str1_len != str2.length()) {
        return 0;
    }

    for (int i = 0; i < str1_len; i++) {
        alpha_count[str1[i] - 'a']++;
        alpha_count[str2[i] - 'a']--;
    }

    running_is_anagram = 0;
    for (int i = 0; i < 26; i++) {
        running_is_anagram = running_is_anagram || alpha_count[i];
    }

    return !running_is_anagram;
}