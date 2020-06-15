
/// Time-872 ms

/// We will calculate everything per block
/// so that during update time we can avoid updating whole n arrays
/// Now,we can update only at most sqrt(n) of a particular elements per update
/// And per query it takes sqrt(n) time complexity
/// because we have to visit at most sqrt(n) blocks

#include <bits/stdc++.h>

using namespace std;

int block_size;/// the size of every block
int last_pos[100001];///what is the last position before going to another block if the ball comes into this hole
int reachable[100001];/// how many holes can be reachable from this point in the same block ?
int arr[100001];
int n;

void sqrt_calculation(int i)
{
   int new_pos=i+arr[i];
   int block_current=i/block_size;
   int block_next_position=new_pos/block_size;
   if(new_pos>(n-1)||(block_current!=block_next_position))
   {
       last_pos[i]=i;
       reachable[i]=0;
   }
   else
   {
       last_pos[i]=last_pos[new_pos];
       reachable[i]=reachable[new_pos]+1;
       /// jumping from i to new_pos add one jump
   }
}

int main()

{
    int idx,val,type,b,q,a;
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    /// pre-calculation of all blocks
    block_size=(int) sqrt (n + .0) + 1;///as zero based length ,so increase one

    /// calculate from right to left as we can jump from left to right
    /// we have to calculate value of right side so that we can compute left side value using those right side's value
    for(int i=n-1;i>=0;i--) sqrt_calculation(i);

    while(q--)
    {
       scanf("%d",&type);
       if(type==1)
       {
            scanf("%d",&a);
            a--;/// making zero based index
            int lastposition=0;
            int count_of_jump_from_a=0;
            while(a<n)
            {
                count_of_jump_from_a+=reachable[a];
            /// last position holds the last possible place of the block of a where we can reach by jumping from a
            /// How much jump we need to reach that last position of the block of a ?
            /// That is reachable[a] which will be added and from.
                lastposition=last_pos[a];
                a=lastposition+arr[lastposition];
                count_of_jump_from_a++;/// this jump is to jump over to reach new block
                ///coming new block
                /// Every time we have to jump over at most only sqrt(n) blocks ,time complexity (sqrt(n)) per query .
            }
            printf("%d %d\n",lastposition+1,count_of_jump_from_a);
       }

      else
		{
		    scanf("%d%d",&a,&b);
			a--;/// making zero based index
			arr[a]=b;
			/// now change the calculation of that only particular block
			int pos=a;
			/// only changing the block values
			/// block elements can be at most sqrt(n)
			/// So,time complexity is sqrt(n)
			while(pos>=0 && pos/block_size==a/block_size )
            {
                sqrt_calculation(pos);
                pos--;
            }
		}

    }

    return 0;
}
