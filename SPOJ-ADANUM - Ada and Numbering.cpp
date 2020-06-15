

/// Time-3620ms
/// It is very classical one 
/// Here ,Exactly you have to find out the minimum possible sum of  freq[i]*any_number  for all i from L to R
/// So ,we have to keep frequency of frequency of numbers in ranges 
/// Then we have to add frequency_of_frequency of every numbers continuously and remove vice versa 


#include<bits/stdc++.h>

using namespace std;

struct query{
	int l;
	int r;
	int i;
};
map<long long,long long>id;/// it will hold
query Q[200005];/// it holds the query structure
long long arr[200005];/// it holds the array numbers
long long query_ans[200005];/// it is for query,YES or NO
long long  freq[200005];
/// it only counts the frequency of a number
static long long freq_of_freq[200005];/// it will count the number with particular freq,in case negative value it will give only zero as we stated it as a static array
long long int answer=0;/// it hold the most frequent number of a value in a range
int block_size;

bool comp(query a, query b){
  if (a.l / block_size != b.l / block_size) return a.l < b.l;
  return a.l / block_size % 2 ? a.r > b.r : a.r < b.r;
}

int main()
{
	int n , q , k , i, j;
	scanf("%d%d",&n,&q);
	block_size=(int) sqrt (n + .0) + 1;

	/// We don't need to keep all numbers,we will give different id number to different numbers and keep track of different numbers in ranges,It's a trick to make fast this algorithm.
	int id_no=1;

	for( i=0;i<n;i++){
	scanf("%lld",&arr[i]);
	if(!id[arr[i]]) id[arr[i]]=id_no++;
	arr[i]=id[arr[i]];
	}

	for( i=0;i<q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);
		Q[i].i = i ;
        Q[i].l-- ; /// make zero based indexed
        Q[i].r--; /// make zero based indexed
	}

	sort(Q , Q+q , comp);

	int curL = 0 , curR = -1;

	int K,L,R;
	int prev;

	for( j=0;j<q;++j)

    {

         L = Q[j].l;
		 R = Q[j].r;

        /// when curL < L , removing numbers from curL....to L-1.
        for(i=curL;i<=L-1;++i)
        {
            answer-=freq_of_freq[ freq[arr[i]] ];
            freq_of_freq[ freq[arr[i]] ]--;
            freq[arr[i]]--;/// change the frequency
        }


        /// when curL > L , adding elements from L to curL-1 as curL is already in
        for(i=L;i<=curL-1;++i)
        {

            freq[arr[i]]++;/// adding element
            freq_of_freq[ freq[arr[i]] ]++;
            answer+=freq_of_freq[ freq[arr[i]] ];
        }


        /// when curR < R , adding elements from curR+1 to R
        for(i=curR+1;i<=R;++i)
        {
            freq[arr[i]]++;/// adding element
            freq_of_freq[ freq[arr[i]] ]++;
            answer+=freq_of_freq[ freq[arr[i]] ];
            ///cout<<cSum[ freq[arr[i]] ]<<" "<<answer<<endl;
        }


        /// when curR > R , removing elements from R+1 ..... to curR
        for(i=R+1;i<=curR;++i)
        {
            answer-=freq_of_freq[ freq[arr[i]] ];
            freq_of_freq[ freq[arr[i]] ]--;
            freq[arr[i]]--;/// change the frequency
        }

        query_ans[Q[j].i]=answer;
        curL=L;
        curR=R;
    }

    for(int j=0;j<q;j++)
    {
        printf("%lld\n",query_ans[j]);
    }

    return 0;
}
