#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits.h>

using namespace std;

int CSCAN(vector<int>& requests, int head, int disk_size) {
    int seek_time = 0;
    vector<int> seek_sequence, differences;

    sort(requests.begin(), requests.end());
    int pos = distance(requests.begin(), lower_bound(requests.begin(), requests.end(), head));

    // Moving towards the end of the disk (towards disk_size)
    for (int i = pos; i < requests.size(); i++) {
        seek_sequence.push_back(requests[i]);
        differences.push_back(abs(requests[i] - head));
        seek_time += abs(requests[i] - head);
        head = requests[i];
    }

    // Move to the end of the disk (disk_size - 1)
    seek_sequence.push_back(disk_size - 1); // Go to the end of the disk (disk_size - 1)
    differences.push_back(abs(disk_size - 1 - head));
    seek_time += abs(disk_size - 1 - head);
    head = disk_size - 1;

    // Wrap around to the beginning of the disk (0)
    seek_sequence.push_back(0); // Go to the start of the disk (cylinder 0)
    differences.push_back(abs(0 - head));
    seek_time += abs(0 - head);
    head = 0;

    // Now, service the requests that are left (those before the initial position)
    for (int i = 0; i < pos; i++) {
        seek_sequence.push_back(requests[i]);
        differences.push_back(abs(requests[i] - head));
        seek_time += abs(requests[i] - head);
        head = requests[i];
    }

    cout << "C-SCAN\n";
    cout << "Sequence of requests: ";
    for (int r : seek_sequence) cout << r << " ";
    cout << "\nDifferences: ";
    for (int d : differences) cout << d << " ";
    cout << "\nTotal Seek Time: " << seek_time << "\n\n";

    return seek_time;
}

int main() {
    int disk_size, head, n;

    cout << "Enter the size of the disk (max cylinder number): ";
    cin >> disk_size;

    cout << "Enter the initial head position: ";
    cin >> head;

    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the disk requests: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    vector<int> cscan_requests = requests;
    CSCAN(cscan_requests, head, disk_size);

    return 0;
}

/*
Enter the size of the disk (max cylinder number): 200
Enter the initial head position: 100
Enter the number of disk requests: 9
Enter the disk requests: 55 58 39 18 90 160 150 38 184
C-SCAN
Sequence of requests: 150 160 184 199 0 18 38 39 55 58 90
Differences: 50 10 24 15 199 18 20 1 16 3 32
Total Seek Time: 388

*/

