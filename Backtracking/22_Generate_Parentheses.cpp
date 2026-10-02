class Solution {
public:

    void generate(int n, int open, int close,
                  string current, vector<string>& ans) {

        // We have used all brackets
        if (current.length() == 2 * n) {
            ans.push_back(current);
            return;
        }

        // Add opening bracket
        if (open < n) {
            generate(n, open + 1, close,
                     current + "(", ans);
        }

        if (close < open) {
            generate(n, open, close + 1,
                     current + ")", ans);
        }
    }

    vector<string> generateParenthesis(int n) {

        vector<string> ans;

        generate(n, 0, 0, "", ans);

        return ans;
    }
};