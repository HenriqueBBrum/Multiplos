#include<iostream>
#include<list>
#include<algorithm>
#include<queue>



class Vertice{
    private:
        std::list<Vertice*> adj;
        unsigned int id;

    public:
        Vertice(){}

        Vertice(unsigned int id){
            this->id  = id;
        }

        inline unsigned int get_id(){ return id; }

        inline void set_id(unsigned int id){
            ///Restrições?
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

};


class Graph{
    private:
        std::list<Vertice*> vertices;
        unsigned int amount = 0;
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

        void add_vertice(unsigned int id){
            for(auto i : vertices){
                if(i->get_id() == id){
                    std::cout<<"Esse elemento já existe"<<std::endl;
                    return;
                }
            }

            Vertice* v =  new Vertice(id);

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

            v1->add_adj_vertice(v2);
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

        void print_edges(unsigned int id){
            Vertice* v = find_vertice(id);
            if(v == nullptr){
                std::cout<<"Nao foi possivel achar os vertices requesitados"<<std::endl;
                return;
            }

            for(auto i: v->get_adj_vertices()){
                std::cout<<i->get_id()<<", ";
            }
            std::cout<<"\n";
        }

        void create_edges(){
            add_edge(0,1);
            add_edge(0,2);
            add_edge(1,2);
            add_edge(2,0);
            add_edge(2,3);
            add_edge(3,3);
        }

        void bfs(unsigned int id){
            Vertice* v = find_vertice(id);

            std::vector<bool> visited(amount,0);

            std::queue<Vertice*> bfs_queue;

            visited[id] = true;
            bfs_queue.push(v);


            while(!bfs_queue.empty())
            {
                Vertice* aux = bfs_queue.front();
                std::cout << aux->get_id() << " ";
                bfs_queue.pop();

                for (auto i : v->get_adj_vertices())
                {
                    if (!visited[i->get_id()])
                    {
                        visited[i->get_id()] = true;
                        bfs_queue.push(i);
                    }
                }
            }
        }


};

int main(){
    int n = 5;
    Graph graph(n);
    for(int i = 0; i<n;i++){
        graph.add_vertice(i);
    }
    graph.print_vertices();
    graph.create_edges();
    for(int i = 0; i<n;i++){
        std::cout<<"Adj do vertice "<<i<<" -> ";
        graph.print_edges(i);
    }
    std::cout<<"Bfs: \n";
    graph.bfs(2);



}
