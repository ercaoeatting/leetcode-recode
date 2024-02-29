#include <cstdint>
#include <string>
#include <unordered_map>
using namespace std;
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在
// 涵盖 t 所有字符的子串，则返回空字符串 "" 。
string minWindow(string s, string t) {
    unordered_map<char, int> charT, res;
    for (auto &ti : t) { ++charT[ti]; }
    int subLen = 0; // 子序列长度
    int left = 0, right = 0, len = INT32_MAX, start = 0, count = 0;
    while (right < s.size()) {
        if (charT.find(s[right]) != charT.end()) {
            ++res[s[right]];
            if (charT[s[right]] == res[s[right]]) { count++; }
        }
        while (count == charT.size()) {
            if ((right - left + 1) < len) {
                len = right - left + 1;
                start = left;
            }
            if (charT.find(s[left]) != charT.end()) {
                if (charT[s[left]] == res[s[left]]) { count--; }
                --res[s[left]];
            }
            left++;
        }
        right++;
    }
    return len == INT32_MAX ? "" : s.substr(start, len);
}
int main() {
    string a = "aa", b = "aa";
    string c = minWindow(a, b);
}