#include "array_operations.hh"

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */

int greatest_v1(int* itemptr, int size) {
    int greatest_elem = 0;
    for (int i = 0; i < size; ++i) {
        if (*(itemptr + i) > greatest_elem) {
            greatest_elem = *(itemptr + i);
        }
    }
    return greatest_elem;
};



/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int* itemptr, int* endptr) {
    int greatest_elem = 0;
    for (int* p = itemptr ; p != endptr ; p++) {
        if (*p > greatest_elem) {
            greatest_elem = *p;
        }
    }
    return greatest_elem;
};

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int* itemptr, int* endptr, int* targetptr) {
    int* first = itemptr;
    int* after_last = endptr;
    while (first != after_last) {
        *targetptr++ = *first++;
    }
};

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int* leftptr, int* rightptr) {
    rightptr--;
    while(*leftptr != *rightptr) {
        int templeft = *leftptr;

        int tempright = *rightptr;
        *leftptr = tempright;
        *rightptr = templeft;
        rightptr--;
        leftptr++;
    }

};
