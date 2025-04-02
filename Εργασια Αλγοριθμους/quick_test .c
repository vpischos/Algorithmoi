//Prodromos Avramidis 03291 Vasillis Pisxos 03175
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define TIMES 50
#define MAX_SIZE 10000000
#define MIN_SIZE 10000

/* The function inits the array to be sorted */
int *init_array(int size) {
    int *array;
    int i;

    array = malloc(sizeof(int)*size);
    if (array == NULL) {
        exit(43);
    }

    for (i = 0; i < size;i++) {
        array[i] = rand()%(2*size) + 1;
    }

    return array;
}

/* The function inits the array of the potential pivots */
int *generate_pivots(int pivot_size, int size) {
    int *array;
    int i;

    array = malloc(sizeof(int)*pivot_size);
    if (array == NULL) {
        exit(43);
    }

    for (i = 0; i < pivot_size;i++) {
        array[i] = rand()%(size);
    }

    return array;
}

/* The function prints the array */
void print(int *array, int size) {
    int i;

    for (i = 0; i < size; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}

/* The function swaps 2 integers */
void swap(int *one, int *two) {
    int temp;

    temp = *one;
    *one = *two;
    *two = temp;
}

/* The function checks if an array is sorted */
int is_sorted(int *array, int size) {
    int i, errors = 0;

    for (i = 1; i < size; i++) {
        if (array[i]< array[i-1]) {
            errors++;
        }
    }

    return errors;
}

/* Quicksort_1p_l
The function uses quicksort with left element pivot to sort the random array */
void quick_sort(int *array, int start, int end, long unsigned int *assignments, long unsigned int *comparisons) {
    int i,j, pivot;

    if ((*comparisons = *comparisons + 1) && start < end) {
        *assignments = *assignments + 1;
        pivot = array[start];
        i = start;
        j = end;

        while((*comparisons = *comparisons + 1) + 1  && i<j) {

            while((*comparisons = *comparisons + 2) && array[i] <= pivot && i < end) {
                i++;
            }

            while((*comparisons = *comparisons + 1)  && array[j] > pivot) {
                j--;
            }

            if ((*comparisons = *comparisons + 1)  && i < j) {
                *assignments = *assignments + 3;
                swap(&array[i], &array[j]);
            }
        }
        *assignments = *assignments + 3;
        swap(&array[start], &array[j]);

        quick_sort(array,start,j-1, assignments, comparisons);
        quick_sort(array,j+1,end, assignments, comparisons);
    }
}

/* Quicksort_1p_r */
/* The function uses quicksort with a random element as pivot to sort the random array */
void quick_sort_random_one(int *array, int start, int end, long unsigned int *assignments, long unsigned int *comparisons ) {
    int i,j;
    int pivot;
    int random;


    if ((*comparisons = *comparisons + 1) && start < end) {
        *assignments = *assignments + 8;
        random = (rand() % (end - start)) + start;
        swap(&array[start], &array[random]); // we place the random pivot on the left of the array

        i = start;
        j = end;
        pivot = array[start];

        while((*comparisons = *comparisons + 1) && i<j) {

            while((*comparisons = *comparisons + 2) && array[i] <= pivot && i < end) {
                i++;
            }

            while((*comparisons = *comparisons + 1) && array[j] > pivot) {
                j--;
            }

            if ((*comparisons = *comparisons + 1) && i < j) {
                *assignments = *assignments + 3;
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[start], &array[j]);

        quick_sort_random_one(array,start,j-1, assignments, comparisons);
        quick_sort_random_one(array,j+1,end, assignments, comparisons);
    }
}

/* Quicksort_1p_m */
/* The function uses quicksort with the median of three random elements as pivot to sort the random array */
void quick_sort_random_median(int *array, int start, int end, long unsigned int *assignments, long unsigned int *comparisons ) {
    int i,j;
    int pivot;
    int random[3];
    int pivot_options[3];


    if ((*comparisons = *comparisons + 1) && start < end) {
        *assignments = *assignments + 10;

        random[0] = (rand() % (end - start)) + start;
        random[1] = (rand() % (end - start)) + start;
        random[2] = (rand() % (end - start)) + start;

        pivot_options[0] = array[random[0]];
        pivot_options[1] = array[random[1]];
        pivot_options[2] = array[random[2]];

        if ((*comparisons = *comparisons + 2) && pivot_options[0] >= pivot_options[1] && pivot_options[0] <= pivot_options[2]) {
            *assignments = *assignments + 1;
            pivot = pivot_options[0];
            swap(&array[start], &array[random[0]]); // we place the random pivot on the left of the array
        }

        if ((*comparisons = *comparisons + 2) && pivot_options[1] >= pivot_options[0] && pivot_options[1] <= pivot_options[2]) {
            *assignments = *assignments + 1;
            pivot = pivot_options[1];
            swap(&array[start], &array[random[1]]); // we place the random pivot on the left of the array
        }

        if ((*comparisons = *comparisons + 2) && pivot_options[2] >= pivot_options[1] && pivot_options[2] <= pivot_options[0]) {
            *assignments = *assignments + 1;
            pivot = pivot_options[2];
            swap(&array[start], &array[random[2]]); // we place the random pivot on the left of the array
        }


        i = start;
        j = end;
        pivot = array[start];

        while((*comparisons = *comparisons + 1) && i<j) {

            while((*comparisons = *comparisons + 2) && array[i] <= pivot && i < end) {
                i++;
            }

            while((*comparisons = *comparisons + 1) && array[j] > pivot) {
                j--;
            }

            if ((*comparisons = *comparisons + 1) && i < j) {
                *assignments = *assignments + 3;
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[start], &array[j]);

        quick_sort_random_median(array,start,j-1, assignments, comparisons);
        quick_sort_random_median(array,j+1,end, assignments, comparisons);
    }
}

/* Quicksort_2p_r */
/* The function uses quicksort with two random elements as pivots to sort the random array */
void quick_sort_random_two(int *array, int start, int end, long unsigned int *assignments, long unsigned int *comparisons) {
    int l,k,g;
    int pivot1, pivot2;
    int random[2];

    if ((*comparisons = *comparisons + 1) && start < end) {
        *assignments = *assignments + 16;
        random[0] = (rand() % (end - start)) + start;
        random[1] = (rand() % (end - start)) + start;

        swap(&array[start], &array[random[0]]);
        swap(&array[end], &array[random[1]]);

        if ((*comparisons = *comparisons + 1) && array[start] > array[end]) {
            *assignments = *assignments + 3;
            swap(&array[start], &array[end]);
        }

        pivot1 = array[start];
        pivot2 = array[end];

        l = start + 1;
        k = l;
        g = end - 1;

        while ((*comparisons = *comparisons + 1) && k <= g) {
            if ((*comparisons = *comparisons + 1) && array[k] < pivot1) {
                *assignments = *assignments + 3;
                swap(&array[k], &array[l]);
                l++;
            }
            else if ((*comparisons = *comparisons + 1) && array[k] >= pivot2) {
                while((*comparisons = *comparisons + 2) && array[g] > pivot2 && k < g) {
                    g--;
                }
                *assignments = *assignments + 3;
                swap(&array[k], &array[g]);
                g--;

                if ((*comparisons = *comparisons + 1) && array[k] < pivot1) {
                    *assignments = *assignments + 3;
                    swap(&array[k],&array[l]);
                    l++;
                }
            }
            k++;
        }

        l--;
        g++;
        swap(&array[start], &array[l]);
        swap(&array[end], &array[g]);

        quick_sort_random_two(array, start, l-1, assignments, comparisons);
        quick_sort_random_two(array, l+1, g-1, assignments, comparisons);
        quick_sort_random_two(array, g+1, end, assignments, comparisons);
    }
}

/* Quicksort_3p_r */
/* The function uses quicksort with three random elements as pivots to sort the random array */
void quick_sort_random_three(int *array, int start, int end, long unsigned int *assignments, long unsigned int *comparisons ) {
    int i,j,k,l;
    int pivot1, pivot2, pivot3;
    int random[3];

    i = start + 2;
    j = start + 2;
    k = end - 1;
    l = end - 1;

    if ((*comparisons = *comparisons + 1) &&start < end) {
        *assignments = *assignments + 27;

        random[0] = (rand() % (end - start)) + start;
        random[1] = (rand() % (end - start)) + start;
        random[2] = (rand() % (end - start)) + start;

        /* We place the random pivots at the correct positions */
        swap(&array[start], &array[random[0]]);
        swap(&array[start+1], &array[random[1]]);
        swap(&array[end], &array[random[2]]);

        pivot1 = array[start];
        pivot2 = array[start+1];
        pivot3 = array[end];

        //printf("pivot1 %d, pivot2 %d, pivot3 %d\n", pivot1, pivot2, pivot3);

        if ((*comparisons = *comparisons + 1) && pivot1 > pivot3) {
            *assignments = *assignments + 6;
            swap(&array[start], &array[end]);
            swap(&pivot1,&pivot3);
        }

        if ((*comparisons = *comparisons + 1) && pivot1 > pivot2) {
            *assignments = *assignments + 6;
            swap(&array[start], &array[start+1]);
            swap(&pivot1,&pivot2);
        }

        if ((*comparisons = *comparisons + 1) && pivot2 > pivot3) {
            *assignments = *assignments + 6;
            swap(&array[end], &array[start+1]);
            swap(&pivot2,&pivot3);
        }

        while ((*comparisons = *comparisons + 1) && j <= k) {
            while ((*comparisons = *comparisons + 2) && array[j] < pivot2 && j <= k) {
                if ((*comparisons = *comparisons + 1) && array[j] < pivot1) {
                    *assignments = *assignments + 3;
                    swap(&array[i], &array[j]);
                    i++;
                }
                j++;
            }
            while ((*comparisons = *comparisons + 2) && array[k] > pivot2 && j <= k) {
                if (array[k] > pivot3) {
                    *assignments = *assignments + 3;
                    swap(&array[k], &array[l]);
                    l--;
                }
                k--;
            }
            if ((*comparisons = *comparisons + 1) && j <= k) {
                if ((*comparisons = *comparisons + 1) && array[j] > pivot3) {
                    if (array[k] < pivot1) {
                        *assignments = *assignments + 6;
                        swap(&array[j], &array[i]);
                        swap(&array[i], &array[k]);
                        i++;
                    }
                    else {
                        *assignments = *assignments + 3;
                        swap(&array[j], &array[k]);
                    }
                    *assignments = *assignments + 3;
                    swap(&array[k], &array[l]);
                    j++;
                    k--;
                    l--;
                }
                else {
                    if ((*comparisons = *comparisons + 1) && array[k] < pivot1) {
                        *assignments = *assignments + 6;
                        swap(&array[j], &array[i]);
                        swap(&array[i], &array[k]);
                        i++;
                    }
                    else {
                        *assignments = *assignments + 3;
                        swap(&array[j], &array[k]);
                    }
                    j++;
                    k--;
                }
            }
        }
        i--;
        j--;
        k++;
        l++;

        swap(&array[start+1], &array[i]);
        swap(&array[i], &array[j]);
        i--;

        swap(&array[start], &array[i]);
        swap(&array[end], &array[l]);


        quick_sort_random_three(array,start,i-1, assignments, comparisons);
        quick_sort_random_three(array,i+1, j-1, assignments, comparisons);
        quick_sort_random_three(array,j+1, l-1, assignments, comparisons);
        quick_sort_random_three(array, l+1, end, assignments, comparisons);
    }

}

/* The function selects one of the pre-generated random pivots */
int random_selection(int *potential_pivots, int *counter_pivot, int start ,int end, int size, int *potential_pos, long unsigned int *assignments, long unsigned int *comparisons ) {
    int random = 0;

    if ((*comparisons = *comparisons + 1) && *counter_pivot == size) {
        return -1;
    }

    while ((*comparisons = *comparisons + 1) && *potential_pos < size) {
        *assignments = *assignments + 1;
        random = potential_pivots[*potential_pos];
        if ((*comparisons = *comparisons + 1) && random > end) {
            return -1;
        }
        if ((*comparisons = *comparisons + 1) && random > start) {
            *assignments = *assignments + 1;
            potential_pivots[*potential_pos] = -1;
            if ((*comparisons = *comparisons + 1) && *potential_pos == *counter_pivot+1) {
                *counter_pivot+= 1;
            }
            return random;
        }
        *potential_pos+=1;
    }

    return -1;
}


/* The function uses quicksort with three random elements that are generated at the start as pivots to sort the random array */
void quick_sort_three_pre_body(int *array, int *potential_pivots, int *counter_pivot, int size, int start, int end, long unsigned int *assignments, long unsigned int *comparisons ) {
    int i,j,k,l;
    int potential_pos;
    int pivot1, pivot2, pivot3;
    int random[3];

    i = start + 2;
    j = start + 2;
    k = end - 1;
    l = end - 1;
    potential_pos = *counter_pivot;

    if (start < end) {
        *assignments = *assignments + 27;

        random[0] = random_selection(potential_pivots, counter_pivot, start, end, size, &potential_pos, assignments, comparisons);
        random[1] = random_selection(potential_pivots, counter_pivot, start, end, size, &potential_pos, assignments, comparisons);
        random[2] = random_selection(potential_pivots, counter_pivot, start, end, size, &potential_pos, assignments, comparisons);

        if ((*comparisons = *comparisons + 1) && random[0] == -1) {
            *assignments = *assignments + 1;
            random[0] = (rand() % (end - start)) + start;
        }
        if ((*comparisons = *comparisons + 1) && random[1] == -1) {
            *assignments = *assignments + 1;
            random[1] = (rand() % (end - start)) + start;
        }
        if ((*comparisons = *comparisons + 1) && random[2] == -1) {
            *assignments = *assignments + 1;
            random[2] = (rand() % (end - start)) + start;
        }

       /* We place the random pivots at the correct positions */
        swap(&array[start], &array[random[0]]);
        swap(&array[start+1], &array[random[1]]);
        swap(&array[end], &array[random[2]]);

        pivot1 = array[start];
        pivot2 = array[start+1];
        pivot3 = array[end];

        //printf("pivot1 %d, pivot2 %d, pivot3 %d\n", pivot1, pivot2, pivot3);

        if ((*comparisons = *comparisons + 1) && pivot1 > pivot3) {
            *assignments = *assignments + 6;
            swap(&array[start], &array[end]);
            swap(&pivot1,&pivot3);
        }

        if ((*comparisons = *comparisons + 1) && pivot1 > pivot2) {
            *assignments = *assignments + 6;
            swap(&array[start], &array[start+1]);
            swap(&pivot1,&pivot2);
        }

        if ((*comparisons = *comparisons + 1) && pivot2 > pivot3) {
            *assignments = *assignments + 6;
            swap(&array[end], &array[start+1]);
            swap(&pivot2,&pivot3);
        }

        while ((*comparisons = *comparisons + 1) && j <= k) {
            while ((*comparisons = *comparisons + 2) && array[j] < pivot2 && j <= k) {
                if ((*comparisons = *comparisons + 1) && array[j] < pivot1) {
                    *assignments = *assignments + 3;
                    swap(&array[i], &array[j]);
                    i++;
                }
                j++;
            }
            while ((*comparisons = *comparisons + 2) && array[k] > pivot2 && j <= k) {
                if (array[k] > pivot3) {
                    *assignments = *assignments + 3;
                    swap(&array[k], &array[l]);
                    l--;
                }
                k--;
            }
            if ((*comparisons = *comparisons + 1) && j <= k) {
                if ((*comparisons = *comparisons + 1) && array[j] > pivot3) {
                    if (array[k] < pivot1) {
                        *assignments = *assignments + 6;
                        swap(&array[j], &array[i]);
                        swap(&array[i], &array[k]);
                        i++;
                    }
                    else {
                        *assignments = *assignments + 3;
                        swap(&array[j], &array[k]);
                    }
                    *assignments = *assignments + 3;
                    swap(&array[k], &array[l]);
                    j++;
                    k--;
                    l--;
                }
                else {
                    if ((*comparisons = *comparisons + 1) && array[k] < pivot1) {
                        *assignments = *assignments + 6;
                        swap(&array[j], &array[i]);
                        swap(&array[i], &array[k]);
                        i++;
                    }
                    else {
                        *assignments = *assignments + 3;
                        swap(&array[j], &array[k]);
                    }
                    j++;
                    k--;
                }
            }
        }
        i--;
        j--;
        k++;
        l++;

        swap(&array[start+1], &array[i]);
        swap(&array[i], &array[j]);
        i--;

        swap(&array[start], &array[i]);
        swap(&array[end], &array[l]);


        quick_sort_three_pre_body(array, potential_pivots, counter_pivot, size, start, i-1, assignments, comparisons);
        quick_sort_three_pre_body(array, potential_pivots, counter_pivot, size, i+1, j-1, assignments, comparisons);
        quick_sort_three_pre_body(array, potential_pivots, counter_pivot, size, j+1, l-1, assignments, comparisons);
        quick_sort_three_pre_body(array, potential_pivots, counter_pivot, size, l+1, end, assignments, comparisons);
    }
}

void quick_sort_two_pre_body(int *array, int *potential_pivots, int *counter_pivot, int size, int start, int end, long unsigned int *assignments, long unsigned int *comparisons) {
    int l,k,g;
    int pivot1, pivot2;
    int random[2];
    int potential_pos = *counter_pivot;

    if ((*comparisons = *comparisons + 1) && start < end) {
        *assignments = *assignments + 16;
        random[0] = random_selection(potential_pivots, counter_pivot, start, end, size, &potential_pos, assignments, comparisons);
        random[1] = random_selection(potential_pivots, counter_pivot, start, end, size, &potential_pos, assignments, comparisons);

        if ((*comparisons = *comparisons + 1) && random[0] == -1) {
            *assignments = *assignments + 1;
            random[0] = (rand() % (end - start)) + start;
        }
        if ((*comparisons = *comparisons + 1) && random[1] == -1) {
            *assignments = *assignments + 1;
            random[1] = (rand() % (end - start)) + start;
        }

        swap(&array[start], &array[random[0]]);
        swap(&array[end], &array[random[1]]);

        if ((*comparisons = *comparisons + 1) && array[start] > array[end]) {
            *assignments = *assignments + 3;
            swap(&array[start], &array[end]);
        }

        pivot1 = array[start];
        pivot2 = array[end];

        l = start + 1;
        k = l;
        g = end - 1;

        while ((*comparisons = *comparisons + 1) && k <= g) {
            if ((*comparisons = *comparisons + 1) && array[k] < pivot1) {
                *assignments = *assignments + 3;
                swap(&array[k], &array[l]);
                l++;
            }
            else if ((*comparisons = *comparisons + 1) && array[k] >= pivot2) {
                while((*comparisons = *comparisons + 2) && array[g] > pivot2 && k < g) {
                    g--;
                }
                *assignments = *assignments + 3;
                swap(&array[k], &array[g]);
                g--;

                if ((*comparisons = *comparisons + 1) && array[k] < pivot1) {
                    *assignments = *assignments + 3;
                    swap(&array[k],&array[l]);
                    l++;
                }
            }
            k++;
        }

        l--;
        g++;
        swap(&array[start], &array[l]);
        swap(&array[end], &array[g]);

        quick_sort_two_pre_body(array, potential_pivots, counter_pivot, size, start, l-1, assignments, comparisons);
        quick_sort_two_pre_body(array, potential_pivots, counter_pivot, size, l+1, g-1, assignments, comparisons);
        quick_sort_two_pre_body(array, potential_pivots, counter_pivot, size, g+1, end, assignments, comparisons);
    }
}


/* Quicksort_3p_r_pre */
/* The function calls the function uses quicksort with three random elements that are generated at the start as pivots to sort the random array */
void quick_sort_three_pre(int *array, int size, long unsigned int *assignments, long unsigned int *comparisons) {
    int *potential_pivots;
    int pivot_size;
    int counter_pivot  =0;

    pivot_size = round(sqrt(size));

    potential_pivots =  generate_pivots(pivot_size, size);

    quick_sort(potential_pivots,0, pivot_size-1, assignments, comparisons);

    quick_sort_three_pre_body(array, potential_pivots, &counter_pivot, pivot_size, 0, size-1, assignments, comparisons);

    free(potential_pivots);
}


/* Quicksort_2p_r_pre */
/* The function calls the function uses quicksort with two random elements that are generated at the start as pivots to sort the random array */
void quick_sort_two_pre(int *array, int size, long unsigned int *assignments, long unsigned int *comparisons) {
    int *potential_pivots;
    int pivot_size;
    int counter_pivot  =0;

    pivot_size = round(sqrt(size));

    potential_pivots =  generate_pivots(pivot_size, size);

    quick_sort(potential_pivots,0, pivot_size-1, assignments, comparisons);

    quick_sort_two_pre_body(array, potential_pivots, &counter_pivot, pivot_size, 0, size-1, assignments, comparisons);

    free(potential_pivots);
}



int main(int argc, char *argv[]) {
    int size, i = 0;
    int j = 0;
    int *array;
    double total_time = 0;
    //int errors;
    long unsigned int assignments = 0, comparisons = 0;
    clock_t start , end;

    srand(time(0));

    for (j = 0; j <= 6; j++) {
                switch (j)
                {
                case 0: {
                    printf("\n\n\nquick_sort\n");
                    break;
                }
                case 1: {
                    printf("\n\n\nquick_sort_random_one\n");
                    break;
                }
                case 2: {
                    printf("\n\n\nquick_sort_random_median\n");
                    break;
                }
                case 3: {
                    printf("\n\n\nquick_sort_random_two\n");
                    break;
                }
                case 4: {
                    printf("\n\n\nquick_sort_random_two_pre\n");
                    break;
                }
                case 5: {
                    printf("\n\n\nquick_sort_random_three\n");
                    break;
                }
                case 6: {
                    printf("\n\n\nquick_sort_random_three_pre\n");
                    break;
                }
                default:
                    break;
                }
        for (size = MIN_SIZE; size <= MAX_SIZE; size = size*10) {
            printf("\n\n\n####%d####\n", size);
            for (i = 0; i < TIMES; i++) {
                total_time = 0;
                assignments = 0;
                comparisons = 0;
                array = init_array(size);

                switch (j) {

                    case 0: {
                        start = clock();
                        quick_sort(array, 0, size-1, &assignments, &comparisons);
                        end = clock();
                        break;
                    }
                    case 1: {
                        start = clock();
                        quick_sort_random_one(array, 0, size-1, &assignments, &comparisons);
                        end = clock();
                        break;
                    }
                    case 2: {
                        start = clock();
                        quick_sort_random_median(array, 0, size-1, &assignments, &comparisons);
                        end = clock();
                        break;
                    }
                    case 3: {
                        start = clock();
                        quick_sort_random_two(array, 0, size-1, &assignments, &comparisons);
                        end = clock();
                        break;
                    }
                    case 4: {
                        start = clock();
                        quick_sort_two_pre(array, size, &assignments, &comparisons);
                        end = clock();
                        break;
                    }
                    case 5: {
                        start = clock();
                        quick_sort_random_three(array, 0, size-1, &assignments, &comparisons);
                        end = clock();
                        break;
                    }
                    case 6: {
                        start = clock();
                        quick_sort_three_pre(array, size, &assignments, &comparisons);
                        end = clock();
                        break;
                    }
                    default: {
                        break;
                    }
                }

                //errors = is_sorted(array, size);
                //printf("\nerrors %d\n\n", errors);

                double time = (double)(end - start)/ CLOCKS_PER_SEC;

                printf("%02d->%lf->%lu->%lu\n", i, time, assignments, comparisons);
                free(array);

                total_time += time;
            }
            // printf("Total runtime is %lf seconds\n", total_time);
            // average_time = total_time/50;
            // printf("Avergage runtime is %lf\n\n", average_time);
        }
    }


    return 0;
}
