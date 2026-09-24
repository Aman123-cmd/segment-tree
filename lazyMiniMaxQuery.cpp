#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;
struct Node{
    int mini;
    int maxi;
    Node(int a,int b){
        mini = a;
        maxi = b;
    }
};

class SegmentTree{
    public:
    int n;
    vector<Node>segTree;

    SegmentTree(vector<int>&nums){
        n = nums.size();
        segTree.resize(4*n,Node(INT_MAX, INT_MIN));
        build(nums,0,0,n-1);
    }

    void build(vector<int>&nums,int i,int l,int r){
        if(l==r){
            segTree[i].maxi = nums[l];
            segTree[i].mini = nums[l];
            return;
        }

        int mid = l+(r-l)/2;

        build(nums,2*i+1,l,mid);
        build(nums,2*i+2,mid+1,r);

        segTree[i].mini = min(segTree[2*i+1].mini,segTree[2*i+2].mini);
        segTree[i].maxi = max(segTree[2*i+1].maxi,segTree[2*i+2].maxi);
    }

    void propagate(int i,int l,int r,int val,vector<int>&lazy){
        if(lazy[i]!=0){
            segTree[i].mini+=lazy[i];
            segTree[i].maxi+=lazy[i];
           if(l!=r){
            lazy[2*i+1]+=lazy[i];
            lazy[2*i+2]+=lazy[i];
           }
            

            lazy[i] = 0;

        }
    }

   
    void rangeUpdate(int start,int end,int i,int l,int r,int val,vector<int>&lazy){
       if(lazy[i]!=0){
      
         propagate(i,l,r,val,lazy);
        
       }
       

        if(l>end || r<start) return;
        
        if(l>=start && r<=end){
           lazy[i]+=val;
           propagate(i,l,r,val,lazy);
           return;
        }

        int mid = (l+r)/2;
        
        rangeUpdate(start,end,2*i+1,l,mid,val,lazy);
        rangeUpdate(start,end,2*i+2,mid+1,r,val,lazy);

        segTree[i].mini = min(segTree[2*i+1].mini,segTree[2*i+2].mini);
        segTree[i].maxi = max(segTree[2*i+1].maxi,segTree[2*i+2].maxi);
    }
        Node rangeQuery(int start,int end,int i,int l,int r){
        if(l>end || r<start) return Node(INT_MAX,INT_MIN);
        if(l>=start && r<=end){
            return segTree[i];
        }

        int mid = l+(r-l)/2;

        Node left = rangeQuery(start,end,2*i+1,l,mid);
        Node right= rangeQuery(start,end,2*i+2,mid+1,r);
        
        if(left.maxi==INT_MIN && right.mini==INT_MAX) return right;
        if(right.maxi==INT_MAX&& right.mini==INT_MIN) return left;
        Node a(min(left.mini,right.mini),
               max(left.maxi,right.maxi));

        return a;

    }


    void print(){
        for(auto it:segTree) cout<<it.maxi<<"->"<<it.mini<<endl;
    }
};

int main(){
    
    vector<int>nums = {4,2,7,3,5,9,1,8,6,2,4};
     int n = nums.size();
    SegmentTree st(nums);
    vector<int>lazy(4*n);
    vector<vector<int>> queries = {{3,7,2},{1,4,4},{6,9,5},{7,9,2}};
    vector<Node>result;
   for(auto &q:queries){
    int start = q[0];
    int end = q[1];
    int val = q[2];
    st.rangeUpdate(start,end,0,0,n-1,val,lazy);
    Node ans =  st.rangeQuery(start,end,0,0,n-1);
    result.push_back(ans);
   }
    
   for(auto it:result) cout<<"mini = "<<it.mini<<" , "<<"maxi = "<<it.maxi<<endl;
    
}