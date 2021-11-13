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

##### 经典前缀和

其实就是这个前n项和S<sub>n</sub>=S<sub>n-1</sub>+a<sub>n</sub>跟

$$
\sum_{idx=m+1}^{n} a[idx] = S_n-S_m
$$

的数列公式。。

举个例子（假设下标从1开始，默认a<sub>0</sub>==S<sub>0</sub>==0）

```
1 2 1 2 1
```

前n项和S<sub>n</sub>为

```
1 3 4 6 7
```

如果k=3

这里S<sub>2</sub>-S<sub>0</sub>==k, 意味着a1+a2==k， 同理S<sub>5</sub>-S<sub>3</sub>==k => a4+a5==k

即 S<sub>n</sub>-S<sub>m</sub> = a<sub>m+1</sub>+a<sub>m+2</sub>+...a<sub>n</sub>

因为是要求连续数组，所以假设遍历到n，就是从n往左找到一个连续的sub array，其和为k

所以每次遍历到一个前n项和S<sub>n</sub>，只要看看有没有S<sub>m</sub>满足S<sub>n</sub>-k==S<sub>m</sub>即可

可以先把前n项和求出来，放到一个`vector<int> s;`里面，然后遍历s即可

但是比较tricky的一点就是这里有负数，所以当遍历到S<sub>n</sub>的时候，不只有一个S<sub>m</sub>满足S<sub>n</sub>-k==S<sub>m</sub>（否则找到S<sub>m</sub>之后res++就vans了）

比如说a<sub>n</sub>：

```
2 1 -1 2 1
```

S<sub>n</sub>：

```
2 1  2 4 5
```

这样的话，当S<sub>n</sub>==4的时候，k=2的话，前面就有两个S<sub>m</sub>满足S<sub>n</sub>-k==S<sub>m</sub>

```
[2, 1, -1], [2]
```

即现在解决：**满足S<sub>n</sub>-k==S<sub>m</sub>的S<sub>m</sub>有几个？**

就弄个`unordered_map<int, int> map;`, k-v为{某一个前n项和S<sub>n</sub>, 其个数}，每次遍历的时候更新一下map即可

其实真正只关心遍历到**某一个时刻的S<sub>n</sub>**，也不会关心**之前某一个满足S<sub>n</sub>-k==S<sub>m</sub>的S<sub>m</sub>的magnitude**，要的只是**S<sub>m</sub>到底有多少个**（放到map里面了）

所以可以只用一个for，先根据S<sub>n</sub> = a<sub>n</sub> + S<sub>n-1 </sub> 把S<sub>n</sub>求出来，其余的不变。。

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        // sn = sn-1 + an (sn = an = 0)
        // vector<int> s;
        // s.push_back(0);
        // for(auto &an : nums)
        //     s.push_back(s.back() + an);
        
        // num of Sn
        unordered_map<int, int> map;
         
        int res = 0, sn = 0;
        map[0] = 1;
        for(int i = 0; i<nums.size(); i++){
            sn += nums[i];

            if(map.count(sn-k))
                res += map[sn-k];
            map[sn]++;
        }
        return res;
    }
};
```

#### [剑指 Offer II 095. 最长公共子序列（dp）](https://leetcode-cn.com/problems/qJnOS7/)

给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列largest common subsequence的长度。如果不存在公共子序列，返回 0 

一个字符串的子序列是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的公共子序列是这两个字符串所共同拥有的子序列。

**举个例子：**

a[i]和b[j]的LCS由**a[i]和b[j-1]**，**a[i-1]与b[j]**的LCS，因为要求最大的那个，那肯定二者选最大

当然当发现**a[i]==b[j]**的时候，那a[i], b[j]的LCS直接由a[i-1]与b[i-1]的LCS+1

所以可以经典dfs一下，

```c
int dfs(string a, string b, int i, int j)
```

假设现在求**a[i], b[j]**的最大LCS，之前的条件翻译成代码as follows：

```c++
// 求a[i]和b[j]得先去看看a[i]和b[j-1] a[i-1]与b[j]的LCS
int cur = max(dfs(a, b, i, j-1), dfs(a, b, i-1, j));
if(a[i]==b[j])
	cur = dfs(a, b, i-1, j-1)+1;
```

**处理一下base case**：什么时候**a[i] b[j]**的最大LCS不用脑壳想就知道呢？

首先，当a b都为空的时候，即i j没东西，一开始直接传

```c
int dfs(a, b, -1, -1); // 没有a[-1]与b[-1]这种东西
```

那直接返回0

还有就是某个序列为空，即只有a， 没有b， or 只有b， 没有a，分别对应j==-1和i==-1

完整版本dfs：求a[len-1]与b[len-1]的最大LCS

```c
    int dfs(string a, string b, int i, int j) {
        if(i==-1 && j==-1)
            return 0;
        if(i==-1)
            return dfs(a, b, -1, j-1);
        if(j==-1)
            return dfs(a, b, i-1, -1);
        int cur = max(dfs(a, b, i, j-1), dfs(a, b, i-1, j));
        if(a[i]==b[j])
            cur = dfs(a, b, i-1, j-1)+1;
        return cur;
    }
```

分析一手，

整个递归过程到base case，下标i j递减，蹭蹭递进得先得到dfs(a, b, -1, -1); 才能知道dfs(a, b, 0, 0); and so on

所以有种下标自顶向下的感觉

**但是，发现dfs有很多重复的部分**，比如说这个

```
abc
ace
```

在dfs(a, b, 2, 2)的stack frame中，得求一下dfs(a, b, 2, 1)和dfs(a, b, 1, 2)

然后在第一个dfs(a, b, 2, 1)里面，会求dfs(a, b, 1, 1);

但是dfs(a, b, 2, 2)的stack frame中，如果a[i]==b[j]，还得求dfs(a, b, 1, 1)，这在前面dfs(a, b, 2, 1)这个子过程中已经求过了（毕竟dfs(a, b, 2, 1)这个递归全执行完才会回到dfs(a, b, 2, 2)这个frame）

所以已经求了的东西，可以先放到内存的某块区域（随你怎么放，放数组，放vector里面都可以），以备不时之需

**问题来了：如何索引我们放进去的东西？**

比如说dfs(a, b, 1, 1)和dfs(a, b, 1, 0)其实可以直接用一个**k v分别是string和int的哈希表**，毕竟“dfs(a, b, 1, 1)”与“dfs(a, b, 1, 0)”这两个字符串本来就不一样。但是发现，他们不一样的只有i j这两个参数，所以把i j参数作为二维数组的两个下标，名字无所谓，叫arr好了（其实还是得转换成一个一维地址）用来索引dfs的返回值

**这个arr数组的空间能开多大呢？**

main里面调的第一个和base case分别是

```c
int len1 = a.size(), len2 = b.size();
// from main
dfs(a, b, len1-1, len2-1);

// base case
dfs(a, b, -1, -1);
```

所以分别需要len1-1-(-1)，len2-1-(-1)的空间

**但是-1这个index是非法的**，所以整体往右边诺一格，即从`arr[0][0]`开始，表示dfs(a, b, -1, -1)这个base case，`arr[len1][len2]`结束即我们要的dfs(a, b, len1-1, len2-1)，相应的，开的空间变成了len1+1, len2+1

所以`arr[0][0]`放的是a[-1]与b[-1]的LCS，不存在！`arr[len1][len2]`放的是a[len1-1]与b[len2-1]的LCS

声明一下缓存：

```c
int arr[len1+1][len2+1];
vector<vector<int>> arr(len1+1, vector<int>(len2+1, 0));
```

现在变成求dfs(a, b, i, j-1, arr)的时候，先去看看`arr[i][j+1]`有东西没，有的话直接用，没有的话就dfs求一遍，再cache一下

```c
        if(a[i]==b[j]){
            // 去看a[i-1]与b[j-1]的LCS，先看缓存里面有没有放arr[i][j]
            if(arr[i][j])
                // retrieve from cache
                cur = arr[i][j];
            else {
                // cache
                cur = arr[i][j] = dfs(a, b, i-1, j-1, arr)+1;
            }
        }
```

**真正的动态规划**

反正都是要自顶向下，从`arr[0][0]`，也就是dfs(a, b, -1, -1)开始求，何不直接通过`arr[0][0]`从左往右，从上到下展开到`arr[len1][len2]`？

毕竟核心就是：

```c
arr[i+1][j+1] = max(arr[i][j+1], arr[i+1][j]);
```

完整版：

```c
class Solution {
public:
    int dp[1005][1005]; // 长度小于1000，开1005够了
    int longestCommonSubsequence(string a, string b) {
        int len1 = a.size(), len2 = b.size();
        
        // 从a[0] b[0]到a[len-1], b[len-1]
        // dp[0][0]放base case，即a[-1]与a[-1]的最大LCS
        // dp[len1][len2]放的是a[len1-1]与b[len2-1]的最大LCS
        for(int i = 0; i<len1; i++) {
            for(int j = 0; j<len2; j++) {
				// 所以a[0][j]与a[i][0]这两排都是0,
                // 相当于dfs(a, b, -1, 0)与dfs(a, b, 0, -1)
                dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
                if(a[i]==b[j])
                    dp[i+1][j+1] = dp[i][j] + 1;
            }
        }
        return dp[len1][len2];
    }
};
```

跟LCS差不多的一个：

#### [712. 两个字符串的最小ASCII删除和](https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/)