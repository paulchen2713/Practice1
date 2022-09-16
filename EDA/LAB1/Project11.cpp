#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iomanip>

using namespace std;

const int MAX_DISTANCE = 10000;
ofstream out;

using Node = string;

struct Edge {
    // 一個edge需要起始點, 終點, 距離
    Node from, to;
    int distance;
    Edge(Node u, Node v, int l) : from(u), to(v), distance(l) {};
};

class Graph {
private:
    // 所有edge, 所有node
    map<Node, vector<Edge>> edges;
    set<Node> nodes;

public:
    // 把一條edge塞入graph, 同時把from和to兩點塞進nodes
    void addEdge(Node from, Node to, int distance)
    {
        edges[from].push_back(Edge(from, to, distance));
        nodes.insert(from);
        nodes.insert(to);
    }

    void bellman_ford(bool is_longest = false)
    {
        // 把set轉為vector
        vector<Node> nodes(this->nodes.begin(), this->nodes.end());
        vector<Node> registers;

        for (const Node& node : nodes)
            if (node[0] == 'R')
                registers.push_back(node);

        // 每個register都當起點試試看
        for (const Node& nodei : registers)
        {
            Node first = nodei;
            //cout << edges[first].size() << endl;
            // register後繼無人直接下一位
            if (edges[first].size() == 0)
                continue;

            map<Node, int> cost;

            // 初始化 所有node的cost都最大
            for (const Node& node : nodes)
            {
                cost[node] = MAX_DISTANCE;
            }

            // 起始點的cost為0
            cost[first] = 0;

            // 每條edge都加進來 relaxation找出最小的cost
            // relaxation要重複 nodes size - 1次 以確定是最小的cost (後面加進來的edge可能讓cost變得更小)
            for (int i = 0; i < nodes.size() - 1; i++)
            {
                for (const Node& node : nodes)
                {
                    for (const Edge& edge : edges[node])
                    {
                        // 當前的cost + 目的地的distance 比 目的地的cost小就改
                        if (cost[node] + edge.distance < cost[edge.to])
                        {
                            cost[edge.to] = cost[node] + edge.distance;
                        }
                    }
                }
            }

            // 印出來 當前register到每個register的cost
            for (const Node& node : registers)
            {
                if (node == first || cost[node] == MAX_DISTANCE)
                    continue;

                out << left << setw(8) << first << setw(8) << node << (is_longest ? -cost[node] : cost[node]) << endl;
                cout << left << setw(8) << first << setw(8) << node << (is_longest ? -cost[node] : cost[node]) << endl;
            }
        }
    }
};

int main()
{

    stringstream ss;
    string line, filename, out_filename;
    // 所有gate的cost
    map<Node, int> dis;
    // 所有edge 和 所有node
    map<Node, vector<Node>> edges;
    set<Node> nodes;

    cin >> filename;
    ifstream in(filename);
    out_filename = filename.substr(0, filename.length() - 4) + "_out.txt";

    out.open(out_filename);

    getline(in, line);

    while (getline(in, line))
    {
        if (line.substr(0, 3) == "END")
            break;

        // 把尾巴的空白去掉 不管\n還是\r\n
        ss << line;
        ss >> line;

        string g;
        int c;
        size_t tmp = line.find(',');

        // 逗號前是gate名 , 逗號後是gate cost
        g = line.substr(1, tmp - 1);
        c = stoi(line.substr(tmp + 1, line.length() - tmp - 2));
        dis[g] = c;

        ss.str("");
        ss.clear();
    }

    getline(in, line);
    getline(in, line);
    getline(in, line);

    while (getline(in, line))
    {
        if (line.substr(0, 3) == "END")
            break;

        string from, to, tmp;

        ss << line;
        ss >> from >> tmp >> to;

        edges[from].push_back(to);
        nodes.insert(from);
        nodes.insert(to);

        ss.str("");
        ss.clear();
    }

    // 所有register
    vector<Node> registers;
    for (const Node& node : nodes)
        if (node[0] == 'R')
            registers.push_back(node);

    // 做兩次 一次最長一次最短
    // 最長的就是把每個edge的distance改成負的找最短的
    // 印結果時再把負號改回來
    for (int i = 0; i < 2; i++)
    {
        bool is_longest = (i == 0);

        out << (is_longest ? "Longest" : "shortest") << " path\n#From   To\n";
        cout << (is_longest ? "Longest" : "shortest") << " path\n#From   To\n";

        // 找出從每個register開始的 subgraph
        // nodei是每個subgraph的起始點
        for (const Node& nodei : registers)
        {
            Graph graph;
            queue<Node> q;
            // 這個subgraph裡的所有node
            set<Node> s;
            // 起始點丟進佇列
            q.push(nodei);

            // 直到佇列空了 跑完找到的set就是這個subgraph所有的node
            while (!q.empty())
            {
                // 佇列頭丟進set裡
                s.insert(q.front());
                /*
                for (set<string>::const_iterator it = s.begin(); it != s.end(); it++)
                    cout << *it << endl;
                */
                cout << "======================================" << endl;
                for (set<string>::const_iterator it = s.begin(); it != s.end(); it++)
                    cout << *it << endl;
                // 當佇列頭不是起始點 且 佇列頭是register 直接跳過
                if (q.front() != nodei && q.front()[0] == 'R')
                {
                    q.pop();
                    continue;
                }
                // 把每個佇列頭開始的edge的to都丟進佇列和set裡
                for (const Node& to : edges[q.front()])
                {
                    // 如果已經在set裡 (在佇列裡或出現過) 就跳過
                    // 其他丟進去
                    if (!s.count(to))
                    {
                        s.insert(to);
                        q.push(to);
                    }
                }
                // 佇列頭丟掉 下面一位
                q.pop();
            }

            // 把所有node開始的edge加到subgraph
            for (const Node& from : s)
            {
                // 當from不是起始點 且 from是register 直接跳過
                if (from != nodei && from[0] == 'R')
                    continue;

                // 每條edge都加 除了目的地是起始點的 避免接回頭出現cycle
                // 如果有cycle, 找longest path會失敗 *
                for (const Node& to : edges[from])
                {
                    // 目的地是起始點的就跳過
                    if (to == nodei)
                        continue;
                    // edge加進graph
                    graph.addEdge(from, to, (is_longest ? -dis[to] : dis[to]));
                }
            }
            // 找最長或最短
            graph.bellman_ford(is_longest);
        }

        out << "END " << (is_longest ? "longest" : "shortest") << " path\n\n";
        cout << "END " << (is_longest ? "longest" : "shortest") << " path\n\n";
    }
    return 0;
}
