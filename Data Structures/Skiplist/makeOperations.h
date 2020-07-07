// Copyright Robert Lica robertlica21@gmail.com
#ifndef MAKEOPERATIONS_H__
#define MAKEOPERATIONS_H__

#include <stdio.h>
#include "./Skiplist.h"
#include "./HashMap.h"


void do_commands(FILE *in, FILE *out);
char check_is_print(FILE *in);

template <typename T>
void make_print(Skiplist<T> *points_skp, FILE *out);

template <typename T>
void makeInitialPoints_skp(Skiplist<T> *skp, int n);

template <typename T>
void doSkiplists(Skiplist<T> *points_skp, int n, FILE* in, int *ranking,
	int *ranking_for_order, int *id_points);

template <typename T>
void put_points(Skiplist<T> *points_skp, int *order, int participants,
	int *id_points);

template <typename T>
void recreate_ranking(Skiplist<T> *points_skp, int *ranking,
	int *ranking_for_order);

template <typename T>
void do_free(Skiplist<T> *points_skp, int *id_points, int *ranking,
	int *past_ranking, int *ranking_for_order);

void print_clasament(int **ranking, int **past_ranking, int *id_points,
	int n, FILE *out);
int computeDifference(int* ranking, int *past_ranking, int i);

#endif  // MAKEOPERATIONS_H__
