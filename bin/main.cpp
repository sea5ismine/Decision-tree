#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
struct node
{
    int attr[4];
    char name;
    int input()
    {
        int x = scanf("%c,%d,%d,%d,%d", &name, &attr[0], &attr[1], &attr[2], &attr[3]);
        getchar();
        return x;
    }
};
struct tree_node
{
    int attr_id;
    int attr_num;
    vector <tree_node*> child;
};
node pt[1005];
tree_node root;
int n;

double Cal_entropy(double frequency, double total)
{
    if(fabs(frequency) < eps)
        return 0.0;
    return - (frequency / total) * log2(frequency / total);
}
int name_to_id(char name)
{
    if(name == 'B')
        return 0;
    if(name == 'L')
        return 1;
    if(name == 'R')
        return 2;
    return -1;
}
vector <tree_node> stk;
void dfs(tree_node *x)
{
    int sta = 0;
    for(int i = 0; i < stk.size(); i++)
        sta |= 1 << stk[i].attr_id;
    double g[3][4][5] = {0};
    double cnt[4] = {0};
    double tot = 0;
    for(int i = 0; i < n; i++)
    {
        int flag = 1;
        for(int j = 0; j < stk.size(); j++)
            if(pt[i].attr[stk[j].attr_id] != stk[j].attr_num)
                flag = 0;
        if(flag)
        {
            for(int j = 0; j < 4; j++)
            {
                g[name_to_id(pt[i].name)][j][pt[i].attr[j]]++;
                cnt[name_to_id(pt[i].name)]++;
                tot++;
            }
        }
    }
    tot /= 4.0;
    double e = 0.0;
    for(int i = 0; i < 3; i++)
    {
        cnt[i] /= 4.0;
        e += Cal_entropy(cnt[i], tot);
    }
    for(int i = 0; i < 4; i++)
    {
        if(!(sta & (1 << i)))
        {

        }
    }
}

int main()
{
    freopen("data.txt", "r", stdin);
    n = 0;
    while(pt[n].input() == 5)
        n++;
    dfs(&root);
    return 0;
}
