#include<iostream>
#include<vector>
using namespace std;
void buildTree(int i,int l,int r,vector<int>&segTree,vector<int>&nums){
       if(l==r){
        segTree[i] = nums[l];
        return ;
       }
       int mid = l+(r-l)/2;     

       buildTree(2*i+1,l,mid,segTree,nums);
       buildTree(2*i+2,mid+1,r,segTree,nums);

       segTree[i] = segTree[2*i+1]+segTree[2*i+2];
}


void pointSeg(int i,int l,int r, int idx,int val,vector<int>&nums,vector<int>&segTree){
     
    if(l==r){
        nums[idx] = val;
        segTree[i] = nums[l];
        return;
    }

    int mid = l+(r-l)/2;
    if(idx<=mid){
      pointSeg(2*i+1,l,mid,idx,val,nums,segTree);
    }
    else pointSeg(2*i+2,mid+1,r,idx,val,nums,segTree);

    segTree[i] = segTree[2*i+1] + segTree[2*i+2];
     
}

int main(){
    vector<int>nums = {3,1,2,7};
    int n = nums.size();
    vector<int>segTree(4*n, 0);
    buildTree(0,0,n-1,segTree,nums);

    for(auto it:segTree) cout<<it<<" ";
    pointSeg(0,0,n-1,1,2,nums,segTree);
    cout<<endl<<"Printing updated segTree"<<endl;
     for(auto it:segTree) cout<<it<<" ";

}
