#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
const int maxk = 10; //预测属性种类数
const int maxa = 10; //其他属性数
const int maxak = 10; //其他属性种类数
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
    int attr_id;   //划分条件
    int attr_num;  //划分值
    int leaf_attr; //最终预测属性
    vector <tree_node*> child;
    tree_node(){}
    tree_node(int _id, int _num): attr_id(_id), attr_num(_num){}
};
node pt[1005]; //样本
tree_node root;
int n;

double Cal_entropy(double frequency, double total)
{
    if(fabs(frequency) < eps)
        return 0.0;
    return -(frequency / total) * log2(frequency / total);
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
void dfs(tree_node *x, int K, int attr, int attr_k)
{
    //cout<<x->attr_id<<" "<<x->attr_num<<endl;
    int sta = 0;
    for(int i = 0; i < stk.size(); i++)
        sta |= 1 << stk[i].attr_id;
    double g[maxk][maxa][maxak] = {0};
    double cnt[maxk] = {0};
    double tot = 0;
    for(int i = 0; i < n; i++)
    {
        int flag = 1;
        for(int j = 0; j < stk.size(); j++)
            if(pt[i].attr[stk[j].attr_id] != stk[j].attr_num)
                flag = 0;
        if(flag)
        {
            for(int j = 0; j < attr; j++)
            {
                g[name_to_id(pt[i].name)][j][pt[i].attr[j]]++;
                cnt[name_to_id(pt[i].name)]++;
                tot++;
            }
        }
    }
    if(sta == (1 << attr) - 1)
    {
        double mx = cnt[0], loc = 0;
        for(int i = 1; i < K; i++)
            if(cnt[i] > mx)
                mx = cnt[i], loc = i;
        x->leaf_attr = loc;
        return ;
    }
    tot /= (double)attr;
    double e = 0.0;
    for(int i = 0; i < K; i++)
    {
        cnt[i] /= (double)attr;
        e += Cal_entropy(cnt[i], tot);
    }
    double mx_gain = INT_MIN, loc;
    for(int i = 0; i < attr; i++)
    {
        if(!(sta & (1 << i)))
        {
            double e_i = 0.0;
            for(int j = 1; j <= attr_k; j++)
            {
                double e_j = 0.0;
                double tot_j = 0.0;
                for(int k = 0; k < K; k++)
                    tot_j += g[k][i][j];
                for(int k = 0; k < K; k++)
                    e_j += Cal_entropy(g[k][i][j], tot_j);
                e_i += tot_j / tot * e_j;
            }
            if(e_i > mx_gain)
                mx_gain = e_i, loc = i;
        }
    }
    for(int i = 1; i <= attr_k; i++)
    {
        stk.push_back(tree_node(loc, i));
        x->child.push_back(new tree_node(loc, i));
        dfs(x->child[x->child.size() - 1], K, attr, attr_k);
        stk.pop_back();
    }
}
void test(node x)
{
    tree_node *now = &root;
    while(now->child.size() != 0)
    {
        for(int i = 0; i < now -> child.size(); i++)
        {
            tree_node *tmp = now -> child[i];
            if(x.attr[tmp -> attr_id] == tmp -> attr_num)
            {
                now = tmp;
                break;
            }
        }
    }
    int cnt = 0;
    //cout<<now->leaf_attr<<" "<<x.name<<endl;
    if(now -> leaf_attr != name_to_id(x.name))
        cout<<++cnt<<endl;
}
int main()
{
    freopen("data.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    n = 0;
    while(pt[n].input() == 5)
        n++;
    dfs(&root, 3, 4, 5);
    for(int i = 0; i < n; i++)
        test(pt[i]);
    return 0;
}
