#include <math.h>
#include "functions.h"
#include <stdlib.h>

float mean(float *data, int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

float median(float *data, int size) {
    float *sorted = (float *)malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        sorted[i] = data[i];
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                float temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    float med = (size % 2 == 0) ? (sorted[size / 2 - 1] + sorted[size / 2]) / 2 : sorted[size / 2];
    free(sorted);
    return med;
}

float variance(float *data, int size) {
    float m = mean(data, size);
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += (data[i] - m) * (data[i] - m);
    }
    return sum / size;
}

float std_dev(float *data, int size) {
    return sqrt(variance(data, size));
}
