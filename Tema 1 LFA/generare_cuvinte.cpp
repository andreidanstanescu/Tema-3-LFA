//cele mai mici 100 de cuvinte
#include<bits/stdc++.h>
#define N 100
#define M 100
using namespace std;

int n,m,start,nre;
vector< pair< int, char > > G[N];
unordered_set<int> sfarsit;
vector<string>ans;
char s[N];

void citire()
{
    ifstream fin("AFN.txt");
    int x,y,i;
    char c;
    fin>>n;
    fin>>m;
    for(i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        G[x].push_back(make_pair(y,c));
    }
    fin>>start;
    fin>>nre;
    for(i=0;i<nre;i++)
    {
        fin>>x;
        sfarsit.insert(x);
    }
    fin>>s;
    fin.close();
}

struct mat{
    int node;
    string cuv;
}q[N*M];

void distante()
{
    int inc,i,l,r,index,nod;
    q[0].node=start;
    q[0].cuv="";
    l=0;
    r=1;
    while(l<r)
    {
		nod = q[l].node;
		//cout<<nod<<' ';
		for (auto &it : G[nod])
		{
			q[r].node = it.first;
			q[r].cuv=q[l].cuv+it.second;
            if(sfarsit.count(it.first))
                {
                    ans.push_back(q[r].cuv);
                    //cout<<ans.size()<<' ';
                    if(ans.size()>=N) goto afisare;
                //cout<<q[r].cuv<<'\n';
                }
            ++r;

		}
		++l;
    }
afisare:
    ofstream fout("cuvinte.out");
    for(i=0;i<ans.size();i++)
        fout<<ans[i]<<'\n';
        fout.close();

}




int main()
{
    citire();
    distante();
}
