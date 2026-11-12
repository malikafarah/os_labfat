#include <stdio.h>
#include <stdbool.h>

// Helper to check if a page is already present in frames
int findPage(int frames[], int capacity, int page) {
    for (int i = 0; i < capacity; i++) {
        if (frames[i] == page) return i;
    }
    return -1;
}

// Helper to find an empty slot (-1)
int findEmpty(int frames[], int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (frames[i] == -1) return i;
    }
    return -1;
}

// Prints frames at the current step
void printFrames(int step, int page, int frames[], int capacity, bool isFault) {
    printf("Step %2d (Page %d) -> [ ", step, page);
    for (int i = 0; i < capacity; i++) {
        if (frames[i] == -1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("] %s\n", isFault ? "(Page Fault)" : "(Hit)");
}

// 1. FIFO
int runFIFO(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0, ptr = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\n--- FIFO Trace ---\n");
    for (int i = 0; i < n; i++) {
        bool isFault = false;
        if (findPage(frames, capacity, pages[i]) == -1) {
            frames[ptr] = pages[i];
            ptr = (ptr + 1) % capacity;
            faults++;
            isFault = true;
        }
        printFrames(i + 1, pages[i], frames, capacity, isFault);
    }
    return faults;
}

// 2. LRU (Least Recently Used)
int runLRU(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\n--- LRU Trace ---\n");
    for (int i = 0; i < n; i++) {
        bool isFault = false;
        if (findPage(frames, capacity, pages[i]) == -1) {
            int idx = findEmpty(frames, capacity);
            if (idx == -1) { // Frame is full: scan backwards for least recently used
                int leastRecent = i;
                for (int j = 0; j < capacity; j++) {
                    for (int k = i - 1; k >= 0; k--) {
                        if (frames[j] == pages[k]) {
                            if (k < leastRecent) { leastRecent = k; idx = j; }
                            break;
                        }
                    }
                }
            }
            frames[idx] = pages[i];
            faults++;
            isFault = true;
        }
        printFrames(i + 1, pages[i], frames, capacity, isFault);
    }
    return faults;
}

// 3. Optimal Page Replacement
int runOptimal(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\n--- Optimal Trace ---\n");
    for (int i = 0; i < n; i++) {
        bool isFault = false;
        if (findPage(frames, capacity, pages[i]) == -1) {
            int idx = findEmpty(frames, capacity);
            if (idx == -1) { // Frame is full: scan forward for page used furthest in future
                int farthest = i + 1;
                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) { farthest = k; idx = j; }
                            break;
                        }
                    }
                    if (k == n) { idx = j; break; } // Not used again in future
                }
            }
            frames[idx] = pages[i];
            faults++;
            isFault = true;
        }
        printFrames(i + 1, pages[i], frames, capacity, isFault);
    }
    return faults;
}

// Helper to print summary row
void printSummaryRow(const char *algoName, int faults, int n) {
    int hits = n - faults;
    float hitRatio = ((float)hits / n) * 100.0f;
    float faultRatio = ((float)faults / n) * 100.0f;
    printf("%-10s | %6d | %5.1f%% | %6d | %5.1f%%\n", algoName, hits, hitRatio, faults, faultRatio);
}

int main() {
    int n, capacity;

    printf("Enter number of pages: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int pages[n];
    printf("Enter reference string (%d numbers): ", n);
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    if (scanf("%d", &capacity) != 1 || capacity <= 0) return 1;

    int fifo_faults = runFIFO(pages, n, capacity);
    int lru_faults  = runLRU(pages, n, capacity);
    int opt_faults  = runOptimal(pages, n, capacity);

    // Summary Table
    printf("\n=======================================================\n");
    printf("%-10s | %6s | %6s | %6s | %6s\n", "Algorithm", "Hits", "Hit %", "Faults", "Fault %");
    printf("-------------------------------------------------------\n");
    printSummaryRow("FIFO", fifo_faults, n);
    printSummaryRow("LRU", lru_faults, n);
    printSummaryRow("OPTIMAL", opt_faults, n);
    printf("=======================================================\n");

    return 0;
}