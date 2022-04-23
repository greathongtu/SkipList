//
// Created by nicol on 2022/4/22.
//

#ifndef SKIPLIST_V3_SKIPLIST_H
#define SKIPLIST_V3_SKIPLIST_H

#include <iostream>
#include <random>
#include "Node.h"

const int MAX_LEVEL =16;

template<typename K,typename V>
class SkipList{

public:
    SkipList();
    bool search(K key) const;

    bool insert(K key, V value);

    bool remove(K key);

    void display_list();

    inline int size(){
        return nodeCount;
    }
    inline int getLevel(){
        return level;
    }

private:
    int level;
    shared_ptr<Node<K, V>> header;
    size_t nodeCount;

    void createList();
    int getRandomLevel();

};

template<typename K, typename V>
void SkipList<K, V>::createList() {
    this->level = 0;

    // create header node
    header->createNode(MAX_LEVEL,header);

    nodeCount = 0;

}

template<typename K, typename V>
SkipList<K, V>::SkipList() {
    createList();
}


template<typename K, typename V>
bool SkipList<K, V>::search(K key) const {
    auto node = header;
    for(int i=level-1;i>=0;i--){
        while(node->forward[i] != nullptr && node->forward[i]->key < key){
            node = node->forward[i];
        }
    }
    node = node ->forward[0];
    if(node != nullptr && node->key == key){
        std::cout<<"key:"<<key<<" found."<<std::endl;
        return true;
    }
    std::cout<<"key:"<<key<<" not found"<<std::endl;
}

template<typename K, typename V>
bool SkipList<K, V>::insert(K key, V value) {
    auto update = vector<shared_ptr<Node<K, V>>>(MAX_LEVEL);
    auto node = header;

    for(int i=level-1;i>=0;i--){
        while(node->forward[i] != nullptr && node->forward[i]->key <key){
            node = node->forward[i];
        }
        update[i] = node;
    }
    node = node -> forward[0];
    if(node != nullptr && node->key == key){
        std::cout<<"key:"<<key<<" already existed."<< std::endl;
        return false;
    }
    int nodeLevel = getRandomLevel();

    // if nodeLevel is higher than current max level

    if(nodeLevel > level){
        for(int i=level;i<nodeLevel;i++){
            update[i] = header;
        }
        level = nodeLevel;
    }

    // create new node
    auto newNode = std::make_shared<Node<K, V>>();
    newNode->createNode(nodeLevel,newNode, key, value);

    //insert the new node into the list
    for(int i=nodeLevel-1; i>=0; i--){
        node = update[i];
        newNode->forward[i]=node->forward[i];
        node->forward[i] = newNode;
    }
    ++nodeCount;
    std::cout<<"key:"<<key<<" insert successfully."<< std::endl;
    return true;
}

template<typename K, typename V>
bool SkipList<K, V>::remove(K key) {
    auto update = vector<shared_ptr<Node<K, V>>>(MAX_LEVEL);
    auto node = header;

    for(int i=level-1;i>=0;i--){
        while(node->forward[i] != nullptr && node->forward[i]->key <key){
            node = node->forward[i];
        }
        update[i] = node;
    }
    node = node -> forward[0];
    if(node == nullptr || node->key != key){
        std::cout<<"key:"<<key<<" do not exist."<< std::endl;
        return false;
    }

    for(int i=0; i<node->nodeLevel; ++i){
        update[i]->forward[i] = node->forward[i];
    }
    node = nullptr;

    //update level
    while(level > 0 && header->forward[level-1] == nullptr){
        --level;
    }
    --nodeCount;
    std::cout<<"key:"<<key<<" delete successfully."<<std::endl;
    return true;
}

template<typename K, typename V>
void SkipList<K, V>::display_list() {
    std::cout << "\n*****Skip List*****\n";
    for(int i=0;i<MAX_LEVEL;i++){
        auto node = header->forward[i];
        std::cout << "Level "<< i << ": ";
        while(node != nullptr){
            std::cout << "(" << node->key << "," << node->value << ");";
            node = node ->forward[i];
        }
        std::cout << std::endl;
    }
}




template<typename K, typename V>
int SkipList<K, V>::getRandomLevel() {
    int k = 1;
    std::mt19937 rng(std::random_device{}());
    while (rng()%2) {
        k++;
    }
    k = k < MAX_LEVEL ? k : MAX_LEVEL;
    return k;
}




#endif //SKIPLIST_V3_SKIPLIST_H
