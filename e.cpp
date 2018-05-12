#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<set>
#include<map>
#include<utility>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<iostream>
#include<assert.h>
using namespace std;

map <string,int> mymap;
map <int,bool> group;
string str,now;
vector <int> myvec[1005];

int main()
{
    int i,j,k,t,a,b,n;

    freopen("in.txt","r",stdin);

    while(scanf("%d",&n) && n)
    {

        cout<<n<<endl;
        for(i=1;i<=n*10;i++) myvec[i].clear();

        mymap.clear();
        group.clear();
        t=1;

        for(int it=1;it<=n;it++)
        {
            cin>>str;

            cout<<str<<endl;

            for(i=0;str[i]!=':';i++) now+=str[i];

            if(mymap[now]==0)
            {
                mymap[now]=t;
                t++;
            }

            a=mymap[now];

            group[a]=1;

            cout<<"P "<<now<<endl;

            now="";

            for(++i;str[i];i++)
            {
                if(str[i]==',' || str[i]=='.')
                {
                    if(mymap[now]==0)
                    {
                        cout<<now<<endl;
                        mymap[now]=t;
                        t++;
                    }

                    b=mymap[now];
                    myvec[a].push_back(b);

                }

                else
                {
                    now+=str[i];

                }
            }


        }




    }


    return 0;
}
