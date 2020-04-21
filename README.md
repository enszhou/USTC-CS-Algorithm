Ex3 最长公共子序列问题和调研报告
1.求解两个字符串s1,s2的最长公共子序列。 s1，s2均是随机生成的字符(大、小写字母和数字，共62种不同字符)。
n,m的规模分别为2^6,2^8。
2.调研求解最长公共子串算法（KMP，QuickSearch，Karp-Rabin）。
并利用K-R算法，求解字符串匹配问题。
文本串T的长度为n，对应的模式串P的长度为m，字符串均是随机生成的字符 (大、小写字母和数字，共62种不同字符)。
n,m的规模为（2^8,8）（2^11,16）(2^14,32)。

Ex4红黑树维护算法及其区间树应用
1.实现红黑树的基本算法，对于n=20,40,60,80分别生成n个随机正整数，将n个正整数作为关键字当作红黑树的结点，从空树依次插入n个节点。
对于生成的红黑树，找出树中第n/4和n/2小的节点，并删除。
2.实现区间树的基本算法，随机取n=100个0~500间随机正整数，将其作为关键字，从空树插入区间树的节点。
对于生成的区间树，找出树中第n/4和n/2小的节点，并删除。

Ex5图搜索BFS算法及存储优化
实现传统BFS以及双向BFS,并可以找到对应搜索节点对之间的路径信息。
要求利用CSR（Compressed Sparse Row）方式存储图。
数据集：http://snap.stanford.edu/data/ego-Facebook.html
