#include<iostream>
#include<cmath>
using namespace std;

int main(){
    int table[128][128];
    int n; cin >> n;
    for(int i = 0; i< n; i ++){
        for(int j= 0; j < n; j ++){
            cin >> table[i][j];
        }
    }
    for(int i = 1; i < n; i ++){
        table[i][0] += table[i-1][0];
        table[0][i] += table[0][i-1];
    }
    for(int i = 1; i < n; i ++){
        for(int j = 1; j < n; j ++){
            table[i][j] += min(table[i-1][j], table[i][j-1]);
        }
    }
    cout << "ANSWER: " << table[n-1][n-1] << endl;
    return 0;
}
