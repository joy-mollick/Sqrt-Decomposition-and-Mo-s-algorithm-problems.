/// Time-0.453ms
/// Finally It is now able to avoid TLE 
/// Time Limit is 500ms ,so strict 
/// Very Nice problem 

#include <bits/stdc++.h>

using namespace std;

unordered_map<int,deque<int> >pos;

int block_size;/// the size of every block
int block_value[330];///sqrt size of max
int arr[100002];

inline int Gcd(int x,int y)
{
    if(y==0) return x;
    else return Gcd(y,x%y);
}

inline int query(int l,int r)
{
    int sum = 0;
    int i;
    int start_block = l / block_size;///from which block,the query starts
    int  end_block = r / block_size;///in which block,the query stops
    int end_range_of_start_block=(start_block+1)*block_size-1;
    ///the before index of next block

   ///if both the starting and closing ranges are in same block,simply iterating,maximum complexity O(sqrt(n))
   if (start_block == end_block){
    for ( i=l; i<=r; ++i)
        sum =Gcd(arr[i],sum);
   }
  ///if both the starting and closing ranges in different blocks
  ///Then iterate the elements from first block and from last block linearly ,maximum sqrt(n)+sqrt(n)=2*sqrt(n).
  ///And iterate through over the values of interval blocks
  else
    {
    ///time complexity O(sqrt(n))
    for( i=l; i<=end_range_of_start_block; ++i)
        sum =Gcd(arr[i],sum);
///as the block numbers can be maximum sqrt(n), so time complexity O(sqrt(n)-2)
    for( i=start_block+1; i<=end_block-1; ++i)
        sum =Gcd(block_value[i],sum);
    ///time complexity O(sqrt(n))
    for ( i=end_block*block_size; i<=r; ++i)
       sum =Gcd(arr[i],sum);
    }
    if(sum==0) sum=1;

    return sum;
///Total Complexity O(sqrt(n)) + O(sqrt(n)) + O(sqrt(n)-2) approximately closely to O(sqrt(n))
}

/// adding val into index idx
inline void update(int idx, int val)
{
    ///in which block idx remains
    int blockNumber = idx / block_size;
    block_value[blockNumber] =Gcd( val,block_value[blockNumber] ); /// adding value to the desired block
    arr[idx]=val;
}

inline void update_cal(int idx)
{
     arr[idx]=0;
     int gcd=0,i;
     int num_block = idx / block_size;///from which block,the query starts
     int end_range_of_num_block=(num_block+1)*block_size-1;
    ///the before index of next block
    for( i=num_block*block_size;i<=end_range_of_num_block;i++)
        gcd=Gcd(arr[i],gcd);

        block_value[num_block]=gcd;

}

int main()

{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,idx,v,k,j;
    char ch;
    vector<int>::iterator it;
    int no=0;
    cin>>n;
    k=n;
    /// pre-calculation of all blocks
    block_size=(int) sqrt (100001 + .0) + 1;///as zero based length ,so increase one

    for ( j=0; j<k; ++j)
    {
        cin>>ch;
        if(ch=='+')
        {
            cin>>v;
            pos[v].push_back(no);
            update(no,v);
            cout<<query(0,no)<<"\n";
            ++no;
        }
        else
        {
            cin>>v;
            idx=pos[v].front();
            pos[v].pop_front();
            update_cal(idx);
            cout<<query(0,no)<<"\n";
        }
    }

    return 0;
}
