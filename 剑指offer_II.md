#### [剑指 Offer II 008. 和大于等于 target 的最短子数组](https://leetcode-cn.com/problems/2VG8Kg/)

给定一个含有 `n` 个正整数的数组和一个正整数 `target` **。**

找出该数组中满足其和 `≥ target` 的长度最小的 **连续子数组** `[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度**。**如果不存在符合条件的子数组，返回 `0` 。

 **示例 1：**

```
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
```

##### 经典双指针

l r分别为nums数组左右指针，设置循环变量
$$
cur = \sum_{idx=l}^{r} nums[idx]
$$

> 这里cur取不取得到左指针还是比较tricky的

res为符合题意的nums子数组的长度，即nums[l]+...nums[r]>=target

当cur<target的时候r往右跑，直到cur>=target

此时l循环往右跑，直到不满足循环条件while(cur>=target)就出来更新一下新的res

注意这里现在nums[l]指着的是满足情况的元素的下一个，即此时
$$
\sum_{idx=l-1}^{r} nums[idx] \ge target
$$
所以res = r-(l-1)-1; 每次找最小的res，即res = min(res, r-l+2);

```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int res = INT_MAX;
        for(int i = 0, j = 0, cur = 0; i<nums.size(); i++){
            // cur = ∑ of nums[i~j]
            // 当cur<target, i往右走
            // 当cur>=target, j往左走
            // 找到 min(cur)
            
            cur += nums[i];
            // cur < target不会去下面那个while的，只会一直在for里面i++
            while (j<=i && cur>=target)
                cur-=nums[j++];}
            if (j>0)
                res = min(res, i-j+2);
        }
        return res==INT_MAX ? 0 : res;
    }
};
```

（关于有没有必要把res写在while里面）

理论上来说当r不动，l往右跑，是不可能比原来那个res小的（只有进while，l才会往右跑）

但是忘了弄一个corner case，就是l没有动的情况。。如果这个时候没有判断(cur>=target)才更新res的话，那res永远都是2（l没动永远是0，所以res初始就是2）



##### 经典二分

如果是暴力的话，即从长度`len`从1到`nums.size()`遍历一边，看是否有`len`满足题目的条件

```c++
int l = 1, r = nums.size(); 
```

那还不如先假设长度是 `mid = (l+r)>>1` 拿这个长度去求是否**“满足题目要求”**（抽象成check()）如果这个长度比target小，那就弄个长一点的长度，否则换个小一点的长度……

直到找到最左边的那个check(mid); 也就是长度最小的 **连续子数组**

因为要求是否有长度为mid的子数组，即转换成了一个**定长双指针**问题。。

> 定长双指针 求有没有长度为mid且和为target的子数组

```c++
int check(int target, vector<int>& nums, int mid) {
    int sum = 0;
    for (int i = 0; i<nums.size(); i++) {
		// 初始化长度为mid, 即先让sum里面充满mid个
        sum += nums[i];
        if (i < (mid-1)) 
            continue;
        // 甚至连左指针也不用。。因为i-(mid-1)就是脑壳
       	if (sum >= target)
            return 0;
        sum -= nums[i - (mid - 1)];
    }
    // 没找到返回-1
    return -1;
}
```

（当然前缀和+二分也可以）

其实也可以把check(mid)的结果给mapping到一个`vector<int>`

然后就是二分了

```c++
int minSubArrayLen(int target, vector<int>& nums) {
	len = nums.size();
    
    // 二分子数组长度，从[1, len]，故意弄个len+1出来预防corner case
    int l = 1, r = len+1;
    while(l<r){
        int mid = (l+r)>>1;
        if(check(target, nums, mid)>=0)
            r = mid;
        else
            l = mid + 1;
    } 
    return r>len ? 0:r;
}
```

有个tricky的点就是把右边界r弄成`nums.size()+1`，搞一个不可能的长度出来、

道理跟双指针里面`int res = INT_MAX`这句话一样

来针对这个corner case。。

**示例 3：**

```
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
```

相当于一直valid的mid都返回-1，最后出来返回len+1这个**故意设置**的illegal的长度，说明不存在符合条件的子数组（毕竟一直不满足情况的话，r不会动，l不断逼近r，直到l==r，break出去）

#### [剑指 Offer II 010. 和为 k 的子数组](https://leetcode-cn.com/problems/QTMn0o/)

给定一个整数数组和一个整数 `k` **，**请找到该数组中和为 `k` 的连续子数组的个数。

**示例 1 :**

```
输入:nums = [1,1,1], k = 2
输出: 2
解释: 此题 [1,1] 与 [1,1] 为两种不同的情况
```