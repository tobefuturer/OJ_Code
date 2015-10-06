
//最多约数问题
//http://ncc.neuq.edu.cn/oj/problem.php?id=1251


//题解(思路分析基本正确 但是贴的代码有点问题)
//http://blog.csdn.net/net_assassin/article/details/8960725


#include <math.h>
#include <iostream>
using namespace std;

#define debug 0

const long MAXP = 100000;
long prime[MAXP];
long cur_max, cur_num, PRIME_NUM; //max存放最多约数个数，numb存放约数个数最多的数
void primes();          //用筛选法产生质数存于prim数组中
void search(long cur_index, long tot, long num, long low, long up);
void search2(long cur_index, long tot, long num, long low, long up);

int counter = 0;

int main()
{
    primes();
    long l, u;
    cin >> l >> u;
    if ((l == 1) && (u == 1))
    {
        cur_max = 1;
        cur_num = 1;
    }
    else
    {
        cur_max = 2;
        cur_num = l;
        search(1, 1, 1, l, u);
    }
    
    cout << cur_max << endl;
    if (debug) {
        cout << cur_num << endl;
        cout << counter<< endl;
    }
    return 0;
}

void primes()
{
    bool get[MAXP+1];
    long i;
    for (i = 2; i <= MAXP; i++)
        get[i] = true;
    for (i = 2; i <= MAXP; i++)
        if (get[i])
        {
            long j = i + i;
            while (j <= MAXP)
            {
                get[j] = false;
                j += i;
            }
        }
    long ii, j;
    for (ii = 2, j = 0; ii <= MAXP; ii++)
        if (get[ii]) prime[++j] = ii;
    PRIME_NUM = j;
}

void search(long cur_index, long tot, long num, long low, long up)
{
    
    if (num >= 1){
        if ( (tot > cur_max) || ((tot == cur_max) && (num < cur_num)) )
        {
            cur_max = tot;
            cur_num = num;
        }
    }
    if ((low == up) && (low > num)) {
        search(cur_index, tot*2, num*low, 1, 1);
    }
    
    for (long i = cur_index; i <=PRIME_NUM; i++)
    {
        counter ++;
        
        if (debug) printf("i : %ld , tot : %ld , num : %ld, low : %ld, up : %ld\n", prime[cur_index], tot, num, low, up);
        
        
        if (prime[i] > up) return;
        else
        {
            long j = prime[i], x = low - 1, y = up, n = num, t = tot;
            while (true)
            {
                t += tot;
                x /= j;
                y /= j;
                n *= j;
                
                if (x == y) break;
                search(i+1, t, n, x+1, y);
            }
            double m = pow(2.0, (log10(up) / log10(j)) + 1);
            if (tot * m < cur_max)
            {
                return;
            }
            
        }
    }
}

bool need_prune(long cur_prime, long cur_tot,long up){
    double t = (log10(up) / log10(cur_prime));
    double m = pow(2.0,  t);
    //cur_up < cur_prime 防止浮点数比较的误判
    if (up < cur_prime || cur_tot * m <= cur_max)
    {
        return true;
    }
    
    return false;
}

//一样的递归和剪枝思路 换一种写法
void search2(long cur_index, long tot, long num, long low, long up){
    
    counter ++;
    if (debug) printf("i : %ld , tot : %ld , num : %ld, low : %ld, up : %ld\n", prime[cur_index], tot, num, low, up);
    
    if ( (tot > cur_max) || ((tot == cur_max) && (num < cur_num)) )
    {
        cur_max = tot;
        cur_num = num;
    }
    
    
    if (cur_index > PRIME_NUM) {
        if (up != 1) {
            // 搜索过程中 搜索的最大质数为sqrt(up)
            // 但最优解当中可能存在一个因子P （P是大于sqrt(up)的质数）

            //到达搜索边界时 如果搜索上界up依然不为1 cur_max的解至少为tot*2
            search2(cur_index, tot*2, num*low, 1, 1);
        }
        
        return;
    }
    
    long cur_prime = prime[cur_index];
    long cur_tot = tot;
    long n = num;
    long cur_exponent = 0;
    long cur_low = low - 1;
    long cur_up = up;
    
    
    while (true) {
        if (need_prune(cur_prime, cur_tot, cur_up)) {
            break;
        }
        
        cur_exponent += 1;
        n *= cur_prime;
        cur_low = cur_low / cur_prime;
        cur_up = cur_up / cur_prime;
        cur_tot = tot * (cur_exponent + 1);
        
        if (cur_low == cur_up) break;
        search2(cur_index + 1, cur_tot, n , cur_low + 1, cur_up);
        
    }
    
    //循环枚举当前质数的幂时 是从1次幂开始的 这里补上0次幂的情况
    //从1次幂开始枚举 是为了尽早出现一个解cur_max 可以更好的剪枝 提高效率
    if ( ! need_prune(cur_prime, tot, up)) {
        search2(cur_index + 1, tot, num , low , up);
    }
}

