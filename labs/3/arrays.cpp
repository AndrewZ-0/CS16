// DO NOT MODIFY THESE NEXT 6 LINES - DO NOT ADD TO THEM
#include <iostream> // for cout, cin
#include <fstream>  // for ifstream
#include <cstdlib>  // for exit
using namespace std;
#include "headers.h"    // contains the function declarations
#include "constants.h"  // contains 4 global variables

//DO NOT MODIFY THIS FILE

int main( )
{
    // DO NOT MODIFY THESE NEXT 3 LINES - DO NOT ADD TO THEM
    ifstream ifs;
    int size = MAXSIZE, array[MAXSIZE];
    getArray(ifs, FILENAME, array, size);


    // You will program 8 TASKS here - see the lab description PDF document...
    //
    // hints for the tasks: 
    // all that needs to be in here is simple calls the functions, like these: 
    // in addition to, some print to std.out statements.
    
    print_array(array, size);
    cout << "Max = " << maxArray(array, size) << endl; 
    cout << "Min = " << minArray(array, size) << endl; 
    cout << "Sum = " << sumArray(array, size) << endl; 
    cout << "Evens: ";
    evensArray(array, size);
    cout << "Primes: ";
    primesArray(array, size);
    cout << "Searches:" << endl;
    AllSearches(array, size);

    return 0;
}


