//Solutie cu multimap pentru acceptarea unui cuvant(citit de la tastatura)
#include<bits/stdc++.h>
#define N 1000
using namespace std;
int n,m,start,nre;

unordered_set<int> sfarsit;
char s[N];

typedef unordered_multimap<char, int>:: iterator umit;

vector<  unordered_multimap< char, int  > > citire()
{
    ifstream fin("AFD.txt");
    //ifstream fin("AFN.txt");
    int x,y,i;
    char c;
    fin>>n;
    fin>>m;
    //some garbage value in order to be initialized this vector
    vector<  unordered_multimap< char, int  > > G(n,{ {'z',-1} });
    for(i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        G[x].insert({c,y});
    }
    fin>>start;
    fin>>nre;
    for(i=0;i<nre;i++)
    {
        fin>>x;
        sfarsit.insert(x);
    }
    cin>>s;
    fin.close();
    //cout<<G[3].count('a');
    return G;
}



bool accepta(vector<  unordered_multimap< char, int  > > G)
{
    //cout<<G[1].count('b');
    int inc,i,l,r,index;
    int q[N]={start};
    l=0;
    r=1;
    for(i=0;i<strlen(s);i++)
    {
        bool gasit=false;
        int k=r;
        for(index=l;index<k;index++)
        {
            inc=q[index];
            //cout<<inc<<' ';
            pair<umit,umit> it=G[inc].equal_range(s[i]);
            umit it1=it.first;
            umit it2=it.second;
            while(it1!=it2)
            {
                if(it1->second!=-1)  //din cauza valorii de initializare
                {q[r++]=it1->second;
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
        inc=q[index];
        if(sfarsit.count(inc))
            return 1;
    }

}


int main()
{
    //vector<  unordered_multimap< char, int  > > G=citire();
    //cout<<G[3].count('a');
    cout<<accepta(citire());
}

//determinist
/*#include<bits/stdc++.h>
#define N 1000
using namespace std;

int n,m,start,nre;
vector< pair< int, char > > G[N];
set<int> sfarsit;
char s[N];

void citire()
{
    ifstream fin("AFD.txt");
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



bool accepta()
{
    int inc=start,i;
    for(i=0;i<strlen(s);i++)
    {
        bool gasit=false;
        for(auto &it:G[inc] )
        {
            if(it.second==s[i])
            {
                inc=it.first;
                gasit=true;
            }
        }
        if(gasit==false)
               return 0;

    }
    if(sfarsit.count(inc))
        return 1;

}


int main()
{
    citire();
    cout<<accepta();
}*/

//nedeterminist-neoptim
/*#include<bits/stdc++.h>
#define N 1000
using namespace std;

int n,m,start,nre;
vector< pair< int, char > > G[N];
set<int> sfarsit;
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
    cin>>s;
    fin.close();
}



bool accepta()
{
    int inc,i,l,r,index;
    int q[N]={start};
    l=0;
    r=1;
    for(i=0;i<strlen(s);i++)
    {
        bool gasit=false;
        int k=r;
        for(index=l;index<k;index++)
        {
            inc=q[index];
        for(auto &it:G[inc] )
        {
            if(it.second==s[i])
            {
                q[r++]=it.first;
                gasit=true;
            }
        }
        }
        if(gasit==false)
               return 0;
        l=k;

    }
    for(index=l;index<r;index++)
    {
        inc=q[index];
        if(sfarsit.count(inc))
            return 1;
    }

}


int main()
{
    citire();
    cout<<accepta();
}*/








