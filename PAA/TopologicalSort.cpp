#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<utility>

struct Vertice{

    std::list<Vertice*> chega, sai;
    unsigned int id;

    Vertice(){}

    Vertice(unsigned int id){
        this->id  = id;
    }


    bool if_chega(Vertice* v){
        if(std::find(chega.begin(),chega.end(),v)!=chega.end())
            return true;
        else
            return false;
    }

    bool if_sai(Vertice* v){
        if(std::find(sai.begin(),sai.end(),v)!=sai.end())
            return true;
        else
            return false;
    }

};




class Graph{
    protected:

        unsigned int amount = 0;

        std::list<Vertice*> vertices;

          /////
        bool topologicalOrder_(std::list<Vertice*>& vertices_copy,std::list<Vertice*>& result){
          for(auto i: vertices_copy){
            if(i->chega.empty()){
              result.push_back(i);
              vertices_copy.remove(i);
              for(auto j: vertices_copy){
                  j->chega.remove(i);
              }
              return true;
            }
          }
          return false;
        }
        /////

    public:
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
                    std::cout<<"Esse elemento j� existe"<<std::endl;
                    return;
                }
            }

            Vertice* v =  new Vertice(id);

            this->vertices.push_back(v);
            this->amount++;
        }

        void create_edges() {
          add_edge(5,2);
          add_edge(5,0);
          add_edge(4,0);
          add_edge(4,1);
          add_edge(2,3);
          add_edge(3,1);

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
        void add_edge(unsigned int id1, unsigned int id2){
            Vertice* v1 = find_vertice(id1);
            Vertice* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            if(v1->if_sai(v2)){
                return;
            }

            v1->sai.push_back(v2);
            v2->chega.push_back(v1);
        }

        void remove_edges(Vertice* v){
            for(auto i: vertices){
                i->sai.remove(v);
                i->chega.remove(v);
            }
        }

        void remove_edge(unsigned int id1, unsigned int id2){
            Vertice* v1 = find_vertice(id1);
            Vertice* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }
            if(v1->if_chega(v2)){
                v1->chega.remove(v2);
                v2->sai.remove(v1);
            }else if(v2->if_chega(v1)){
                v2->chega.remove(v1);
                v1->sai.remove(v2);
            }

        }
          //////
        void topologicalOrder(){
            std::cout<<"Topological order\n";
            std::list<Vertice*> result;
            std::list<Vertice*> vertices_copy(vertices);
            while(!vertices_copy.empty()){
                bool resp = topologicalOrder_(vertices_copy, result);
                if(resp==false){
                  std::cout<<"Ha um ciclo\n";
                  return;
                }
            }

            for(auto i: result){
              std::cout<<i->id<<" ";
            }
            std::cout<<std::endl;

        }
          //////
        void print_edges(){
          for(auto i:vertices){
            std::cout<< i->id << "\n  Sai   ";
            for(auto j: i->sai){
              std::cout<<"->"<<j->id<<"       ";
            }

            std::cout<<"\n  Chega   ";
            for(auto j: i->chega){
              std::cout<<"<-"<<j->id<<"        ";
            }
            std::cout<<"\n";
          }
        }



};




int main(){
    int n = 6;
    int aux = 0;
    Graph graph(n);
    for(int i = 0; i<n;i++){
      graph.add_vertice(i);
    }

    graph.create_edges();
    graph.print_edges();
    std::cout<<"\n\n";
    graph.topologicalOrder();
}
