#include <stdio.h>
#define MAX_PAGES 3

int isInMemory(int page, int* memory, int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (memory[i] == page) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

void displayMemory(int* memory, int numFrames) {
    printf("Memory: ");
    for (int i = 0; i < numFrames; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

void FIFO(int* pages, int numPages) {
    int memory[MAX_PAGES] = { -1 };
    int front = 0;
    int hits = 0, misses = 0;

    printf("Referenced String: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("FIFO Page Replacement:\n");
    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];
        if (isInMemory(currentPage, memory, MAX_PAGES)) {
            hits++;
        } else {
            misses++;
            memory[front] = currentPage;
            front = (front + 1) % MAX_PAGES;
        }
        displayMemory(memory, MAX_PAGES);
    }

    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Page Faults: %d\n", misses);
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

    // Call the FIFO function with the inputted pages
    FIFO(pages, numPages);

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
FIFO Page Replacement:
Memory: 7 0 0
Memory: 7 0 0
Memory: 7 1 0
Memory: 7 1 2
Memory: 0 1 2
Memory: 0 3 2
Memory: 0 3 2
Memory: 0 3 4
Memory: 2 3 4
Memory: 2 3 4
Memory: 2 0 4 
Memory: 2 0 3
Memory: 1 0 3
Memory: 1 2 3
Memory: 1 2 0
Hits: 3
Misses: 12
Page Faults: 12
*/
