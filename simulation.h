#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#define N 73
//#define transmission_rate 0.7
#define n 73
#define initial_node_selection 5
#ifndef simulation_H
#define simulation_H
int timestamp;
int xx;
float transmission_rate;


 


using namespace std;



  class simulation 
  {
     public:
         int network_information[N][N];                 
	 int status[n][N]; 
	 int time[n][N]; 
	 

	
	 
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
	    file_read_graph_topology();
	   cout << "GREAT CALLED ME !!" <<endl;
	    int counter_for_visualize_button;   
	     ifstream inFile_visualize ("visualize_button.txt", ios::in);
	     inFile_visualize >> counter_for_visualize_button;
	     
	 
	    ifstream inFile_clickstream ("clickstream.txt", ios::in);
	   
	    int initial_node_status_from_user[initial_node_selection];
	    
	    cout <<"VALUE OF RANDOM OUT DEGREE:"<<endl;
	    
	    
	    
	    for(int i=0;i<5;i++)
	    {
	      inFile_clickstream >> initial_node_status_from_user[i];
	    		
	    }
	    
	
	        if((initial_node_status_from_user[2]<0) || (initial_node_status_from_user[2]>72))
		{
		  
		  (initial_node_status_from_user[2]=0);
		}
		  
		if((initial_node_status_from_user[3]<0) || (initial_node_status_from_user[3]>72))
		{
		  
		  (initial_node_status_from_user[3]=0);
		}
		  
		if((initial_node_status_from_user[4]<0) || (initial_node_status_from_user[4]>72))
		{
		  
		  (initial_node_status_from_user[4]=0);
		}
		
	 // This code sets the first status of the status matrix
	   
	      for(int j=0;j<N;j++)
	      {
		
		  if(j==initial_node_status_from_user[0] ||
		     j==initial_node_status_from_user[1] ||
		     j==initial_node_status_from_user[2] ||
		     j==initial_node_status_from_user[3] ||
		     j==initial_node_status_from_user[4] 
		  )
		  {
		    status[0][j]=1;
		    time[0][j]=1;
		   
		    
		  }
		  
		  else 
		    
		  status[0][j]=0;
		  
		}
		
		
		for(int i=1;i<N;i++)
		{
		  for(int j=0;j<N;j++)
		  {
		  
		  status[i][j]=0;
		  }
		  
		
		
	      }
	      
	
	    
	     // cout <<"Matrix of the first status of nodes:"<<endl;
	      
	       ofstream first_simulation_matrix;
	       first_simulation_matrix.open ("simulation1.txt");
	       
	      
	      for(int i=0;i<N;i++)
	      {
		for(int j=0;j<N;j++)
		{
		  if (status[0][0]==1)
		  {
		    status[0][0]=0;
		  }
		  
		    first_simulation_matrix << status[i][j] << " ";
		  
		 // cout<<status[i][j] <<" ";
		}
		//cout<<endl;
		first_simulation_matrix<< endl;
	      }
	       first_simulation_matrix.close();
	      
	    
	    
	    run_simulation();
	  
	      
	    }
	    
	 /*
	   void update_status_table1(int states)
	    {  
	      
	      fstream filestr;x
       	      filestr.open ("simulation.txt", fstream::in | fstream::out | fstream::app);
	 
	      for(int i=0;i<N;i++)
	      {
		 // cout<<status[states-1][i]<<endl;
	      filestr<<status[states][i]<< " ";      
	      }
	      filestr<<endl;
	      filestr.close();
	      }
	      */
	      
	      
	      
	      
	      
	     void run_simulation()
	     {
	       
	       //update_status_table();
	    
	     
		   
		   // storing the status of simulation 1 (initial simulation state to compute future simulation state)
		   
		   ifstream inFile1 ("simulation1.txt", ios::in);
		   ofstream outfile("simulation.txt",ios::out);
		   ofstream outfile2("infection_time.txt",ios::out);
	
		  for(int i=0;i<N;i++)
		  {
		    for(int j=0;j<n;j++)
		    {
		      inFile1>>status[i][j];  
					    
		    }
		  }
		  
		  for(int i=0;i<N;i++)
		  {
		    outfile<<status[0][i]<<" ";
		    		    
		    
		  }
		  outfile<<endl;
		  
		
	       
	        file_read_graph_topology();
              
            
            for(int k=0;k<N;k++)
		{
		  
		  if ( status[0][k] < 1 ) {
		     status[0][k] = 0;
		     time[0][k] = 0;
		  }		
		}
		                                        
             
		    for(int i=1;i<N;i++)
		    {
		      
		      
		       for(int k=0;k<N;k++)
			{
				  status[i][k] = status[i-1][k];
				  time[i][k] = time[i-1][k];

			}
		      
		      
		      
		       for(int j=0;j<N;j++)
		       {
			 int node_number;
			 
			
			 //checking the infection status of the nodes
			  if(status[i][j] == 1 )
			     {
			      node_number= get_out_degree(j);
			      

			      if (node_number >= 0 && node_number <= 72 ) // Yes it infected 
			      {
			      
			       cout<<"THIS IS YYYYY:"<<node_number<<endl;
			        cout << time[i][node_number]<< "<==>" << i<<"<==>" << node_number<<endl ;
			       // Time less than 5 just increase time by 1
			       // status = 1
				// File to read the infection period given by the user
				int infection_period;
				ifstream  inFile3 ("Infection_period.txt", ios::in);
				          inFile3>>infection_period;
				
			       if( time[i][node_number] < infection_period) 
			       {
				 time[i][node_number] += 1;
				 cout << time[i][node_number] << i << node_number<<endl ;
				 
				 
				 status[i][node_number]  = 1;
			       }
			       else // Time = 5 -> change status = 2;
			       {
		  
				  status[i][node_number] = 2;
		
			       }
			 
			      }
        
			     }
                               
			}
			     
		  
			 
		}
			
			
		for(int i=0;i<N;i++)
		{
			  for(int j=0;j<N;j++)
			{
			  
		         outfile<<status[i][j]<<" ";
			 outfile2<<time[i][j]<<" ";
			}
			
		  outfile<<endl;
		  outfile2<<endl;
		
		  }
             
   
	       
	     }
	     
	     
	     
	     
	     
	    int get_out_degree(int out_deg)
	     {
		  ifstream  inFile2 ("transmission_probablity.txt", ios::in);
		  inFile2>>transmission_rate;
		  
		  cout<<"TRANSMISSION PROBABLITY FROM GUI:"<< transmission_rate<<endl;
		  
	          file_read_graph_topology();
		  int counter=0;
		  int out_deg_store[N];
		  
		  cout<<"SELECTED NODE FROM STATUS:"<<out_deg<<endl;
		  for(int i=0;i<N;i++)
		  {
		    if(network_information[out_deg][i]==1)
		    {
		      out_deg_store[counter]=i;
		      counter++;
		    }
	
		    
		  }
		  
		  int random_out_degree_picker= rand() % counter;
		 
		  double transmission_probablity =((double) rand() / (RAND_MAX+1))*-1 ;
		  
		  // Reading the transmission_rate from the GUI 
		  
	
		  
		  
		  if(transmission_probablity < transmission_rate && out_deg_store[random_out_degree_picker] <73)
		    
		  {
		    cout<<"THIS IS THE OUTDEGREE PICKED RANDOMLY:"<<out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"I AM INFECTING YOU : "<< out_deg <<"==>"<< out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"THIS IS THE PROBABILITY PICKED RANDOMLY:"<<transmission_probablity<<endl;
		  
		    return out_deg_store[random_out_degree_picker];
 
		  }
		  
		  else
		  {
		    cout<<"You cannot be infected :"<<endl;
		    cout<<"THIS IS THE OUTDEGREE PICKED RANDOMLY:"<<out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"THIS IS THE PROBABILITY PICKED RANDOMLY:"<<transmission_probablity<<endl;
		    
		  }
		
	       
	    }
                       
            

  };
  #endif

                     

	  
	  
	  
	  
	  