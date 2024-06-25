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

// Function to predict the future index of each page
int predict(int pages[], vector<int>& frame, int pn, int index) {
    vector<int> futureIndex(frame.size(), pn); // Initialize with maximum index
    int res = -1;
    for (int i = 0; i < frame.size(); i++) {
        int page = frame[i];
        for (int j = index; j < pn; j++) {
            if (pages[j] == page) {
                futureIndex[i] = j;
                break;
            }
        }
        if (futureIndex[i] == pn) {
            return i; // Page not found in future, replace it
        }
        if (futureIndex[i] > res) {
            res = futureIndex[i]; // Update the farthest future index
        }
    }
    for (int i = 0; i < frame.size(); i++) {
        if (futureIndex[i] == res) {
            return i; // Return the index of the page with farthest future index
        }
    }
    return res; // Return the page to be replaced
}

void optimalPage(int pages[], int pn, int fn) {
    vector<int> frame;
    int page_faults = 0;

    for (int i = 0; i < pn; i++) {
        int pageIndex = findIndex(pages[i], frame);
        if (pageIndex == -1) { // Page fault
            if (frame.size() < fn) { // Frame has space
                frame.push_back(pages[i]);
            } else { // Frame is full, need to replace a page
                int j = predict(pages, frame, pn, i + 1);
                frame[j] = pages[i];
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
    int pn, fn;
    cout << "Enter the number of pages: ";
    cin >> pn;
    int pages[pn];
    cout << "Enter the page reference string: ";
    for (int i = 0; i < pn; i++) {
        cin >> pages[i];
    }
    cout << "Enter the number of frames: ";
    cin >> fn;

    optimalPage(pages, pn, fn);

    return 0;
}
