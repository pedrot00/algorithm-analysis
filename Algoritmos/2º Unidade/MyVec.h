#include <iostream>
#include <cassert>

template <typename T>
class MyVec;

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVec<T>& vec);


template<class T>
class MyVec{
private:
    T* data;
    int dataSize = 0;
    int dataCapacity = 0;

    /*Ok */ void create();
    /*Ok */ void destroy();
    /*Ok */ void resizeCapacity(int newCapacity);
    /*Ok */ void mergeSort(int inicio, int fim);
    /*Ok */ void merge(int inicio, int meio, int fim);

public:
    /*Ok */ MyVec();
    /*Ok */ MyVec(int n, const T& init);
    /*Ok */ ~MyVec();

    /*Ok */ int size() const;
    /*Ok */ void resize();

    /*Ok */ void push_back(const T& val);
    /*Ok */ void pop_back();
    /*Ok */ void insert(const T& val, int pos);

    /*Ok */ friend std::ostream& operator<< <>(std::ostream& os, const MyVec<T>& vec);
    /*Ok */ T& operator[](int index);
    /*Ok */ const T& operator[](int index) const;

    /*Ok */ void imprimir();
    /*Ok */ void imprimirInverso();

    /*Ok */ void ordenar();
    /*Ok */ int find(const T& elem);
    /*Ok */ bool empty();
};

template<class T>
void MyVec<T>::create(){
    data = nullptr;
    dataSize = 0;
    dataCapacity = 0;
}

template<class T>
void MyVec<T>::destroy(){
    if (data) delete[] data;
}

template<class T>
MyVec<T>::MyVec(){
    create();
}

template<class T>
MyVec<T>::MyVec(int n, const T& init): data(new T[n]), dataSize(n), dataCapacity(n){
   for(int i=0; i<n; i++){
    data[i] = init;
   }
}

template<class T>
MyVec<T>::~MyVec(){
    destroy();
}

template<class T>
int MyVec<T>::size() const{
    return dataSize;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const MyVec<T>& vec) {
    os << "[ ";
    for (int i = 0; i < vec.size(); ++i) {
        os << vec.data[i] << " ";
    }
    os << "]";
    return os;
}

template<class T>
T& MyVec<T>::operator[](int pos){
    return data[pos];
}

template<class T>
const T& MyVec<T>::operator[](int pos) const{
    return data[pos];
}

template<class T>
void MyVec<T>::push_back(const T& val){
    if(size() == dataCapacity){
        if(size() == 0){
            resizeCapacity(1);
        }
        else{
            resizeCapacity(dataCapacity * 2);
        }
    }
    data[dataSize] = val;
    dataSize++;
}

template<class T>
void MyVec<T>::pop_back(){
    if(size() == 0){return;}
    dataSize--;
}

template<class T>
void MyVec<T>::insert(const T& val, int pos){
    if(pos < 0 || pos > size()){
        std::cout<<"Indice nao existe";
        return;
    }
    if(size() == dataCapacity){
        resize();
    }

    dataSize++;
    for(int i = size()-1; i> pos; i--){
        data[i] = data[i-1];
    }
    data[pos] = val;
}

template <class T>
void MyVec<T>::resize(){
    resizeCapacity(2*dataCapacity);
}

template <class T>
void MyVec<T>::resizeCapacity(int newCapacity){
    dataCapacity = newCapacity;
    T* newData = new T[dataCapacity];

    for(int i = 0; i<size(); i++){
        newData[i] = data[i]; 
    }
    destroy();
    data = newData;
}

template<class T>
void MyVec<T>::imprimir(){
    std::cout << "[";
    for(int i=0; i<size(); i++){
        std::cout << data[i] << " ";
    }
    std::cout<< "]" << std::endl;
}

template<class T>
void MyVec<T>::imprimirInverso(){
     std::cout << "[";
    for(int i = size()-1; i>=0; i--){
        std::cout << data[i] << " ";
    }
    std::cout<< "]" << std::endl;
}

template<class T>
bool MyVec<T>::empty(){
    return (size() == 0);
}

template<class T>
int MyVec<T>::find(const T& elem){
    for(int i=0; i<size(); i++){
        if(data[i] == elem){
            return i;
        }
    }
    return -1;
}

template<class T>
void MyVec<T>::ordenar(){
    mergeSort(0, size()-1);
}

template <class T>
void MyVec<T>::mergeSort(int inicio, int fim){
    if (inicio >= fim) return; 
    int meio = inicio + (fim - inicio) / 2;
   
    mergeSort(inicio, meio);
    mergeSort(meio + 1, fim);
    merge(inicio, meio, fim);
}

template <class T>
void MyVec<T>::merge(int inicio, int meio, int fim){
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    
    T* tempEsq = new T[n1];
    T* tempDir = new T[n2];
    
    for (int i = 0; i < n1; i++)
        tempEsq[i] = data[inicio + i];
    for (int j = 0; j < n2; j++)
        tempDir[j] = data[meio + 1 + j];

    int i = 0, j = 0, k = inicio; 
    
    while (i < n1 && j < n2) {
        if (tempEsq[i] <= tempDir[j]) {
            data[k] = tempEsq[i];
            i++;
        } else {
            data[k] = tempDir[j];
            j++;
        } 
        k++;
    }
    
    while (i < n1) {
        data[k] = tempEsq[i];
        i++; 
        k++;
    }
    while (j < n2) {
        data[k] = tempDir[j];
        j++; 
        k++;
    }
    delete[] tempEsq;
    delete[] tempDir;
}