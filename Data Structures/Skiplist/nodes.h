// Copyright Robert Lica robertlica21@gmail.com
#ifndef NODES_H__
#define NODES_H__

#include <iostream>

template <typename T>
struct Node {
    T id, points;
    Node<T> *up;
    Node<T> *right;
    Node<T> *down;
    Node<T> *left;

    Node(T id, T points) {
        this->id = id;
        this->points = points;
        up = nullptr;
        right = nullptr;
        down = nullptr;
        left = nullptr;
    }

    Node(T id, T points, Node<T> *up_, Node<T> *right_,
            Node<T> *down_, Node<T> *left_) {
        this->id = id;
        this->points = points;
        up = up_;
        right = right_;
        down = down_;
        left = left_;
    }
};

#endif  // NODES_H__
