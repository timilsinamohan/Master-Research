#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define N 73
#define transmission_rate 0.3
#define n 35
#ifndef simulation_H
#define simulation_H
int timestamp;


using namespace std;

  

  class simulation 
  {
     public:
         int network_information[N][N];                 
	 int status[n][N]; 
	 int random_out_degree_picker; 
	 
	   void file_read_graph_topology()
	  {
		ifstream inFile ("graph_topology.txt", ios::in);

		for(int i=0;i<N;i++)
		{
		  for(int j=0;j<N;j++)
		    {
		      inFile >> network_information[i][j];
		    }
		}

	  }
	  
	   void update_status_table()
	  {
	    
	      for(int i=0;i<n;i++)
		{
		  for(int j=0;j<N;j++)
		    {
		    status[i][j]=0;
		    }
	    
		}   
	  }
	  
	  
	   void update_status_table1(int states)
	    {  
	      fstream filestr;

	      filestr.open ("simulation.txt", fstream::in | fstream::out | fstream::app);
	    
	    
	      cout<<"STATUS AT EVERY TIME STAMP:"<<timestamp<<endl; 
	      //filestr <<states <<" : "<<endl;
	      for(int i=0;i<N;i++)
	      {
		  cout<<status[states-1][i]<<endl;
		  filestr<<status[states-1][i]<< " ";      
	      }
	      filestr<<endl;
	      filestr.close();
	      }
	      
	     void run_simulation()
	     {
	       
	        file_read_graph_topology();
               // int i,j;
                srand((unsigned)time(0)); 
                timestamp=1;
                double probablity_checker;
                int counter_time=n;
                
                update_status_table();
                cout<<"counter:"<<counter_time<<endl;
              
                                                     
                 while (counter_time>0)
                 
		  {
                          random_out_degree_picker = (rand()%N)+1; 
                          
                            for(int j=0;j<N;j++)
                             {
                                                                                               
                              if(network_information[random_out_degree_picker][j]==1)
                                 {
                                
                                     probablity_checker=((double) rand() / (RAND_MAX+1))*-1 ;
                                          
                                 if( probablity_checker < transmission_rate) 
                                 {
                                      cout<<random_out_degree_picker<<","<<j<<","<< probablity_checker<<endl;
                                      
                                    //status[timestamp][j]=status[timestamp-1][j]+1;
                                    
                                    if(timestamp>1 && 1 + status[timestamp-2][j]>=2)
				    {
                                     status[timestamp-1][j]=2;
                                        //status[timestamp-1][j] = 1 + status[timestamp-2][j];
                                    }
                                    
                                    else
				    {
                                        status[timestamp-1][j] = 1;
                                    }
                                    
                                 } 
                                 
                                 else
				 {
                                    status[timestamp-1][j] = status[timestamp-2][j];
                                 }
                                
                                                                                                                                                                                        
                                
                                 
           
                
              } 
                  else
                      {
                       status[timestamp-1][j] = status[timestamp-2][j];
		      }
            
                  
                
             }   
                       
                      
               
 
                   
                
               update_status_table1(timestamp);
                  --counter_time;
               timestamp=timestamp+1; 
                }

	       
	    }
  };
  #endif

                     

	  
	  
	  
	  
	  