#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool string_compare(string s, string t){
    vector<int> result(26,0);
    if(s.size()!=t.size())
        return false;
    int len = s.size();
    for(int i=0;i<len;i++){
        result[s[i]-'a']++;
        result[t[i]-'a']--;
    }
    for (int count:result){
        if (count!=0) return false;
    }
    return true;
}

int main(){
    vector<string> strs{"cab","abc"};
    cout<<string_compare(strs[0],strs[1])<<endl;

    return 0;
}