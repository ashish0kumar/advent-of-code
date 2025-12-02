#include <bits/stdc++.h>
using namespace std;

struct Op
{
    string w1, w2, out, type;
};

bool isInputWire(const string &w)
{
    return w[0] == 'x' || w[0] == 'y';
}

int main()
{
    string line;
    regex pattern(R"(([a-z0-9]+) ([A-Z]+) ([a-z0-9]+) -> ([a-z0-9]+))");
    smatch match;
    vector<Op> ops;
    unordered_map<string, vector<Op>> mp;
    int maxZ = 0;

    while (getline(cin, line))
    {
        if (!regex_search(line, match, pattern))
            continue;
            
        Op op = {match[1], match[3], match[4], match[2]};
        ops.push_back(op);
        mp[op.w1].push_back(op);
        mp[op.w2].push_back(op);

        if (op.out[0] == 'z')
            maxZ = max(maxZ, stoi(op.out.substr(1)));
    }

    for (auto &[wire, vec] : mp)
    {
        sort(vec.begin(), vec.end(), [](const auto &a, const auto &b)
             { return a.type < b.type; });
    }

    set<string> outs;
    for (const auto &op : ops)
    {
        const auto &w1 = op.w1, &w2 = op.w2, &out = op.out, &type = op.type;
        if (out[0] == 'z')
        {
            int idx = stoi(out.substr(1));
            if (idx == 0 || idx == maxZ)
                continue;
        }

        bool isInput = isInputWire(w1);
        bool isAlsoInput = isInputWire(w2);

        if (isInput && !isAlsoInput)
            outs.insert(out);

        if (type == "XOR")
        {
            if (isInput && out[0] == 'z')
                outs.insert(out);
            if (isInput && (mp[out][0].type != "AND" || mp[out][1].type != "XOR"))
                outs.insert(out);
            if (!isInput && out[0] != 'z')
                outs.insert(out);
        }

        else if (type == "AND" && (mp[out].size() < 1 || mp[out][0].type != "OR"))
            outs.insert(out);

        else if (type == "OR")
        {
            if (isInput || isAlsoInput)
                outs.insert(out);
            if (!mp.count(out) || mp[out].size() != 2 ||
                mp[out][0].type != "AND" || mp[out][1].type != "XOR")
                outs.insert(out);
        }
    }

    for (const auto &op : ops)
    {
        if (op.w1 == "x00" || op.w2 == "x00" || op.w1 == "y00" || op.w2 == "y00")
            outs.erase(op.out);
    }

    for (const auto &out : outs)
        cout << out << ',';

    cout << endl;
}