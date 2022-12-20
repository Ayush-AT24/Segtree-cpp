#pragma GCC optimize("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
 
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define all(cont) cont.begin(), cont.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define MP make_pair
#define PB push_back
#define MOD 1000000007
#define ll long long
#define ld long double
#define el '\n'
#define sp ' '
#define S second
#define F first
#define vi vector<int>
#define vl vector <long long int>
#define vop vector<pair<ll,ll>>
#define vov vector<vector<ll>>
#define dbg(x)      cout << #x << " is " << x << endl;
 
 
 
 
mt19937 rng (chrono::high_resolution_clock::now().time_since_epoch().count());
template <typename A, typename B> ostream& operator<< (ostream &cout, pair<A, B> const &p) { return cout << "(" << p.first << ", " << p.second << ")"; }
template <typename A> ostream& operator<< (ostream &cout, vector<A> const &v) {cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template <typename A, typename B> istream& operator>> (istream& cin, pair<A, B> &p) {cin >> p.first; return cin >> p.second;}
template <typename A> istream& operator>> (istream& cin, vector<A> &x){for(int i = 0; i < x.size()-1; i++) cin >> x[i]; return cin >> x[x.size()-1];}
 
void test_case(){
    ll n, q;
    cin >> n >> q;
    vl a(n);
    REP(i, n)
    {
        cin >> a[i];
    }
 
 
    while(__builtin_popcount(n) != 1)
    {
        a.push_back(0);
        n++;
    }
 
    // Buidling tree
 
 
    vector<ll> tree(2*n);
 
    for(int i = 0; i < n; i++)
    {
        tree[n+i] = a[i];
    }
 
    for(int i = n-1; i>=1; i--)
    {
        tree[i] += tree[2*i] + tree[2*i+1];
    }
 
 
    // search function
 
 
    function<ll(ll, ll, ll, ll, ll)> func;
    
    func = [&](ll node, ll l, ll r,ll ql,ll qr)->ll{
        if(l >= ql && qr >= r)
            return tree[node];
        if(r < ql || l > qr)
            return 0;
        ll div = (l+r)/2;
        return func(2*node, l, div, ql, qr) + func(2*node+1, div+1, r, ql, qr);
    };


    // update


    function<void(ll,ll)> point_update;


    point_update = [&](ll i, ll v){
        tree[n+i] = v;

        for(int j = (n+i)/2; j >= 1; j/=2)
        {
            tree[j] = tree[2*j] + tree[2*j+1];
        }

    };
 
 
    // querries

 
    while(q--)
    {
        ll type, lo, hi;
        cin >> type >> lo >> hi;
        lo--; hi--;
        if(type == 1) hi++;
 
        if(type == 1)
            point_update(lo, hi);
        else
            cout << func(1, 0, n-1, lo, hi) << el;
    }
}
 
int main() {
ios_base::sync_with_stdio(0);
cin.tie(0); cout.tie(0); 
int t=1;
// cin>>t;
while(t--) test_case();
return 0;
}
