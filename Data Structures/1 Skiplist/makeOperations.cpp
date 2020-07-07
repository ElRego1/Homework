// Copyright Robert Lica robertlica21@gmail.com
#include "./makeOperations.h"

void do_commands(FILE *in, FILE *out) {
    int n, m, k;
    fscanf(in, "%d%d%d", &n, &m, &k);
    Skiplist<int> *points_skp = new Skiplist<int>();
    // Tinem punctajul fiecarui concurent pentru a-l accesa rapid cand
    // cautam/inseram in skiplist ca sa ne folosim de avantajele lui
    int *id_points = (int*)calloc(n, sizeof(int));
    // Tinem id-urile in ordinea ranking-ului
    int *ranking = (int*)malloc(n * sizeof(int));
    // Tinem ranking-ul fiecarui concurent
    int *ranking_for_order = (int*)malloc(n * sizeof(int));
    if (!id_points || !ranking || !ranking_for_order) {
            fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
            exit(1);
        }

    int *past_ranking = nullptr;
    for (int i = 0; i < n; ++i) {
        ranking[i] = i;
        ranking_for_order[i] = i;
    }

// Nu stiu de ce aceste linii, aparent inutile, sunt importante pentru a nu
// da "Abord(Core Dumped)" pe parcursul programului. Este foarte interesant si
// curios, am sa discut cu laborantul despre aceasta, dar momentan hai sa
// ignoram warning-ul, ca facem ceva inutil ca stiu ac pare batut in cap, dar
// fara aceste linii mie pe local nu imi merge :)
    for (int i = 0; i < n; ++i) {
        ranking[i];
    }
    for (int i = 0; i < n; ++i) {
        ranking_for_order[i];
    }

    makeInitialPoints_skp(points_skp, n);

    while (m + k--) {
        if (!check_is_print(in)) {
            doSkiplists(points_skp, n, in, ranking, ranking_for_order,
                id_points);
        } else {
            print_clasament(&ranking, &past_ranking, id_points, n, out);
        }
    }
    do_free(points_skp, id_points, ranking, past_ranking, ranking_for_order);
}

template <typename T>
void doSkiplists(Skiplist<T> *points_skp, int n, FILE* in, int *ranking,
            int *ranking_for_order, int *id_points) {
    int *temp_time = (int*)malloc(n * sizeof(int));
    int max_value = 0;
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", (temp_time + i));
        if (temp_time[i] > max_value) max_value = temp_time[i];
    }
    HashMap *hash_m = new HashMap(n, temp_time, ranking_for_order, max_value);
    int participants;
    int *order = hash_m->getIDorder(&participants);
    delete hash_m;
    put_points(points_skp, order, participants, id_points);
    recreate_ranking(points_skp, ranking, ranking_for_order);
    free(order);
    free(temp_time);
}

template <typename T>
void put_points(Skiplist<T> *points_skp, int *order, int participants,
            int *id_points) {
    int points_to_add;
    Node<T> *calcule;
    for (int i = 0; i < participants / 2; ++i) {
        points_to_add = participants / 2 - i;
        calcule = points_skp->popNodeByIDandPoints(order[i],
            id_points[order[i] - 1]);
        id_points[order[i] - 1] += points_to_add;
        calcule->points = id_points[order[i] - 1];
        points_skp->addNodeForPoints(calcule);
    }
    if (participants % 2) {
        points_to_add = 0;
        calcule = points_skp->popNodeByIDandPoints(order[participants / 2],
            id_points[order[participants / 2] - 1]);
        id_points[order[participants / 2] - 1] += points_to_add;
        calcule->points = id_points[order[participants / 2] - 1];
        points_skp->addNodeForPoints(calcule);

        for (int i = participants / 2 + 1; i < participants; ++i) {
            points_to_add = participants / 2 -  i;
            calcule = points_skp->popNodeByIDandPoints(order[i],
                id_points[order[i] - 1]);
            id_points[order[i] - 1] += points_to_add;
            calcule->points = id_points[order[i] - 1];
            points_skp->addNodeForPoints(calcule);
        }
    } else {
        for (int i = participants / 2; i < participants; ++i) {
            points_to_add = participants / 2 - 1 - i;
            calcule = points_skp->popNodeByIDandPoints(order[i],
                id_points[order[i] - 1]);
            id_points[order[i] - 1] += points_to_add;
            calcule->points = id_points[order[i] - 1];
            points_skp->addNodeForPoints(calcule);
        }
    }
}

template <typename T>
void recreate_ranking(Skiplist<T> *points_skp, int *ranking,
            int *ranking_for_order) {
    points_skp->reorderRanking(ranking);
    points_skp->reorderRankingForOrder(ranking_for_order);
}

void print_clasament(int **ranking, int **past_ranking, int *id_points, int n,
            FILE *out) {
    if (*past_ranking) {
        for (int i = 0; i < n; ++i) {
            fprintf(out, "%d %d %d\n", ((*ranking)[i] + 1),
                id_points[(*ranking)[i]],
                computeDifference(*ranking, *past_ranking, i));
        }
        free(*past_ranking);
        *past_ranking = *ranking;
        *ranking = nullptr;
    } else {
        *past_ranking = *ranking;
        *ranking = nullptr;
        for (int i = 0; i < n; ++i) {
            fprintf(out, "%d %d 0\n", ((*past_ranking)[i] + 1),
                id_points[(*past_ranking)[i]]);
        }
    }
    fprintf(out, "\n");
    fflush(out);
    (*ranking) = (int*)malloc(n * sizeof(int));
    if (!ranking) {
        fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
        exit(1);
    }
}

int computeDifference(int *ranking, int *past_ranking, int i) {
    int search = 0;
    while (past_ranking[search] != ranking[i]) {
        ++search;
    }
    return search - i;
}

char check_is_print(FILE *in) {
    char c = '\n';
    while (c == '\n' || c == ' ') {
        fscanf(in, "%c", &c);
    }
    if (c == 'p') {
        while (c != 't') {
            fscanf(in, "%c", &c);
        }
        return 1;
    } else {
        fseek(in, -sizeof(char), 1);
    }
    return 0;
}

template <typename T>
void do_free(Skiplist<T> *points_skp, int *id_points, int *ranking,
        int *past_ranking, int *ranking_for_order) {
    delete points_skp;
    free(id_points);
    free(ranking);
    free(past_ranking);
    free(ranking_for_order);
}

template <typename T>
void makeInitialPoints_skp(Skiplist<T>* skp, int n) {
    do {
        skp->addNodeInitialList(n, 0);
    } while (--n);
}
