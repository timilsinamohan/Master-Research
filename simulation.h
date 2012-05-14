#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <cstddef>

#define N 73
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
             int initial_node_status_from_user[initial_node_selection];	
	     
            cout<<"FILE READING !!"<<endl;
	    ifstream inFile_clickstream ("clickstream.txt", ios::in);
	    for(unsigned int i=0;i<5;i++)
	      
	    {
	      inFile_clickstream >> initial_node_status_from_user[i];
	      cout<< initial_node_status_from_user[i]<<endl;
	    }
	    inFile_clickstream.close();
	     
	    ifstream inFile_clickstream1("clickstream.txt", ios::in);
	    
	     string line ;
	     int line_of_files_receiver;
	    vector<string> lines ;
	    while( getline(inFile_clickstream1, line ) ) lines.push_back( line ) ;
	    line_of_files_receiver=lines.size();
	    cout<<"NUMBER OF LINES OF THE FILE:"<<line_of_files_receiver<<endl;  	      	
	    cout <<"VALUE OF RANDOM OUT DEGREE:"<<endl;
            
	    int a[lines.size()];
	    
	 
	

	    for(unsigned int i=0;i<lines.size();i++)
	    {
	      
	      
	    //  if(initial_node_status_from_user[i]>= 0 &&  initial_node_status_from_user[i]<=72)
	      //{
		a[i]=initial_node_status_from_user[i];
		
	       cout<<a[i]<<endl;
	      // first_simulation_matrix << status[0][initial_node_status_from_user[i]] << " ";
	      
	    
	     // }
	      //else
	      //{
	//	a[i]=-1;
		
	//      }
	     
	    }
	    
	    
	
	 // This code sets the first status of the status matrix
	 cout<<"YAHA DHYAN DINEE kasto print gardo rahicha:"<<endl;

	    

	      for(int j=0;j<N;j++)
	      {
		
		
		
		  
		  if(j==a[0] ||
		     j==a[1] ||
		     j==a[2] ||
		     j==a[3] ||
		     j==a[4] 
		  )
		  {
		  // cout<<j<<endl;
		   
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
	      
	    


	 

	      ofstream first_simulation_matrix;
	      first_simulation_matrix.open ("simulation1.txt");


	      for(int i=0;i<N;i++)
	      {
		for(int j=0;j<N;j++)
		{
		

		     
		   first_simulation_matrix << status[i][j] << " ";

		}
		
	      first_simulation_matrix<< endl;
	      }
	       first_simulation_matrix.close();



	    run_simulation();


	    }


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

		  if ( status[0][k] < 1 ) 
		  {
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


		       int node_number;
		       for(int j=0;j<N;j++)
		       {
			


			 //checking the infection status of the nodes
			  if(status[i][j] == 1 )
			     {
			      node_number= get_out_degree(j);
			      
			      if(node_number!=33 && node_number!=35)
			      {
			     // cout<<"NODE NUMBER:"<<j<<":"<<"OUT DEGREE PICKED:"<<get_out_degree(j)<<endl;


			      if (node_number >= 0 && node_number <= 72 ) // Yes it infected 
			      {
                              /*
			       cout<<"THIS IS YYYYY:"<<node_number<<endl;
			        cout << time[i][node_number]<< "<==>" << i<<"<==>" << node_number<<endl ;*/
			       // Time less than 5 just increase time by 1
			       // status = 1
				// File to read the infection period given by the user
				int infection_period;
				ifstream  inFile3 ("Infection_period.txt", ios::in);
				          inFile3>>infection_period;

			       if( time[i][node_number] < infection_period) 
			       {
				 time[i][node_number] += 1;
				// cout << time[i][node_number] << i << node_number<<endl ;


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
	       
	       //cout<<"lIST OF OUT DEGREE SEND FOR THE SELECTION:"<<out_deg<<endl;
		  ifstream  inFile2 ("transmission_probablity.txt", ios::in);
		  inFile2>>transmission_rate;

		//  cout<<"TRANSMISSION PROBABLITY FROM GUI:"<< transmission_rate<<endl;

	          file_read_graph_topology();
		  int counter=0;
		  int out_deg_store[N];

		 // cout<<"SELECTED NODE FROM STATUS:"<<out_deg<<endl;
		  for(int i=0;i<N;i++)
		  {
		    if(network_information[out_deg][i]==1)
		    {
		      out_deg_store[counter]=i;
		      counter++;
		    }


		  }
		  
		  

		  int random_out_degree_picker= rand() % counter;
		//  cout <<"WHICH NUMBER YOU PRINT LET ME SEE:"<<out_deg<<"==>"<<random_out_degree_picker<<endl;

		  double transmission_probablity =((double) rand() / (RAND_MAX+1))*-1 ;

		  // Reading the transmission_rate from the GUI 




		  if(transmission_probablity < transmission_rate && out_deg_store[random_out_degree_picker] <73)

		  {
		    /*
		    cout<<"THIS IS THE OUTDEGREE PICKED RANDOMLY:"<<out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"I AM INFECTING YOU : "<< out_deg <<"==>"<< out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"THIS IS THE PROBABILITY PICKED RANDOMLY:"<<transmission_probablity<<endl;
		     */ 
		    return out_deg_store[random_out_degree_picker];
 
		  }

		  else
		  {
		    /*
		    cout<<"You cannot be infected :"<<endl;
		    cout<<"THIS IS THE OUTDEGREE PICKED RANDOMLY:"<<out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"THIS IS THE PROBABILITY PICKED RANDOMLY:"<<transmission_probablity<<endl;*/

		  }


	    }
                       
            

  };
  #endif

                     





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
            
	    int a[5];
	    


	    for(int i=0;i<5;i++)
	    {
	      inFile_clickstream >> initial_node_status_from_user[i];
	      
	      if(initial_node_status_from_user[i]>= 0 &&  initial_node_status_from_user[i]<=72)
	      {
		a[i]=initial_node_status_from_user[i];
		
	       cout<<initial_node_status_from_user[i]<<endl;
	      // first_simulation_matrix << status[0][initial_node_status_from_user[i]] << " ";
	      
	    
	      }
	      else
	      {
		a[i]=73;
		
	      }
	     
	    }
	    
	
	 // This code sets the first status of the status matrix
	 cout<<"YAHA DHYAN DINEE:"<<endl;
	

	      for(int j=0;j<N;j++)
	      {
		
		
		
		  
		  if(j==a[0] ||
		     j==a[1] ||
		     j==a[2] ||
		     j==a[3] ||
		     j==a[4] 
		  )
		  {
		   cout<<j<<endl;
		   
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
	      
	    


	 

	      ofstream first_simulation_matrix;
	      first_simulation_matrix.open ("simulation1.txt");


	      for(int i=0;i<N;i++)
	      {
		for(int j=0;j<N;j++)
		{
		

		     
		   first_simulation_matrix << status[i][j] << " ";

		}
		
	      first_simulation_matrix<< endl;
	      }
	       first_simulation_matrix.close();



	    run_simulation();


	    }


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

		  if ( status[0][k] < 1 ) 
		  {
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


		       int node_number;
		       for(int j=0;j<N;j++)
		       {
			


			 //checking the infection status of the nodes
			  if(status[i][j] == 1 )
			     {
			      node_number= get_out_degree(j);
			      
			      if(node_number!=33)
			      {
			     // cout<<"NODE NUMBER:"<<j<<":"<<"OUT DEGREE PICKED:"<<get_out_degree(j)<<endl;


			      if (node_number >= 0 && node_number <= 72 ) // Yes it infected 
			      {
                              /*
			       cout<<"THIS IS YYYYY:"<<node_number<<endl;
			        cout << time[i][node_number]<< "<==>" << i<<"<==>" << node_number<<endl ;*/
			       // Time less than 5 just increase time by 1
			       // status = 1
				// File to read the infection period given by the user
				int infection_period;
				ifstream  inFile3 ("Infection_period.txt", ios::in);
				          inFile3>>infection_period;

			       if( time[i][node_number] < infection_period) 
			       {
				 time[i][node_number] += 1;
				// cout << time[i][node_number] << i << node_number<<endl ;


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
	       
	       //cout<<"lIST OF OUT DEGREE SEND FOR THE SELECTION:"<<out_deg<<endl;
		  ifstream  inFile2 ("transmission_probablity.txt", ios::in);
		  inFile2>>transmission_rate;

		//  cout<<"TRANSMISSION PROBABLITY FROM GUI:"<< transmission_rate<<endl;

	          file_read_graph_topology();
		  int counter=0;
		  int out_deg_store[N];

		 // cout<<"SELECTED NODE FROM STATUS:"<<out_deg<<endl;
		  for(int i=0;i<N;i++)
		  {
		    if(network_information[out_deg][i]==1)
		    {
		      out_deg_store[counter]=i;
		      counter++;
		    }


		  }
		  
		  

		  int random_out_degree_picker= rand() % counter;
		//  cout <<"WHICH NUMBER YOU PRINT LET ME SEE:"<<out_deg<<"==>"<<random_out_degree_picker<<endl;

		  double transmission_probablity =((double) rand() / (RAND_MAX+1))*-1 ;

		  // Reading the transmission_rate from the GUI 




		  if(transmission_probablity < transmission_rate && out_deg_store[random_out_degree_picker] <73)

		  {
		    /*
		    cout<<"THIS IS THE OUTDEGREE PICKED RANDOMLY:"<<out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"I AM INFECTING YOU : "<< out_deg <<"==>"<< out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"THIS IS THE PROBABILITY PICKED RANDOMLY:"<<transmission_probablity<<endl;
		     */ 
		    return out_deg_store[random_out_degree_picker];
 
		  }

		  else
		  {
		    /*
		    cout<<"You cannot be infected :"<<endl;
		    cout<<"THIS IS THE OUTDEGREE PICKED RANDOMLY:"<<out_deg_store[random_out_degree_picker]<<endl;
		    cout<<"THIS IS THE PROBABILITY PICKED RANDOMLY:"<<transmission_probablity<<endl;*/

		  }


	    }
                       
            

  };
  #endif

                     





