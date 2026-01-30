#include <iostream> // for cout, cin, endl
#include <cmath>    // for pow -- the only one you're allowed to use from this lib
#include <iomanip>  // for setprecision, setw -- the only ones you're allowed to use from this lib
using namespace std;

void bubbleSort(int *array, int size);
double average(int *array, int size);
double median(int* array, int size);
double stddev(int* array, int size);

int main() {
    cout << fixed << showpoint;
    cout << setprecision(2);

    int no_grades;
    cout << "Enter number of grades: ";
    cin >> no_grades;

    if (no_grades < 1) { //must have one or more grades for algorithm to work
        cerr << "Error!" << endl;
        exit(1);
    }

    int *grades = new int[no_grades]; //create new dynamic array with size of no grades

    cout << "Enter grades (each on a new line):" << endl;
    for (int i = 0; i < no_grades; i++) {
        cin >> grades[i];
    }

    bubbleSort(grades, no_grades);
    cout << "Here are some statistics:" << endl;

    cout << "Average: " << average(grades, no_grades) << endl;
    cout << setw(9) << "Median: " << median(grades, no_grades) << endl;
    cout << setw(9) << "StdDev: " << stddev(grades, no_grades) << endl;

    delete[] grades;

    return 0;
}


// This is bubbleSort - it is given for you to use.
// Pre-Condition:: It takes in a dynamic int array and its size
// Post-Condition: It sorts the array in ascending order of its values
void bubbleSort(int *array, int size) {
    int temp;
    for (int i = size-1; i >= 0; i--) {
        for (int j = 1; j <= i; j++) {
        if (array[j-1] > array[j]) {
            temp = array[j-1];
            array[j-1] = array[j];
            array[j] = temp;
        } // if
        } // for j
    } // for i
}

double total; //declare outside to avoid redeclaring each time fn is called
double average(int *array, int size) { //takes in dyn int arr and its size
    total = 0; 
    for (int i = 0; i < size; i++) {
        total += array[i]; //sum each element to running total
    }
    return total / size; //compute and output avg
}

//assumes that arr is sorted
int m; //declare outside to avoid redeclaring each time fn is called
double median(int* array, int size) { //takes in dyn int arr and its size
    m = size / 2;
    if (size % 2) { //if odd num of elements, median is just the middlemost element
        return array[m];
    } //otherwise median is the avg of the two middle elements
    return (array[m - 1] + array[m]) / 2.0;
}

double sum_sq, mu, diff; //declare outside to avoid redeclaring each time fn is called
double stddev(int* array, int size) { //takes in dyn int arr and its size
    if (size == 1) { //to avoid division by zero later along the line
        return 0;
    }

    mu = average(array, size); //calc average outside loop to avoid calling every iter
    sum_sq = 0;
    for (int i = 0; i < size; i++) {
        diff = array[i] - mu;
        sum_sq += diff * diff; //better way to do square
    } //compute and return stddev
    return pow(sum_sq / (size - 1), 0.5);  //doing sqrt with pow
}