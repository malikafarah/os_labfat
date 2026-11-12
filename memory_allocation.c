#include <stdio.h>

#define MAX 20

// Helper function to print results cleanly without duplicating code
void printAllocationTable(const char *title, int processes[], int n, int allocation[], int remainingBlocks[]) {
    printf("\n--- %s ---\n", title);
    printf("Process No.\tProcess Size\tBlock No.\tRemaining Block Size\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\t\t%d\n", allocation[i] + 1, remainingBlocks[allocation[i]]);
        } else {
            printf("Not Allocated\t-\n");
        }
    }
}

// First Fit: allocate the first block that fits
void firstFit(int blocks[], int m, int processes[], int n) {
    int allocation[MAX], tempBlocks[MAX];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    for (int i = 0; i < m; i++) tempBlocks[i] = blocks[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tempBlocks[j] >= processes[i]) {
                allocation[i] = j;
                tempBlocks[j] -= processes[i];
                break; // Stop at the first available match
            }
        }
    }
    printAllocationTable("First Fit Allocation", processes, n, allocation, tempBlocks);
}

// Best Fit: allocate the smallest block that fits
void bestFit(int blocks[], int m, int processes[], int n) {
    int allocation[MAX], tempBlocks[MAX];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    for (int i = 0; i < m; i++) tempBlocks[i] = blocks[i];

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (tempBlocks[j] >= processes[i]) {
                if (bestIdx == -1 || tempBlocks[j] < tempBlocks[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlocks[bestIdx] -= processes[i];
        }
    }
    printAllocationTable("Best Fit Allocation", processes, n, allocation, tempBlocks);
}

// Worst Fit: allocate the largest block that fits
void worstFit(int blocks[], int m, int processes[], int n) {
    int allocation[MAX], tempBlocks[MAX];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    for (int i = 0; i < m; i++) tempBlocks[i] = blocks[i];

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (tempBlocks[j] >= processes[i]) {
                if (worstIdx == -1 || tempBlocks[j] > tempBlocks[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            tempBlocks[worstIdx] -= processes[i];
        }
    }
    printAllocationTable("Worst Fit Allocation", processes, n, allocation, tempBlocks);
}

int main() {
    int blocks[] = {100, 500, 200, 300, 600};
    int processes[] = {212, 417, 112, 426};

    int m = sizeof(blocks) / sizeof(blocks[0]);
    int n = sizeof(processes) / sizeof(processes[0]);

    firstFit(blocks, m, processes, n);
    bestFit(blocks, m, processes, n);
    worstFit(blocks, m, processes, n);

    return 0;
}