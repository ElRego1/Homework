// Copyright Robert Lica robertlica21@gmail.com
#include "./HashMap.h"

// De aici incep metodele PUBLICE
HashMap::HashMap(int n, int *time, int *ranking, int max_value) {
    size = max_value;
    root = (Info**)malloc(size * sizeof(Info*));
    if (!root) {
        fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
        exit(1);
    }
    for (int i = 0; i < size; ++i) {
        root[i] = nullptr;
    }
    for (int i = 0; i < n; ++i) {
        if (time[i]) {
            ++participants;
            addInfo(i, time[i] - 1, ranking);
        }
    }
}

HashMap::~HashMap() {
    Info *p, *q;
    for (int i = 0; i < size; ++i) {
        p = root[i];
        while (p) {
            q = p;
            p = p->next;
            free(q);
        }
    }
    free(root);
}

int* HashMap::getIDorder(int *participants){
  int *a = (int*)malloc(this->participants * sizeof(int));
  *participants = this->participants;
  int index = 0;
  if (!a) {
      fprintf(stderr, "EROARE!!! Nu s-a alocat memorie\n");
      exit(1);
  }
  Info *p;
  for (int i = 0; i < size; ++i) {
      p = root[i];
      while (p) {
          a[index] = p->value;
          p = p->next;
          ++index;
      }
  }
  return a;
}

// De aici incep metodele PRIVATE
void HashMap::addInfo(int i, int info, int *ranking) {
    Info *to_put = (Info*)malloc(sizeof(Info));
    to_put->value = i + 1;
    to_put->next = nullptr;
    if (!root[info]) {
        root[info] = to_put;
    } else {
        Info *p = root[info], *q = p;
        if (ranking[p->value - 1] > ranking[i]) {
            root[info] = to_put;
            to_put->next = p;
            return;
        }
            while (p && ranking[p->value - 1] < ranking[i]) {
                q = p;
                p = p->next;
            }
            q->next = to_put;
            if (q != p) {
                to_put->next = p;
            }
    }
}
