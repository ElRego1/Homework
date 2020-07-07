// Copyright 2018 Blah Blah <ceva@ceva.com>
#include <stdio.h>
#include <math.h>

double domGeom(int n, double mGeom);
float domArm(int n, float mArm);
float domPatr(int n, float mPatr);
float dostdev(float mPatr, float mArit);

int main() {
    double mGeom = 1;
    float mArit = 0, mArm = 0, mPatr = 0, stdev = 0;
    int n, contor = 0, contorLung = 0, minimContor = 0, maximContor = 0;
    float temp, ti = 0, minim = 0,   maxim = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &temp);
        // cautam valoarea minima
        if (!minim || minim > temp) {
            minim = temp;
            minimContor = 1;
        } else if (minim == temp) {
            minimContor++;
        }
        // cautam valoarea maxima
        if (!maxim || maxim < temp) {
            maxim = temp;
            maximContor = 1;
        } else if (maxim == temp) {
            maximContor++;
        }
        // cautam cel mai lung sir
        if (ti <= temp) {
            contor++;
        } else {
            if (contorLung < contor) {
                contorLung = contor;
            }
            contor = 1;
        }
        ti = temp;
        if (contorLung < contor) {
            contorLung = contor;
        }

        // adaugam la media aritmetica
        mArit += temp;
        // inmultim la media geometrica
        if (temp > 0 && mGeom != -1.0) {
            mGeom *= temp;
        } else {
            mGeom = -1.0;
        }
        // adunam la media armonica
        mArm += 1.0 / temp;
        // adunam la media patratica
        mPatr += (temp * temp);
    }
    mArit = mArit / n;
    mGeom = domGeom(n, mGeom);
    mArm = domArm(n, mArm);
    mPatr = domPatr(n, mPatr);
    stdev = dostdev(mPatr, mArit);
    printf("%.4f\n", mArit);
    if (mGeom > 0) {
        printf("%.4lf\n", mGeom);
    } else {
        printf("-\n");
    }
    printf("%.4f\n", mArm);
    printf("%.4f\n", mPatr);
    printf("%.4f\n", stdev);
    printf("%.4f %d\n", minim, minimContor);
    printf("%.4f %d\n", maxim, maximContor);
    printf("%d\n", contorLung);
    return 0;
}

double domGeom(int n, double mGeom) {
    if (mGeom < 0) {
        return -1.0;
    } else {
        mGeom = pow(mGeom, 1.0 / n);
    }
    return mGeom;
}

float domArm(int n, float mArm) {
    return n / mArm;
}

float domPatr(int n, float mPatr) {
    return sqrt(mPatr / n);
}

float dostdev(float mPatr, float mArit) {
    return sqrt(mPatr * mPatr - mArit * mArit);
}
