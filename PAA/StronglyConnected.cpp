#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<utility>

struct Vertex{
    ///Adj são os Vertexs que saem do nodo caso seja direcionado
    ///ou é a as arestas caso sem direção
    std::list<Vertex*> adj;
    unsigned int id;

    Vertex(){}

    Vertex(unsigned int id){
        this->id  = id;
    }

    ///v -> this Vertex
    bool chega(Vertex* v){
        if(std::find(v->adj.begin(),v->adj.end(),this)!=v->adj.end())
            return true;
        else
            return false;
    }

    ///This Vertex -> v or (This Vertex -> v && This Vertex <- v)
    bool sai(Vertex* v){
        if(std::find(adj.begin(),adj.end(),v)!=adj.end())
            return true;
        else
            return false;
    }



};


class Graph{
    protected:

        unsigned int amount = 0;

        std::list<Vertex*> vertices;

        void removeEdges(Vertex* v){
            for(auto i: vertices){
                i->adj.remove(v);
            }
            v->adj.clear();
        }

    public:

        std::list<Vertex*> getVertexs(){ return vertices; }

        Graph(unsigned int amt ){ amount = amt;}

        int get_amt(){
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
        virtual void addEdge(unsigned int id1, unsigned int id2) = 0;

        virtual void removeEdge(unsigned int id1, unsigned int id2) = 0;

        virtual void printEdges()= 0 ;

};

class UndirectedGraph: public Graph{

    public:

        UndirectedGraph(unsigned int amt):Graph(amt){}

        void addEdge(unsigned int id1, unsigned int id2){
            Vertex* v1 = findVertex(id1);
            Vertex* v2 = findVertex(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os Vertexs requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                return;
            }

            v1->adj.push_back(v2);
            v2->adj.push_back(v1);
        }

        void removeEdge(unsigned int id1, unsigned int id2){
            Vertex* v1 = findVertex(id1);
            Vertex* v2 = findVertex(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os Vertexs requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                v1->adj.remove(v2);
                v2->adj.remove(v1);
            }

        }

        void createEdges() {
          addEdge(0,1);
          addEdge(0,2);
          addEdge(2,3);
          //addEdge(3,1);
          addEdge(3,5);
          addEdge(5,0);

        }

        void printEdges(){
          for(auto i:vertices){
            std::cout<< i->id << "\n  Aresta   ";
            for(auto j: i->adj){
              std::cout<<"->"<<j->id<<"       ";
            }
            std::cout<<"\n";
          }
        }
};


class DirectedGraph: public Graph{
    protected:
        bool topologicalOrder_(std::list<Vertex*>& vertices_copy,std::list<Vertex*>& result){
          for(auto i: vertices_copy){
            unsigned int qnt_chega = 0;
            for(auto k: vertices_copy){
                if(k->sai(i) && i==k) return false;
                if(k->sai(i)) qnt_chega++;
            }
            if(qnt_chega<=1){
              result.push_back(i);
              vertices_copy.remove(i);
              for(auto j: vertices_copy){
                  j->adj.remove(i);
              }
              i->adj.clear();
              return true;
            }
          }
          return false;
        }

    public:

        DirectedGraph(unsigned int amt):Graph(amt){}

        ///Sai de id1 para id2
        void addEdge(unsigned int id1, unsigned int id2){
            Vertex* v1 = findVertex(id1);
            Vertex* v2 = findVertex(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os Vertexs requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                return;
            }

            v1->adj.push_back(v2);
        }
        ///Remove edge from id1 to id2
        void removeEdge(unsigned int id1, unsigned int id2){
            Vertex* v1 = findVertex(id1);
            Vertex* v2 = findVertex(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os Vertexs requesitados"<<std::endl;
                return;
            }

            if(v1->chega(v2)){
               v2->adj.remove(v1);
            }

            if(v1->sai(v2)){
                v1->adj.remove(v2);
            }

        }

        void createEdges(UndirectedGraph undirGraph) {
            std::list<Vertex*> undirVertices = undirGraph.getVertexs();
            if(undirVertices.empty()){
                std::cout<<"Grafo nao direcionado esta vazio\n";
                return;
            }
            for(auto i : undirVertices){
                this->addVertex(i);
            }
        }

        void createEdges(){
            //addEdge();
        }

        void printEdges(){
          for(auto i:vertices){
            std::cout<< i->id << "\n  Sai   ";
            for(auto j: i->adj){
              std::cout<<"->"<<j->id<<"       ";
            }

            std::cout<<"\n  Chega   ";
            for(auto j:vertices){
                if(i->chega(j)){
                  std::cout<<"<-"<<j->id<<"        ";
                }
            }
            std::cout<<"\n";
          }
        }

        void topologicalOrder(){
            std::cout<<"Topological order\n";
            std::list<Vertex*> result;
            std::list<Vertex*> vertices_copy(vertices);
            while(!vertices_copy.empty()){
                bool resp = topologicalOrder_(vertices_copy, result);
                if(resp==false){
                    std::cout<<"Ha um ciclo\nEsse ciclo eh: ";
                    for(auto i: vertices_copy){
                        std::cout<<i->id<<" ";
                    }
                    std::cout<<std::endl;
                    return;
                }
            }

            for(auto i: result){
              std::cout<<i->id<<" ";
            }
            std::cout<<std::endl;

        }

        void dfs_(Vertex* v, std::list<Vertex*>& visited){
            visited.push_back(v);
            //std::cout<<v->id<<" - ";
            for(auto i: v->adj){
              if (std::find(visited.begin(),visited.end(),i)==visited.end()){
                  dfs_(i,visited);
              }
            }

        }

        std::list<Vertex*> dfs(unsigned int id){
            Vertex* v = findVertex(id);

            std::list<Vertex*> visited;

            //std::cout<<"\nDfs do "<<id<<std::endl;

            dfs_(v, visited);

           // std::cout<<"\n";

            return visited;
        }

        bool stronglyConnected(){
            for(auto i: vertices){
                std::list<Vertex*> dfsResult = dfs(i->id);
                if(dfsResult.size()!=this->amount){
                    std::cout<<"Grafo nao fortemente conectado\n";
                    return false;
                }
            }
            std::cout<<"Grafo fortemenete conectado\n";
            return true;

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

    std::cout<<"Grafo direcionado\n";
    DirectedGraph dirGraph(n);

    dirGraph.createEdges(undirGraph);
    dirGraph.printEdges();
    std::cout<<"\n\n\n";
    dirGraph.topologicalOrder();
    auto resp = dirGraph.stronglyConnected();
}
