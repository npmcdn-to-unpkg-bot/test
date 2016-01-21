#include <iostream>

void print_array(int* array, unsigned size);

void quick_sort(int* array, int left, int right) {
    if (left < right) {
        int key = array[left];
        int low = left;
        int high = right;
        while (low < high) {
            while (low < high && array[high] > key) {
                high --;
            }
            array[low] = array[high];
            while (low < high && array[low] < key) {
                low ++;
            }
            array[high] = array[low];
        }
        array[low] = key;
        // std::cout << "key:[" << key << "] ";
        // print_array(array, 10);
        quick_sort(array, left, low - 1);
        quick_sort(array, low + 1, right);
    }
}


void print_array(int* array, unsigned size) {
    for (unsigned i=0; i<size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    int array[] = { 5,7,2,6,8,1,9,0,3,4};
    unsigned size = sizeof(array)/sizeof(int);
    print_array(array, size);

    quick_sort(array, 0, size - 1);
    print_array(array, size);
}