#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

class SegmentTree{
    public:
    int n;
    vector<int>segTree;

    SegmentTree(vector<int>nums){
        n = nums.size();
        segTree.resize(4*n);
        build(nums,0,0,n-1);
    }

    void build(vector<int>&nums,int i,int l,int r){
        if(l==r){
            segTree[i] = l;
            return;
        }

        int mid = l+(r-l)/2;

        build(nums,2*i+1,l,mid);
        build(nums,2*i+2,mid+1,r);

        int leftMaxIdx = segTree[2*i+1];
        int rightMaxIdx = segTree[2*i+2];

        segTree[i] = nums[leftMaxIdx]>=nums[leftMaxIdx]?leftMaxIdx:rightMaxIdx;
    }
    
    int rangeQuery(vector<int>&nums,int start,int end,int i,int l,int r){
        if(l>end || r<start) return -1;

        if(l>=start && r<=end) return segTree[i];

        int mid = l+(r-l)/2;

        int leftIdx = rangeQuery(nums,start,end,2*i+1,l,mid);
        int rightIdx = rangeQuery(nums,start,end,2*i+2,mid+1,r);
        
        if(leftIdx==-1) return rightIdx;
        if(rightIdx==-1) return leftIdx;

        return nums[leftIdx]>=nums[rightIdx]?leftIdx:rightIdx;
    }

    int RMIQ(vector<int>&nums,int start,int end){

        return rangeQuery(nums,start,end,0,0,n-1);
    }

    int leftMostMax(vector<int>&nums,int a,int b){
        int i = a+1;
        int j = n-1;
        
        int ans = INT_MAX;

        while(i<=j){
           int mid = i+(j-i)/2;
           int maxi = RMIQ(nums,i,mid);

           if(nums[maxi]>max(nums[a],nums[b])){
            ans = min(ans,maxi);
            j = mid-1;
           }
           else i = mid+1;
        }
        return ans==INT_MAX?-1:ans;
    }
};

int main(){
     
    vector<int>nums = {6,4,8,5,2,7};
    int n = nums.size();
    SegmentTree st(nums);

    vector<vector<int>> queries = {{0,1},{0,3},{2,4},{3,4},{2,2}};
    vector<int>result;

    for(auto &q:queries){
        int max_idx = max(q[0],q[1]);
        int min_idx = min(q[0],q[1]);

        if(max_idx==min_idx) result.push_back(max_idx);

        else if(nums[max_idx]>nums[min_idx]) result.push_back(max_idx);

        else result.push_back(st.leftMostMax(nums,max_idx,min_idx));
    }

    for(auto it:result) cout<<it<<" ";
}