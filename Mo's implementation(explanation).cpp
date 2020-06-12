
/// Mo's algorithm explanation and implementation of sample problem 

/*

1) why the reason the block size is sqrt(n) not like log(n)! 

2) why the same algorithm used in Mo's algorithm will lead to time complexity O(n*n) without re-ordering the queries in a particular manner?

3) How the block size does make vary the time complexity?

4)Why sorting of queries on basis of blocks needed actually in Mo's algorithm? 
We can sort it normally on the basis of L first and in case of a tie on the basis of R.
I mean this can be done sorting a vector of pair simply. But we didn't sort it normally , why?

-----------------proof-----------------------

lets assume that block size is x.
than no of blocks are n / x.
No of queries in each block is = x = block size.
we have two pointer left and right in problem.
Here for each query left will move at most x ( within query ). And for each block right will move at most n( from index 0 to end of array)

so now for each block left pointer will move = x * x ( x of each query at most) , and right will move n (at most)

so for each block total moves = left pointer move + right pointer move = x * x + n.

As we know there are n/x block.

for all blocks total moves = (n/x) * ( x * x + n).
f(x) = (n/x) * (x * x + n) = n * x + (n *n ) / x.
To minimise this function f(x)
f '(x) = 0;
n + (n*n) * ( -1 / ( x*x ) ) = 0
n = (n*n)/(x*x)
x * x = n ==> x = sqrt(n);

So overall time complexity of our algorithm ,when block size is sqrt(n) ----> 

Let us talk about the right pointer first. 
For each block, the queries are sorted in increasing order, so clearly the right pointer (currentR) moves in increasing order. 
During the start of next block the pointer possibly at extreme end will move to least R in next block. 
That means for a given block, the amount moved by right pointer is O(N). We have O(Sqrt(N)) blocks, so the total is O(N * Sqrt(N)). Great!

Let us see how the left pointer moves. 
For each block, the left pointer of all the queries fall in the same block, as we move from query to query the left pointer might move but as previous L and current L fall in the same block, the moment is O(Sqrt(N)) (Size of the block). 
In each block the amount left pointer movies is O(Q * Sqrt(N)) where Q is number of queries falling in that block. Total complexity is O(M * Sqrt(N)) for all blocks.

There you go, total complexity is O( (N + M) * Sqrt(N)) = O( N * Sqrt(N)).

It is a standard for such problem of offline queries.

*/

/// Here is implementation of code to find number of distinct elements in range using MO's implementation 

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

