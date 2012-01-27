#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <iomanip>
#include <unistd.h>
#include <time.h>
#include <fstream>
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


#ifndef stochastic_matrix_H
#define stochsatic_matrix_H
using namespace std;

class stochastic_matrix
{

public:

  void calculate_stochastic_matrix()
  {
   double ii=0;  
   const char *inname = "graph_topology.txt";
   double points[73][73];

  ifstream infile(inname);  
    double adjacency_storage[5329];
    int cnt=0,counter=0;  
    cout << "Adjacency: " << inname << " for reading." << endl;
    
  
    while (infile >> ii) 
    {
	adjacency_storage[cnt++]=ii;
 
    }
  
     for(int i=0;i<73;i++){
     for(int j=0;j<73;j++){
	points[i][j]=adjacency_storage[counter];
	counter++;
	
		}
		
     }
	//computation of the stochastic_matrix
	 const char *inname1 = "out_degree.txt";
	 double jj=0;  
	// double degree_points[73];
	 ifstream infile1(inname1);
	 double degree_storage[73];
	 int cnt1=0; 
	 
	   while (infile1 >> jj) 
	{
	 degree_storage[cnt1++]=jj;
 
	}
	 
	 
	cout<<"stochastic_matrix"<<endl;
	
  ofstream stm;
  stm .open ("stochastic_matrix.txt");
  
  cout.precision(2);
  stm.precision(2);
   for(int i=0;i<73;i++){
     for(int j=0;j<73;j++){
       cout<<fixed<<points[i][j]/degree_storage[i]<<" ";
       stm<<fixed<<points[i][j]/degree_storage[i]<<" ";
     }
     cout<<endl;
     stm<<endl;
   }
   
   stm.close();
      
  }
  
  
};
#endif
