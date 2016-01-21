#include <iostream>

void heap_adjust(int* array, int current_index, int size) {
    if (current_index < 0 || current_index >= size) {
        return;
    }

    auto l_index = 2 * current_index + 1;
    auto r_index = 2 * current_index + 2;
    // find out the index of max value
    auto max_index = current_index;
    if (l_index < size && array[max_index] < array[l_index]) {
        max_index = l_index;
    }
    if (r_index < size && array[max_index] < array[r_index]) {
        max_index = r_index;
    }

    if (max_index != current_index) {
        std::swap(array[current_index], array[max_index]);
        // adjust child since we swap child with parent
        heap_adjust(array, max_index, size);
    }
}

void initiliaze_heap(int* array, int size) {
    // index i,
    // left = 2*i + 1
    // right: 2*i + 2
    // n is the size of array
    // so the last node with leaves
    // 2*i + 1 = n-1 or 2*i + 2 = n-1 (index starts from 0, max i == n - 1)
    // i = (n-2)/2 = n/2 - 1
    // or
    // i = (n-3)/2 = n/2 - 1
    for (int i = size/2 - 1; i>=0; i--) {
        heap_adjust(array, i, size);
    }
}

void heap_sort(int* array, int size) {
    initiliaze_heap(array, size);

    for (int i = size - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heap_adjust(array, 0, i);
    }
}

void print_array(int* array, int size) {
    if (!array || size < 1) {
        return;
    }

    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    int size = 10;
    int array[size] = { 3, 2, 1, 5, 6, 7, 9, 0, 4, 8};

    print_array(array, size);
    // initiliaze_heap(array, size);
    heap_sort(array, size);
    print_array(array, size);


}