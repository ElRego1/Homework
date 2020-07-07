// Copyright Robert Lica robertlica21@gmail.com
#ifndef HASHMAP_H__
#define HASHMAP_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct info{
    int value;
    struct info *next = nullptr;
}Info;

class HashMap {
    struct info **root;
    int size, participants = 0;

	public:
    HashMap(int n, int *time, int *ranking, int max_value);

    ~HashMap();

    int* getIDorder(int *participants);

	private:
    void addInfo(int i, int info, int *ranking);
};
#endif  // HASHMAP_H__
