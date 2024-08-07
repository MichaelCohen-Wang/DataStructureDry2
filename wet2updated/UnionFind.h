#ifndef UNIONFIND_H_
#define UNIONFIND_H_

#include "HashNode.h"
#include "DynamicArray.h"
#include "PrimeHelper.h"
#include <memory>

template<typename K, typename V>
class UnionFind {
private:
    DynamicArray<std::unique_ptr<HashNode<K, V>>> table;
    int capacity;
    int size;

    int hash_function(const K& key) const;
    void resize_table();
    HashNode<K, V>* find_root(HashNode<K, V>* node);
    HashNode<K, V>* find_node(const K& key);

public:
    UnionFind(int capacity = 16);
    ~UnionFind();

    bool insert(const K& key, std::unique_ptr<V> value);
    bool remove(const K& key);
    V* find(const K& key);
    bool unite(const K& key1, const K& key2);
    int get_size() const;
};

template<typename K, typename V>
UnionFind<K, V>::UnionFind(int capacity) : table(PrimeHelper::next_prime(capacity)), capacity(PrimeHelper::next_prime(capacity)), size(0) {
    for (int i = 0; i < capacity; ++i) {
        table.push_back(nullptr);
    }
}

template<typename K, typename V>
UnionFind<K, V>::~UnionFind() {
    // Unique_ptr automatically cleans up the memory
}

template<typename K, typename V>
int UnionFind<K, V>::hash_function(const K& key) const {
    return (key * 2654435761) % capacity;  // Simple hash function using multiplication method
}

template<typename K, typename V>
void UnionFind<K, V>::resize_table() {
    int old_capacity = capacity;
    capacity = PrimeHelper::next_prime(capacity * 2);
    
    DynamicArray<std::unique_ptr<HashNode<K, V>>> new_table(capacity);

    for (int i = 0; i < old_capacity; ++i) {
        std::unique_ptr<HashNode<K, V>> entry = std::move(table[i]);
        while (entry != nullptr) {
            HashNode<K, V>* next = entry->next;
            int new_hash_value = hash_function(entry->key);
            entry->next = new_table[new_hash_value].release();
            new_table[new_hash_value] = std::move(entry);
            entry.reset(next);
        }
    }

    table = std::move(new_table);
}

template<typename K, typename V>
HashNode<K, V>* UnionFind<K, V>::find_root(HashNode<K, V>* node) {
    if (node->parent != node) {
        node->parent = find_root(node->parent);  // Path compression
    }
    return node->parent;
}

template<typename K, typename V>
HashNode<K, V>* UnionFind<K, V>::find_node(const K& key) {
    int hash_value = hash_function(key);
    HashNode<K, V>* entry = table[hash_value].get();

    while (entry != nullptr && entry->key != key) {
        entry = entry->next;
    }

    return entry;
}

template<typename K, typename V>
bool UnionFind<K, V>::insert(const K& key, std::unique_ptr<V> value) {
    if (size >= capacity) {
        resize_table();
    }

    int hash_value = hash_function(key);
    auto new_node = std::unique_ptr<HashNode<K, V>>(new HashNode<K, V>(key, std::move(value)));
    new_node->next = table[hash_value].release();
    table[hash_value] = std::move(new_node);

    ++size;
    return true;
}

template<typename K, typename V>
bool UnionFind<K, V>::remove(const K& key) {
    int hash_value = hash_function(key);
    std::unique_ptr<HashNode<K, V>> entry = std::move(table[hash_value]);
    HashNode<K, V>* prev = nullptr;

    while (entry != nullptr && entry->key != key) {
        prev = entry.get();
        entry.reset(entry->next);
    }

    if (entry == nullptr) {
        return false;
    }

    if (prev == nullptr) {
        table[hash_value].reset(entry->next);
    } else {
        prev->next = entry->next;
    }

    --size;
    return true;
}

template<typename K, typename V>
V* UnionFind<K, V>::find(const K& key) {
    HashNode<K, V>* node = find_node(key);
    if (node != nullptr) {
        return node->value.get();
    }
    return nullptr;
}

template<typename K, typename V>
bool UnionFind<K, V>::unite(const K& key1, const K& key2) {
    HashNode<K, V>* node1 = find_node(key1);
    HashNode<K, V>* node2 = find_node(key2);

    if (node1 == nullptr || node1->key != key1 || node2 == nullptr || node2->key != key2) {
        return false;
    }

    HashNode<K, V>* root1 = find_root(node1);
    HashNode<K, V>* root2 = find_root(node2);

    if (root1 == root2) {
        return true;
    }

    if (root1->rank < root2->rank) {
        root1->parent = root2;
    } else if (root1->rank > root2->rank) {
        root2->parent = root1;
    } else {
        root2->parent = root1;
        root1->rank += 1;
    }

    return true;
}

template<typename K, typename V>
int UnionFind<K, V>::get_size() const {
    return size;
}

#endif // UNIONFIND_H_
