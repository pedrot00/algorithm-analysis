void merge(int *v, int *aux, int p, int q, int r) {
    int n = r - p;

    int it1 = p; 
    int it2 = q;
    int cursor = 0;

    while(it1 < q && it2 < r) {
        if(v[it1] <= v[it2]) {
            aux[cursor++] = v[it1++];
        } else {
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
}

void mergeSort(int *v, int p, int r){
    int n = r - p;
    if(n > 1){
        int meio = (p + r) / 2;

        mergeSort(v, p, meio);
        mergeSort(v, meio, r);

        int *aux = new int[n];
        merge(v, aux, p, meio, r);
        delete[] aux;
    }
}

void mergeSort2(int *v, int n){
    mergeSort(v,0, n);
}
