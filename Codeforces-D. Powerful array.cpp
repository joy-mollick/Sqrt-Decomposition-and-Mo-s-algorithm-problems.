
/// Mo's algorithm explanation and implementation of a good problem
/// Time-3.280s

/*
There you go, total complexity is O( (N + Q) * Sqrt(N)) = O( N * Sqrt(N)).

*/

/// power of sub-array (L....R)
/// freqi*freqi*i , where i goes from L to R .

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct query{
	int l;
	int r;
	int i;
};

query Q[200001];
int arr[200001] ;
ll query_ans[200001];
int freq[1000001];
ll power_subarray=0ll;
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


	int n , q;
	cin>>n>>q;
	block_size=(int) sqrt (n + .0) + 1;
	for(int i=0;i<n;i++)
	cin>>arr[i];

	for(int i=0;i<q;i++){
		cin>>Q[i].l>>Q[i].r;
		Q[i].i = i ;
        Q[i].l-- ; /// make zero based indexed
        Q[i].r--; /// make zero based indexed
	}

	sort(Q , Q+q , comp);

	int curL = 0 , curR = -1;
	ll pref_freq;
    ll curr_pref;

	int i,j;

	for( j=0;j<q;j++)

    {

        int L = Q[j].l;
		int R = Q[j].r;

        /// when curL < L , removing numbers from curL....to L-1.
        for(i=curL;i<=L-1;i++)
        {
            pref_freq=freq[arr[i]];///prefix frequency
            freq[arr[i]]--;/// removing element
            curr_pref=freq[arr[i]];/// current frequency

           /// as this element arr[i] is been deleted
           /// so , power of prefix will be deleted
           /// and new_power will be added thought of prefix freq has been changed
           /// So , the new power will be accordingly to the curr freq.
           power_subarray-=(pref_freq*pref_freq*(ll)arr[i]);
           power_subarray+=(curr_pref*curr_pref*(ll)arr[i]);
        }

        /// when curL > L , adding elements from L to curL-1 as curL is already in
        for(i=L;i<=curL-1;i++)
        {
            pref_freq=freq[arr[i]];///prefix frequency
            freq[arr[i]]++;/// adding element
            curr_pref=freq[arr[i]];/// current frequency

             /// as this element arr[i] is been added
           /// so , power of previous prefix will be deleted
           /// and new_power will be added thought of prefix freq has been changed
           /// So ,the new power will be accordingly to the curr freq.
           power_subarray-=(pref_freq*pref_freq*(ll)arr[i]);
           power_subarray+=(curr_pref*curr_pref*(ll)arr[i]);
        }

        /// when curR < R , adding elements from curR+1 to R
        for(i=curR+1;i<=R;i++)
        {
            pref_freq=freq[arr[i]];///prefix frequency
            freq[arr[i]]++;/// adding element
            curr_pref=freq[arr[i]];/// current frequency

           /// as this element arr[i] is been added
           /// so , power of previous prefix will be deleted
           /// and new_power will be added thought of prefix freq has been changed
           /// So ,the new power will be accordingly to the curr freq.

           power_subarray-=(pref_freq*pref_freq*(ll)arr[i]);
           power_subarray+=(curr_pref*curr_pref*(ll)arr[i]);
        }

        /// when curR > R , removing elements from R+1 ..... to curR
        for(i=R+1;i<=curR;i++)
        {
            pref_freq=freq[arr[i]];///prefix frequency
            freq[arr[i]]--;/// removing element
            curr_pref=freq[arr[i]];/// current frequency

           /// as this element arr[i] is been deleted
           /// so , power of prefix will be deleted
           /// and new_power will be added thought of prefix freq has been changed
           /// So , the new power will be accordingly to the curr freq.
           power_subarray-=(pref_freq*pref_freq*(ll)arr[i]);
           power_subarray+=(curr_pref*curr_pref*(ll)arr[i]);
        }

        query_ans[Q[j].i]=power_subarray;
        curL=L;
        curR=R;
    }

    for(j=0;j<q;j++)
    {
        cout<<query_ans[j]<<'\n';
    }

    return 0;
}

