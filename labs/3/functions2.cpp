#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

#include "constants.h"

//alternative with some good old-fashioned for loop abuse
//(assumes if I/O is not broken: so cout is cast to true always)


void getArray(ifstream& in, string fname, int arr[], int size) {
    for (int i = !((in.open(fname), in.fail()) && (exit((cerr << "Input file opening failed.\n", 1)), 0)); i < size; in >> arr[i++]);
}

void print_array(int arr[], int asize) {
    for (int cond = 1, i = 0; cond || !(cout << endl); cout << arr[i++] && (cond = i < asize && cout << ", "));
}



