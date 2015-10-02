//
//  main.cpp
//  OJ
//
//  Created by jun on 15/10/3.
//  Copyright © 2015年 jun. All rights reserved.
//



// SDUT OJ 1704
// 数位统计问题
// http://acm.sdut.edu.cn/sdutoj/problem.php?action=showproblem&problemid=1704


#include <iostream>
using namespace std;


int ans[10];
int n;

int main(int argc, const char * argv[]) {
    
    cin >> n;
    

    for (int p = 1; n / p > 0; p *= 10) {
        //p=100时 表示计算百位
        
        
        
        int cir = n / (p * 10); // 当前位置左边（高位）部分的数字
        int cur = n / p % 10; // 当前位置的数字
        int mod = n % p; // 当前位置右边（低位）部分的数字
        
        
        for (int i = 0; i < 10; i ++) {
            ans[i] += cir * p;
        }
        
        for (int i = 0; i < cur; i ++) {
            ans[i] += 1 * p;
        }
        
        ans[cur] += mod + 1;
    }
    

    
    //计算多余的前导0个数
    int count_0 = 0;
    for (int p = 1; n / p > 0; p *= 10) {
        count_0 += p;
    }
    ans[0] -= count_0;
    
    
    for (int i = 0; i < 10; i ++) {
        cout << ans[i] << endl;
    }

    return 0;
}
