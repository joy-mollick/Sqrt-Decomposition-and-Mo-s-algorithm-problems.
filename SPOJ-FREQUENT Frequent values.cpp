/// Nice problem
/// Using MO's algorithm
/// Keep track of only different numbers that's why I use map by which I gave an id number to different numbers so that I can avoid use of map in four loops
/// That's all
/// Time- 280ms

#include<bits/stdc++.h>

using namespace std;

struct query{
	int l;
	int r;
	int i;
};
int freq[100001];
int arr[100001] ;/// it holds the array numbers
int query_ans[100001];/// it is for query
int block_size;
static int numberOfValuesWithCount[100001];

/*
bool comp(query a , query b)
{
	if(a.l / block_size != b.l/block_size)
	return a.l/block_size < b.l/block_size;

	return a.r < b.r;
}
*/

bool comp(query a, query b){
  if (a.l / block_size != b.l / block_size) return a.l < b.l;
  return a.l / block_size % 2 ? a.r > b.r : a.r < b.r;
}

int main()
{

    int n , q;

    while(scanf("%d",&n)&&n!=0)
    {
    scanf("%d",&q);

	memset(numberOfValuesWithCount,0,sizeof(numberOfValuesWithCount));
	memset(freq,0,sizeof(freq));
    map<int,int>id;/// it only counts the frequency of a number
    int mxfreq=0;/// it hold the most frequent number of a value in a range
    query Q[q+1];/// it holds the query structure

	block_size=(int) sqrt (n + .0) + 1;
	int id_no=1;

	for(int i=0;i<n;i++){
	scanf("%d",&arr[i]);
	if(!id[arr[i]]) id[arr[i]]=id_no++;
	arr[i]=id[arr[i]];
	}
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
        for(i=L;i<=curL-1;i++)
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
        for(i=curR+1;i<=R;i++)
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
        for(i=R+1;i<=curR;i++)
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

        query_ans[Q[j].i]=mxfreq;
        curL=L;
        curR=R;
    }

    for(j=0;j<q;j++)
    {
        printf("%d\n",query_ans[j]);
    }

    }

    return 0;
}
