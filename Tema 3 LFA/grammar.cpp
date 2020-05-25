#include<bits/stdc++.h>
#define N 100
#define M 100
using namespace std;


class RegGrammar{
    map< string, set<string> > noneps;
    //map< string, set<string> > fsa;
    vector< string >eps;
    vector< int > v[N][M];
    int inc,nrf,sfarsit[N];

public:
    RegGrammar()
    {

    }
    RegGrammar EpsFree();
    void FSA();
    void dfa();
    friend istream& operator>>(istream& ,RegGrammar&);
    friend ostream& operator<<(ostream& out,RegGrammar& R);
    ~RegGrammar()
    {

    }
};


RegGrammar RegGrammar::EpsFree()
{
    RegGrammar R;
    for(map< string, set<string> >::iterator it=noneps.begin();it!=noneps.end();++it)
    {
        for(const auto& it2:noneps[it->first])
            R.noneps[it->first].insert(it2);
    }
    for(const auto& it:eps)
    {
        string to_find=it;
        if(to_find=="S")
            {
                //tratez maine cazul
                string aux("S1");
                R.noneps[aux].insert(to_find);
                R.noneps[aux].insert("$");
            }
        else
        {
            for(map< string, set<string> >::iterator it=noneps.begin();it!=noneps.end();++it)
                for(const auto& it2:noneps[it->first])
                    if(it2.find(to_find))
                        {//cout<<it2.substr(0)<<' ';
                            if(it2.size()==2)
                            {   string aux=it2.substr(0,1);
                                R.noneps[it->first].insert(aux);
                                //cout<<aux<<' ';
                            }
                            else
                            {
                                //cout<<it2<<' ';
                                eps.push_back(it2);
                            }
                        }
        }
    }
    string to_find="S1";
    map< string, set<string> >::iterator it=R.noneps.find(to_find);
    if(it!=R.noneps.end())
        {for(const auto& it2:R.noneps["S"])
            R.noneps[to_find].insert(it2);
        R.noneps[to_find].erase("S");
        }
    return R;
}


void RegGrammar::FSA()
{
    //cout<<noneps.size();
    ofstream cout("grammar.out");
    inc=0;
    nrf=2;
    int nrtranz=0;
    for(int i=0;i<noneps.size();++i)
        sfarsit[i]=0;
    sfarsit[0]=1;
    sfarsit[noneps.size()]=1;
    int p=1;
    for(map< string, set<string> >::iterator it=noneps.begin();it!=noneps.end();++it){
        //cout<<it->first<<' ';
        for(const auto& it2:noneps[it->first])
    {

        if(it2.size()==2)
        {
            string aux=it2.substr(0,1);
            string aux2=it2.substr(1,1);
            //cout<<it->first<<' '<<aux<<' '<<aux2<<endl;
            //cout<<aux2<<' ';
            if(it->first!="S1")
                {
                    v[it->first[0]-'A'+1][aux[0]-'a'].push_back(aux2[0]-'A'+1);
                }
            else
                v[0][aux[0]-'a'].push_back(aux2[0]-'A'+1);
            ++nrtranz;
        }
        else
        {
            if(it2!="$")
                {
                    //cout<<it->first<<' '<<it2<<' '<<"D0"<<endl;
                    if(it->first!="S1")
                        v[it->first[0]-'A'+1][it2[0]-'a'].push_back(noneps.size());
                    else
                        v[0][it2[0]-'a'].push_back(noneps.size());
                    ++nrtranz;
                }
            //v[it][it2].push_back("D0");
        }
    }
    }
    cout<<noneps.size()+1<<endl;
    cout<<nrtranz<<endl;
    for(map< string, set<string> >::iterator it=noneps.begin();it!=noneps.end();++it){
        //cout<<it->first<<' ';
        for(const auto& it2:noneps[it->first])
    {

        if(it2.size()==2)
        {
            string aux=it2.substr(0,1);
            string aux2=it2.substr(1,1);
            cout<<it->first<<' '<<aux<<' '<<aux2<<endl;
            //cout<<aux2<<' ';
        }
        else
            if(it2!="$")
                cout<<it->first<<' '<<it2<<' '<<"D0"<<endl;

    }
    }
    cout<<"S1\n";
    cout<<2<<endl;
    cout<<"S1 "<<"D0"<<endl;

    //nfa->dfa(din tema 2)
    queue<int> q;
    q.push(0);
    int dfa[N][M];
    vector< set<int> > sol;
    int ns=1;  //numar stari din dfa
    set<int> s;
    s.insert(inc);
    sol.push_back(s);

    while(!q.empty())
    {
        int nod=q.front();
        q.pop();

        for(int i=0;i<M;i++)
        {
            set<int> sc; //starile curente, ce trebuie adaugate in coada
            for(int j:sol[nod])
                  for(int k:v[j][i])
                {
                    sc.insert(k);
                    //cout<<k<<' ';
                }
        //verific daca a mai aparut setul curent
        //for(int j:sc)
            //cout<<j<<' ';
        //cout<<endl;
        bool gasit=0;
        int j;
        for(j=0;j<ns && !gasit;++j)
            if(sol[j]==sc)
                {
                    gasit=1;
                    //break;
                }
        //cout<<(sol[0]==sc)<<endl;
        if(!gasit)
        {
            sol.push_back(sc);
            q.push(ns);
            dfa[nod][i]=ns;
            ++ns;
        }
        else
            dfa[nod][i]=j-1;

        }

    }

    cout<<"Numarul de stari al dfa-ului echivalent:"<<ns<<endl;
    cout<<"Starile sunt:\n";
    for(int i=0;i<ns;i++)
    {   cout<<'{';
        for(int j:sol[i])
    cout<<j<<' ';
    cout<<'}'<<endl;
    }
    cout.close();
}

istream& operator>>(istream& in,RegGrammar& R)
{
    string left,right;
    in>>left;
    in>>right;
    while(in>>left)
    {
        in>>right;
        if(right.find('$'))
            {
                R.noneps[left].insert(right);
                continue;
            }
        R.eps.push_back(left);
    }
    return in;
}

ostream& operator<<(ostream& out,RegGrammar& R)
{
    //out<<R.eps.size()<<endl;
    out<<"Gramatica fara productii epsilon:\n";
    for(map< string, set<string> >::const_iterator it=R.noneps.begin();it!=R.noneps.end();++it)
    {
        out<<it->first<<":";
        for(const auto& it2:R.noneps[it->first])
           out<<it2<<' ';
        out<<'\n';
    }
    return out;
}

int main()
{
    RegGrammar reg,reg_sol;
    ifstream fin("grammar.in");
    fin>>reg;
    fin.close();
    //cout<<reg;
    reg_sol=reg.EpsFree();
    cout<<reg_sol<<endl;
    reg_sol.FSA();
}
