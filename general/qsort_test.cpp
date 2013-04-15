#include <iostream>
#include <cstdlib>

using namespace std;

void show_array(int (*array)[2]);
int cmpfunction(const void *a, const void *b);

int main(int argc, char *argv[]) {
    int array[][2] = {{3,7},{2,5},{1,3},{5,6},{9,2}};

    show_array(array);

    qsort(array, 5, sizeof(array[0]), cmpfunction);

    cout << endl;
    show_array(array);

    return EXIT_SUCCESS;
}

void show_array(int (*array)[2]) {
    for(int i=0; i<5; i++) {
        cout << array[i][0] << " " << array[i][1] << endl;
    }
}

int cmpfunction(const void *a, const void *b) {
    int *p1 = (int *)a;
    int *p2 = (int *)b;

    return p1[1] - p2[1];
}
