#include<iostream>
#include<vector>

using namespace std;

void build(vector<int>&nums,int i,int l,int r,vector<int>&segTree){
    if(l==r){
        segTree[i] = nums[l];
        return ;
    }

    int mid = l+(r-l)/2;

    build(nums,2*i+1,l,mid,segTree);
    build(nums,2*i+2,mid+1,r,segTree);

    segTree[i] = segTree[2*i+1]+segTree[2*i+2];
}
 int rangeSum(int start,int end,int i,int l,int r,vector<int>&segTree){
    if(l>end || r<start) return 0;
    if(l>=start && r<=end) return segTree[i];

    int mid = l+(r-l)/2;

    return rangeSum(start,end,2*i+1,l,mid,segTree)+
           rangeSum(start,end,2*i+2,mid+1,r,segTree);
 } 

void rangeUpdate(int start,int end,int i,int l,int r,vector<int>&segTree,vector<int>&lazy,int val){
     
    if(lazy[i]!=0){
        segTree[i]+=lazy[i]*(r-l+1);
        if(l!=r){
          lazy[2*i+1] += lazy[i];
          lazy[2*i+2] += lazy[i];
        }
        
        lazy[i] = 0;
    }

    if(l>end || r<start) return;

    if(l>=start && r<=end){
        segTree[i]+=(r-l+1)*val;
        if(l!=r){
            lazy[2*i+1] += val;
            lazy[2*i+2] += val;
        }
        return;
    }

    int mid = l+(r-l)/2;

    rangeUpdate(start,end,2*i+1,l,mid,segTree,lazy,val);
    rangeUpdate(start,end,2*i+2,mid+1,r,segTree,lazy,val);

     segTree[i] = segTree[2*i+1]+segTree[2*i+2];

}
int main(){
    vector<int>nums = {3,4,2,5,3,6,3,4};
    int n = nums.size();
    vector<vector<int>>queries = {{1,4,3},{4,7,4},{1,6,8}};
    vector<int>segTree(4*n);
    vector<int>lazy(4*n);
    vector<int>result;
    build(nums,0,0,n-1,segTree);
    for(auto &q:queries){
        int start = q[0];
        int end  = q[1];
        int val = q[2];
        rangeUpdate(start,end,0,0,n-1,segTree,lazy,val);
        result.push_back(rangeSum(start,end,0,0,n-1,segTree));
    }

    for(auto it:result) cout<<it<<" ";
}