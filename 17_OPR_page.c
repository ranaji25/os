#include <stdio.h>
#include <limits.h>
#define MAX_PAGES 3

// Function to check if a page is in memory
int isInMemory(int page, int* memory, int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (memory[i] == page) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

// Function to display the current state of memory
void displayMemory(int* memory, int numFrames) {
    printf("Memory: ");
    for (int i = 0; i < numFrames; i++) {
        if (memory[i] == -1)
            printf("- ");
        else
            printf("%d ", memory[i]);
    }
    printf("\n");
}

// Function to find the optimal page to replace
int findOptimal(int* pages, int start, int numPages, int* memory, int numFrames) {
    int farthest = -1;
    int farthestIndex = -1;
    for (int i = 0; i < numFrames; i++) {
        int currentPage = memory[i];
        int j;
        for (j = start; j < numPages; j++) {
            if (pages[j] == currentPage) {
                if (j > farthest) {
                    farthest = j;
                    farthestIndex = i;
                }
                break;
            }
        }
        if (j == numPages) {
            return i; // If a page will not be referenced in the future, replace it
        }
    }
    if (farthestIndex == -1) {
        return 0; // Default case: replace the first page if no other page is farthest
    }
    return farthestIndex;
}

// Function to simulate Optimal Page Replacement (OPT) algorithm
void OPT(int* pages, int numPages) {
    int memory[MAX_PAGES] = { -1, -1, -1 }; // Initialize memory with -1 (empty)
    int hits = 0, misses = 0;
    int filledSlots = 0; // To track the number of frames that are filled

    printf("Referenced String: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("OPT Page Replacement:\n");
    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];

        // If the page is already in memory, it's a hit
        if (isInMemory(currentPage, memory, MAX_PAGES)) {
            hits++;
            printf("Page %d: Hit\n", currentPage);
        } else {
            misses++;
            int replaceIndex = -1;

            // If memory has empty slots (marked by -1), load the page into an empty slot
            if (filledSlots < MAX_PAGES) {
                // Fill empty slots without replacement
                for (int j = 0; j < MAX_PAGES; j++) {
                    if (memory[j] == -1) {
                        memory[j] = currentPage;
                        filledSlots++;
                        replaceIndex = j;
                        break;
                    }
                }
            }

            // If all slots are filled, use optimal page replacement
            if (replaceIndex == -1) {
                replaceIndex = findOptimal(pages, i + 1, numPages, memory, MAX_PAGES);
            }

            printf("Page %d: Miss (replace page %d)\n", currentPage, memory[replaceIndex]);
            memory[replaceIndex] = currentPage; // Replace the page
        }

        displayMemory(memory, MAX_PAGES); // Show memory after each page access
    }

    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Page Faults: %d\n", misses);
}

int main() {
    int numPages;

    // Get the number of pages from the user
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pages[numPages];

    // Get the page references from the user
    printf("Enter the page references:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Call the OPT function to simulate the page replacement
    OPT(pages, numPages);

    return 0;
}

/*
Enter the number of pages: 18
Enter the page references:
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7
Referenced String: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7
OPT Page Replacement:
Page 7: Miss (replace page 7)
Memory: 7 - -
Page 0: Miss (replace page 0)
Memory: 7 0 -
Page 1: Miss (replace page 1)
Memory: 7 0 1
Page 2: Miss (replace page 7)
Memory: 2 0 1
Page 0: Hit
Memory: 2 0 1
Page 3: Miss (replace page 1)
Memory: 2 0 3
Page 0: Hit
Memory: 2 0 3
Page 4: Miss (replace page 0)
Memory: 2 4 3
Page 2: Hit
Memory: 2 4 3 
Page 3: Hit
Memory: 2 4 3
Page 0: Miss (replace page 4)
Memory: 2 0 3
Page 3: Hit
Memory: 2 0 3
Page 2: Hit
Memory: 2 0 3
Page 1: Miss (replace page 3)
Memory: 2 0 1
Page 2: Hit
Memory: 2 0 1
Page 0: Hit
Memory: 2 0 1
Page 1: Hit
Memory: 2 0 1
Page 7: Miss (replace page 2)
Memory: 7 0 1 
Hits: 9
Misses: 9
Page Faults: 9
PS E:\_.sem5\OS\lab ex>
*/
