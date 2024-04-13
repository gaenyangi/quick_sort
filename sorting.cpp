#include<iostream>
#include<fstream>
#include<cstdlib>

class Sorting { // sorting class implementing all 3 kinds of sorting methods as static function
public:

    /*-----------------------swap function------------------------*/

    static void swap(int* a, int* b) { // swap 2 input element's value
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    /*-----------------------median function------------------------*/

    static int median(int a, int b, int c) { // function for finding median of 3 input numbers
        if ((a <= b && b <= c) || (c <= b && b <= a)) { return b; }
        else if ((b <= a && a <= c) || (c <= a && a <= b)) { return a; }
        else { return c; }
    }

    /*-----------------------naive quick sort------------------------*/

    static int partition(int* unsorted, int start, int end) { //parition the given array based on comparing to pivot, and return the index of pivot's right position
        int pivot = unsorted[end]; // set the pivot as end of the array
        int i = start - 1;

        for (int j = start; j <= end - 1; j++) { // j is for scan array, i is the last index of left sub array
            if (unsorted[j] < pivot) { // if some element is less than pivot, put in in the left sub array
                i++;
                swap(&unsorted[i], &unsorted[j]); // switch the first element right sub array and j so the boundary of left sub array increased by 1.
            }
        }

        unsorted[end] = unsorted[i + 1]; // after full divide, set the pivot's right position and return
        unsorted[i + 1] = pivot;
        return i + 1;
    }

    static void nquick_sort(int* unsorted, int start, int end) {
        if (start < end) {
            int q = partition(unsorted, start, end);
            nquick_sort(unsorted, start, q-1);
            nquick_sort(unsorted, q+1, end);
        }
    }

    /*----------------randomized quick sort : median of 3 method------------------------*/

    static int rand_partition(int* unsorted, int start, int end) { // partition functoin for setting pivot as median of 3

        int rand1 = start + rand() % (end - start + 1); //get 3 random numbers
        int rand2 = start + rand() % (end - start + 1);
        int rand3 = start + rand() % (end - start + 1);

        int pivot = median(unsorted[rand1], unsorted[rand2], unsorted[rand3]); // set the median value as pivot
        int pivot_index = 0;

        if (pivot == unsorted[rand1]) { pivot_index = rand1; }
        else if (pivot == unsorted[rand2]) { pivot_index = rand2; }
        else { pivot_index = rand3; }

        swap(&unsorted[pivot_index], &unsorted[end]); // swap the last element with pivot, and use the same partition function above.

        return partition(unsorted, start, end); 

    }

    static void rquick_sort(int* unsorted, int start, int end) {
        if (start < end) {
            int q = rand_partition(unsorted, start, end);
            rquick_sort(unsorted, start, q - 1);
            rquick_sort(unsorted, q + 1, end);
        }
    }

    /*-----------------------------------Tail recursive quick sort (for better space complexity) -----------------------------------*/


    static void tquick_sort(int* unsorted, int start, int end) { // tail recursive quick sort
        while (start < end) {
            int q = rand_partition(unsorted, start, end); // use the randomized partition method to avoid worst case
            if (q - start < end - q) {
                tquick_sort(unsorted, start, q - 1);
                start = q + 1; // set the start as the first index of smaller sub array, and partition large one smaller again.
            }
            else {
                tquick_sort(unsorted, q + 1, end);
                end = q - 1;
            }
        }
    }

};

int main(int argc, char* argv[]) { // execute in CLI with "compiledname", "inputfile", "outputfile"

    /*----------check number of arguments -------------------------------------------------*/

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    /*------------------------check input file opened--------------------------------------*/

    std::ifstream input_file(argv[1]);

    if (!input_file.is_open()) {
        std::cerr << "Error opening input file: " << argv[1] << std::endl;
        return 1;
    }

    /*------------------------------get data from input.txt---------------------------*/

    int input_size;
    input_file >> input_size; // get the number of input (first line)

    int* input_array = new int[input_size]; // array for storing unsorted numbers

    for (int i = 0; i < input_size; ++i) { // get the unsorted numbers (second line)
        input_file >> input_array[i];
    }

    input_file.close();

    /*-------------copy the input value for each method --------------*/

    int* naive_input = new int[input_size];
    int* rand_input = new int[input_size];
    int* tailrecur_input = new int[input_size];

    for (int i = 0; i < input_size; ++i) {
        naive_input[i] = input_array[i];
        rand_input[i] = input_array[i];
        tailrecur_input[i] = input_array[i];
    }

    /*------------------------------- sort -----------------------------------------*/

    Sorting::nquick_sort(naive_input, 0, input_size-1);
    Sorting::rquick_sort(rand_input, 0, input_size-1);
    Sorting::tquick_sort(tailrecur_input, 0, input_size-1);

    /*---------------make the output.txt and check ------------------*/

    std::ofstream output_file(argv[2]);

    if (!output_file.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    /*--------------------print naive quick sort values --------------------------------*/

    for (int i = 0; i < input_size - 1; ++i)
        output_file << naive_input[i] << " ";
    output_file << naive_input[input_size - 1] << std::endl;

    /*--------------------print randomized quick sort values --------------------------------*/

    for (int i = 0; i < input_size - 1; ++i)
        output_file << rand_input[i] << " ";
    output_file << rand_input[input_size - 1] << std::endl;

    /*--------------------print tail recursive quick sort values --------------------------------*/

    for (int i = 0; i < input_size - 1; ++i)
        output_file << tailrecur_input[i] << " ";
    output_file << tailrecur_input[input_size - 1];

    /*------------------- free allocated memory & close output file ---------------------*/

    delete[] input_array;
    delete[] naive_input;
    delete[] rand_input;
    delete[] tailrecur_input;

    output_file.close();

    return 0;
}
