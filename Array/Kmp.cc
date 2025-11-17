#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
  build_lps(pattern)
  ------------------
  计算模式串 pattern 的 lps 数组（longest proper prefix which is also suffix）。
  lps[i] 的定义：
    对于模式串 pattern[0..i]（长度 i+1），
    lps[i] = 最大的 k（0 <= k < i+1），使得
      pattern[0..k-1] == pattern[i-k+1 .. i]
    注意 "proper" 前缀意思是 k < i+1（不能等于整个子串长度）。
  这个数组用于在失配时决定模式串应该向右移动多少（而不是回到 0）。
*/
vector<int> build_lps(const string &pat) {
    int m = (int)pat.size();
    vector<int> lps(m, 0);     // 初始化所有位置为 0
    if (m == 0) return lps;    // 空串直接返回空数组

    // len：表示目前匹配的最长前缀后缀的长度（对于 pat[0..i-1]）
    // 我们从 i = 1 开始计算，因为 lps[0] = 0（单字符没有 proper 前后缀）
    int len = 0;
    int i = 1;

    // 循环直到处理完所有 i（0..m-1）
    while (i < m) {
        if (pat[i] == pat[len]) {
            // pat[i] 与 pat[len] 匹配：
            // 我们可以把当前最长长度扩展 1
            len++;           // 增加匹配长度
            lps[i] = len;    // 设置 lps[i]
            i++;             // 处理下一个 i
        } else {
            // pat[i] 与 pat[len] 不匹配
            if (len != 0) {
                // 如果 len != 0，我们不能直接把 lps[i] 置 0。
                // 依据 KMP 思路，需要回溯到 lps[len-1] 去尝试缩短前缀长度，
                // 因为较短的前缀可能仍然和当前后缀对齐。
                len = lps[len - 1];
                // 注意：此处不要增加 i，因为我们想用新的 len 再比较 pat[i]。
                // 这就是 KMP 能做到线性时间的关键（避免重复从 0 开始）。
            } else {
                // len == 0，说明没有任何可回退的前缀：lps[i] = 0
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/*
  kmp_search_all(txt, pat)
  -------------------------
  使用 KMP 算法在 txt 中查找模式 pat 的所有出现位置（返回所有起始下标）。
  返回值：vector<int>，包含所有匹配起始下标（按升序）。
  复杂度：O(n + m)，其中 n = txt.length(), m = pat.length().
*/
vector<int> kmp_search_all(const string &txt, const string &pat) {
    vector<int> res;
    int n = (int)txt.size();
    int m = (int)pat.size();
    if (m == 0) {
        // 约定：空模式串在每个位置都“匹配”，但通常我们只返回 0。
        res.push_back(0);
        return res;
    }
    vector<int> lps = build_lps(pat);

    int i = 0; // txt 索引
    int j = 0; // pat 索引

    while (i < n) {
        if (txt[i] == pat[j]) {
            i++;
            j++;
            if (j == m) {
                // 完全匹配一次：记录起始位置 i - j
                res.push_back(i - j);
                // 为了继续查找可能的重叠匹配，按照 KMP 做法：
                j = lps[j - 1]; // 回退到可能的下一个匹配位置
            }
        } else {
            // 不匹配
            if (j != 0) {
                // 不从头开始；回退 pat 指针到 lps[j-1]
                j = lps[j - 1];
                // 注意：不增加 i（用新的 j 重新比较 txt[i] 与 pat[j]）
            } else {
                // j == 0，无法回退，移动文本指针
                i++;
            }
        }
    }
    return res;
}

/* ---------- 测试 main ---------- */
int main() {
    string txt = "abcxabcdabcdabcyabcdabcy";
    string pat = "abcdabcy";

    // 1) 打印 lps 数组以便查看
    vector<int> lps = build_lps(pat);
    cout << "Pattern: " << pat << "\nLPS: ";
    for (int x : lps) cout << x << ' ';
    cout << "\n\n";

    // 2) 找出所有匹配位置
    vector<int> matches = kmp_search_all(txt, pat);
    if (matches.empty()) {
        cout << "No matches found\n";
    } else {
        cout << "Matches found at indices: ";
        for (int idx : matches) cout << idx << ' ';
        cout << "\n";
    }

    return 0;
}
