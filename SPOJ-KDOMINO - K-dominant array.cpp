
/// Time-2040ms
/// Use map to identify different numbers it will reduce time complexity 
/// Otherwise you have to use mapping in four loops which will cause TLE 

#include<bits/stdc++.h>

using namespace std;

struct query{
	int l;
	int r;
	int i;
	int k;
};
map<int,int>id;/// it will hold
query Q[200001];/// it holds the query structure
int arr[200001] ;/// it holds the array numbers
int query_ans[200001];/// it is for query,YES or NO
int freq[200001];
/// it only counts the frequency of a number
static int numberOfValuesWithCount[200001];/// it will count the number with particular freq,in case negative value it will give only zero as we stated it as a static array
int mxfreq=0;/// it hold the most frequent number of a value in a range
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
	scanf("%d",&arr[i]);
	if(!id[arr[i]]) id[arr[i]]=id_no++;
	arr[i]=id[arr[i]];
	}

	for( i=0;i<q;i++){
        scanf("%d%d%d",&Q[i].l,&Q[i].r,&k);
		Q[i].i = i ;
		Q[i].k = k;
        Q[i].l-- ; /// make zero based indexed
        Q[i].r--; /// make zero based indexed
	}

	sort(Q , Q+q , comp);

	int curL = 0 , curR = -1;

	int K,L,R;

	for( j=0;j<q;++j)

    {

         L = Q[j].l;
		 R = Q[j].r;
        K = Q[j].k;


        /// when curL < L , removing numbers from curL....to L-1.
        for(i=curL;i<=L-1;++i)
        {
        /// arr[i] will be removed,so the freq of this number will be decreased
        /// But before decreasing we should decrease the count number also of this freq[arr[i]].
            numberOfValuesWithCount[freq[arr[i]]]--;

///if freq[arr[i]] is max freq i.e. arr[i] is most frequent values .As arr[i] is going to be deleted so, numberOfValuesWithCount[this freq] will be decreased also
/// But,if only arr[i] was most frequent value in range i.e. now numberOfValuesWithCount[mxfreq]==0,then for removing this arr[i] ,of course mxfreq will be decreased by one
            if( freq[arr[i]]==mxfreq && numberOfValuesWithCount[freq[arr[i]]]==0 )
            {
                mxfreq--;
            }

            freq[arr[i]]--;/// change the frequency
            numberOfValuesWithCount[freq[arr[i]]]++;/// now new freq will be taken into account
        }


        /// when curL > L , adding elements from L to curL-1 as curL is already in
        for(i=L;i<=curL-1;++i)
        {
            numberOfValuesWithCount[freq[arr[i]]]--;

        /// if freq[arr[i]] is the most frequency in the range i.e. arr[i] is most frequent value .So , adding this value mxfreq will be increased
            if(freq[arr[i]]==mxfreq)
            {
                mxfreq++;
            }

            freq[arr[i]]++;/// adding element

            numberOfValuesWithCount[freq[arr[i]]]++;/// count this new frequency
        }


        /// when curR < R , adding elements from curR+1 to R
        for(i=curR+1;i<=R;++i)
        {
           numberOfValuesWithCount[freq[arr[i]]]--;

        /// if freq[arr[i]] is the most frequency in the range i.e. arr[i] is most frequent value .So , adding this value mxfreq will be increased
            if(freq[arr[i]]==mxfreq)
            {
                mxfreq++;
            }

            freq[arr[i]]++;/// adding element

            numberOfValuesWithCount[freq[arr[i]]]++;/// count this new frequency
        }


        /// when curR > R , removing elements from R+1 ..... to curR
        for(i=R+1;i<=curR;++i)
        {
            /// arr[i] will be removed,so the freq of this number will be decreased
        /// But before decreasing we should decrease the count number also of this freq[arr[i]].
            numberOfValuesWithCount[freq[arr[i]]]--;

///if freq[arr[i]] is max freq i.e. arr[i] is most frequent values .As arr[i] is going to be deleted so, numberOfValuesWithCount[this freq] will be decreased also
/// But,if only arr[i] was most frequent value in range i.e. now numberOfValuesWithCount[mxfreq]==0,then for removing this arr[i] ,of course mxfreq will be decreased by one
            if( freq[arr[i]]==mxfreq && numberOfValuesWithCount[freq[arr[i]]]==0 )
            {
                mxfreq--;
            }

            freq[arr[i]]--;/// change the frequency
            numberOfValuesWithCount[freq[arr[i]]]++;/// now new freq will be taken into account
        }

        query_ans[Q[j].i]=((mxfreq*K)>=(R-L+1));
        curL=L;
        curR=R;
    }

    for(j=0;j<q;++j)
    {
        if(query_ans[j]==1)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
