#include <iostream>
#include <cassert>

// Declaração antecipada do template operator<<
template <typename T>
class MyVec;

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVec<T>& vec);

template <class T>
class MyVec {
public:
    // Correção aqui: uso de <> para indicar que é uma função template
    friend std::ostream& operator<< <>(std::ostream& os, const MyVec<T>& vec);

    T &operator[](int pos);
    const T& operator[](int pos) const;

    void push_back(const T&);
    void pop_back() { assert(dataSize != 0); dataSize--; }

    MyVec(int n, const T& init = T());
    MyVec();
    ~MyVec();

    int size() const;
    void resize(int newCapacity, const T& fill = T());

private:
    T* data;
    int dataSize;
    int dataCapacity;

    void create();
    void destroy();
    void resizeCapacity(int newCapacity);
};

// Definição do operador <<
template <class T>
std::ostream& operator<<(std::ostream& os, const MyVec<T>& vec) {
    os << "[ ";
    for (int i = 0; i < vec.size(); ++i) {
        os << vec.data[i] << " ";
    }
    os << "]";
    return os;
}

template <class T>
T& MyVec<T>::operator[](int pos) {
    return data[pos];
}

template <class T>
const T& MyVec<T>::operator[](int pos) const {
    return data[pos];
}

template <class T>
MyVec<T>::MyVec() {
    create();
}

template <class T>
void MyVec<T>::create() {
    data = nullptr;
    dataSize = dataCapacity = 0;
}

template <class T>
void MyVec<T>::destroy() {
    delete[] data;
}

template <class T>
MyVec<T>::MyVec(int n, const T& init) : data(new T[n]), dataSize(n), dataCapacity(n) {
    for (int i = 0; i < n; i++) {
        data[i] = init;
    }
}

template <class T>
MyVec<T>::~MyVec() {
    destroy();
}

template <class T>
int MyVec<T>::size() const {
    return dataSize;
}

template <class T>
void MyVec<T>::resize(int newCapacity, const T& fill) {
    if (newCapacity == dataCapacity) return;

    T* newData = new T[newCapacity];
    dataSize = std::min(dataSize, newCapacity);

    for (int i = 0; i < dataSize; i++) {
        newData[i] = data[i];
    }

    for (int i = dataSize; i < newCapacity; i++) {
        newData[i] = fill;
    }

    destroy();
    data = newData;
    dataCapacity = newCapacity;
}

template <class T>
void MyVec<T>::resizeCapacity(int newCapacity) {
    dataCapacity = newCapacity;
    T* newData = new T[dataCapacity];

    for (int i = 0; i < dataSize; i++) {
        newData[i] = data[i];
    }

    destroy();
    data = newData;
}

template <class T>
void MyVec<T>::push_back(const T& elem) {
    if (size() == dataCapacity) {
        if (dataCapacity == 0) {
            resizeCapacity(1);
        } else {
            resizeCapacity(dataCapacity * 2);
        }
    }
    data[dataSize] = elem;
    dataSize++;
}
