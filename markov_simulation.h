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
#ifndef markov_simulation_H
#define markov_simulation_H
#define N 72
#define STEPS 17
float a[N][N];
float allResult[N][N];
bool computed[STEPS];
using namespace std;

class markov_simulation
{
  public:
    
 void file_read()
 {
  ifstream inFile ("stochastic_matrix.txt", ios::in);

  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++)
      {
	inFile >> a[i][j];
      }
  }

  }
  
  void multiplyMatrix( float a[][N], float x[], float res[] )
  {
    bool bDebug = false;
    if( bDebug )
      {
        cout << "Matrix a:" << endl;
        for( int i = 0; i < N; i++ )
        {
            for( int j = 0; j < N; j++ )
            {
                cout << a[i][j] << "\t";    
            }
            cout << endl;            
        }
        cout << "Matrix x:" << endl;
        for( int i = 0; i < N; i++ )
            cout << x[i] << "\t";    
            cout << endl;            
      }   
    
        for( int i = 0; i < N; i++ )
        {
            for( int j = 0; j < N; j++ )
            {
                    res[i] += x[j]*a[j][i];
            }
        }
}

void computeAllX()
{

    // Initialization 
    for( int i = 0; i < N; i++ ) 
    {  
     
    
        computed[i] = false;
        for( int j = 0; j < N; j++ )
        {
        
            allResult[i][j] = 0.0f;
           
        }
        
    }
    cout<<"Here am I :"<<endl;
  
    
    allResult[0] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }; 
 
    computed[0] = true;
    int i = 1;
    float prevResult[N];
    cout << "STEPS to compute = " << STEPS << endl;
    while( i < STEPS )
    {
        cout << endl << "Computing for step = " << (i+1) << endl;
        if( computed[ i-1 ] )
        { 
            for( int m = 0; m < N; m++ )
            {
                prevResult[m] = allResult[i-1][m];
            }
            multiplyMatrix( a, prevResult, allResult[i] );
            computed[i] = true;
            i++;
        }
        else
        {
                cerr << "This should not happen" << endl;
        }
        for( int j = 0; j < N; j++ )
        {
            cout << allResult[i-1][j] << "\t";
        }
        cout << endl;
     }
     
     // Check result
     cout << "Final result :" << endl;
     for( int i = 0; i < STEPS; i++ )
     {
        cout << "Step " << (i+1) << ": ";
        for( int j = 0; j < N; j++ )
        {
            cout << allResult[i][j] << "\t";
        }
        cout << endl;
     }
}

void simulation_caller()
  {
	    file_read();
             
             computeAllX();
             
             int iStep = 9;
	     ofstream timestep;
	     timestep .open ("simulation.txt");
             cout << endl;
             cout << "Accessing for step = " << iStep << endl;
             for( int j = 0; j < N; j++ )
             {
                cout << allResult[iStep-1][j] << "\t";
		timestep << allResult[iStep-1][j]<<endl;
             }
             cout << endl;
  
  }
    
    
    
    
    };
#endif
