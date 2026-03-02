void removeExtraSpaces(string& s) {
    int slow = 0; 
    for (int fast = 0; fast < s.size(); ++fast) {
        // 场景 1: 遇到非空格字符，说明找到了一个单词
        if (s[fast] != ' ') {
            // 场景 2: 如果 slow != 0，说明这不是第一个单词，
            // 我们需要在单词之间手动补一个空格
            if (slow != 0) {
                s[slow++] = ' ';
            }

            // 场景 3: 循环写入整个单词，直到遇到空格或结尾
            while (fast < s.size() && s[fast] != ' ') {
                s[slow++] = s[fast++];
            }
        }
    }
    // 最后，将字符串的大小重置为 slow 的位置
    s.resize(slow);
}