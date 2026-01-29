#include <iostream> // for cout, cin, endl
#include <cmath>    // for pow -- the only one you're allowed to use from this lib
#include <iomanip>  // for setprecision, setw -- the only ones you're allowed to use from this lib
using namespace std;

void bubbleSort(int *array, int size);
double average(int *array, int size);
double median(int* array, int size);
double stddev(int* array, int size);

int main() {
    // Sets the printing of floating-point numbers
    // to show only 2 places after the decimal point
    cout << fixed << showpoint;
    cout << setprecision(2);

    int no_grades;
    cout << "Enter number of grades: ";
    cin >> no_grades;

    if (no_grades < 1) {
        cout << "Error!" << endl;
        exit(1);
    }

    int *grades = new int[no_grades];

    cout << "Enter grades (each on a new line):" << endl;
    for (int i = 0; i < no_grades; i++) {
        cin >> grades[i];
    }

    bubbleSort(grades, no_grades);
    cout << "Here are some statistics:" << endl;

    cout << "Average: " << average(grades, no_grades) << endl;
    cout << setw(9) << "Median: " << median(grades, no_grades) << endl;
    cout << setw(9) << "Stddev: " << stddev(grades, no_grades) << endl;

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

double total;
double average(int *array, int size) {
    total = 0;
    for (int i = 0; i < size; i++) {
        total += array[i];
    }
    return total / size;
}

//assumes that arr is sorted
int m;
double median(int* array, int size) {
    m = size / 2;
    if (size % 2) {
        return array[m];
    }
    return (array[m - 1] + array[m]) / 2;
}

double sum_sq, mu, diff;
double stddev(int* array, int size) {
    if (size == 1) {
        return 0;
    }

    mu = average(array, size);
    sum_sq = 0;
    for (int i = 0; i < size; i++) {
        diff = array[i] - mu;
        sum_sq += diff * diff;
    }
    return pow(sum_sq / (size - 1), 0.5);
}