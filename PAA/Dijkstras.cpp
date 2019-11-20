#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<utility>

struct Edge{
    ///direction : 0 =  no direction, 1 = from v1 to v2, 2 from v2 to v2
    unsigned int price, direction;
    unsigned int v1, v2;

    Edge(){}

    Edge(unsigned int price,unsigned int direction, unsigned int v1, unsigned int v2){
        this->price  = price;
        this->direction  =  direction;
        this->v1 = v1;
        this->v2 = v2;
    }

    bool is_part(unsigned int v){
        if(v == v1 || v == v2) return true;
        return false;
    }

};

struct Vertex{
    std::list<Edge*> edges;
    unsigned int id;

    Vertex(){}

    Vertex(unsigned int id){
        this->id  = id;
    }

    bool chega(Vertex* v){
        for(auto i: edges){
            if(i->is_part(v->id)){
                if((i->v1==v->id && i->direction == 1) ||
                   (i->v2==v->id && i->direction == 2) ||
                    i->direction  == 0)
                    return true;
            }
        }
        return false;
    }

    bool sai(Vertex* v){
        for(auto i: edges){
            if(i->is_part(v->id)){
                if((i->v1==v->id && i->direction == 2) ||
                   (i->v2==v->id && i->direction == 1) ||
                    i->direction == 0)
                        return true;
            }
        }
        return false;
    }

    Edge* findEdge(Vertex* v){
        for(auto i: edges){
            if(i->is_part(v->id))
                return i;
        }

        return nullptr;
    }
};


class Graph{
    protected:

        unsigned int amount = 0;

        std::list<Vertex*> vertices;

        void removeEdges(Vertex* v){
            for(auto i: vertices){
                i->edges.remove(i->findEdge(v));
            }
            v->edges.clear();
        }

    public:

        std::list<Vertex*> getVertices(){ return vertices; }

        Graph(unsigned int amt ){ amount = amt;}

        int getAmt(){
            return amount;
        }

        Vertex* findVertex(unsigned int id){
            for(auto i: vertices){
                if(i->id == id)
                    return i;
            }

            return nullptr;
        }

        void addVertex(unsigned int id){
            for(auto i : this->vertices){
                if(i->id == id){
                    std::cout<<"Esse elemento ja existe"<<std::endl;
                    return;
                }
            }

            Vertex* v =  new Vertex(id);

            this->vertices.push_back(v);
            this->amount++;
        }

        void addVertex(Vertex* v){
            if(std::find(vertices.begin(),vertices.end(),v)!=vertices.end()){
                std::cout<<"Esse elemento ja existe"<<std::endl;
                return;
            }
            this->vertices.push_back(v);
            this->amount++;
        }

        bool removeVertex(unsigned int id){
            Vertex* v = findVertex(id);

            if(v!=nullptr){
                removeEdges(v);
                vertices.remove(v);
                free(v);
                amount--;
                return true;
            }
            return false;
        }

        ///Add edge from id1 to id2
        virtual void addEdge(unsigned int id1, unsigned int id2, unsigned int price) = 0;

        virtual void removeEdge(unsigned int id1, unsigned int id2) = 0;

        virtual void printEdges()= 0 ;

};

class UndirectedGraph: public Graph{

    public:

        UndirectedGraph(unsigned int amt):Graph(amt){}

        void addEdge(unsigned int id1, unsigned int id2, unsigned int price){
            Vertex* v1 = findVertex(id1);
            Vertex* v2 = findVertex(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os Vertexs requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                return;
            }

            Edge* edge =  new Edge(price,0,id1,id2);

            v1->edges.push_back(edge);
            v2->edges.push_back(edge);
        }

        void removeEdge(unsigned int id1, unsigned int id2){
            Vertex* v1 = findVertex(id1);
            Vertex* v2 = findVertex(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os Vertexs requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                v1->edges.remove(v1->findEdge(v2));
                v2->edges.remove(v2->findEdge(v1));
            }

        }

        void createEdges() {
          addEdge(0,1,4);
          addEdge(0,2,5);
          addEdge(2,3,10);
          addEdge(3,1,6);
          addEdge(3,5,9);
          addEdge(5,4,2);

        }

        void printEdges(){
          for(auto i:vertices){
            std::cout<< i->id << "\n  Arestas   ";
            for(auto j: i->edges){
              std::cout<<"->"<<"("<<j->v1<<","<<j->v2<<")"<<" price = "<<j->price<<"       ";
            }
            std::cout<<"\n";
          }
        }


        void dijkstra(unsigned int id){
            std::list<Edge*> result;
            std::list<Vetex*>
        }
};


int main(){
    int n = 6;
    int aux = 0;
    std::cout<<"Grafo nao direcionado\n";
    UndirectedGraph undirGraph(n);
    for(int i = 0; i<n;i++){
        undirGraph.addVertex(i);
    }

    undirGraph.createEdges();
    undirGraph.printEdges();
    std::cout<<"\n\n";
}
