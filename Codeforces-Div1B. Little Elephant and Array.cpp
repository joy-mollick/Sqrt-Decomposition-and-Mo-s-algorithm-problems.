
/// Nice problem
/// Using MO's algorithm
/// How many numbers in range (L,R) occurs equal to that number 
/// Keep track of only frequency of number and is that frequency is equal to that number 
/// That's all
/// Time- 140 ms	

#include<bits/stdc++.h>

using namespace std;

struct query{
	int l;
	int r;
	int i;
};

query Q[100001];/// it holds the query structure
int arr[100001] ;/// it holds the array numbers
int freq[100001];/// hold frequency of number
int query_ans[100001];/// it is for query
int block_size;
int such_numbers=0;

bool comp(query a, query b){
  if (a.l / block_size != b.l / block_size) return a.l < b.l;
  return a.l / block_size % 2 ? a.r > b.r : a.r < b.r;
}

int main()
{

    int n , q;

    scanf("%d%d",&n,&q);

	block_size=(int) sqrt (n + .0) + 1;
	for(int i=0;i<n;i++)
	scanf("%d",&arr[i]);

	for(int i=0;i<q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);
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
            if(arr[i]>n) continue;
            if(freq[arr[i]]==arr[i])/// a number arr[i] occurs arr[i] times,which will be changed
            {
                such_numbers--;
            }
            freq[arr[i]]--;/// change the frequency
            if(freq[arr[i]]==arr[i])
            {
                such_numbers++;
            }

        }


        /// when curL > L , adding elements from L to curL-1 as curL is already in
        for(i=L;i<=curL-1;i++)
        {
             if(arr[i]>n) continue;

              if(freq[arr[i]]==arr[i])/// a number arr[i] occurs arr[i] times,which will be changed
            {
                such_numbers--;
            }

            freq[arr[i]]++;/// adding element

             if(freq[arr[i]]==arr[i])
            {
                such_numbers++;
            }
        }


        /// when curR < R , adding elements from curR+1 to R
        for(i=curR+1;i<=R;i++)
        {
            if(arr[i]>n) continue;

              if(freq[arr[i]]==arr[i])/// a number arr[i] occurs arr[i] times,which will be changed
            {
                such_numbers--;
            }

            freq[arr[i]]++;/// adding element

             if(freq[arr[i]]==arr[i])
            {
                such_numbers++;
            }
        }


        /// when curR > R , removing elements from R+1 ..... to curR
        for(i=R+1;i<=curR;i++)
        {
            if(arr[i]>n) continue;
            if(freq[arr[i]]==arr[i])/// a number arr[i] occurs arr[i] times,which will be changed
            {
                such_numbers--;
            }
            freq[arr[i]]--;/// change the frequency
            if(freq[arr[i]]==arr[i])
            {
                such_numbers++;
            }

        }

        query_ans[Q[j].i]=such_numbers;
        curL=L;
        curR=R;
    }

    for(j=0;j<q;j++)
    {
        printf("%d\n",query_ans[j]);
    }

    return 0;
}
