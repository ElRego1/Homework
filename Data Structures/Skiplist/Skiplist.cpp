// Copyright Robert Lica robertlica21@gmail.com
#include "./Skiplist.h"

// ----------------------------------------------------------------------------
// De aici incep metodele PUBLICE
// ----------------------------------------------------------------------------
template <typename T>
Skiplist<T>::Skiplist() {
    noLeyers = 1;
    maximLeyers = INITIAL;
    leyers = new Node<T>*[INITIAL];
    for (int i = 0; i < INITIAL; ++i) leyers[i] = nullptr;
    Node<T> *head = new Node<T>(-1, -1);
    leyers[0] = head;
}

template <typename T>
Skiplist<T>::~Skiplist() {
    while (noLeyers--) {
        Node<T> *p = leyers[noLeyers];
        Node<T> *next;
        while (p) {
            next = p->right;
            delete p;
            p = next;
        }
    }
    delete[] leyers;
}

template <typename T>
Skiplist<T>::Skiplist(const Skiplist &other) {
    Node<T> *p = other.leyers[0];
    while (p->right) {
        p = p->right;
    }
    while (p != other.leyers[0]) {
        this->addNodeInitialList(p->id, p->points);
        p = p->left;
    }
}

template <typename T>
void Skiplist<T>::addNodeForPoints(Node<T> *nou) {
    if (nou) {
        cleanNode(nou);
        if (leyers[0]->right) {
            Node<T> *p = findBottom(nou->points);
            findPlace(nou, p);
        } else {
            leyers[0]->right = nou;
            nou->left = leyers[0];
        }
    goUpRemastered(nou, 1);
    } else {
        // aici as lasa return-ul pe aceeasi linie cu else ul pentru ca este
        // mult mai frumos, dar din pacate s-ar putea ca unii sa asculte
        // numai de checker-ul de codingstyle
        return;
    }
}

template <typename T>
void Skiplist<T>::addNodeInitialList(T id, T points) {
    Node<T> *nou = new Node<T>(id, points);
    if (!nou) {
        fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
        exit(1);
    }
    if (leyers[0]->right) {
        insertToLeft(nou, leyers[0]->right);
    } else {
        leyers[0]->right = nou;
        nou->left = leyers[0];
    }
}

template <typename T>
Node<T>* Skiplist<T>::popNodeByIDandPoints(T id, T points) {
    Node<T> *remember = findBottom(points);
    // Incepem sa ne uitam dupa nodul cu id-ul cautat, il stergem din skiplist
    // si l returnam
    if (id == remember->id) {
        return deleteByNode(remember);
    }
    Node<T> *p;

    p = remember->left;
    while (p && p != leyers[0] && p->points == points) {
        if (id == p->id) {
            return deleteByNode(p);
        }
        p = p->left;
    }
    p = remember->right;
    while (p && p->points == points) {
        if (id == p->id) {
            return deleteByNode(p);
        }
        p = p->right;
    }
    p = leyers[0];
    while (p && p->id != id) {
        p = p->right;
    }
    return deleteByNode(p);
}

template <typename T>
Node<T>* Skiplist<T>::getNodeByID(T id) {
    Node<T> *p = leyers[0]->right;
    while (p && p->id != id) p = p->right;
    return p;
}

template <typename T>
int Skiplist<T>::getPositionOfID(T id) {
    int index = 0;
    Node<T> *p = leyers[0]->right;
    while (p && p->id != id) {
        index++;
        p = p->right;
    }
    if (p) {
        return index;
    } else {
        std::cout << "Nu e bine la get position by id\n";
        return -1;
    }
}

template <typename T>
void Skiplist<T>::reorderRanking(int *ranking) {
    Node<T> *p = leyers[0]->right;
    int index = 0;
    while (p) {
        ranking[index] = p->id - 1;
        ++index;
        p = p->right;
    }
}

template <typename T>
void Skiplist<T>::reorderRankingForOrder(int *ranking_for_order) {
    Node<T> *p = leyers[0]->right;
    int index = 0;
    while (p) {
        ranking_for_order[index] = this->getPositionOfID(index + 1);
        ++index;
        p = p->right;
    }
}
// ----------------------------------------------------------------------------
// De aici incep metodele PRIVATE
// ----------------------------------------------------------------------------
template <typename T>
Node<T>* Skiplist<T>::deleteByNode(Node<T> *toReturn) {
    Node<T> *p = toReturn->up;
    toReturn->up = nullptr;
    toReturn->left->right = toReturn->right;
    if (toReturn->right) toReturn->right->left = toReturn->left;
    char firstTime = 1;
    int h = 1;
    Node<T> *toDelete;

    while (p) {
        toDelete = p;
        p->left->right = p->right;
        if (p->right) {
            p->right->left = p->left;
        } else if (p->left == leyers[h]) {
            if (firstTime) {
                leyers[h - 1]->up = nullptr;
                firstTime = 0;
            }
            delete leyers[h];
            --noLeyers;
        }
        p = p->up;
        ++h;
        delete toDelete;
    }
    return toReturn;
}

template <typename T>
void Skiplist<T>::goUpRemastered(Node<T> *nou, T height) {
    std::random_device rd;
    if (rd() % 2) {
        if (noLeyers == height) {
            ++noLeyers;
            if (noLeyers == maximLeyers) {
                Node<T> ** nouLeyer = new Node<T>*[maximLeyers + INITIAL];
                if (!nouLeyer) {
                    fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
                    exit(1);
                }
                for (int i = 0; i < maximLeyers; ++i) {
                    nouLeyer[i] = leyers[i];
                }
                delete[] leyers;
                leyers = nouLeyer;
                maximLeyers += INITIAL;
            }
            Node<T> *nouHead = new Node<T>(-1, -1);
            if (!nouHead) {
                fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
                exit(1);
            }
            leyers[noLeyers - 1] = nouHead;
            leyers[noLeyers - 2]->up = nouHead;
            nouHead->down = leyers[noLeyers - 2];
        }
        Node<T> *leftUp = findUpperLeft(nou, height);
        Node<T> *nouUp = new Node<T>(nou->id, nou->points, nullptr,
                leftUp->right, nou, leftUp);
        if (!nouUp) {
            fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
            exit(1);
        }
        nou->up = nouUp;
        if (leftUp->right) leftUp->right->left = nouUp;
        leftUp->right = nouUp;
        goUpRemastered(nouUp, height + 1);
    }
}

template <typename T>
Node<T>* Skiplist<T>::findUpperLeft(Node<T> *nou, int height) {
    Node<T> *p = nou->left;
    if (p == leyers[height - 1]) {
        return leyers[height];
    }
    while (p != leyers[height - 1]) {
        if (p->up) {
            return p->up;
        }
        p = p->left;
    }
    return leyers[height];
}

template <typename T>
Node<T>* Skiplist<T>::findBottom(T points) {
    int height = noLeyers - 1;
    Node<T> *p = leyers[height];
    while (p->down) {
        while (p->right) {
            if (!height) {
                break;
            }
            if (p == leyers[height] && p->right->right) {
                p = p->right;
            } else if (p == leyers[height]) {
                p = p->down;
                --height;
                continue;
            }
            if (points < p->points) {
                p = p->right;
            } else if (points > p->points) {
                p = p->left;
                p = p->down;
                --height;
            } else {
                while (p->down) {
                    p = p->down;
                    --height;
                }
            }
        }
        if (p->down && points < p->points) {
            p = p->down;
            --height;
        } else if (p->down) {
            p = p->left->down;
            --height;
        }
    }
    if (p == leyers[0] && p->right) {
        p = p->right;
    } else if (p == leyers[0]) {
    }
    return p;
}

template <typename T>
void Skiplist<T>::findPlace(Node<T> *nou, Node<T> *p) {
    while (p->right) {
        if (nou->points < p->points) {
            p = p->right;
        } else if (nou->points == p->points) {
            findPlaceByID(nou, p);
            return;
        } else {
            insertToLeft(nou, p);
            return;
        }
    }
    if (nou->points < p->points) {
        insertToRight(nou, p);
    } else if (nou->points > p->points) {
        insertToLeft(nou, p);
    } else {
        if (nou->id < p->id) {
            insertToLeft(nou, p);
        } else {
            insertToRight(nou, p);
        }
    }
}

template <typename T>
void Skiplist<T>::findPlaceByID(Node<T> *nou, Node<T> *p) {
    if (nou->id < p->id) {
        findPlaceLeft(nou, p);
    } else if (nou->id > p->id) {
        findPlaceRight(nou, p);
    } else {
        std::cout << "Dc sunt 2 cu id-ul identic????? :(((((\n";
        exit(1);
    }
}

template <typename T>
void Skiplist<T>::findPlaceLeft(Node<T> *nou, Node<T> *p) {
    while (p != leyers[0] && nou->points == p->points && nou->id < p->id) {
        p = p->left;
    }
    insertToRight(nou, p);
}

template <typename T>
void Skiplist<T>::findPlaceRight(Node<T> *nou, Node<T> *p) {
    while (p->right && nou->points == p->points && nou->id > p->id) {
        p = p->right;
    }
    if (p->right) {
        insertToLeft(nou, p);
    } else {
        if (nou->points == p->points) {
            if (nou->id < p->id) {
                insertToLeft(nou, p);
            } else {
                insertToRight(nou, p);
            }
        } else {
            insertToLeft(nou, p);
        }
    }
}

// De aici incep niste functii utile pentru metode, dar care nu au nevoie de
// acces la elementele private
template <typename T>
void cleanNode(Node<T> *nou) {
    nou->up = nullptr;
    nou->right = nullptr;
    nou->down = nullptr;
    nou->left = nullptr;
}

template <typename T>
void insertToLeft(Node<T> *nou, Node<T> *p) {
    nou->left = p->left;
    nou->right = p;
    p->left->right = nou;
    p->left = nou;
}

template <typename T>
void insertToRight(Node<T> *nou, Node<T> *p) {
    nou->right = p->right;
    nou->left = p;
    if (p->right) {
        p->right->left = nou;
    }
    p->right = nou;
}

template class Skiplist<int>;
