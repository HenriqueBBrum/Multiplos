#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<utility>

struct Vertice{
    ///Adj são os vertices que saem do nodo caso seja direcionado
    ///ou é a as arestas caso sem direção
    std::list<Vertice*> adj;
    unsigned int id;

    Vertice(){}

    Vertice(unsigned int id){
        this->id  = id;
    }

    ///v -> this vertice
    bool chega(Vertice* v){
        if(std::find(v->adj.begin(),v->adj.end(),this)!=v->adj.end())
            return true;
        else
            return false;
    }

    ///This vertice -> v or (This vertice -> v && This vertice <- v)
    bool sai(Vertice* v){
        if(std::find(adj.begin(),adj.end(),v)!=adj.end())
            return true;
        else
            return false;
    }



};


class Graph{
    protected:

        unsigned int amount = 0;

        std::list<Vertice*> vertices;

        void remove_edges(Vertice* v){
            for(auto i: vertices){
                i->adj.remove(v);
            }
            v->adj.clear();
        }

    public:

        std::list<Vertice*> get_vertices(){ return vertices; }

        Graph(unsigned int amt ){ amount = amt;}

        int get_amt(){
            return amount;
        }

        Vertice* find_vertice(unsigned int id){
            for(auto i: vertices){
                if(i->id == id)
                    return i;
            }

            return nullptr;
        }

        void add_vertice(unsigned int id){
            for(auto i : this->vertices){
                if(i->id == id){
                    std::cout<<"Esse elemento ja existe"<<std::endl;
                    return;
                }
            }

            Vertice* v =  new Vertice(id);

            this->vertices.push_back(v);
            this->amount++;
        }

        void add_vertice(Vertice* v){
            if(std::find(vertices.begin(),vertices.end(),v)!=vertices.end()){
                std::cout<<"Esse elemento ja existe"<<std::endl;
                return;
            }
            this->vertices.push_back(v);
            this->amount++;
        }

        bool remove_vertice(unsigned int id){
            Vertice* v = find_vertice(id);

            if(v!=nullptr){
                remove_edges(v);
                vertices.remove(v);
                free(v);
                amount--;
                return true;
            }
            return false;
        }

        ///Add edge from id1 to id2
        virtual void add_edge(unsigned int id1, unsigned int id2) = 0;

        virtual void remove_edge(unsigned int id1, unsigned int id2) = 0;

        virtual void print_edges()= 0 ;

};

class UndirectedGraph: public Graph{

    public:

        UndirectedGraph(unsigned int amt):Graph(amt){}

        void add_edge(unsigned int id1, unsigned int id2){
            Vertice* v1 = find_vertice(id1);
            Vertice* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                return;
            }

            v1->adj.push_back(v2);
            v2->adj.push_back(v1);
        }

        void remove_edge(unsigned int id1, unsigned int id2){
            Vertice* v1 = find_vertice(id1);
            Vertice* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                v1->adj.remove(v2);
                v2->adj.remove(v1);
            }

        }

        void create_edges() {
          add_edge(0,1);
          add_edge(0,2);
          add_edge(2,3);
          add_edge(3,1);
          add_edge(3,5);
          add_edge(5,4);

        }

        void print_edges(){
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
        bool topologicalOrder_(std::list<Vertice*>& vertices_copy,std::list<Vertice*>& result){
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
        void add_edge(unsigned int id1, unsigned int id2){
            Vertice* v1 = find_vertice(id1);
            Vertice* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            if(v1->sai(v2)){
                return;
            }

            v1->adj.push_back(v2);
        }
        ///Remove edge from id1 to id2
        void remove_edge(unsigned int id1, unsigned int id2){
            Vertice* v1 = find_vertice(id1);
            Vertice* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            if(v1->chega(v2)){
               v2->adj.remove(v1);
            }

            if(v1->sai(v2)){
                v1->adj.remove(v2);
            }

        }

        void create_edges(UndirectedGraph undirGraph) {
            std::list<Vertice*> undirVertices = undirGraph.get_vertices();
            if(undirVertices.empty()){
                std::cout<<"Grafo nao direcionado esta vazio\n";
                return;
            }
            for(auto i : undirVertices){
                this->add_vertice(i);
            }

        }

        void print_edges(){
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
            std::list<Vertice*> result;
            std::list<Vertice*> vertices_copy(vertices);
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
};


int main(){
    int n = 6;
    int aux = 0;
    std::cout<<"Grafo nao direcionado\n";
    UndirectedGraph undirGraph(n);
    for(int i = 0; i<n;i++){
        undirGraph.add_vertice(i);
    }

    undirGraph.create_edges();
    undirGraph.print_edges();
    std::cout<<"\n\n";

    std::cout<<"Grafo direcionado\n";
    DirectedGraph dirGraph(n);

    dirGraph.create_edges(undirGraph);
    dirGraph.print_edges();
    std::cout<<"\n\n\n";
    dirGraph.topologicalOrder();
}
