#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <omp.h>

using namespace std;

/*
    INPUT:  N = 5
            Array = [423, 847, 12, 635, 291]  (random values)

    OUTPUT:
            Min: 12         | Time: 0.000001s
            Min (Parallel): 12 | Time: 0.000003s

            Max: 847        | Time: 0.000001s
            Max (Parallel): 847 | Time: 0.000002s

            Sum: 2208       | Time: 0.000001s
            Sum (Parallel): 2208 | Time: 0.000002s

            Avg: 441.6      | Time: 0.000001s
            Avg (Parallel): 441.6 | Time: 0.000002s
*/

void minimum(const vector<int>& arr) {
    int min = INT_MAX;
    double start = omp_get_wtime();
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] < min) min = arr[i];
    cout << "Min: " << min << " | Time: " << omp_get_wtime() - start << "s\n";

    int pMin = INT_MAX;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(min: pMin)
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] < pMin) pMin = arr[i];
    cout << "Min (Parallel): " << pMin << " | Time: " << omp_get_wtime() - start << "s\n\n";
}

void maximum(const vector<int>& arr) {
    int max = INT_MIN;
    double start = omp_get_wtime();
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] > max) max = arr[i];
    cout << "Max: " << max << " | Time: " << omp_get_wtime() - start << "s\n";

    int pMax = INT_MIN;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(max: pMax)
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] > pMax) pMax = arr[i];
    cout << "Max (Parallel): " << pMax << " | Time: " << omp_get_wtime() - start << "s\n\n";
}

void sum(const vector<int>& arr) {
    int sum = 0;
    double start = omp_get_wtime();
    for (int i = 0; i < arr.size(); i++)
        sum += arr[i];
    cout << "Sum: " << sum << " | Time: " << omp_get_wtime() - start << "s\n";

    int pSum = 0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+: pSum)
    for (int i = 0; i < arr.size(); i++)
        pSum += arr[i];
    cout << "Sum (Parallel): " << pSum << " | Time: " << omp_get_wtime() - start << "s\n\n";
}

void average(const vector<int>& arr) {
    float avg = 0;
    double start = omp_get_wtime();
    for (int i = 0; i < arr.size(); i++)
        avg += arr[i];
    cout << "Avg: " << avg / arr.size() << " | Time: " << omp_get_wtime() - start << "s\n";

    float pAvg = 0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+: pAvg)
    for (int i = 0; i < arr.size(); i++)
        pAvg += arr[i];
    cout << "Avg (Parallel): " << pAvg / arr.size() << " | Time: " << omp_get_wtime() - start << "s\n\n";
}

int main() {
    // INPUT: User enters the number of elements
    // Array is auto-filled with random values between 0-999
    int N;
    cout << "Enter number of elements: ";
    cin >> N;                           // e.g. N = 5

    vector<int> arr(N);
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 1000;         // e.g. arr = [423, 847, 12, 635, 291]

    // OUTPUT: Each function prints sequential and parallel results with time
    minimum(arr);   // Min: 12         | Min (Parallel): 12
    maximum(arr);   // Max: 847        | Max (Parallel): 847
    sum(arr);       // Sum: 2208       | Sum (Parallel): 2208
    average(arr);   // Avg: 441.6      | Avg (Parallel): 441.6

    return 0;
}