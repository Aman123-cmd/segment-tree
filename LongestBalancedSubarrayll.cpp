#include<iostream>
#include<vector>
#include<limits.h>
#include<unordered_map>
using namespace std;

struct Node{
    int mini;
    int maxi;
   
      Node():mini(0),maxi(0){}
    
};

class SegmentTree{
    public:
    int n;
    vector<Node>segTree;
    vector<int>lazy;

    SegmentTree(int size){
        n = size;
        segTree.assign(4*n,Node());
        lazy.assign(4*n,0);
    }


    void propagate(int i,int l,int r){
       if(lazy[i]!=0){
         segTree[i].maxi+=lazy[i];
         segTree[i].mini+=lazy[i];
       }

       if(l!=r){
         lazy[2*i+1]+=lazy[i];
         lazy[2*i+2]+=lazy[i];
       }
       lazy[i] = 0;
    }

    void rangeUpdate(int start,int end,int i,int l,int r,int val){
        propagate(i,l,r);
        if(l>end || r<start) return;

        if(l>=start && r<=end){
            lazy[i]+=val;
            propagate(i,l,r);
            return;
        }

        int mid = l+(r-l)/2;

       rangeUpdate(start,end,2*i+1,l,mid,val);
       rangeUpdate(start,end,2*i+2,mid+1,r,val);

       segTree[i].mini = min(segTree[2*i+1].mini,segTree[2*i+2].mini);
       segTree[i].maxi = max(segTree[2*i+1].maxi,segTree[2*i+2].maxi);

    }

    int leftMostZero(int i,int l,int r){

        propagate(i,l,r);
        if(segTree[i].mini>0 || segTree[i].maxi<0) return -1;

        if(l==r) return l;

        int mid = l+(r-l)/2;

        int left = leftMostZero(2*i+1,l,mid);

        if(left!=-1) return left;

        return leftMostZero(2*i+2,mid+1,r);
    }
};

int main(){
    unordered_map<int,int> mp;
    vector<int>nums = {3,2,2,5,4};
    int n = nums.size();
    SegmentTree st(n);

  
    int maxL = 0;

    for(int r = 0;r<n;r++){
       int val = (nums[r]%2==0)?1:-1;
       int prev = -1;

       if(mp.count(nums[r])){
        prev=mp[nums[r]];
       }

       if(prev!=-1){
        st.rangeUpdate(0,prev,0,0,n-1,-val);
       }

       st.rangeUpdate(0,r,0,0,n-1,val);

       int l = st.leftMostZero(0,0,n-1);
      
       if(l!=-1)
          maxL=max(maxL,r-l+1);

       mp[nums[r]] = r;
    }

    cout<<"Maximum length is = "<<maxL;

}