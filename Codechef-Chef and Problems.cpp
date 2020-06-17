

/// Let's think about query(L,R) 
/// ----|--L---i|----|-----j|---R-|------|---
/// Here bar(|) is the boundary of every block.
/// It is not possible to traverse from L to R with naive approach.
/// So, here two blocks are inside the path of L to R 
/// We previously computed the answer for every point of block 
/// So ,the max distance of same number from ith point to jth point has been calculated previous
/// Now it is easy to check the occurrences of only elements of the (L to i) and (j to R) 
/// The elements among every block can be at most sqrt(n).
/// Now one thing is sometimes sqrt(n) block size will not give best time complexity.
/// I ,here,use block size 110 


#include<bits/stdc++.h>

using  namespace std;

/// we will state block_value[i][j] as the maximum such value from ith point to jth point, where every point is the starting element of any block 
const int N=100001;
int a[N];
int blockvalue[1001][1001];///it will take answer for ith block to jth block
vector<int>position[N];///taking positions
int block_size;
int total_blocks;

int main()
{
     int n,m,k,l,r,i,j;
    scanf( "%d%d%d" ,&n,&m,&k);
    //block_size=(int) sqrt (n + .0) + 1;
    block_size=110;
    int numBlocks = ceil((double)n/block_size);
     for ( int i= 0 ;i<n;i++ ){
        scanf( "%d" ,&a[i]);
        position[a[i]].push_back(i);
    }
    int index[m+1];
    int temp,pos;
    /// it will iterate over first element of the every block
    for( i=0;i<n;i+=block_size)
    {
        memset(index,-1,sizeof(index));
        /// every time we will clear this
        /// for calculating every block
        /// it is working as a hashmap 
        temp=0;/// by temp variable we will take max distance of the same value ,then when new block found update answer 
        int starting_of_block=i;
        /// from starting index of every block, it will calculate max answer for every block which are next to current block 
        for( j=starting_of_block;j<n;++j)
        {
            ///That means j is the starting of another block ,so we have to update answer now as new block's first element has been found 
            /// So think about the query is i to j ,so update block answer 
            if(j%block_size==0)
            {
                blockvalue[i/block_size][j/block_size]=temp;
            }
            if(index[a[j]]== -1)
            {
                index[a[j]]=j;
            }
            else
            {
                temp=max(temp,j-index[a[j]]);
            }
        }
        blockvalue[i/block_size][numBlocks]=temp;
    }

    while(k--)
    {
       scanf("%d%d",&l,&r);
        l--;
        int till_next_block=(l/block_size);
        ++till_next_block;
        int next_block=till_next_block*block_size;/// it is the first element of the next block of the index l .
        int block_of_r=(r/block_size)*block_size;/// it is the first element in which block r is remaining 
        int res=blockvalue[till_next_block][block_of_r/block_size];/// it is the answer of the from the point L to R ,where L is the closest block's first element and R is the closest previous block's first element from R .

        for( i=l;i<next_block;++i)
        {
         pos=lower_bound(position[a[i]].begin(),position[a[i]].end(),r)-position[a[i]].begin();
         --pos;///we will find the lower bound of the index r not (r-1) ,for that we will decrease one position 
        if(pos<0) continue;/// there is no other position of a[i] in range r,without position of i ,so ignore
        res=max(res,position[a[i]][pos]-i);
        }

        for( i=block_of_r;i<(r);++i)
        {
             pos = lower_bound(position[a[i]].begin(), position[a[i]].end(), l) - position[a[i]].begin();
            if(pos == position[a[i]].size()) continue;
            res = max(res, i - position[a[i]][pos]);
        }
        printf("%d\n",res);
    }

}
