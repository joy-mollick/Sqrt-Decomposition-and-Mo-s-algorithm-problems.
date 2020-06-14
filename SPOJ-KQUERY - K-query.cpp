
/// Time-790ms
/// Nice one 

#include <bits/stdc++.h>

using namespace std;

const int mx=30001; int sqt=sqrt(mx)+1;/// maximum block size
int arr[mx];
int block_size;/// the size of every block
vector<int> block_values[600];

int query(int l,int r,int val)
{
    int nmber_of_elements_greater = 0;
    int start_block = l / block_size;///from which block,the query starts
    int  end_block = r / block_size;///in which block,the query stops
    int end_range_of_start_block=(start_block+1)*block_size-1;
    ///the before index of next block

   ///if both the starting and closing ranges are in same block,simply iterating,maximum complexity O(sqrt(n))
   if (start_block == end_block){

    for (int i=l; i<=r; ++i)
    {
        if(val<arr[i]) nmber_of_elements_greater++;
    }

   }
  ///if both the starting and closing ranges in different blocks
  ///Then iterate the elements from first block and from last block linearly ,maximum sqrt(n)+sqrt(n)=2*sqrt(n).
  ///And iterate through over the values of interval blocks
  else

    {
    ///time complexity O(sqrt(n))
    for(int i=l; i<=end_range_of_start_block; ++i){
         if(val<arr[i]) nmber_of_elements_greater++;
    }
///as the block numbers can be maximum sqrt(n), so time complexity O(sqrt(n)-2)
    for(int i=start_block+1; i<=end_block-1; ++i)
    {
        int res_per_block;
        res_per_block=block_values[i].end()- upper_bound(block_values[i].begin(),block_values[i].end(),val);
        nmber_of_elements_greater+=res_per_block;
    }

    ///time complexity O(sqrt(n))
    for (int i=end_block*block_size; i<=r; ++i)
        if(val<arr[i]) nmber_of_elements_greater++;
    }

    return nmber_of_elements_greater;
///Total Complexity O(sqrt(n)) + O(sqrt(n)) + O(sqrt(n)-2) approximately closely to O(sqrt(n))
}

int main()

{

    int n,idx,val,type,u,v,q;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    /// pre-calculation of all blocks
    block_size=(int) sqrt (n + .0) + 1;///as zero based length ,so increase one
    for (int i=0; i<n; ++i)
    block_values[i / block_size].push_back(arr[i]);

    int numBlocks = ceil((double)n/block_size);

    /// sorting the block values
    /// so that we can use binary search to find out answer
    /// sqrt(n)*log(sqrt(n)) time complexity for each sort of block ,total block is sqrt(n)
    /// so ,over all this sorting will take sqrt(n)*sqrt(n)*log(sqrt(n)) = n*log(sqrt(n)) .
    for(int block=0;block<numBlocks;block++)
    {
        sort(block_values[block].begin(),block_values[block].end());
    }

    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d%d",&v,&u,&val);
        u--;v--;
        printf("%d\n",query(v,u,val));
    }
    return 0;
}
