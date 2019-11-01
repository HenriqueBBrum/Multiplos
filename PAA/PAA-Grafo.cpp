//Adicionar genericos

#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<utility>

class Vertice{
    private:
        std::list<Vertice*> adj;
        unsigned int id;


    public:
        std::pair<int, int> ponto;
        Vertice(){}

        Vertice(unsigned int id, std::pair<int, int> ponto){
            this->id  = id;
            this->ponto = ponto;
        }

        inline unsigned int get_id(){ return id; }

        inline void set_id(unsigned int id){
            ///Restri��es?
            this->id = id;
        }

        void add_adj_vertice(Vertice* adj_vertice){
            adj.push_back(adj_vertice);
        }

        void set_adj(std::list<Vertice*> adj){
            this->adj = adj;
        }

        std::list<Vertice*> get_adj_vertices(){
            return adj;
        }

        bool is_adj(Vertice* v){
            if(std::find(adj.begin(),adj.end(),v)!=adj.end())
                return true;
            else
                return false;
        }

};


class Graph{
    private:
        std::list<Vertice*> vertices;
        unsigned int amount = 0;

        bool is_bipartite_(std::list<Vertice*> graph){
            std::map<Vertice*,int> colors;
            for(auto i:  graph){
                colors[i] = -1;
            }

            Vertice* v = graph.front();

            std::queue<Vertice*> bfs_queue;

            bfs_queue.push(v);

            auto it = colors.find(v);
            if(it!=colors.end())
                it->second = 0;

            while(!bfs_queue.empty()){
                Vertice* aux = bfs_queue.front();
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

        Vertice* find_vertice(unsigned int id){
            for(auto i: vertices){
                if(i->get_id() == id)
                    return i;
            }

            return nullptr;
        }

        void add_vertice(unsigned int id, std::pair<int,int> ponto){
            for(auto i : vertices){
                if(i->get_id() == id){
                    std::cout<<"Esse elemento j� existe"<<std::endl;
                    return;
                }
            }



            Vertice* v =  new Vertice(id, ponto);

            vertices.push_back(v);
            amount++;
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

        void remove_edges(Vertice* v){
            for(auto i: vertices){
                std::list<Vertice*> adj = i->get_adj_vertices();
                adj.remove(v);
                i->set_adj(adj);
            }
        }

        void remove_edge(unsigned int id1, unsigned int id2){
            Vertice* v1 = find_vertice(id1);
            Vertice* v2 = find_vertice(id2);

            if(v1 == nullptr || v2 == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            std::list<Vertice*> v1_adj = v1->get_adj_vertices();
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

        void print_edges(){
            for(auto v: vertices){
                if(v == nullptr){
                    std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                    return;
                }
                std::cout<<std::get<0>(v->ponto)<<","<<std::get<1>(v->ponto)<<" - > ";
                for(auto j: v->get_adj_vertices()){
                    std::cout<<std::get<0>(j->ponto)<<","<<std::get<1>(j->ponto)<<" - > ";
                }
                std::cout<<"\n";
            }

        }

        void create_edges(){
            for(auto v1: vertices){
              for(auto v2: vertices){
                  if(v1==v2 || v1->is_adj(v2))
                    continue;

                  if((std::get<0>(v1->ponto)==std::get<0>(v2->ponto) &&
                    ((std::get<1>(v1->ponto)==std::get<1>(v2->ponto)+1) ||
                    (std::get<1>(v1->ponto)==std::get<1>(v2->ponto)-1))) ||
                    (std::get<1>(v1->ponto)==std::get<1>(v2->ponto) &&
                    (std::get<0>(v1->ponto)==std::get<0>(v2->ponto)+1 ||
                    std::get<0>(v1->ponto)==std::get<0>(v2->ponto)-1))){

                        add_edge(v1->get_id(), v2->get_id());
                  }

              }
            }
        }

        std::list<Vertice*> bfs(unsigned int id){
            std::list<Vertice*> result;
            Vertice* v = find_vertice(id);

            std::list<Vertice*> visited;

            std::queue<Vertice*> bfs_queue;

            visited.push_back(v);
            bfs_queue.push(v);


            while(!bfs_queue.empty())
            {
                Vertice* aux = bfs_queue.front();
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

        void dfs_(Vertice* v, std::list<Vertice*> visited){
            visited.push_back(v);
            std::cout<<v->get_id()<<" - ";
            for(auto i: v->get_adj_vertices()){
              if (std::find(visited.begin(),visited.end(),i)==visited.end()){
                  dfs_(i,visited);
              }
            }

        }

        std::list<Vertice*> dfs(unsigned int id){
            Vertice* v = find_vertice(id);

            std::list<Vertice*> visited;

            std::cout<<"Dfs do "<<id<<std::endl;

            dfs_(v, visited);

            std::cout<<"\n";

            return visited;
        }

        //eficiencia = O(V+E)
        std::list<Vertice*> connected(Vertice* v){
            if(v==nullptr){
              return {};
            }
            std::list<Vertice*> connected = bfs(v->get_id());
            return connected;
        }
        //eficiencia = O(G*(V+E+E))
        //G é a quantidade de caminhos
        std::list<std::list<Vertice*>> allconnected(){
            std::list<std::list<Vertice*>> paths = {};
            std::list<Vertice*> aux = vertices;
            std::list<Vertice*> seen = {};
            while(!aux.empty()){
              Vertice* i = aux.front();
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
            std::list<std::list<Vertice*>> graphs = allconnected();

            for(auto i: graphs){
                if(!is_bipartite_(i))
                    return false;

            }

            return true;
        }

        void print_list_vertices(std::list<Vertice*> l){
            for(auto i: l){
                std::cout<<std::get<0>(i->ponto)<<","<<std::get<1>(i->ponto)<<"  ";
            }
        }

};



int main(){
    int n = 5;
    int aux = 0;
    Graph graph(n);
    for(int i = 0; i<n;i++){
        for(int j = 0;j<5;j++){
            graph.add_vertice(aux, std::make_pair(i,j));
            aux++;
        }
    }

    graph.create_edges();

    Graph h(n*n);



    //graph.print_edges();/*

    //std::cout<<"\nBipartido "<<graph.is_bipartite()<<std::endl;

    //graph.dfs(3);

    std::cout<<"Bfs do 1\n";
    graph.print_list_vertices(graph.bfs(3));
    std::cout<<std::endl;
}
