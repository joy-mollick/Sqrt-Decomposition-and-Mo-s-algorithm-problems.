 
/// RMQ problem 
/// It can be easily solved with segment tree algorithm,but here I used sqrt decomposition algorithm.
/// Time-0.060s

#include <bits/stdc++.h>

using namespace std;

int block_size;/// the size of every block
int block_value[1001];
int arr[100001];

int query(int l,int r)
{
    int mn =INT_MAX;
    int start_block = l / block_size;///from which block,the query starts
    int  end_block = r / block_size;///in which block,the query stops
    int end_range_of_start_block=(start_block+1)*block_size-1;
    ///the before index of next block

   ///if both the starting and closing ranges are in same block,simply iterating,maximum complexity O(sqrt(n))
   if (start_block == end_block){
    for (int i=l; i<=r; ++i)
        mn=min(arr[i],mn);
   }
  ///if both the starting and closing ranges in different blocks
  ///Then iterate the elements from first block and from last block linearly ,maximum sqrt(n)+sqrt(n)=2*sqrt(n).
  ///And iterate through over the values of interval blocks
  else
    {
    ///time complexity O(sqrt(n))
    for(int i=l; i<=end_range_of_start_block; ++i)
        mn=min(arr[i],mn);
///as the block numbers can be maximum sqrt(n), so time complexity O(sqrt(n)-2)
    for(int i=start_block+1; i<=end_block-1; ++i)
        mn=min(block_value[i],mn);
    ///time complexity O(sqrt(n))
    for (int i=end_block*block_size; i<=r; ++i)
        mn=min(arr[i],mn);
    }
    return mn;
///Total Complexity O(sqrt(n)) + O(sqrt(n)) + O(sqrt(n)-2) approximately closely to O(sqrt(n))
}

int main()

{
    for(int i=0;i<1001;i++)
    {
        block_value[i]=INT_MAX;
    }
    int n,idx,val,type,u,v,q;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    /// pre-calculation of all blocks
    block_size=(int) sqrt (n + .0) + 1;///as zero based length ,so increase one
    for (int i=0; i<n; ++i)
    block_value[i / block_size] = min(arr[i],block_value[i / block_size]);
    scanf("%d",&q);
    while(q--)
    {
       scanf("%d%d",&u,&v);
       printf("%d\n",query(u,v));
    }

    return 0;
}
