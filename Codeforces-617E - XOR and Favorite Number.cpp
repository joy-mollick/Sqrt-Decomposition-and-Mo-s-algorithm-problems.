
/// Mo's algorithm 
/// Time-312 ms

/*
There you go, total complexity is O( (N + Q) * Sqrt(N)) = O( N * Sqrt(N)).

*/
/// So , our objective is to find the number of sub-arrays (ai,ai+1......aj) whose xor will give you k inside the range (L,R)
/// so, subarray xor is like  prefixxor[L-1]^prefixxor[R]=xor of all(a(L),.......a(R)).
/// We have to find out the number of pairs (i,j) for which prefixxor[i]^prefixxor[j] will be equal to k . where L-1 <=i <= j <=R.
/// For each i ,we have to take into account frequency of such j which will give  prefixxor[i]^prefixxor[j]=k.
/// Pre-compute prefixxor ,then it is easy problem .

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct query{
	int l;
	int r;
	int i;
};

query Q[100001];
int arr[100001] ;
long long query_ans[100001];
int freq[1 << 20];/// it will keep the frequency of pref[i]
long long such_pairs=0;
int block_size;

bool comp(query a , query b)
{
	if(a.l / block_size != b.l/block_size)
	return a.l/block_size < b.l/block_size;

	return a.r < b.r;
}

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	int n , q,k;
	cin>>n>>q>>k;
	block_size=(int) sqrt (n + 1) + 1;/// we will deal with pref array of xor ,so take according to (n+1)
	for(int i=0;i<n;i++)
	cin>>arr[i];

	vector<int> pref(n + 1,0);
    for (int i =0; i <n; i++) {
        pref[i+1] = pref[i]^arr[i];
    }


	for(int i=0;i<q;i++){
		cin>>Q[i].l>>Q[i].r;
		Q[i].i = i ;
		/// sybarray xor will have pref[l-1] ^ pref[r]
        Q[i].l-- ; /// make zero based indexed
        Q[i].r; /// make zero based indexed
	}

	sort(Q , Q+q , comp);

	int curL = 0 , curR = -1;


	int i,j;

	for( j=0;j<q;j++)

    {

        int L = Q[j].l;
		int R = Q[j].r;
        int xorr;
        /// when curL < L , removing numbers from curL....to L-1.
        for(i=curL;i<=L-1;i++)
        {
            freq[pref[i]]--;/// removing element
            xorr=pref[i]^k;///the prefix xor which can make k with pref[i]
            such_pairs-=(long long)freq[xorr];///those who will make xor of subarray equal to k are deleted
        }

        /// when curL > L , adding elements from L to curL-1 as curL is already in
        for(i=L;i<=curL-1;i++)
        {
            xorr=pref[i]^k;/// the prefix xor which can make k with pref[i]
            such_pairs+=(long long)freq[xorr];/// those who will make xor of subarray equal to k are added
            freq[pref[i]]++;/// adding element
        }

        /// when curR < R , adding elements from curR+1 to R
        for(i=curR+1;i<=R;i++)
        {
            xorr=pref[i]^k;/// the prefix xor which can make k with pref[i]
            such_pairs+=(long long)freq[xorr];/// those who will make xor of subarray equal to k are added
            freq[pref[i]]++;/// adding element
        }

        /// when curR > R , removing elements from R+1 ..... to curR
        for(i=R+1;i<=curR;i++)
        {
            freq[pref[i]]--;/// removing element
            xorr=pref[i]^k;///the prefix xor which can make k with pref[i]
            such_pairs-=(long long)freq[xorr];///those who will make xor of subarray equal to k are deleted
        }

        query_ans[Q[j].i]=such_pairs;
        curL=L;
        curR=R;
    }

    for(j=0;j<q;j++)
    {
        cout<<query_ans[j]<<'\n';
    }

    return 0;
}

