#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<utility>

template<class T, class U>
class Vertice{
    private:
        std::list<Vertice*> adj;
        unsigned int id;


    public:
        std::pair<T, U> ponto;
        Vertice(){}

        Vertice(unsigned int id, std::pair<T, U> ponto){
            this->id  = id;
            this->ponto = ponto;
        }

        inline unsigned int get_id(){ return id; }

        inline void set_id(unsigned int id){
            ///Restri��es?
            this->id = id;
        }

        void add_adj_vertice(Vertice<T,U>* adj_vertice){
            adj.push_back(adj_vertice);
        }

        void set_adj(std::list<Vertice<T,U>>* adj){
            this->adj = adj;
        }

        std::list<Vertice<T,U>*> get_adj_vertices(){
            return adj;
        }

        bool is_adj(Vertice<T,U>* v){
            if(std::find(adj.begin(),adj.end(),v)!=adj.end())
                return true;
            else
                return false;
        }

};



template<class T, class U>
class Graph{
    protected:
        std::list<Vertice<T,U>*> vertices;
        unsigned int amount = 0;

        bool is_bipartite_(std::list<Vertice<T,U>*> graph){
            std::map<Vertice<T,U>*,int> colors;
            for(auto i:  graph){
                colors[i] = -1;
            }

            Vertice<T,U>* v = graph.front();

            std::queue<Vertice<T,U>*> bfs_queue;

            bfs_queue.push(v);

            auto it = colors.find(v);
            if(it!=colors.end())
                it->second = 0;

            while(!bfs_queue.empty()){
                Vertice<T,U>* aux = bfs_queue.front();
                it = colors.find(aux);
                bfs_queue.pop();
                for (auto i : aux->get_adj_vertices()){
                    if(i==aux){
                      std::cout<<"\nNao eh bipartido\n";
                      return false;
                    }
                    auto it_aux = colors.find(i);
                    if(it_aux!=colors.end()){
                        if(it_aux->second == -1 ){
                            it_aux->second = 1 - it->second;
                            bfs_queue.push(i);
                        }else if(it_aux->second==it->second){
                            std::cout<<"\nNao eh bipartido\n";
                            return false;
                        }
                    }
                }

            }
            return true;

        }

    public:

        Graph(unsigned int amt ){ amount = amt;}

        int get_amt(){
            return amount;
        }

        //Refazer para difreente gráfos
        Vertice<T,U>* find_vertice(unsigned int id){
            for(auto i: vertices){
                if(i->get_id() == id)
                    return i;
            }

            return nullptr;
        }

        void add_vertice(unsigned int id, std::pair<T,U> ponto){
            for(auto i : this->vertices){
                if(i->get_id() == id){
                    std::cout<<"Esse elemento j� existe"<<std::endl;
                    return;
                }
            }



            Vertice<T,U>* v =  new Vertice<T,U>(id,ponto);

            this->vertices.push_back(v);
            this->amount++;
        }

        virtual void print_edges() = 0;

        virtual void create_edges() = 0;

        bool remove_vertice(unsigned int id){
            Vertice<T,U>* v = find_vertice(id);

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
            Vertice<T,U>* v1 = find_vertice(id1);
            Vertice<T,U>* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            if(v1->is_adj(v2)){
                return;
            }

            if(v1==v2){
                v1->add_adj_vertice(v2);
            }else{
                v1->add_adj_vertice(v2);
                v2->add_adj_vertice(v1);
            }
        }

        void remove_edges(Vertice<T,U>* v){
            for(auto i: vertices){
                std::list<Vertice<T,U>*> adj = i->get_adj_vertices();
                adj.remove(v);
                i->set_adj(adj);
            }
        }

        void remove_edge(unsigned int id1, unsigned int id2){
            Vertice<T,U>* v1 = find_vertice(id1);
            Vertice<T,U>* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            std::list<Vertice<T,U>*> v1_adj = v1->get_adj_vertices();
            for(auto i: v1_adj){
                if(i->get_id()==id2){
                    v1_adj.remove(v2);
                    return;
                }
            }

        }

        void print_vertices(){
            for(auto i: vertices){
                std::cout<<"Vertice de id = "<<i->get_id()<<std::endl;
            }
        }


        std::list<Vertice<T,U>*> bfs(unsigned int id){
            std::list<Vertice<T,U>*> result;
            Vertice<T,U>* v = find_vertice(id);

            std::list<Vertice<T,U>*> visited;

            std::queue<Vertice<T,U>*> bfs_queue;

            visited.push_back(v);
            bfs_queue.push(v);


            while(!bfs_queue.empty())
            {
                Vertice<T,U>* aux = bfs_queue.front();
                result.push_back(aux);
                bfs_queue.pop();

                for (auto i : aux->get_adj_vertices())
                {
                    if (std::find(visited.begin(),visited.end(),i)==visited.end())
                    {
                        visited.push_back(i);
                        bfs_queue.push(i);
                    }
                }
            }

            return result;
        }

        void dfs_(Vertice<T,U>* v, std::list<Vertice<T,U>*> visited){
            visited.push_back(v);
            std::cout<<v->get_id()<<" - ";
            for(auto i: v->get_adj_vertices()){
              if (std::find(visited.begin(),visited.end(),i)==visited.end()){
                  dfs_(i,visited);
              }
            }

        }

        std::list<Vertice<T,U>*> dfs(unsigned int id){
            Vertice<T,U>* v = find_vertice(id);

            std::list<Vertice<T,U>*> visited;

            std::cout<<"Dfs do "<<id<<std::endl;

            dfs_(v, visited);

            std::cout<<"\n";

            return visited;
        }

        //eficiencia = O(V+E)
        std::list<Vertice<T,U>*> connected(Vertice<T,U>* v){
            if(v==nullptr){
              return {};
            }
            std::list<Vertice<T,U>*> connected = bfs(v->get_id());
            return connected;
        }
        //eficiencia = O(G*(V+E+E))
        //G é a quantidade de caminhos
        std::list<std::list<Vertice<T,U>*>> allconnected(){
            std::list<std::list<Vertice<T,U>*>> paths = {};
            std::list<Vertice<T,U>*> aux = vertices;
            std::list<Vertice<T,U>*> seen = {};
            while(!aux.empty()){
              Vertice<T,U>* i = aux.front();
              seen = connected(i);
              for(auto j: seen){
                if(std::find(aux.begin(),aux.end(),j)!=aux.end()){
                    aux.remove(j);
                }
              }
              paths.push_back(connected(i));
            }

            return paths;

        }
        //eficiecia = O(G*(V+V+E))
        //G é a quantidade de caminhos
        bool is_bipartite(){
            std::list<std::list<Vertice<T,U>*>> graphs = allconnected();

            for(auto i: graphs){
                if(!is_bipartite_(i))
                    return false;

            }

            return true;
        }

};

template<class T, class U>
class Graph_G : public Graph<T,U>{
  private:


  public:

    Graph_G(unsigned int n) : Graph<T,U>(n){};

    void create_edges(){
        for(auto v1: this->vertices){
          for(auto v2: this->vertices){
              if(v1==v2 || v1->is_adj(v2))
                continue;

              if((v1->ponto.first==v2->ponto.first &&
                ((v1->ponto.second==v2->ponto.second+1) ||
                (v1->ponto.second==v2->ponto.second-1))) ||
                (v1->ponto.second==v2->ponto.second &&
                (v1->ponto.first==v2->ponto.first+1 ||
                v1->ponto.first==v2->ponto.first-1))){

                    this->add_edge(v1->get_id(), v2->get_id());
              }

          }
        }
    }

    void print_edges(){
        for(auto v: this->vertices){
            if(v == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }
            std::cout<<v->ponto.first<<","<<v->ponto.second<<" - > ";
            for(auto j: v->get_adj_vertices()){
                std::cout<<j->ponto.first<<","<<j->ponto.second<<" - > ";
            }
            std::cout<<"\n";
        }

    }


};

template<class T, class U>
class Graph_H : public Graph<T,U>{
  private:


  public:

    Graph_H(unsigned int n) : Graph<T,U>(n){};

    template<class V,class W>
    void add_vertice_(Graph_G<V,W> g){
        

        this->add_vertice(id,ponto);
    }

  void create_edges(){

  }

  void print_edges(){


  }


};

int main(){
    int n = 5;
    int aux = 0;
    Graph_G<int,int> graph(n);
    for(int i = 0; i<n;i++){
        for(int j = 0;j<5;j++){
            graph.add_vertice(aux, std::make_pair(i,j));
            aux++;
        }
    }

    graph.create_edges();

    //Graph h(n*n);



    graph.print_edges();

    //std::cout<<"\nBipartido "<<graph.is_bipartite()<<std::endl;

    //graph.dfs(3);

    /*std::cout<<"Bfs do 1\n";
    graph.print_list_vertices(graph.bfs(3));
    std::cout<<std::endl;*/
}
