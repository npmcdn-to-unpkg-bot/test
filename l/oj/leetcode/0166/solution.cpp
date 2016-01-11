class Solution {
public:
    // 43% and best.
    string fractionToDecimal(int numerator, int denominator) {
        // numerator -2147483648, denominator -1 can cuase overflow exception.
        int64_t n = numerator, d = denominator;
        if (n == 0) {
            return "0";
        }
        std::string res;
        if (n<0 ^ d<0) {
            res += "-";
        }
        n = abs(n);
        d = abs(d);
        res += std::to_string(n/d);
        auto left = n%d;
        if (left != 0) {
            unordered_map<int, int> h; // <left, index of string>
            string tmp;
            getDecimal(left, d, h, tmp);
            res += string(".") + tmp;
        }
        return res;
    }
    
    void getDecimal(int64_t n, int64_t d, unordered_map<int, int>& h, string& result) {
        if (n == 0) {
            return;
        }
        // n in (1, d)
        const auto it = h.find(n);
        if (it != h.end()) {
            result.insert(it->second, "(");
            result += ')';
            return;
        }
        
        // If not
        result += to_string(n*10/d);
        h[n] = result.size() - 1; // index
        getDecimal((n*10)%d, d, h, result);
    }
};