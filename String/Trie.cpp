#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Trie {
    bool finish = false;
    Trie* child[10];
    
    Trie() {
        for (int i = 0; i < sizeof(child)/sizeof(child[0]); i++) child[i] = NULL;
    }
    
    ~Trie() {
        for (int i = 0; i < sizeof(child)/sizeof(child[0]); i++) if (child[i]) delete child[i];
    }

    void insert (const char* key) {
        if (*key == '\0') this->finish = true;
        else {
            int curr = *key - '0';
            if (child[curr] == NULL) child[curr] = new Trie();
            child[curr]->insert(key + 1);
        }
    }
    
    Trie* find (const char* key) {
        if (*key == '\0') return this;
        int curr = *key - '0';
        if (child[curr] == NULL) return NULL;
        return child[curr]->find(key + 1);
    }
    
    bool traversal() {
        int cnt = 0;
        for (int i = 0; i < sizeof(child)/sizeof(child[0]); i++) {
            if (child[i] != NULL) {
                if (!child[i]->traversal()) return false;
                cnt++;
            }
        }
        if (cnt>0 && this->finish) return false;
        return true;
    }
};

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int tc; cin >> tc;
    for (int i = 0; i < tc; i++) {
        int n; cin >> n;
        Trie* root = new Trie();
        vector<string> str;
        for (int j = 0; j < n; j++) {
            string s; cin >> s;
            str.push_back(s);
        }
        for (int j = 0; j < n; j++) {
            root->insert(str[j].c_str());
        }
        if (root->traversal()) cout << "YES\n";
        else cout << "NO\n";
        delete root;
    }
}