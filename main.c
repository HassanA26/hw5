#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void print_usage() {
    printf("Usage: stats infile [outfile]\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_usage();
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (!infile) {
        fprintf(stderr, "Error: Could not open input file.\n");
        return 1;
    }

    int size = 0;
    float temp;
    while (fscanf(infile, "%f", &temp) == 1) {
        size++;
    }
    rewind(infile);

    float *data = (float *)malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        fscanf(infile, "%f", &data[i]);
    }
    fclose(infile);

    float m = mean(data, size);
    float med = median(data, size);
    float var = variance(data, size);
    float std = std_dev(data, size);

    FILE *outfile = (argc == 3) ? fopen(argv[2], "w") : stdout;
    if (argc == 3 && !outfile) {
        fprintf(stderr, "Error: Could not open output file.\n");
        free(data);
        return 1;
    }

    fprintf(outfile, "Mean: %.2f\n", m);
    fprintf(outfile, "Median: %.2f\n", med);
    fprintf(outfile, "Variance: %.2f\n", var);
    fprintf(outfile, "Standard Deviation: %.2f\n", std);

    if (outfile != stdout) fclose(outfile);
    free(data);
    return 0;
}
