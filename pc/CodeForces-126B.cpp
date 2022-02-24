/*


THE SOLUTION IS NOT MINE, THIS IS FROM THE COMMENTS


i couldnt quite do it, because i couldnt understand how to select the prefix function
so i got tle for example 
in the word aadaaeaa
i use kmp on word "a" a then "aa" 
which make me use kmp=O(n)*s (s=size of string)
z_function is kmp function, it saves on Z array on the first element of the word w and the size of the word w
select_prefix = ?
*/

#include <iostream>
#include <stdint.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <cassert>
#include <set>
 
#define IS_GOOGLE_CODEJAM 0
 
using namespace std;
 
#define PRINT_CONTAINER(arr)  do{ cerr <<"DBG " << #arr << " : "; for(auto& _x : arr){cerr << _x << "  ";} cerr << endl; }while(0)
#define PRINT_ARRAY(arr,limit)  do{ cerr <<"DBG " << #arr << " : "; for(auto _index=0; _index<(limit); ++_index) {cerr << arr[_index] << "  ";} cerr << endl; }while(0)
#define PRINT_ELEM(x)  do{ cerr <<"DBG " << #x << " : " << (x) << endl; } while(0)
 
#define READ_ARRAY(arr,n) do{ for(int _i=0; _i<(n); ++_i) cin>>arr[_i]; } while(0)
 
// ---------------------------------
 
 
const int MAXN = 1000000 + 1;
 
void extend_window(const char *str, int str_len, int left, int &right) {
    // S[0:right-left] == S[left:right]   closed interval
    // if S[0] != S[right], resulting in  left+1==right, indicating an empty range
    while (right < str_len && str[right - left] == str[right]) {
        ++right;
    }
    --right;
}
void z_function(const char *str, int str_len, int Z[]) {
    Z[0] = 0;
    int left = -1;
    int right = -1;
    for (int i=1; i < str_len; ++i) {
        if (i > right) {
            left = right = i;
            extend_window(str, str_len, left, right);
            Z[i] = right - left + 1;
        } else {
            int k = i - left;
            // We know S[0:right-left]  ==  S[left:right] =>
            //      1. S[0:k]           ==  S[left:i]
            //      2. S[k, right-left] ==  S[i:right]
            if (Z[k] < right - i + 1) {
                // exist p>=0, S[k+p] != S[p] => S[i+p] != S[p]
                Z[i] = Z[k];
            } else {
                left = i;
                extend_window(str, str_len, left, right);
                Z[i] = right - left + 1;
            }
        }
    }
    // PRINT_ARRAY(Z, str_len);
}
 
void select_prefix(const string &s, const int Z[]) {
    int max_answer = 0;
    int max_zi = Z[1];
    for (int suffix = 2; suffix < s.length(); ++suffix) {
        // if [suffix, n-1] is possible
 
        if (Z[suffix] == 0)
            continue;
        int answer_len = s.length() - suffix;
        int available_z = max_zi;
        max_zi = max(max_zi, Z[suffix]);
        if (Z[suffix] != answer_len) continue;
        if (available_z >= answer_len) {
            max_answer = answer_len;
            break;
        }
    }
    if (max_answer > 0) {
        for(int i=0; i<max_answer; ++i)
            cout << s[i];
    } else {
        cout << "Just a legend";
    }
    return;
}
int main()
{
    string input;
    cin >> input;
    static int Z_value[MAXN];
    z_function(input.c_str(), input.length(), Z_value);
    select_prefix(input, Z_value);
    return 0;
}