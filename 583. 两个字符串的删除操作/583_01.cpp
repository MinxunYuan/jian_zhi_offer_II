class Solution
{
public:
    int minDistance(string a, string b)
    {
        // 整体往右边挪一格，相当于把if(i==-1 && j==-1)的这个base case放到dp[0][0]里面
        a = ' ' + a;
        b = ' ' + b;
        int len1 = a.size(), len2 = b.size();

        // 缓存从0~len，长度为len+1
        vector<vector<int>> dp = vector(len1 + 1, vector<int>(len2 + 1, 0));

        // ' '与' '是一样的
        dp[0][0] = 0;

        // ' '与b[j]是肯定不一样的
        for (int j = 1; j <= len2; j++)
            dp[0][j] = dp[0][j - 1] + 1;

        // ' '与a[i]是肯定不一样的
        for (int i = 1; i <= len1; i++)
            dp[i][0] = dp[i - 1][0] + 1;

        // 从a[1] b[1]开始遍历, 从左往右 从上到下填充用dp[i-1][j-1]填充dp[i][j]
        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                dp[i][j] = min(dp[i][j - 1] + 1, dp[i - 1][j] + 1);

                if (a[i] == b[j])
                    dp[i][j] = dp[i - 1][j - 1];
            }
        }
        return dp[len1][len2];
        // dfs(a, b, a.size(), b.size());
    }
    // 遍历到a[i]与b[j]，看怎么删 能让a b一样，并且删得次数最小
    int dfs(string a, string b, int i, int j)
    {
        // base case, 走到底了
        if (i == -1 && j == -1)
            return 0;
        if (i == -1)
            // a到底了 只能删b[j]
            return dfs(a, b, -1, j - 1) + 1;
        if (j == -1)
            // b到底了 只能删a[i]
            return dfs(a, b, i - 1, -1) + 1;

        // 如果a[i]==b[j]就不用删，否则 删a[i],不删b[j]，或者删b[j]不删a[i]
        int cur = min(dfs(a, b, i - 1, j) + 1, dfs(a, b, i, j - 1) + 1);
        if (a[i] == b[j])
            cur = min(cur, dfs(a, b, i - 1, j - 1));
        return cur;
    }
};