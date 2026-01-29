/*
/ Skeleton File for FUNCTIONS.CPP for CS16, UCSB
/ Copyright © 2026 by Ziad Matni. All rights reserved.
/
*/

// DO NOT MODIFY THESE NEXT 5 LINES - DO NOT ADD TO THEM
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

// INCLUDE HEADER FILE(S) HERE:
#include "constants.h"

// The following function is defined for you. ***Do not change it AT ALL.***
//
// Pre-Condition: takes in an ifstream object for input file, 
//              a string for an input filename, an integer array and its size
// Post-Condition: the array will be populated with all the numbers from the input file
void getArray(ifstream& in, string fname, int arr[], int size)
{
    in.open(fname);
    if ( in.fail() ) 
    { 
        cerr << "Input file opening failed.\n"; 
        exit(1); 
    }
    for (int i = 0; i < size; i++)
    {
        in >> arr[i];
    }
}

// Add your 8 functions definitions below:

void print_array(int arr[], int asize) {
    if (asize <= 0) return; //if array is empty, loop won't run but indexing on_less_asize will be a logic error so returning early accounts for this.

    int one_less_asize = asize - 1; //do all but last element
    for (int i = 0; i < one_less_asize; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[one_less_asize] << endl; //ensures only last element does not have comma at end
}

//Based alternative with some good old-fashioned for loop abuse
//(assumes if I/O is not broken: so cout is cast to true always)
void print_array2(int arr[], int asize) {
    for (int cond = 1, i = 0; cond || !(cout << endl); cout << arr[i++] && (cond = i < asize && cout << ", "));
}

int maxArray(int arr[], int asize) {
    int biggest = arr[0]; //assume that first element is the biggest (also that there is at least one element)
    for (int i = 1; i < asize; i++) {
        if (arr[i] > biggest) { //check if there exists a bigger element
            biggest = arr[i]; //if true, replace prev biggest with curr biggest
        }
    }
    return biggest;
}

int minArray(int arr[], int asize) {
    int smallest = arr[0]; //assume that first element is the smallest (also that there is at least one element)
    for (int i = 1; i < asize; i++) { 
        if (arr[i] < smallest) { //check if there exists a smaller element
            smallest = arr[i]; //if true, replace prev smallest with curr smallest
        }
    }
    return smallest;
}

int sumArray(int arr[], int asize) {
    int cumlitive = 0; //inital value to fold onto
    for (int i = 0; i < asize; i++) {
        cumlitive += arr[i]; //sum curr val to running total
    }
    return cumlitive;
}

void evensArray(int arr[], int asize) {
    for (int i = 0; i < asize; i++) {
        int e = arr[i]; //basically for each without for each through the array
        if (!(e % 2)) { //do a divisable by 2 check 
            cout << e << ", "; //if divisable, print element with dilineator
        }
    }
    cout << "end" << endl;
}

//by trial division method
void primesArray(int arr[], int asize) {
    int e; //short for "element"
    bool prime; //boolean flag bc I can't use more elegant solutions since we can't create other fns
    for (int j = 0; j < asize; j++) {
        prime = 1; 
        e = arr[j];

        if (e < 2) {
            prime = 0;
        } else if (e % 2) { //used an additional selection instead of || in if statement to avoid having to not e % 2
            //only have to go up to and including sqrt of each num since:
            // -> larger factors than sqrt(e) will have been covered by smaller factors
            // -> additionally, if the e itself is a square num, it's sqrt itself is a factor which must be accounted for
            for (int i = 3; i * i <= e; i += 2) { //bc even nums are accounted for by prior selection of 2, only odd numbers can be factors
                if (!(e % i)) { //equiv to e % i == 0 due to automatic int->bool casting by cpp
                    prime = 0;
                    break;
                }
            }
        } else if (e != 2) { //special case: 2 is divsable by 2 so it falls through however 2 is prime so we enforce that condition here
            prime = 0;
        }

        if (prime) {
            cout << e << ", "; 
        }
    }
    cout << "end" << endl;
}


//the more elegant fn I was talking about
bool isPrime(int n) {
    if (n < 2) return 0; //return instead of chained if-else 
    if (n % 2) {
        for (size_t i = 3; i * i <= n; i += 2) { //I'm surprised Prof Matni has not taught us size_t yet... Kinda miss being able to use it
            if (!(n % i)) return 0; //return directly which saves an if statement
        }
    }
    if (n != 2) return 0;

    return 1;
}
void primesArray2(int arr[], int asize) {
    int e; //short for "element"
    for (size_t j = 0; j < asize; j++) {
        if (isPrime(arr[j])) {
            cout << e << ", ";
        }
    }
    cout << "end" << endl;
}


//even more elegant solution: Using wheel factorisation method (2, 3, 5)
/*
2 * 3 * 5 = modulo 30
multiples of (2, 3, 5) -> 2 3 4 5 6 8 9 10 12 14 15 16 18 20 21 22 24 25 26 27 28 30
non-multiples -> 1* 7 11 13 17 19 23 29
delta non-mult -> 6* 4 2 4 2 4 6 2
*/ 
//modulo wheel starting with 7 (since 1 is not prime)
//keeps track of diff from numbers eliminated by being multiples of 2,3,5 within mod 30
//so summing each element to i produces the next number guarenteed to not be a multiple of 2, 3 && 5
const int wheel[] = {4, 2, 4, 2, 4, 6, 2, 6}; 
bool isPrime2(int n) {
    if (n == 2 || n == 3  || n == 5) return 1; //selection for base primes

    //n & 1 is the same as n % 2 but just faster (And yes, I know that the compiler probaby optimizes this but this is like one of the first times I get to use it so I got a bit excited)
    if (n < 2 || !(n & 1) || !(n % 3) || !(n % 5)) return 0; //first eliminate multiples of 2, 3, 5 and negative nums + 0 and 1

    int i = 7, j = 0; //start with the next smallest prime
    while (i * i <= n) { //same range as trial division still applies
        if (!(n % i)) return 0; //if is factor, not prime and return
        i += wheel[j++]; //jump through all non-multiples
        j &= 7; //fastest alternative of j %= 8 that I can think of: since 8 is a multiple of 2, applying bitmask is functionally the same since j is only incremented
    }

    return 1; //if not returned already, must be prime
}

                            //bruh
int SeqSearch(int arr[], int array_size, int target) { 
    for (int i = 0; i < array_size; i++) { //basically a linear search
        if (arr[i] == target) { 
            return i; //return idx if target matches curr element
        }
    }
    return -1;
}

                    //BRUH
void AllSearches(int array[], int array_size) {
    int found_idx, target;
    for (int i = 0; i < NSEARCHES; i++) {
        target = SEARCHES[i]; //curr target from constant header
        cout << "Looking for " << target << ".";
        found_idx = SeqSearch(array, array_size, target); //curr output of the search

        if (found_idx == -1) { //deal with case if not found
            cout << " Not Found!" << endl;
        } else { 
            cout << " Found at index: " << found_idx << endl;
        }
    }
}

