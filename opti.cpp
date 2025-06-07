#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
#define int long long
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
map<pair<int, int>, int> pts;

struct node{
  int x, y, val;
};

int n, m;
int N,K;
vector<node> crystal, mine;
vector<node>buildings;
int achieved;
int totalPositive;
int totalNegative; 
int total;
int total_achieved;

void _input(){
  pts.clear();
  cin >> N >> K;
  n=0,m=0;
  buildings.clear();
  buildings.resize(N);
  crystal.clear();
  mine.clear();
  totalPositive = 0;
  totalNegative = 0;
  for(int i = 0; i < N; i++){
    cin >> buildings[i].x >> buildings[i].y >> buildings[i].val;
    if(buildings[i].val<0){
      crystal.push_back(buildings[i]);
      n++;
    }
    else{
      mine.push_back(buildings[i]);
      m++;
    }
  }
  for(int i = 0; i < n; i++){
    crystal[i].val*=-1;
    totalPositive += crystal[i].val;
    pts[{crystal[i].x, crystal[i].y}] += crystal[i].val;
  }
  for(int i = 0; i < m; i++){
    mine[i].val *= -1;
    totalNegative += mine[i].val;
    pts[{mine[i].x, mine[i].y}] += mine[i].val;
  }
}
