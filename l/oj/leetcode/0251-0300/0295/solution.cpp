class MedianFinder {
public:
    // 62%
    // two list, one is left, one is right.
    // left.size - right.size <= 1
    // left.front() is the max of the list
    // right.front() is the min of the list

    // Adds a number into the data structure.
    void addNum(int num) {
        if (left.empty()) {
            left.push(num);
        } else {
            if (num < left.top()) {
                left.push(num);
            } else {
                right.push(num);
            }
        }
        // adjust
        // do not use left.size() - right.size() > 1.
        // because size() is unsigned, 0 - 1 = -1, that will be a large unsigned.
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        } 
    }

    // Returns the median of current data stream
    double findMedian() {
        if (left.size() > right.size()) {
            return left.top();
        }
        
        return static_cast<double>(left.top() + right.top()) / 2;
    }

private:
    priority_queue<int, vector<int>, less<int>> left; // left.front() is the max of the list
    priority_queue<int, vector<int>, greater<int>> right; // right.front() is the min of the list
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian(); 