#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

void build(vector<int>&nums,int i,int l,int r,vector<int>&segTree){
    if(l==r){
        segTree[i] = nums[l];
        return ;
    }

    int mid = l+(r-l)/2;

    build(nums,2*i+1,l,mid,segTree);
    build(nums,2*i+2,mid+1,r,segTree);

    segTree[i] = min(segTree[2*i+1],segTree[2*i+2]);
}
 int rangeMin(int start,int end,int i,int l,int r,vector<int>&segTree){
    if(l>end || r<start) return INT_MAX;
    if(l>=start && r<=end) return segTree[i];

    int mid = l+(r-l)/2;

    return min(rangeMin(start,end,2*i+1,l,mid,segTree),
           rangeMin(start,end,2*i+2,mid+1,r,segTree));
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
        result.push_back(rangeMin(start,end,0,0,n-1,segTree));
    }

    for(auto it:result) cout<<it<<" ";
}