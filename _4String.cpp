#include <algorithm>
#include <vector>
#include <string>
using namespace std;
class lc344 {
public:
    void reverseString(vector<char> &s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    };
};
class lc541 {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2 * k) {
            if (i + k <= s.size()) { reverse(s.begin() + i, s.begin() + i + k); }
            else { reverse(s.begin() + i, s.end()); }
        }
        return s;
    }
};
class KamaCoder_54 {
public:
    bool ifNum(char word) { return (word >= '0' && word <= '9') ? true : false; }
    void replaceNum(string &s) {
        int countNum = 0;
        for (char i : s) {
            if (ifNum(i)) { ++countNum; }
        }
        int size = s.size();
        s.resize(s.size() + countNum * 5);
        for (int pOld = size - 1, pNew = s.size() - 1; pOld >= 0;) {
            if (ifNum(s[pOld])) {
                s[pNew] = 'r';
                s[pNew - 1] = 'e';
                s[pNew - 2] = 'b';
                s[pNew - 3] = 'm';
                s[pNew - 4] = 'u';
                s[pNew - 5] = 'n';
                --pOld;
                pNew -= 6;
            }
            else {
                s[pNew] = s[pOld];
                --pNew;
                --pOld;
            }
        }
    }
};
class lc151 {
public:
    void reverse(string &s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) { swap(s[i], s[j]); }
    }
    string reverseWords(string s) {
        int slow = 0, fast = 0;
        while (s.size() > 0 && fast < s.size() && s[fast] == ' ') { fast++; }
        for (; fast < s.size(); fast++) {
            if (fast - 1 > 0 && s[fast - 1] == s[fast] && s[fast] == ' ') { continue; }
            else { s[slow++] = s[fast]; }
        }
        if (slow - 1 > 0 && s[slow - 1] == ' ') { s.resize(slow - 1); }
        else { s.resize(slow); }
        reverse(s, 0, s.size() - 1);
        for (int i = 0, start = 0; i <= s.size(); i++) {
            if (i == s.size() || s[i] == ' ') {
                reverse(s, start, i - 1);
                start = i + 1;
            }
        }
        return s;
    }
};
class lc28 {
public:
    void getNext(int *next, string needle) {
        int j = -1;
        next[0] = j;
        for (int i = 1; i < needle.size(); i++) {
            while (j >= 0 && needle[i] != needle[j + 1]) { j = next[j]; }
            if (needle[i] == needle[j + 1]) { j++; }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int j = -1;
        int next[needle.size()];
        for (int i = 0; i < haystack.size(); i++) {
            while (haystack[i] != needle[j + 1]) { j = next[j]; }
            if (haystack[i] == needle[j + 1]) { j++; }
            if (j == needle.size() - 1) { return i - (needle.size() - 1); }
        }
        return -1;
    }
};
class lc459 {
public:
    // 移动匹配
    bool repeatedSubstringPattern(string s) { return (s + s).find(s, 1) != s.size(); }
    void getNext(int *next, const string &s) {
        next[0] = -1;
        int j = -1;
        for (int i = 1; i < s.size(); i++) {
            while (j >= 0 && s[i] != s[j + 1]) { j = next[j]; }
            if (s[i] == s[j + 1]) { j++; }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern2(string s) {
        if (s.size() == 0) { return false; }
        int next[s.size()];
        getNext(next, s);
        int len = s.size();
        if (next[len - 1] != -1 && len % (len - (next[len - 1] + 1)) == 0) { return true; }
        return false;
    }
};