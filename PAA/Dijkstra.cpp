#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<utility>
#include<climits>

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

        }

        void addVertex(Vertex* v){
            if(std::find(vertices.begin(),vertices.end(),v)!=vertices.end()){
                std::cout<<"Esse elemento ja existe"<<std::endl;
                return;
            }
            this->vertices.push_back(v);
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

	int minDist(std::vector<int> dist, std::list<Vertex*> spTree){
		int min = INT_MAX, min_index = -1;

		for(auto i: vertices){
			auto isInSpTree = std::find(spTree.begin(),spTree.end(),i);

			if(isInSpTree == spTree.end() && dist[i->id]<=min){
				min = dist[i->id];
				min_index = i->id;
			}
		}
		return min_index;	
				
	}


        void dijkstra(unsigned int id){
        	std::vector<int> dist(this->amount);
        	std::list<Vertex*> spTree;

		
		for(auto i = 0;i<this->amount;i++){
			dist[i] = INT_MAX;
		}
		
		dist[id] = 0;

		for(auto i: vertices){
			int u = minDist(dist,spTree);	
			if(u==-1) return;
			spTree.push_back(this->findVertex(u));


			for(auto j: findVertex(u)->edges){
				auto k = -1;	
				j->v1 == u ? k = j->v2 : k = j->v1;
				auto isInSpTree = std::find(spTree.begin(),spTree.end(),this->findVertex(k));
				if(isInSpTree == spTree.end() && dist[u]!=INT_MAX &&
				   dist[u] + j->price < dist[k])
					dist[k] = dist[u] + j->price;


			}

			
		}

		std::cout<<"\n\nDijkstra for vertex "<<id<<" \n";
		for(int i = 0;i<this->amount;i++){
			if(dist[i] != INT_MAX)	
				std::cout<<"Distance from node "<< id<<" to node "<<i<<" = "<<dist[i]<<"\n";
			else
				std::cout<<"There is no path from node "<< id<<" to node "<<i<<"\n";
		}
		  
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
	
    undirGraph.dijkstra(3);
    std::cout<<"\n";
}
