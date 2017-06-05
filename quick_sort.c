#include <stdio.h>

void adjust_array(int array[], int length, int start) {
    int tmp;
    for (int i=start; i<=length/2-1; ) {
        if (array[2*i+1] > array[i] || 2*i+2 < length \
            && array[2*i+2] > array[i]) {
            tmp = array[i];
            if (2*i + 2 < length && array[2*i+2] > array[2*i+1]) {
                array[i] = array[2*i+2];
                array[2*i+2] = tmp;
                i = 2*i + 2;
            } else {
                array[i] = array[2*i+1];
                array[2*i+1] = tmp;
                i = 2*i + 1;
            }
        } else {
            break;
        }
    }
}

void quick_sort(int array[], int length) {
    int tmp;
	for (int i=length/2-1; i>=0; i--) {
        if (array[2*i+1] > array[i] || 2*i+2 < length \
            && array[2*i+2] > array[i]) {
            tmp = array[i];
            if (2*i + 2 < length && array[2*i+2] > array[2*i+1]) {
                array[i] = array[2*i+2];
                array[2*i+2] = tmp;
                adjust_array(array, length, 2*i+2);
            } else {
                array[i] = array[2*i+1];
                array[2*i+1] = tmp;
                adjust_array(array, length, 2*i+1);
            }
        }
    }
    for (int i=0; i<length; i++) {
        tmp = array[length-i-1];
        array[length-i-1] = array[0];
        array[0] = tmp;
        adjust_array(array, length-i-1, 0);
    }
}

int main() {
    int array[] = {2, 99, 5, 6, 2, 33, 4, 27, 3, 3, 53, 18};
    quick_sort(array, 12);
    for (int i=0; i<12; i++) {
        printf("%d  ", array[i]);
    }
    printf("\n");

    return 0;
}
