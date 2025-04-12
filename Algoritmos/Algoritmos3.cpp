#include <iostream>
#include <cstdlib>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

// ===== ALGORITMOS DE ORDENAÇÃO =====
void bubbleSort(int *v, int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[minPos]) {
                minPos = j;
            }
        }
        swap(v[i], v[minPos]);
    }
}

void insertionSort(int *v, int n) {
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

// Função merge para partes de um vetor
void merge(int *v, int p, int q, int r) {
    int n = r - p;
    int *aux = new int[n];

    int it1 = p; 
    int it2 = q;
    int cursor = 0;

    while(it1 < q && it2 < r) {
        if(v[it1] < v[it2]) {
            aux[cursor++] = v[it1++];
        }
        else {
            aux[cursor++] = v[it2++];
        }
    }

    while(it1 < q) {
        aux[cursor++] = v[it1++];
    }
    while(it2 < r) {
        aux[cursor++] = v[it2++];
    }

    for(int i = 0; i < n; i++) {
        v[p+i] = aux[i];
    }

    delete[] aux;
}

// Merge Sort principal
void mergeSort(int *v, int p, int r) {
    if (r - p > 1) {
        int q = (p + r) / 2;
        mergeSort(v, p, q);
        mergeSort(v, q, r);
        merge(v, p, q, r);
    }
}

// Wrapper para interface uniforme
void mergeSortWrapper(int *v, int n) {
    mergeSort(v, 0, n);
}

// ===== GERADOR DE ARRAY ALEATÓRIO =====
void generateRandomArray(int *arr, int size, int maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, maxVal - 1);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
}

// ===== FORMATA O TEMPO EM SEGUNDOS (0,0000s) =====
string formatTime(double seconds) {
    stringstream ss;
    ss << fixed << setprecision(4) << seconds;
    string timeStr = ss.str();
    replace(timeStr.begin(), timeStr.end(), '.', ',');
    return timeStr + " segundos";
}

// ===== MEDE O TEMPO DE EXECUÇÃO =====
double measureTime(void (*sortFunc)(int*, int), int *arr, int size) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, size);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Uso: " << argv[0] << " [MODO] [TAMANHO] [MAX_VAL]\n";
        cout << "Modos:\n0 -> Todos\n1 -> Bubble\n2 -> Selection\n3 -> Insertion\n4 -> Merge\n";
        return 1;
    }

    int mode = atoi(argv[1]);
    int size = atoi(argv[2]);
    int maxVal = atoi(argv[3]);

    if (size <= 0 || maxVal <= 0) {
        cout << "Erro: Tamanho e valor maximo devem ser > 0\n";
        return 1;
    }

    int *originalArr = new int[size];
    generateRandomArray(originalArr, size, maxVal);

    // --- Modo 0: Testa todos os algoritmos ---
    if (mode == 0) {
        int *arr = new int[size];
        
        // Bubble Sort
        copy(originalArr, originalArr + size, arr);
        double bubbleTime = measureTime(bubbleSort, arr, size);
        cout << "Bubble Sort: " << formatTime(bubbleTime) << "\n";

        // Selection Sort
        copy(originalArr, originalArr + size, arr);
        double selectionTime = measureTime(selectionSort, arr, size);
        cout << "Selection Sort: " << formatTime(selectionTime) << "\n";

        // Insertion Sort
        copy(originalArr, originalArr + size, arr);
        double insertionTime = measureTime(insertionSort, arr, size);
        cout << "Insertion Sort: " << formatTime(insertionTime) << "\n";

        // Merge Sort
        copy(originalArr, originalArr + size, arr);
        double mergeTime = measureTime(mergeSortWrapper, arr, size);
        cout << "Merge Sort: " << formatTime(mergeTime) << "\n";

        delete[] arr;
    }
    // --- Modo 1/2/3/4: Apenas um algoritmo ---
    else {
        int *arr = new int[size];
        copy(originalArr, originalArr + size, arr);

        string algoName;
        double time;

        switch (mode) {
            case 1:
                algoName = "Bubble Sort";
                time = measureTime(bubbleSort, arr, size);
                break;
            case 2:
                algoName = "Selection Sort";
                time = measureTime(selectionSort, arr, size);
                break;
            case 3:
                algoName = "Insertion Sort";
                time = measureTime(insertionSort, arr, size);
                break;
            case 4:
                algoName = "Merge Sort";
                time = measureTime(mergeSortWrapper, arr, size);
                break;
            default:
                cout << "Modo invalido! Use 0-4.\n";
                return 1;
        }

        cout << algoName << ": " << formatTime(time) << "\n";
        delete[] arr;
    }

    delete[] originalArr;
    return 0;
}