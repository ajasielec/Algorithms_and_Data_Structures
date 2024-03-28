#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


double findMax(const vector<double>& numbers) {
	//Wyszukuje najwiêkszy element w ci¹gu liczb rzeczywistych
	double max = numbers[0];		//Z³o¿onoœæ O(1)

	for (const auto& element : numbers) {
		if (element > max) {
			max = element;			//Z³o¿onoœæ 0(1)
		}
	}

	return max;						//Z³o¿onoœæ 0(1)
}


//quick sort
int partition(int arr[], int start, int end){
    int pivot = arr[start];                 //Z³o¿onoœæ O(1)
    int count = 0;                          //Z³o¿onoœæ O(1)
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;                        //Z³o¿onoœæ O(1)
    }
    int pivotIndex = start + count;         //Z³o¿onoœæ O(1)
    swap(arr[pivotIndex], arr[start]);      //Z³o¿onoœæ O(3)
    int i = start, j = end;                 //Z³o¿onoœæ O(2)

    while (i < pivotIndex && j > pivotIndex) {
        while (arr[i] <= pivot) {
            i++;                            //Z³o¿onoœæ O(1)
        }
        while (arr[j] > pivot) {
            j--;                            //Z³o¿onoœæ O(1)
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);       //Z³o¿onoœæ O(3)
        }
    }
    return pivotIndex;                      //Z³o¿onoœæ O(1)
}

void quickSort(int arr[], int start, int end){
    if (start >= end)
        return;                             //Z³o¿onoœæ O(1)
    int p = partition (arr, start, end);    //Z³o¿onoœæ O(1)
    quickSort(arr, start, p - 1);           //Z³o¿onoœæ O(1)
    quickSort(arr, p + 1, end);             //Z³o¿onoœæ O(1)
}

void sortujOdwrotniePosortowane(int tab[], int rozmiar) {
    for (int i = 0; i < rozmiar/2; i++) {
        swap(tab[i], tab[rozmiar - 1 - i]); //Z³o¿onoœæ O(3)
    }
}

int main()
{
    vector<double> numbers = { 1.7755, 2.894, 66.63, 17.834 };
    cout << findMax(numbers);


    int arr[] = {9, 8, 4, 3, 2, 1};
    int n = 6;
    sortujOdwrotniePosortowane(arr, n);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}

