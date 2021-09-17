class Solution
{
public:
    // 求一下nums是否有长度的mid的子数组其和>=target
    vector<int> ar; // 打印一下二分结果

    int check(int target, vector<int> &nums, int mid)
    {
        // l r左右指针
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            // sum初始化长度为i
            if (i < (mid - 1))
                continue;
            // 初始化之后一定要先judge一次（用do while也行）
            if (sum >= target)
            {
                this->ar.insert(ar.begin() + mid, 0);
                return 0;
            }
            sum -= nums[i - (mid - 1)];
        }
        return -1;
    }

    int minSubArrayLen(int target, vector<int> &nums)
    {
        // 如果是暴力的话，就是假设“满足其和 ≥ target 的长度最小的连续子数组”的长度为0 1 2 3 ... nums.size()
        // 那还不如先假设长度是nums.size()/2，拿这个长度去求是否“满足要求”
        // 即二分的是子数组长度，范围是[1, nums.size()]。。不可能数组长度为0吧

        // 有个tricky的点就是弄一个nums.size()+1，这样一个不可能的长度，道理跟双指针里面int res = INT_MAX;这句话一样
        // 即nums.size()是合法的，如果二分到nums.size()+1（最小的满足check()的长度比nums.size()还大），返回0

        int len = nums.size();
        // 可以把二分结果打印一下
        vector<int> arr(len, -1);
        this->ar = arr;

        int l = 1, r = len + 1;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            // mid为连续子数组长度
            // 即break出去之后找l r指着最左边那个满足check()的mid
            if (check(target, nums, mid) >= 0)
                r = mid;
            else
                l = mid + 1;
            cout << l << " " << r << " " << endl;
        }
        for (auto x : ar)
            cout << x << " ";
        return r > len ? 0 : r;
    }
};