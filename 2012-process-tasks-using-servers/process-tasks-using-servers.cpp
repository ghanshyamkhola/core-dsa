#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> freeServers;

        priority_queue<tuple<long long, int, int>,
                       vector<tuple<long long, int, int>>,
                       greater<tuple<long long, int, int>>> busyServers;

        int n = servers.size();
        int m = tasks.size();

        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        vector<int> ans(m);
        long long time = 0;

        for (int j = 0; j < m; j++) {
            time = max(time, (long long)j);

            while (!busyServers.empty() &&
                   get<0>(busyServers.top()) <= time) {
                auto [t, w, i] = busyServers.top();
                busyServers.pop();
                freeServers.push({w, i});
            }

            if (freeServers.empty()) {
                time = get<0>(busyServers.top());

                while (!busyServers.empty() &&
                       get<0>(busyServers.top()) <= time) {
                    auto [t, w, i] = busyServers.top();
                    busyServers.pop();
                    freeServers.push({w, i});
                }
            }

            auto [w, i] = freeServers.top();
            freeServers.pop();

            ans[j] = i;

            busyServers.push({time + tasks[j], w, i});
        }

        return ans;
    }
};