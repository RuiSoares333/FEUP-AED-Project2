// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include <vector>
#include <unordered_map>

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

using namespace std;

// Classe MinHeap disponibilizada pela UC, nas aulas práticas, com documentação

// Binary min-heap to represent integer keys of type K with values (priorities) of type V
template <class K, class V>
class MinHeap {
    struct Node { // An element of the heap: a pair (key, value)
        K key;
        V value;
    };

    int size;                  // Number of elements in heap
    int maxSize;               // Maximum number of elements in heap
    vector<Node> a;            // The heap array
    unordered_map<K, int> pos; // maps a key into its position on the array a
    const K KEY_NOT_FOUND;

    void upHeap(int i);
    void downHeap(int i);
    void swap(int i1, int i2);

public:
    MinHeap(int n, const K& notFound); // Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
    int getSize();              // Return number of elements in the heap
    bool hasKey(const K& key);  // Heap has key?
    void insert(const K& key, const V& value);      // Insert (key, value) on the heap
    void decreaseKey(const K& key, const V& value); // Decrease value of key
    K removeMin(); // remove and return key with smaller value
};

// ----------------------------------------------

/// Faz um valor "subir a árvore" até chegar à posição pretendida
/// Complexidade Temporal: O(log|V|), where V = stops
/// \param i posição final pretendida
template <class K, class V>
void MinHeap<K,V>::upHeap(int i) {
    while (i>1 && a[i].value < a[PARENT(i)].value) { // while pos smaller than parent, keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}

/// Faz um valor "descer a árvore" até chegar à posição pretendida
/// Complexidade Temporal: O(log|V|), where V = stops
/// \param i posição final pretendida
template <class K, class V>
void MinHeap<K,V>::downHeap(int i) {
    while (LEFT(i) <= size) { // while within heap limits
        int j = LEFT(i);
        if (RIGHT(i)<=size && a[RIGHT(i)].value < a[j].value) j = RIGHT(i); // choose smaller child
        if (a[i].value < a[j].value) break;   // node already smaller than children, stop
        swap(i, j);                    // otherwise, swap with smaller child
        i = j;
    }
}

/// Troca duas posições da heap
/// Complexidade Temporal: O(1)
/// \param i1 posição 1 que queremos alterar
/// \param i2 posição 2 que queremos alterar
// Swap two positions of the heap (update their positions)
template <class K, class V>
void MinHeap<K,V>::swap(int i1, int i2) {
    Node tmp = a[i1]; a[i1] = a[i2]; a[i2] = tmp;
    pos[a[i1].key] = i1;
    pos[a[i2].key] = i2;
}

// ----------------------------------------------

/// Constructor
/// Cria uma min-heap para um máximo de n pares (K, V) com notFound a ser retornado quando a heap está vazia
/// \param n número máximo de pares (K, V) da heap
/// \param notFound mensagem retornada quando a heap está vazia
template <class K, class V>
MinHeap<K,V>::MinHeap(int n, const K& notFound) : KEY_NOT_FOUND(notFound), size(0), maxSize(n), a(n+1) {
}

/// Retorna o número de elementos na heap
/// \return número de elementos na heap
template <class K, class V>
int MinHeap<K,V>::getSize() {
    return size;
}

/// Verifica se uma determinada key está presente na heap
/// Complexidade Temporal: O(|V|), where V = stops
/// \param key key que queremos verificar se está na heap
/// \return true se a key estiver presente na heap, false se não
template <class K, class V>
bool MinHeap<K, V>::hasKey(const K& key) {
    return pos.find(key) != pos.end();
}

/// Insere o par (key, value) na heap
/// Complexidade Temporal: O(|V|), where V = stops
/// \param key key do par a ser inserido
/// \param value valor do par a ser inserido
template <class K, class V>
void MinHeap<K,V>::insert(const K& key, const V& value) {
    if (size == maxSize) return; // heap is full, do nothing
    if (hasKey(key)) return;     // key already exists, do nothing
    a[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}

/// Diminui o valor de determinada key para o valor recebido
/// Complexidade Temporal: O(|V|), where V = stops
/// \param key key a ser alterada
/// \param value valor para o qual queremos alterar
template <class K, class V>
void MinHeap<K,V>::decreaseKey(const K& key, const V& value) {
    if (!hasKey(key)) return; // key does not exist, do nothing
    int i = pos[key];
    if (value > a[i].value) return; // value would increase, do nothing
    a[i].value = value;
    upHeap(i);
}

/// Remove e retorna a key de menor valor
/// Complexidade Temporal: O(log|V|), where V = stops
/// \return key de menor valor
template <class K, class V>
K MinHeap<K,V>::removeMin() {
    if (size == 0) return KEY_NOT_FOUND;
    K min = a[1].key;
    pos.erase(min);
    a[1] = a[size--];
    downHeap(1);
    return min;
}

#endif
