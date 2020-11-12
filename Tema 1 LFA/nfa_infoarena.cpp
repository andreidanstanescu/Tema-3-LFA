#include<bits/stdc++.h>
#define N 152
#define Nmax 301
using namespace std;
int n,m,q,start,nre;

//unordered_set<int> sfarsit;
int sfarsit[Nmax];
char s[N];
//typedef unordered_multimap<char, int>:: iterator umit;

vector< pair<int,char> > mat[Nmax];

/*bool accepta(vector<  unordered_multimap< char, int  > >& G,string s)
{
    int inc,i,l,r,index;
    int q[N*Nmax]={start};
    queue<int> q1;
    q1.push(start);
    l=0;
    r=1;
    for(i=0;i<s.size();i++)
    {
        bool gasit=false;
        int k=r;
        for(index=l;index<k;index++)
        {
            //inc=q[index];
            inc=q1.front();
            q1.pop();
            //cout<<inc<<' ';
            pair<umit,umit> it=G[inc].equal_range(s[i]);
            umit it1=it.first;
            umit it2=it.second;
            while(it1!=it2)
            {
                if(it1->second!=-1)  //din cauza valorii de initializare
                {//q[r++]=it1->second;
                    q1.push(it1->second);
                    r++;
                    gasit=true;
                    it1++;
                }
            }

        }
        if(gasit==false)
               return 0;
        l=k;

    }
    for(index=l;index<r;index++)
    {
        //inc=q[index];
        inc=q1.front();
        q1.pop();
        if(sfarsit.count(inc))
            return 1;
    }
    return 0;

}*/

bool raspuns,viz[Nmax][N];

void dfs(int x,int i)
{
    if(raspuns)
        return;
    if(i==strlen(s))
    {
        if(sfarsit[x])
            raspuns=1;
        return;
    }
    viz[x][i]=1;
    for(int index=0;index<mat[x].size();++index)
    {
        if((mat[x][index].second)==s[i])
        {
            int curr=mat[x][index].first;
            //daca am mai ajuns in acest nod la pozitia actuala nu are rost sa mai verific inca o data
            if(!viz[curr][i+1])
                dfs(curr,i+1);
        }
    }

}

void citire()
{
    ifstream fin("nfa.in");
    ofstream fout("nfa.out");
    int x,y,i;
    char c;
    fin>>n;
    fin>>m;
    fin>>nre;
    fin>>start;
    for(i=0;i<nre;i++)
    {
        fin>>x;
        sfarsit[x]=1;
    }
    //some garbage value in order to be initialized this vector
    //vector<  unordered_multimap< char, int  > > G(Nmax+1);
    for(i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        //G[x].insert({c,y});
        mat[x].push_back({y,c});
    }
    fin>>q;
    for(i=0;i<q;i++)
    {
        fin>>s;
        //fout<<accepta(G,s)<<'\n';
        raspuns=0;
        //memset(viz,0,sizeof(viz));
        for(int k=1;k<=n;k++)
            for(int l=0;l<=strlen(s);l++)
            viz[k][l]=0;
        dfs(start,0);
        fout<<raspuns<<'\n';
    }
    fin.close();
    fout.close();
    //cout<<G[3].count('a');
    //return G;
}



int main()
{
    //vector<  unordered_multimap< char, int  > > G=citire();
    //cout<<G[3].count('a');
    citire();
}

