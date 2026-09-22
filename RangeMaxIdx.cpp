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

    if(nums[leftMaxIdx]>=nums[rigthtMaxIdx]){
        segTree[i] = leftMaxIdx;
    }
    else segTree[i] = rigthtMaxIdx;
}

int rangeMaxIdx(int start,int end,int i,int l,int r,vector<int>&segTree,vector<int>&nums){

    if(l>end || r<start) return INT_MIN;

    if(l>=start && r<=end) return segTree[i];

    int mid = l+(r-l)/2;

    int leftMaxIdx = rangeMaxIdx(start,end,2*i+1,l,mid,segTree,nums);
    int rightMaxIdx = rangeMaxIdx(start,end,2*i+2,mid+1,r,segTree,nums);
    
    if(nums[leftMaxIdx]>=nums[rightMaxIdx]) return leftMaxIdx;
     return rightMaxIdx;
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