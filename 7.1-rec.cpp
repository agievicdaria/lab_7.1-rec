#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** a, const int rowCount, const int colCount, int i, int j);
void Sort(int **a, const int rowCount, const int colCount, int rowIndex, int colIndex);
void Change(int **a, const int row1, const int row2, const int colIndex, const int colCount);
void Calc(int** a, const int rowCount, const int colCount, int i, int j, int& S, int &k);

void Create(int** a, const int rowCount, const int colCount,
 const int Low, const int High, int i, int j)
{
 a[i][j] = Low + rand() % (High-Low+1);
 if (j<colCount-1) {
     Create(a, rowCount, colCount, Low, High, i, j+1);
 } else if (i<rowCount-1) {
     Create(a, rowCount, colCount, Low, High, i+1, 0);
 }
}

void Print(int** a, const int rowCount, const int colCount, int i, int j) {
 cout << setw(6) << a[i][j];
 if (j<colCount-1) {
     Print(a, rowCount, colCount, i, j+1);
 } else {
     if (i<rowCount-1) {
        cout << endl;
        Print(a, rowCount, colCount, i+1, 0);
     } else {
         cout << endl << endl;
     }
 }
 
}

void Change(int **a, const int row1, const int row2, const int colIndex, const int colCount) {
    if (colIndex < colCount) {
        int tmp = a[row1][colIndex];
        a[row1][colIndex] = a[row2][colIndex];
        a[row2][colIndex] = tmp;

        Change(a, row1, row2, colIndex + 1, colCount);
    }
}

void Sort(int **a, const int rowCount, const int colCount, int rowIndex, int colIndex) {
    if (rowIndex < rowCount - 1) {
        if (colIndex < rowCount - rowIndex - 1) {
            if ((a[colIndex][0] > a[colIndex + 1][0]) ||
                (a[colIndex][0] == a[colIndex + 1][0] &&
                a[colIndex][1] > a[colIndex + 1][1]) ||
                (a[colIndex][0] == a[colIndex + 1][0] &&
                a[colIndex][1] == a[colIndex + 1][1] &&
                a[colIndex][2] > a[colIndex + 1][2])) {
                Change(a, colIndex, colIndex + 1, 0, colCount);
            }
            Sort(a, rowCount, colCount, rowIndex, colIndex + 1);
        } else {
            Sort(a, rowCount, colCount, rowIndex + 1, 0);
        }
    }
}

void Calc(int** a, const int rowCount, const int colCount, int i, int j, int& S, int &k)
{
 if (a[i][j] < 0 && !(a[i][j] % 4 == 0)) {
    S += a[i][j];
    k++; 
    a[i][j] = 0;
 }
 if (j<colCount-1) {
    Calc(a, rowCount, colCount, i, j+1, S, k);
 }
 else if (i<rowCount-1) {
    Calc(a, rowCount, colCount, i+1, 0, S, k);
 }
}

int main() {
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 14;
    int rowCount = 8;
    int colCount = 5;

    int **a = new int *[rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High, 0, 0);
    cout << "Початковий масив:" << endl;
    Print(a, rowCount, colCount, 0, 0);

    int **originalArray = new int *[rowCount];
    for (int i = 0; i < rowCount; i++) {
        originalArray[i] = new int[colCount];
        for (int j = 0; j < colCount; j++) {
            originalArray[i][j] = a[i][j];
        }
    }

    int S = 0;
    int k = 0;

    Calc(a, rowCount, colCount,0, 0, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Масив після заміни нулями:" << endl;
    Print(a, rowCount, colCount, 0, 0);

    Sort(originalArray, rowCount, colCount, 0, 0);
    cout << "Відсортований масив:" << endl;
    Print(originalArray, rowCount, colCount, 0, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    for (int i = 0; i < rowCount; i++)
        delete[] originalArray[i];
    delete[] originalArray;

    return 0;
}