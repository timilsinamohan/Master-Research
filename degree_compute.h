#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include<fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdlib> 
#include <string>
#include <boost/config.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp> 
#include <vector>
#include <boost/graph/properties.hpp>
#define N 73

#ifndef degree_compute_H
#define degree_compute_H

using namespace std;
using namespace boost;

int total_degree_information[73];
int out_degree_computation[73];

class degree_compute{
  
  
public:
  void degree_calculate()
  
   {
    
      typedef adjacency_list<vecS, vecS,undirectedS, 
      property<vertex_degree_t,int> > Graph1;
      typedef adjacency_list<vecS, vecS,directedS, 
      property<vertex_degree_t,int> > Graph;
      typedef graph_traits<Graph>::vertex_descriptor Vertex;
      typedef graph_traits<Graph>::vertices_size_type size_type;
      typedef std::pair<std::size_t, std::size_t> Pair; 
      typedef graph_traits<Graph1>::vertex_descriptor Vertex;
      typedef graph_traits<Graph1>::vertices_size_type size_type;
      
      //codes to read the line of the file
      ifstream file1( "graph_topology.txt" ) ;
      string line ;
      vector<string> lines ;
      while( getline( file1, line ) ) lines.push_back( line ) ;
    //  cout << "graph_topology: " << lines.size()<< '\n' ;
      Graph g(lines.size());
      Graph1 g1(lines.size());
      
	  
	    // Nodes of the graph
	  
	 int node[lines.size()];
      
	for (unsigned int i=0;i<lines.size();i++)
	{
	  node[i]=i; //storing the information of the nodes
	}
	    
	 ifstream file("graph_topology.txt", ios::in);

	 int a[N][N];
	 
	  
	  for(unsigned int i=0; i < N; i++)// col. number
	  {
	      for(unsigned int j=0; j< N; j++)// rows number
	      {
		  file >> a[i][j];
	    
	      }
	      
	  }
	  
	  
  int degree_in[lines.size()];
    for(unsigned int i=0;i<lines.size();i++){
      for(unsigned int j=0;j<lines.size();j++){
	if (a[i][j]==1)
	{
	    add_edge(i,j,g);
	    add_edge(i,j,g1);
	}
      }
    }
    graph_traits<Graph>::vertex_iterator ui, ui_end;
    property_map<Graph,vertex_degree_t>::type deg = get(vertex_degree, g);
  //  cout<<"Out Degree calculation.............................."<<endl;
    
 
   
      
    
      for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ui++){
	out_degree_computation[*ui]=out_degree(*ui, g); 
	deg[*ui] = out_degree(*ui, g); 
	cout<<deg[*ui]<<endl;
	
      }
      
  ofstream degreefile;
  degreefile .open ("out_degree.txt");
  for(int i=0;i<73;i++)
  {
  degreefile << deg[i]<<endl;
  }
  degreefile.close();
      
      
      
      
      
      
      
      
      
      
      
	   
  //  cout<<"Total Degree calculation.............................."<<endl;  
    graph_traits<Graph1>::vertex_iterator ui1, ui1_end;
    property_map<Graph1,vertex_degree_t>::type deg1 = get(vertex_degree, g1);
    int degree_counter=0;
    for (boost::tie(ui1, ui1_end) = vertices(g1); ui1 != ui1_end; ui1++){
    deg1[*ui1]=degree(*ui1, g1);
   // cout<<deg1[*ui1]<<endl;
   //Here we will get the total degree of the each nodes
   total_degree_information[degree_counter]= deg1[*ui1];
   degree_counter++;
   // return deg1[*ui];
    }
  // cout<<"indegree calculation................"<<endl;
  for(unsigned int i=0;i<lines.size();i++)
  {
    degree_in[i]=deg1[i]-deg[i];
   // cout<<degree_in[i]<<endl;  
  }
/*
  std::cout << "vertex set: ";
  print_vertices(g, node);
  std::cout << std::endl;

  std::cout << "edge set: ";
  print_edges(g, node);
  std::cout << std::endl;
  
  std::cout << "incident edges: " << std::endl;
  print_graph(g, node);
  std::cout << std::endl;

 */
 std::cout << "incident edges: " << std::endl;
  print_graph(g, node);
  std::cout << std::endl;


// Here is the calculation of the stochastic matrix of the adjacency matrix
	/*    
       for(int i=0;i<73;i++){
       for(int j=0;i<73;j++){
	points[i][j]= points[i][j]/deg[j];
	
	 
      }
    }  
*/	    
	    
    }
    
  void total_degree(){
   
  degree_calculate(); 
  ofstream myfile;
  myfile.open ("total_degree.txt");
  for(int i=0;i<N;i++)
  {
  myfile << total_degree_information[i]<<endl;
  }
  myfile.close();
  
  
 
    
  }
    
};
#endif