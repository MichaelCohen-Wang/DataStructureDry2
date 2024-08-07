#ifndef HASHNODE_H_
#define HASHNODE_H_

template<typename K, typename V>
class HashNode {
public:
    K key;
    V value;
    HashNode* next;
    HashNode* parent;
    int rank;

    HashNode(const K& key, const V& value)
        : key(key), value(value), next(nullptr), parent(this), rank(0) {}
};

#endif // HASHNODE_H_



