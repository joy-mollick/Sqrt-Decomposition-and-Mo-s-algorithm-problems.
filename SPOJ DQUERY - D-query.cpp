
/// Very Clear and Clean Code 
/// Time Complexity Approximately  O((N+M)*sqrt(N))

#include<bits/stdc++.h>

using namespace std;

struct query{
	int l;
	int r;
	int i;
};

query Q[200001];
int arr[30001] ;
int query_ans[200001];
int freq[1000001];
int nmber_of_dstnct_elements=0;
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
	cin>>n;
	block_size=(int) sqrt (n + .0) + 1;
	for(int i=0;i<n;i++)
	cin>>arr[i];

	cin>>q;
	for(int i=0;i<q;i++){
		cin>>Q[i].l>>Q[i].r;
		Q[i].i = i ;
        Q[i].l-- ; /// make zero based indexed
        Q[i].r--; /// make zero based indexed
	}

	sort(Q , Q+q , comp);

	int curL = 0 , curR = -1;

	int i,j;

	for( j=0;j<q;j++)

    {

        int L = Q[j].l;
		int R = Q[j].r;


        /// when curL < L , removing numbers from curL....to L-1.
        for(i=curL;i<=L-1;i++)
        {
            freq[arr[i]]--;/// removing element
            if(freq[arr[i]]==0)/// one distinct element is removed
                nmber_of_dstnct_elements--;
        }

        /// when curL > L , adding elements from L to curL-1 as curL is already in
        for(i=L;i<=curL-1;i++)
        {
            freq[arr[i]]++;/// adding element
            if(freq[arr[i]]==1)/// one distinct element is added
                nmber_of_dstnct_elements++;
        }

        /// when curR < R , adding elements from curR+1 to R
        for(i=curR+1;i<=R;i++)
        {
            freq[arr[i]]++;/// adding element
            if(freq[arr[i]]==1)/// one distinct element is added
                nmber_of_dstnct_elements++;
        }

        /// when curR > R , removing elements from R+1 ..... to curR
        for(i=R+1;i<=curR;i++)
        {
            freq[arr[i]]--;/// removing element
            if(freq[arr[i]]==0)/// one distinct element is removed
                nmber_of_dstnct_elements--;
        }

        query_ans[Q[j].i]=nmber_of_dstnct_elements;
        curL=L;
        curR=R;
    }

    for(j=0;j<q;j++)
    {
        cout<<query_ans[j]<<'\n';
    }

    return 0;
}

