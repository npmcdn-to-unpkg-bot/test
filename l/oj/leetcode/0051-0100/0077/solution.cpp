 class Solution {
public:
	// 25%
    // C(n,k) = C(n-1, k-1) + c(n-1, k)
    // n is selected, then, select k-1 in n-1
    // then n-1 is selected, select k-1 in n-1-1
    vector<vector<int>> combine(int n, int k) {
        if (n < 1 || k < 1 || k > n) {
            return vector<vector<int>>();
        }
        
        // When == 1, return [[1],[2],[3]..[n]]
        if (k == 1) {
            vector<vector<int>> res;
            for (int i=1; i<= n; i++) {
                vector<int> v;
                v.push_back(i);
                res.push_back(v);
            }
            return  res;
        }
        
        // when n == k return [[1,2,3...k]]
        if (n == k) {
            vector<vector<int>> res;
            vector<int> v;
            for (int i=1; i<=k; i++) {
                v.push_back(i);
            }
            res.push_back(v);
            return res;
        }

        // n is selected, find k-1 in [1, n-1]
        auto A = combine(n-1, k-1);
        // add n to each vector, now it's k
        for (auto& v : A) {
            v.push_back(n);
        }
        
        // n is not selected, find k in [1, n-1]
        auto B = combine(n-1, k);
        
        // merge the result
        vector<vector<int>> res;
        res.reserve(A.size() + B.size());
        res.insert(res.end(), A.begin(), A.end());
        res.insert(res.end(), B.begin(), B.end());
        return res;
    }
};

class Solution2 {
public:
	// 85%
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> temp;
        combine(1,n,k,ans,temp); //call fuction to get combination of k numbers which range is 1-n
        return ans;
    }
private:
       void combine(int begin,int n, int k, vector<vector<int>> &ans, vector<int>& temp){
            if(k==0){ 
                ans.push_back(temp);
                return;
            } 
            //condition : n-i+1 is the range, range must greater than k
            for(int i=begin;n-i+1>=k;i++){ // for the ith iteration, get the combination of i and k-1 numbers differ from i.
                temp.push_back(i); 
                combine(i+1,n,k-1,ans,temp);// get the combination of k-1 numbers which range is(i+1,n) 
                temp.pop_back();
            }
        }
};


class Solution3 {
    public:
    	// memory or time limit. I don't know why.
    	// It should be as fast as solution2
        // maybe -- is much slower than ++ ???
        vector<vector<int>> combine(int n, int k) {
            if (n < 1 || k < 1 || k > n) {
                return vector<vector<int>>();
            }
            vector<vector<int>> res;
            vector<int> tmp;
            combine(n, k, res, tmp);
            return res;
        }
        
        void combine(int start, int k, vector<vector<int>>& res, vector<int>& tmp) {
            if (k == 0) {
                res.push_back(tmp);
                return;
            }

            for (int i=start; i >= k; i--) {
                tmp.push_back(i);         
                combine(start-1, k-1, res, tmp);
                tmp.pop_back();
            }
        }
    };