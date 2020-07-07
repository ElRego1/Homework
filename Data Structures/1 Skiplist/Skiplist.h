// Copyright Robert Lica robertlica21@gmail.com
#ifndef SKIPLIST_H__
#define SKIPLIST_H__

#define INITIAL 5

#include <random>
#include "./nodes.h"

template <typename T>
class Skiplist{
    int noLeyers;
    int maximLeyers;
    Node<T> **leyers;

	public:
    Skiplist();

    ~Skiplist();

    Skiplist(const Skiplist &other);

    void addNodeForPoints(Node<T> *nou);

    void addNodeInitialList(T id, T points);

    Node<T>* popNodeByIDandPoints(T id, T points);

    Node<T>* getNodeByID(T id);

    int getPositionOfID(T id);

    void reorderRanking(int *ranking);

    void reorderRankingForOrder(int *ranking_for_order);

	private:
    Node<T>* deleteByNode(Node<T> *toReturn);

    // Functie recursiva de urcat nivele random in skiplist
    void goUpRemastered(Node<T> *nou, T height);

    Node<T>* findUpperLeft(Node<T> *nou, int height);

    // Gaseste nivelul cel mai de jos al skiplist-ului si act mai aproape
    // posibil de nodul cu acel anumit punctaj
    Node<T>* findBottom(T points);

    // cauta dupa ordinea id-urilor unde sa puna nodurile cu acelasi punctaj
    void findPlace(Node<T> *nou, Node<T> *p);

    void findPlaceByID(Node<T> *nou, Node<T> *p);

    void findPlaceLeft(Node<T> *nou, Node<T> *p);

    void findPlaceRight(Node<T> *nou, Node<T> *p);
};

template <typename T>
void cleanNode(Node<T> *nou);

template <typename T>
void insertToLeft(Node<T> *nou, Node<T> *p);

template <typename T>
void insertToRight(Node<T> *nou, Node<T> *p);

#endif  // SKIPLIST_H__
