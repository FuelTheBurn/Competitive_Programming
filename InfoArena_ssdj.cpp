//My solution didn't use a single stack :P
//So the idea is like the solution of CF Rectangles problem:https://usaco.guide/problems/cf-rectangles/solution, you should do this problem first and understand its solution of else this won't make sense
//Only 26 letters in the alphabet, iterate a-z (variable k in my code), start with N x N zeroes (oneZero), on first iteration you convert all a's to 1, then all b's to 1 (the a's still stay 1), and so on.

//Do the prefix sum (pSum) with the 1's for each row like in CF Rectangles
//You find a 0, signifying that the grid contains a high letter, and fix it as top left corner. Take the number of the prefix sum (pSum) to the right of the top left corner 0, and add 1 to that value; this is your maximum rectangle width. Then you look at the next row, and if it is shorter in 1's, you can take the point represented by the 0 after the 1's to create a working rectangle (the bottom right point). 
//Repeat this until you encounter a 0 in prefix sum, in which you reset everything and fix this as the new top left corner.
//to avoid overcounting, take min(top left point, bottom right point), and only add it to the answer if it equals k+1
#include <bits/stdc++.h>
#include <algorithm> //__gcd(a,b);
using namespace std;


void setIO(string s) {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
}

using ll = long long;
using ld = long double;
using db = double;
using str = string;

typedef long long ll;
typedef vector<ll> vl; 
typedef vector<pair<ll,ll>> vpl; 
 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x) //will not work for bool
#define travBool(a,x) for (auto a: x)
#define print(x) trav(a,x){cout<<a<<" ";}cout<<endl; //will not work for bool
#define printPair(x) trav(a,x){cout<<"{"<<a.first<<" "<<a.second<<"} ";}cout<<endl; //will not work for bool
#define printBool(x) travBool(a,x){cout<<a<<" ";}cout<<endl;
#define print2d(x) trav(a,x){trav(b,a){cout<<b<<" ";}cout<<endl;}
#define print2dBool(x) trav(a,x){travBool(b,a){cout<<b<<" ";}cout<<endl;}
#define doPrefixSum2d(data, prefixSum,x,y){prefixSum.resize(x,vector<ll>(y,0));F0R(i,x){prefixSum[i][0]=0;}F0R(j,y){prefixSum[0][j]=0;}FOR(i,1,x){FOR(j,1,y){prefixSum[i][j]=data[i][j]+prefixSum[i-1][j]+prefixSum[i][j-1]-prefixSum[i-1][j-1];}}}//x and y are the size of prefixSum and data including the first row of 0s
#define printQueue(q){auto copyOfQ=q;if(copyOfQ.empty()){cout<<"empty";}while(!copyOfQ.empty()){cout<<copyOfQ.front()<<" ";copyOfQ.pop();}cout<<endl;}
#define printDeque(q){auto copyOfQ=q;if(copyOfQ.empty()){cout<<"empty";}while(!copyOfQ.empty()){cout<<copyOfQ.front()<<" ";copyOfQ.pop_front();}cout<<endl;}
#define printDequePair(q){auto copyOfQ=q;if(copyOfQ.empty()){cout<<"empty";}while(!copyOfQ.empty()){cout<<"{"<<copyOfQ.front().first<<" "<<copyOfQ.front().second<<"} ";copyOfQ.pop_front();}cout<<endl;}
#define printStack(q){auto copyOfQ=q;if(copyOfQ.empty()){cout<<"empty";}while(!copyOfQ.empty()){cout<<copyOfQ.top()<<" ";copyOfQ.pop();}cout<<endl;} //printed backwards, last in first out occurs first in the print


#define pb push_back
#define pf push_front //for deques
#define rsz resize
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second

const int MOD = 1e9+7; // 998244353; //this is a completely different unrelated prime number
//const __int128 MOD = 13000000000000019; prime number, for hashing shit
const int MX = 2e5+5;
const ll INF = 1e18; // not too close to LLONG_MAX
const ld PI = acos((ld)-1);

bool debug=false;
bool ysort(const pair<ll,ll>& x, const pair<ll,ll>& y){
    return x.s<y.s;
}
vector<vector<ll>> grid;
//a is 97
ll N=0;
vector<ll> p;
deque<ll> A;
deque<pair<ll,ll>> B;
stack<ll> C;
vector<vector<ll>> oneZero;
int main(){
    //same messages as above, just more convenient right next to the code
    
	//My solution didn't use a single stack :P
	//So the idea is like the solution of CF Rectangles problem:https://usaco.guide/problems/cf-rectangles/solution, you should do this problem first and understand its solution of else this won't make sense
	//Only 26 letters in the alphabet, iterate a-z (variable k in my code), start with N x N zeroes (oneZero), on first iteration you convert all a's to 1, then all b's to 1 (the a's still stay 1), and so on.

	//Do the prefix sum (pSum) with the 1's for each row like in CF Rectangles
	//You find a 0, signifying that the grid contains a high letter, and fix it as top left corner. Take the number of the prefix sum (pSum) to the right of the top left corner 0, and add 1 to that value; this is your maximum rectangle width. Then you look at the next row, and if it is shorter in 1's, you can take the point represented by the 0 after the 1's to create a working rectangle (the bottom right point). 
    //Repeat this until you encounter a 0 in prefix sum, in which you reset everything and fix this as the new top left corner.
	//to avoid overcounting, take min(top left point, bottom right point), and only add it to the answer if it equals k+1
	

    setIO("ssdj");
    cin>>N;
    ll ans=0;
    grid.rsz(N,vector<ll>(N));
    oneZero.rsz(N,vector<ll>(N,0));
    F0R(i,N){
        F0R(j,N){
            char a;
            cin>>a;
            ll x=((ll)a)-96;
            grid[i][j]=x;
        }
    }
    //print2d(grid);
    FOR(k,1,26){
        //cout<<"k "<<k<<endl;
        //cout<<k<<" turns into 1"<<endl;
        F0R(i,N){
            F0R(j,N){
                //cout<<grid[i][j]<<endl;
                //cout<<k<<endl;
                if(grid[i][j]==k){
                    //cout<<"yay"<<endl;
                    oneZero[i][j]=1;
                }
            }
        }
        vector<vector<ll>> pSum;
        //print2d(oneZero);
        pSum.rsz(N,vector<ll>(N,0));
        F0R(i,N){
            ll cur=0;
            R0F(j,N){
                if(oneZero[i][j]==1){
                    cur++;
                }
                else{
                    cur=0;
                }
                pSum[i][j]=cur;
            }
        }
        //print2d(pSum);
        F0R(j,N-1){
            //cout<<"j "<<j<<endl;
            F0R(i,N-1){
                if(pSum[i][j]==0){
                    ll original=grid[i][j];
                    //cout<<i<<" "<<j<<endl;
                    ll mi=pSum[i][j+1]+1;
                    //cout<<i<<endl;
                    i++;
                    while(mi!=0&&i<=N-1&&pSum[i][j]!=0){
                        //cout<<"gate "<<pSum[i][j]<<endl;
                        if(mi>pSum[i][j]){
                            mi=pSum[i][j];
                            //cout<<"w"<<endl;
                            if((min(grid[i][j+mi],original)==k+1)){
                                //cout<<"ans"<<endl;
                                ans++;
                            }
                        }
                        i++;
                    }
                    i--;
                    //cout<<i<<endl;

                }

            }
        }
        
    }
    cout<<ans<<endl;
}