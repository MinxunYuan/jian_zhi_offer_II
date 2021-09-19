class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {

        // sn = sn-1 + an (sn = an = 0)
        // vector<int> s;
        // s.push_back(0);
        // for(auto &an : nums)
        //     s.push_back(s.back() + an);

        // num of Sn
        unordered_map<int, int> map;

        int res = 0, sn = 0;
        map[0] = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            sn += nums[i];

            if (map.count(sn - k))
                res += map[sn - k];
            map[sn]++;
        }
        return res;
    }
};