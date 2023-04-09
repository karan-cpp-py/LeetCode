class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n=colors.size();
        vector<int> color(26,0),indegree(n,0);
        vector<vector<int>> adj(n),cnt(n,vector<int>(26,0));
        for(int i=0;i<edges.size();i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            indegree[edges[i][1]]++;
        }
        vector<bool> vis(n,false),pathVis(n,false);
        for(int i=0; i<n; i++){
            if(vis[i]==false){
                if(dfs(i,adj,vis,pathVis)) return -1;
            }
        }
        for(int i=0; i<n; i++){
            cnt[i][colors[i]-'a']++;
        }
        queue<int> q;
        for(int i=0;i<indegree.size();i++){
            if(indegree[i]==0) q.push(i);
        }
        int ans=0;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(auto i : adj[node]){
                for(int j=0; j<26; j++){
                    cnt[i][j]=max(cnt[i][j],cnt[node][j]+(colors[i]-'a'==j?1:0));
                }
                indegree[i]--;
                if(indegree[i]==0) q.push(i);
            }
            ans=max(ans,*max_element(cnt[node].begin(),cnt[node].end()));
        }
        return ans;
    }
    bool dfs(int src, vector<vector<int>>& adj, vector<bool>& vis, vector<bool>& pathVis){
        vis[src]=true;
        pathVis[src]=true;
        for(auto i : adj[src]){
            if(vis[i]==false){
                if(dfs(i,adj,vis,pathVis)) return true;
            }
            else if(pathVis[i]==true) return true;
        }
        pathVis[src]=false;
        return false;
    }
};