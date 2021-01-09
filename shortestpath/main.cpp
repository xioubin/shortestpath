#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Vertex{
private:
public:
    bool labeled;
    int index;
    float label;
    vector<Vertex*> list;
    vector<pair<float, Vertex*>> path;
    Vertex(){}
    Vertex(int index){
        this->index=index;
    }
    ~Vertex(){}
};
int main(){
    int vertexnum,pathnum,start,end;
    cin>>vertexnum>>pathnum>>start>>end;

    map<int,Vertex*> vertice;

    for(int i=0;i<vertexnum;i++){
        int fromindex,toindex;
        float weight=0;
        cin>>fromindex>>toindex>>weight;

        map<int,Vertex*>::iterator fromV=vertice.find(fromindex);
        map<int,Vertex*>::iterator toV=vertice.find(toindex);
        if(fromV==vertice.end()){
            Vertex* newV=new Vertex(fromindex);
            auto newfromV=new pair<int,Vertex*>(fromindex,newV);
            vertice.insert(*newfromV);
            fromV=vertice.find(fromindex);
        }
        if(toV==vertice.end()){
            Vertex* newV=new Vertex(toindex);
            auto newtoV=new pair<int,Vertex*>(toindex,newV);
            vertice.insert(*newtoV);
            toV=vertice.find(toindex);
        }

        fromV->second->path.push_back(pair<float,Vertex*>(weight,toV->second));
    }

    vector<Vertex*> shortestpath;
    set<Vertex*> waiting;
    Vertex* smallestV=vertice[start];
    shortestpath.push_back(smallestV);
    while(shortestpath.size()<vertexnum&&smallestV->index!=end){
        for(auto it:smallestV->path){
            float newlabel=smallestV->label+it.first;
            if(!it.second->labeled||newlabel<it.second->label){
                it.second->list=smallestV->list;
                it.second->list.push_back(smallestV);
                it.second->label=newlabel;
                it.second->labeled=true;
            }
            waiting.insert(it.second);
        }
        smallestV=*waiting.begin();
        for(auto it:waiting){
            if(it->label<smallestV->label)
                smallestV=it;
        }
        shortestpath.push_back(smallestV);
        waiting.erase(smallestV);
    }
    auto result=vertice[end];
    for(int i=0;i<result->list.size();i++){
        cout<<result->list[i]->index<<" ";
    }
    cout<<result->index<<endl;
    cout<<vertice[end]->label;

}
