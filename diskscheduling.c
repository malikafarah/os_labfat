#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Helper comparator for sorting requests in ascending order
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// 1. FCFS
int fcfs(int req[], int n, int head) {
    int total = 0, cur = head;
    for (int i = 0; i < n; i++) {
        total += abs(cur - req[i]);
        cur = req[i];
    }
    return total;
}

// 2. SSTF
int sstf(int req[], int n, int head) {
    int total = 0, cur = head;
    bool done[n];
    for (int i = 0; i < n; i++) done[i] = false;

    for (int step = 0; step < n; step++) {
        int best_idx = -1;
        int min_dist = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && abs(cur - req[i]) < min_dist) {
                min_dist = abs(cur - req[i]);
                best_idx = i;
            }
        }

        total += min_dist;
        cur = req[best_idx];
        done[best_idx] = true;
    }
    return total;
}

// 3. SCAN (Moves toward 0 first, hits 0, then reverses)
int scan(int req[], int n, int head) {
    int sorted[n];
    for (int i = 0; i < n; i++) sorted[i] = req[i];
    qsort(sorted, n, sizeof(int), compare);

    // Find the split point (first request >= head)
    int split = 0;
    while (split < n && sorted[split] < head) split++;

    int total = 0, cur = head;

    // Service lower side in descending order
    for (int i = split - 1; i >= 0; i--) {
        total += abs(cur - sorted[i]);
        cur = sorted[i];
    }

    // Reach the boundary (cylinder 0)
    total += abs(cur - 0);
    cur = 0;

    // Service upper side in ascending order
    for (int i = split; i < n; i++) {
        total += abs(cur - sorted[i]);
        cur = sorted[i];
    }
    return total;
}

// 4. C-SCAN (Moves toward diskSize - 1, jumps to 0, moves up)
int cscan(int req[], int n, int head, int diskSize) {
    int sorted[n];
    for (int i = 0; i < n; i++) sorted[i] = req[i];
    qsort(sorted, n, sizeof(int), compare);

    // Find the split point (first request >= head)
    int split = 0;
    while (split < n && sorted[split] < head) split++;

    int total = 0, cur = head;

    // Service upper side in ascending order
    for (int i = split; i < n; i++) {
        total += abs(cur - sorted[i]);
        cur = sorted[i];
    }

    // Reach the high boundary
    total += abs(cur - (diskSize - 1));
    cur = diskSize - 1;

    // Jump to cylinder 0 (counted as seek time in traditional C-SCAN)
    total += abs(cur - 0);
    cur = 0;

    // Service remaining lower side in ascending order
    for (int i = 0; i < split; i++) {
        total += abs(cur - sorted[i]);
        cur = sorted[i];
    }
    return total;
}

int main() {
    int n, head, diskSize;

    printf("Enter number of requests: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int req[n];
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);

    printf("Enter initial head position and disk size: ");
    scanf("%d %d", &head, &diskSize);

    // Compare all four directly
    printf("\n=========================================\n");
    printf("      DISK SCHEDULING TOTAL MOVEMENT     \n");
    printf("=========================================\n");
    printf("FCFS   Movement : %d cylinders\n", fcfs(req, n, head));
    printf("SSTF   Movement : %d cylinders\n", sstf(req, n, head));
    printf("SCAN   Movement : %d cylinders\n", scan(req, n, head));
    printf("C-SCAN Movement : %d cylinders\n", cscan(req, n, head, diskSize));
    printf("=========================================\n");

    return 0;
}