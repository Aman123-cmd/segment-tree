#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

void build(vector<int>&nums,int i ,int l,int r,vector<int>&segTree){
      
    if(l==r){
        segTree[i] = l;
        return;
    }

    int mid = l+(r-l)/2;
    
    build(nums,2*i+1,l,mid,segTree);
    build(nums,2*i+2,mid+1,r,segTree);

    int leftMaxIdx = segTree[2*i+1];
    int rigthtMaxIdx = segTree[2*i+2];

   segTree[i] = nums[leftMaxIdx]>=nums[rigthtMaxIdx]?leftMaxIdx:rigthtMaxIdx;
}

int rangeMaxIdx(int start,int end,int i,int l,int r,vector<int>&segTree,vector<int>&nums){

    if(l>end || r<start) return INT_MIN;

    if(l>=start && r<=end) return segTree[i];

    int mid = l+(r-l)/2;

    int leftMaxIdx = rangeMaxIdx(start,end,2*i+1,l,mid,segTree,nums);
    int rightMaxIdx = rangeMaxIdx(start,end,2*i+2,mid+1,r,segTree,nums);
    
    if(leftMaxIdx==-1) return leftMaxIdx;
    if(rightMaxIdx==-1) return rightMaxIdx;

    return nums[leftMaxIdx]>=nums[rightMaxIdx]?leftMaxIdx:rightMaxIdx;
}
int main(){
    vector<int>nums = {3,5,1,6,3,7,9,3};
    int n = nums.size();

    vector<int>segTree(4*n);
    
    build(nums,0,0,n-1,segTree);

    vector<vector<int>> queries = {{1,4},{4,6},{1,7},{2,6}};
    vector<int>result;

    for(auto &q:queries){
        int start = q[0];
        int end = q[1];
        result.push_back(rangeMaxIdx(start,end,0,0,n-1,segTree,nums));
    }

    for(auto it:result) cout<<it<<" ";
}
// class Solution {
// public:
//     int minOperations(vector<int>& nums, int x) {
//       int n = nums.size();
//       vector<int>leftSum(n);
//       vector<int>rightSum(n);
//       leftSum[0] = nums[0];
//       rightSum[n-1] = nums[n-1];

//       for(int i = 1,j=n-2;i<n && j>=0;i++,j--){
//         leftSum[i] = leftSum[i-1]+nums[i];
//         rightSum[j] = rightSum[j+1]+nums[j];
//       }   


//       int i = 0;int j  = leftSum[n-1];
     
//      while(i<=j){}


//       return -1;
//     //   if(x>leftSum[n-1]) return -1;
//     //    vector<pair<int,int>>merge(2*n);
//     //    int i = 0;
//     //    int j = 0;
//     //    int k = 0;

//     //    while(i<n && j<n){
//     //     if(leftSum[i]<=rightSum[j]){
//     //      pair<int,int> p ;
//     //      if(i<=j)
//     //      {        
//     //      p.first = leftSum[i];
//     //      p.second = i;
//     //      i++;
//     //      }
//     //      else{
//     //         p.first = rightSum[j];
//     //         p.second = j;
//     //         j++;
//     //      }
//     //      merge[k] = p;
       
//     //      k++;
//     //     }
//     //     else{
//     //     pair<int,int> p ;
//     //      p.first = rightSum[j];
//     //      p.second = j;
//     //      merge[k] = p;
//     //      j++;
//     //      k++;
//     //     }
//     //    }

//     //    while(i<n){
//     //      pair<int,int> p ;
//     //      p.first = leftSum[i];
//     //      p.second = i;
//     //      merge[k] = p;
//     //      i++;
//     //      k++;
//     //    }
//     //    while(j<n){
//     //      pair<int,int> p ;
//     //      p.first = rightSum[j];
//     //      p.second = j;
//     //      merge[k] = p;
//     //      j++;
//     //      k++;
//     //    }
//     //    i = 0;
//     //    j = 2*n-1;
//     //   int sum = 0;
//     //   int opearatins = 0; 
//     //   int ans = -1;
//     //    while(j<2*n){
//     //       sum+=merge[j].first;
//     //       operations += merge[j].second
//     //       while(i<j && ((j-i+1)>2 || sum>x)){
//     //         sum-=merge[i].first;
//     //         operations-=merge[i].second;
//     //         i++;
//     //       }

//     //       if(sum==x){
//     //         int ans = operations;
//     //         break;
//     //       }
//     //       j++;
//     //    }

      
//     }
// };