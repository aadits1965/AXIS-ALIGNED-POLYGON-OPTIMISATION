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

pair<int, set<pair<pair<double, double>, pair<double, double>>>> generate_stripperX(int threshold){
  map<int, int> m;  
  map<double, double> e1, e2;
  for(auto i : crystal){
    m[i.x] += i.val;
  }
  for(auto i : mine){
    m[i.x] += i.val;
  }
  vector<pair<int, pair<int, int>>> v;
  int curr = 0;
  int st = 0;
  for(int i = 0; i <= 1e4; i++){
    if(m[i] >= threshold){
      curr += m[i];
    }
    else{
      if(st == i){
        curr = 0;
        st++;
        continue;
      }      
      v.push_back({curr, {st, i - 1}});
      curr = 0;
      st = i + 1;
    }
  }
  if(curr > 0) v.push_back({curr, {st, 10000}});
  sort(rall(v));
  int cost = 0;
  vector<pair<pair<double, double>, pair<double, double>>> edgeH, edgeV; 
  set<pair<pair<double, double>, pair<double, double>>> fin;
  for(int i = 0; i < min((int) v.size(), 250ll); i++){
    if(v[i].first <= 0) break;
    double st = v[i].second.first;
    double en = v[i].second.second;
    if(st == en) en += 0.5;
    edgeV.push_back({{st, 0}, {st, 1e4}});
    edgeV.push_back({{en, 0}, {en, 1e4}});
    edgeH.push_back({{st, 0}, {en, 0}});
    edgeH.push_back({{st, 1e4}, {en, 1e4}});
    e1[st] = en;
    e1[en] = st;
    e2[st] = en;
    e2[en] = st;
    cost += v[i].first;
  }
  for(auto i : edgeV) fin.insert(i);
  for(auto i : edgeH) fin.insert(i);
  sort(all(edgeH));
  sort(all(edgeV));
  int ex = 0;
  for(int i = 0; i + 2 < edgeH.size(); i += 2){
    int up = 0;
    int down = 0;
    for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
      up += pts[{j, 0}];
    }
    for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
      down += pts[{j, 1e4}];
    }
    double pehle = edgeH[i].second.first;
    double baad = edgeH[i + 2].first.first;
    if(up >= down){
      fin.erase({{e1[pehle] , 0}, {pehle, 0}});
      fin.erase({{baad, 0}, {e1[baad], 0}});
      fin.insert({{e1[pehle], 0}, {e1[baad], 0}});
      fin.insert({{pehle, 0.5}, {baad, 0.5}});
      fin.erase({{pehle, 0}, {pehle, 1e4}});
      fin.erase({{baad, 0}, {baad, 1e4}});
      fin.insert({{pehle, 0.5}, {pehle, 1e4}});
      fin.insert({{baad, 0.5}, {baad, 1e4}});
      e1[e1[baad]] = e1[pehle];      
      ex += up;
    }
    else{
      fin.erase({{e2[pehle] , 1e4}, {pehle, 1e4}});
      fin.erase({{baad, 1e4}, {e2[baad], 1e4}});
      fin.insert({{e2[pehle], 1e4}, {e2[baad], 1e4}});
      fin.insert({{pehle, 9999.5}, {baad, 9999.5}});
      fin.erase({{pehle, 0}, {pehle, 1e4}});
      fin.erase({{baad, 0}, {baad, 1e4}});
      fin.insert({{pehle, 0}, {pehle, 9999.5}});
      fin.insert({{baad, 0}, {baad, 9999.5}});
      e2[e2[baad]] = e2[pehle];
      ex += down;
    }
  }
  achieved = max(achieved, cost + ex);
  return {cost + ex, fin};
}

pair<int, set<pair<pair<double, double> , pair<double, double>>>> generate_stripperY(int threshold){
  map<int, int> m;  
  map<double, double> e1, e2;
  for(auto i : crystal){
    m[i.y] += i.val;
  }
  for(auto i : mine){
    m[i.y] += i.val;
  }
  vector<pair<int, pair<int, int>>> v;
  int curr = 0;
  int st = 0;
  for(int i = 0; i <= 1e4; i++){
    if(m[i] >= threshold){
      curr += m[i];
    }
    else{
      if(st == i){
        curr = 0;
        st++;
        continue;
      }      
      v.push_back({curr, {st, i - 1}});
      curr = 0;
      st = i + 1;
    }
  }
  if(curr > 0) v.push_back({curr, {st, 10000}});
  sort(rall(v));
  int cost = 0;
  vector<pair<pair<double, double>, pair<double, double>>> edgeH, edgeV; 
  set<pair<pair<double, double>, pair<double, double>>> fin;
  for(int i = 0; i < min((int) v.size(), 250ll); i++){
    if(v[i].first <= 0) break;
    double st = v[i].second.first;
    double en = v[i].second.second;
    if(st == en) en += 0.5;
    edgeV.push_back({{st, 0}, {st, 1e4}});
    edgeV.push_back({{en, 0}, {en, 1e4}});
    edgeH.push_back({{st, 0}, {en, 0}});
    edgeH.push_back({{st, 1e4}, {en, 1e4}});
    e1[st] = en;
    e1[en] = st;
    e2[st] = en;
    e2[en] = st;
    cost += v[i].first;
  }
  for(auto i : edgeV) fin.insert(i);
  for(auto i : edgeH) fin.insert(i);
  sort(all(edgeH));
  sort(all(edgeV));
  int ex = 0;
  for(int i = 0; i + 2 < edgeH.size(); i += 2){
    int up = 0;
    int down = 0;
    for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
      up += pts[{0, j}];
    }
    for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
      down += pts[{1e4, j}];
    }
    double pehle = edgeH[i].second.first;
    double baad = edgeH[i + 2].first.first;
    if(up >= down){
      fin.erase({{e1[pehle] , 0}, {pehle, 0}});
      fin.erase({{baad, 0}, {e1[baad], 0}});
      fin.insert({{e1[pehle], 0}, {e1[baad], 0}});
      fin.insert({{pehle, 0.5}, {baad, 0.5}});
      fin.erase({{pehle, 0}, {pehle, 1e4}});
      fin.erase({{baad, 0}, {baad, 1e4}});
      fin.insert({{pehle, 0.5}, {pehle, 1e4}});
      fin.insert({{baad, 0.5}, {baad, 1e4}});
      e1[e1[baad]] = e1[pehle];    
      ex += up;
    }
    else{
      fin.erase({{e2[pehle] , 1e4}, {pehle, 1e4}});
      fin.erase({{baad, 1e4}, {e2[baad], 1e4}});
      fin.insert({{e2[pehle], 1e4}, {e2[baad], 1e4}});
      fin.insert({{pehle, 9999.5}, {baad, 9999.5}});
      fin.erase({{pehle, 0}, {pehle, 1e4}});
      fin.erase({{baad, 0}, {baad, 1e4}});
      fin.insert({{pehle, 0}, {pehle, 9999.5}});
      fin.insert({{baad, 0}, {baad, 9999.5}});
      e2[e2[baad]] = e2[pehle];
      ex += down;
    }
  }
  achieved = max(achieved, cost + ex);
  achieved = max(achieved, cost + ex);
  return {cost + ex, fin};
}
