//DO NOT MODIFY THIS FILE

void print_array(int arr[], int asize);
// Pre-Condition: takes in an integer array and its size.
// Post-Condition: prints all elements in the array.

int maxArray(int arr[], int asize);
// Pre-Condition: takes in an integer array and its size.
// Post-Condition: returns the maximum number in the array.

int minArray(int arr[], int asize);
// Pre-Condition: takes in an integer array and its size.
// Post-Condition: returns the minimum number in the array.

int sumArray(int arr[], int asize);
// Pre-Condition: takes in an integer array and its size.
// Post-Condition: returns the sum of the array.

void evensArray(int arr[], int asize);
// Pre-Condition: takes in an integer array and its size.
// Post-Condition: prints all the even numbers in the array.

void primesArray(int arr[], int asize);
// Pre-Condition: takes in an integer array and its size
// Post-Condition: prints all the prime numbers in the array.

int SeqSearch(int arr[], int array_size, int target);
// Pre-Condition: takes in an integer array, its size, and an int target.
//                  This function must be called within AllSearches().
// Post-Condition: if the function finds "target", it returns its index in the array, otherwise it returns -1.
//                  the function only takes ONE integer (at a time) when searching.

void AllSearches(int array[], int array_size);
// Pre-Condition: runs a loop of SeqSearch() of an array, given the array and its size.
//                  This function has to call on SeqSearch() function.
// Post-Condition: outputs either of the following for every iteration of the loop:
//              Looking for <search parameter>. Not found
//              Looking for <search parameter>. Found at index: <index value>

void getArray(ifstream& in, string fname, int arr[], int size);
// IMPORTANT NOTE: This function has been defined for you in the functions_skeleton.cpp file!
//
// Pre-Condition: takes in an ifstream object for input file, a string for an input filename, an integer array and its size
// Post-Condition: the array will be populated with all the numbers from the input file
