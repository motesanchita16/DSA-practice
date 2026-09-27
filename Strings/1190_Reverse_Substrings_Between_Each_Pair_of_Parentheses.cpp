class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();

        vector<int> pair(n);
        stack<int> st;

        // Find matching parentheses
        for (int i = 0; i < n; i++) {

            if (s[i] == '(') {
                st.push(i);
            }
            else if (s[i] == ')') {
                int open = st.top();
                st.pop();

                pair[open] = i;
                pair[i] = open;
            }
        }

        string ans;

        int i = 0;
        int direction = 1;

        while (i < n) {

            if (s[i] == '(' || s[i] == ')') {

                // Jump to matching bracket
                i = pair[i];

                // Change direction
                direction = -direction;
            }
            else {
                ans += s[i];
            }

            i += direction;
        }

        return ans;
    }
};