#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print array */
void print_array(int array[], size_t length) {
    for (int i=0; i<length; i++) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

/* heap sort
 *
 * addjust heap
 */
void heap_adjust(int array[], int length, int start) {
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

/* heap sort
 *
 * build heap and adjust heap
 */
void heap_sort(int array[], int length) {
    int tmp;
    for (int i=length/2-1; i>=0; i--) {
        if (array[2*i+1] > array[i] || 2*i+2 < length \
            && array[2*i+2] > array[i]) {
            tmp = array[i];
            if (2*i + 2 < length && array[2*i+2] > array[2*i+1]) {
                array[i] = array[2*i+2];
                array[2*i+2] = tmp;
                heap_adjust(array, length, 2*i+2);
            } else {
                array[i] = array[2*i+1];
                array[2*i+1] = tmp;
                heap_adjust(array, length, 2*i+1);
            }
        }
    }
    for (int i=0; i<length; i++) {
        tmp = array[length-i-1];
        array[length-i-1] = array[0];
        array[0] = tmp;
        heap_adjust(array, length-i-1, 0);
    }
}

/* quik sort */
void quik_sort(int array[], size_t length) {
    int i = 0;
    int j = length - 1;
    int key = array[i];

    if (i >= j) {
        return;
    }

    while(i < j) {
        while(i < j && array[j] >= key) {
            j--;
        }
        array[i] = array[j];
        while(i < j && array[i] <= key) {
            i++;
        }
        array[j] = array[i];
    }
    array[i] = key;
    quik_sort(&array[0], i);
    quik_sort(&array[i+1], length - i - 1);
}

int main() {
    int array[] = {2, 99, 5, 6, 2, 33, 4, 27, 3, 3, 53, 18};
    int nb = sizeof(array);
    int nel = sizeof(array) / sizeof(array[0]);
    int *tmp = malloc(sizeof(array));

    /* test heap sort */
    memcpy(tmp, array, nb);
    heap_sort(tmp, nel);
    printf("heap sort: ");
    print_array(tmp, nel);

    /* test quik sort */
    memcpy(tmp, array, nb);
    quik_sort(tmp, nel);
    printf("quik sort: ");
    print_array(tmp, nel);

    return 0;
}
