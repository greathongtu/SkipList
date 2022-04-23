//
// Created by nicol on 2022/4/22.
//

#ifndef SKIPLIST_V3_NODE_H
#define SKIPLIST_V3_NODE_H

#include <iostream>
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

template<typename K,typename V>
class SkipList;

template<typename K,typename V>
class Node{
    friend class SkipList<K, V>;

public:
    Node() = default;

    Node(K k, V v);

    K getKey() const;

    V getValue() const;

private:
    K key;
    V value;
    vector<shared_ptr<Node<K, V>>>  forward;
    int nodeLevel;

    void createNode(int level, shared_ptr<Node<K, V>>& node);
    void createNode(int level, shared_ptr<Node<K, V>>& node, K key, V value);
};

template<typename K, typename V>
Node<K, V>::Node(K k, V v) {
    key = k;
    value = v;
}

template<typename K, typename V>
K Node<K, V>::getKey() const {
    return key;
}

template<typename K, typename V>
V Node<K, V>::getValue() const {
    return value;
}

template<typename K, typename V>
void Node<K, V>::createNode(int level, shared_ptr<Node<K, V>> &node) {
    node = std::make_shared<Node<K, V>>();
    node -> forward = vector<shared_ptr<Node<K, V>>>(level, nullptr);
    node ->nodeLevel = level;
}

template<typename K, typename V>
void Node<K, V>::createNode(int level, shared_ptr<Node<K, V>>& node , K key, V value) {
    node = std::make_shared<Node<K, V>>(key,value);
    node -> forward = vector<shared_ptr<Node<K, V>>>(level, nullptr);
    node ->nodeLevel = level;

    // node == nullptr ?
}




#endif //SKIPLIST_V3_NODE_H
