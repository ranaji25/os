#include <stdio.h>
#include <stdlib.h>

void fcfs(int requestQueue[], int n, int head) {
    int totalMovement = 0;
    int cumulativeSeek = 0;

    printf("FCFS Disk Scheduling Algorithm\n");
    printf("+------------------------+------------------+------------------+\n");
    printf("| Request                | Head Movement     | Cumulative Seek  |\n");
    printf("+------------------------+------------------+------------------+\n");

    for (int i = 0; i < n; i++) {
        int movement = abs(requestQueue[i] - head);
        totalMovement += movement;
        cumulativeSeek += movement;
        printf("| %-22d -> %-6d | %-16d | %-16d |\n", head, requestQueue[i], movement, cumulativeSeek);
        head = requestQueue[i];
    }

    printf("+------------------------+------------------+------------------+\n");
    printf("Total Seek Time (FCFS): %d\n\n", totalMovement);
}

int main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requestQueue[n];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    fcfs(requestQueue, n, head);
    return 0;
}


/*
Enter the number of requests: 9
Enter the request queue:
55 58 39 18 90 160 150 38 184
Enter the initial head position: 100
FCFS Disk Scheduling Algorithm
+------------------------+------------------+------------------+
| Request                | Head Movement     | Cumulative Seek  |
+------------------------+------------------+------------------+
| 100                    -> 55     | 45               | 45               |
| 55                     -> 58     | 3                | 48               |
| 58                     -> 39     | 19               | 67               |
| 39                     -> 18     | 21               | 88               |
| 18                     -> 90     | 72               | 160              |
| 90                     -> 160    | 70               | 230              |
| 160                    -> 150    | 10               | 240              |
| 150                    -> 38     | 112              | 352              |
| 38                     -> 184    | 146              | 498              |
+------------------------+------------------+------------------+
Total Seek Time (FCFS): 498

PS E:\_.sem5\OS\lab ex>
*/

