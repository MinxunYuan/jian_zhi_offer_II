class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int res = INT_MAX;
        for (int i = 0, j = 0, cur = 0; i < nums.size(); i++)
        {
            // cur = ∑ of nums[i~j]
            // 当cur<target, i往右走
            // 当cur>=target, j往左走
            // min(cur)

            cur += nums[i];
            // cur < target不会去下面那个while的，只会一直for
            while (j <= i && cur >= target)
            {
                cur -= nums[j++];
                // res = min(res, i-j+2);
            }
            if (j > 0)
                res = min(res, i - j + 2);
            cout << i << " " << j << " " << res << endl;

            // if (cur>=target) res = min(res, i-(j-1)+1);
            // 出while之后cur<target, 但是∑ nums[j-1, i] >= target
            // 所以算的长度应该是i-(j-1)+1

            // 或者是intuitive一点，如果j往右滑一个之后，cur还比target大，那就滑，
            // while(cur-nums[j]>=target){
            //     cur -= nums[j++];
            //     cout<<i<<" "<<j<<endl;
            // }
            // 所以这种情况i==5，j==3的时候进while，出去之后j==4，保证∑ nums[j, i] >= target
            // 相当于就是找每一个i对应的最短的[j~i]
            // if (cur>=target) res = min(res, i-j+1);
        }
        return res == INT_MAX ? 0 : res;
    }
};