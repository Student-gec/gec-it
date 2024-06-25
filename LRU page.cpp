#include <iostream>
#include <vector>
using namespace std;

// Function to find the index of a page in the frame
int findIndex(int page, vector<int>& frame) {
    for (int i = 0; i < frame.size(); i++) {
        if (frame[i] == page) {
            return i;
        }
    }
    return -1; // Page not found in frame
}

// Function to find the index of the least recently used page in the frame
int findLRUIndex(vector<int>& recent, vector<int>& frame) {
    int minIndex = 0;
    for (int i = 1; i < frame.size(); i++) {
        if (recent[frame[i]] < recent[frame[minIndex]]) {
            minIndex = i;
        }
    }
    return minIndex;
}

void LRU(int pages[], int n, int capacity) {
    int page_faults = 0;
    vector<int> frame;
    vector<int> recent(101, -1); // Assuming page numbers are between 0 and 100

    for (int i = 0; i < n; i++) {
        // Page is already in frame, update its recent index
        int pageIndex = findIndex(pages[i], frame);
        if (pageIndex != -1) {
            recent[pages[i]] = i;
        } else { // Page fault, insert page into frame
            if (frame.size() < capacity) {
                // Frame has space, insert page into frame
                frame.push_back(pages[i]);
                recent[pages[i]] = i;
            } else {
                // Frame is full, evict least recently used page
                int lruIndex = findLRUIndex(recent, frame);
                frame[lruIndex] = pages[i];
                recent[pages[i]] = i;
            }
            page_faults++;
        }

        // Display frames at each step
        cout << "Step " << i + 1 << ": ";
        for (int j = 0; j < frame.size(); j++) {
            cout << frame[j] << " ";
        }
        cout << endl;
    }

    // Display total page faults
    cout << "Total Page Faults: " << page_faults << endl;
}

int main() {
    int capacity, n;
    cout << "Enter the number of frames: ";
    cin >> capacity;
    cout << "Enter the number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter the page reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    LRU(pages, n, capacity);

    return 0;
}
