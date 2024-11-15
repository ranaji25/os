#include <stdio.h>
#define MAX_FRAMES 3

// Function to check if the page is in memory
int isInMemory(int page, int* memory, int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (memory[i] == page) {
            return i; // Return the frame index if page is found
        }
    }
    return -1; // Page not found
}

// Function to display the current state of memory
void displayMemory(int* memory, int numFrames) {
    printf("Memory: ");
    for (int i = 0; i < numFrames; i++) {
        if (memory[i] == -1) {
            printf("- "); // Placeholder for empty slots
        } else {
            printf("%d ", memory[i]);
        }
    }
    printf("\n");
}

// Function to update LRU counters
void updateLRU(int* lru, int numFrames, int accessedFrame) {
    for (int i = 0; i < numFrames; i++) {
        lru[i]++;
    }
    lru[accessedFrame] = 0; // Reset the counter for the accessed frame
}

// LRU page replacement algorithm
void LRU(int* pages, int numPages) {
    int memory[MAX_FRAMES] = { -1, -1, -1 };  // Initialize memory with -1 (empty)
    int lru[MAX_FRAMES] = { 0 };              // LRU counters for each frame
    int hits = 0, misses = 0;

    // Print the referenced page string
    printf("Referenced String: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("LRU Page Replacement:\n");
    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];
        int accessedFrame = isInMemory(currentPage, memory, MAX_FRAMES);

        if (accessedFrame != -1) {
            // If the page is in memory, it's a hit
            hits++;
            updateLRU(lru, MAX_FRAMES, accessedFrame);
        } else {
            // Page miss, replace the least recently used page
            misses++;

            // Find the frame with the largest LRU counter (least recently used)
            int replaceIndex = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (lru[j] > lru[replaceIndex]) {
                    replaceIndex = j;
                }
            }
            memory[replaceIndex] = currentPage; // Replace the least recently used page
            updateLRU(lru, MAX_FRAMES, replaceIndex); // Update LRU after replacement
        }

        // Display the current state of memory
        displayMemory(memory, MAX_FRAMES);
    }

    // Print the results
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Page Faults: %d\n", misses);  // Misses and page faults are the same
}

int main() {
    int numPages;

    // Get the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pages[numPages];

    // Get the page references from the user
    printf("Enter the page references:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    LRU(pages, numPages);
    return 0;
}

/*
Enter the number of pages: 15
Enter the page references:
7  
0
1
2
0
3
0
4
2
3
0
3
1
2
0
Referenced String: 7 0 1 2 0 3 0 4 2 3 0 3 1 2 0
LRU Page Replacement:
Memory: 7 - -
Memory: 7 0 -
Memory: 7 0 1
Memory: 2 0 1
Memory: 2 0 1
Memory: 2 0 3
Memory: 2 0 3
Memory: 4 0 3
Memory: 4 0 2
Memory: 4 3 2
Memory: 0 3 2
Memory: 0 3 2
Memory: 0 3 1
Memory: 2 3 1
Memory: 2 0 1
Hits: 3
Misses: 12
Page Faults: 12
PS E:\_.sem5\OS\lab ex> 
*/
