
/// It will modify to reduce some iterations 
/// It is more faster than normal comparator used in Mo's algorithm 

bool comp(query a, query b){
  if (a.l / block_size != b.l / block_size) return a.l < b.l;
  return a.l / block_size % 2 ? a.r > b.r : a.r < b.r;
}
