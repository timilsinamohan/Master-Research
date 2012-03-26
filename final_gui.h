#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
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
#include <boost/graph/betweenness_centrality.hpp>
#include "simulation.h"
#define N 73
#ifndef final_gui_H
#define final_gui_H
double network_point_storage[N][N];
int points[N][2];
int click[5];
int countf=0;
static gint counter_for_visualize_button=0;
simulation sim;
int time_stamp_from_gui;

double coordinate_storage[N*2];
using namespace boost;
gfloat transmission_probablity;






// This function I made to calculate the distance between every nodes in the map:

  double calculate_distance(double x1,double y1,double x2,double y2)
  {
    
      double dist;
      dist =sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
  
      return (dist);
  }
  
  // function to sort the centrality nodes
  
   void bubble(double store_centrality[])  
  {  
        int i,j,t;  
         for(i=N-2;i>=0;i--)  
         {  
            for(j=0;j<=i;j++)  
  
                  {  
                    if(store_centrality[j]<store_centrality[j+1])  
                                    {  
                                      t=store_centrality[j];  
                                     store_centrality[j]=store_centrality[j+1];  
                                     store_centrality[j+1]=t;  
                                    }  
                   }  
         
  
           }  
  
  } 
  

class final_gui
  {
    
  public:

  static gboolean
  on_expose_event(GtkWidget *widget,
      GdkEventExpose *event,
      gpointer data)
	{
	  cairo_t *cr;
	  cairo_t *ic;
	  cairo_surface_t *surface;
	cout<<"VALUE OF THE VIZZ BTNNN:"<<counter_for_visualize_button<<endl;
	 
	  //image = cairo_image_surface_create_from_png("prj1.png");
	  gint width, height;

	  cr = gdk_cairo_create (widget->window);
	  gtk_window_get_size(GTK_WINDOW(widget), &width, &height); 
	  
	  width = cairo_image_surface_get_width(image);
	  height = cairo_image_surface_get_height(image);
	  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 
								    width, height);
	   ic = cairo_create(surface);
	  cairo_rectangle(ic, 0, 0, width, height);
	  cairo_fill(ic);
	  
	  cairo_set_source_surface(cr, image, 10, 10);
	 cairo_mask_surface(cr,surface,10,10);
	 
	  cairo_move_to(cr,800,38);
	 cairo_set_source_rgb (cr, 0, 0, 0);
	 cairo_show_text (cr, "Enter epidemic radius");
	 cairo_stroke(cr);
	 
	
	 
	 cairo_move_to(cr,800,88);
	 cairo_set_source_rgb (cr, 0, 0, 0);
	 cairo_show_text (cr, "Transmission Probablity");
	 cairo_stroke(cr);
	 
	 cairo_move_to(cr,800,138);
	 cairo_set_source_rgb (cr, 0, 0, 0);
	 cairo_show_text (cr, "Infection Period");
	 cairo_stroke(cr);
	 
	 cairo_move_to(cr,800,188);
	 cairo_set_source_rgb (cr, 0, 0, 0);
	 cairo_show_text (cr, "Simulation Timestep");
	 cairo_stroke(cr);
	 
	  //Map direction
		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_set_line_width (cr, 7); 
		cairo_move_to(cr,50,50);
		cairo_line_to(cr,50,80);
		cairo_stroke(cr);
		cairo_set_line_width (cr, 3);
		cairo_move_to(cr,50,50);
		cairo_line_to(cr,60,50);
		cairo_move_to(cr,50,50);
		cairo_line_to(cr,40,50);
		cairo_move_to(cr,40,50);
		cairo_line_to(cr,50,45);
		cairo_move_to(cr,60,50);
		cairo_line_to(cr,50,45);
		cairo_move_to(cr,65,70);
		cairo_show_text (cr, "North");
		cairo_stroke(cr);
	 
	 
	   
	  // Drawing the cities in the map_coordinate
	  
      for(unsigned int i=0;i<N;i++)
      {
	cairo_set_source_rgba(cr, 0, 0, 0,1);
	cairo_set_line_width (cr, 0.3); 
	cairo_arc(cr, points[i][0]+10, points[i][1], 5, 0,M_PI*2);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
      
      }
      
      
      //Drawing the network in the map:
      
      
  if (counter_for_visualize_button >=1)
      {
	
		// code to write the adjcencies matrix in file
	ofstream outFile;
	outFile.open("graph_topology.txt"); //opening the file to store the co_ordinate of the map
	
	double distance_storage;
	int adjacency_matrix[N][N];
	int edge_counter=0;
	for(int i=0;i<N;i++)
	{
	  for(int j=0;j<N;j++)
	  {
	    double x1,x2,y1,y2;
	    x1=points[i][0];
	    y1=points[i][1];
	    x2=points[j][0];
	    y2=points[j][1];
            distance_storage= calculate_distance(x1,y1,x2,y2);
	    cairo_set_line_width (cr, 0.13);
	    
	    int epidemic_rad;
	    ifstream epi_rad("epidemic_radius.txt");
	    epi_rad>>epidemic_rad;
	    
	    if(distance_storage<=epidemic_rad)
	    {
	     adjacency_matrix[i][j]=1;
	     edge_counter++;
	    // usleep(5000);
	     cairo_move_to(cr,points[i][0]+10,points[i][1]);  
	     cairo_line_to(cr,points[j][0]+10,points[j][1]);
	     cairo_stroke_preserve(cr);
	     cairo_stroke(cr);  
	     	     
	      
	    }
	    else 
	    {
	      adjacency_matrix[i][j]=0;
	    }
	 
	  }
	}
	
	for(int i=0;i<73;i++)
	{
	  for(int j=0;j<73;j++)
	  {
	    network_point_storage[i][j]=adjacency_matrix[i][j];
	    outFile<<adjacency_matrix[i][j]<<" ";
	  }
	  outFile<<endl;
	}
	
	    //for the Y axis caption
		cairo_move_to(cr,420,225);
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Poultry farms");
		
	
	        //codes to draw the epidemic curve
		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_set_line_width (cr, 2); 
		//for Y-Axis epidemic curve

		cairo_move_to(cr,508,150);
		cairo_line_to(cr,508,300);
		cairo_move_to(cr,503,150);
		cairo_line_to(cr,513,150);
		cairo_line_to(cr,508,145);
		cairo_line_to(cr,503,150); 
		
		cairo_move_to(cr,490,160);
		cairo_show_text (cr, "72");
		
		//for Y-Axis degree distribution
		cairo_move_to(cr,508,350);
		cairo_line_to(cr,508,500);
		cairo_move_to(cr,503,350);
		cairo_line_to(cr,513,350);
		cairo_line_to(cr,508,345);
		cairo_line_to(cr,503,350); 
		
		
		cairo_move_to(cr,430,440);
		cairo_show_text (cr, "Node");
		cairo_move_to(cr,430,450);
		cairo_show_text (cr, "Frequency");
		
		//for X-Axis degree distribution
		cairo_move_to(cr,508,500);
		cairo_line_to(cr,768,500);
		cairo_move_to(cr,768,500);
		cairo_line_to(cr,768,495);
		cairo_move_to(cr,768,500);
		cairo_line_to(cr,768,505);
		cairo_move_to(cr,768,505);
		cairo_line_to(cr,773,500);
		cairo_move_to(cr,768,495);
		cairo_line_to(cr,773,500);
		
		cairo_move_to(cr,623,530);
		cairo_show_text (cr, "Node degree");
		
		
		
	      //for X-Axis epidemic curve
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_move_to(cr,508,300);
		cairo_line_to(cr,758,300);
		cairo_stroke(cr);
		
		// curve legend
		
		cairo_set_source_rgb (cr, 0, 1, 0);
		cairo_set_line_width (cr, 0.6);
		cairo_move_to(cr,550,80);
		cairo_line_to(cr,560,80);
		cairo_stroke(cr);
		cairo_move_to(cr,565,80);
		
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Recovered poultry farms");
		cairo_stroke(cr);
		
		cairo_set_source_rgb (cr, 1, 0, 0);
		cairo_set_line_width (cr, 0.6);
		cairo_move_to(cr,550,100);
		cairo_line_to(cr,560,100);
		cairo_stroke(cr);
		cairo_move_to(cr,565,100);
		
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Infected poultry farms");
		cairo_stroke(cr);
		
		
		cairo_set_source_rgb (cr, 0, 0, 1);
		cairo_set_line_width (cr, 0.6);
		cairo_move_to(cr,550,120);
		cairo_line_to(cr,560,120);
		cairo_stroke(cr);
		cairo_move_to(cr,565,120);
		
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Susceptible poultry farms");
		cairo_stroke(cr);
		
		
			//Graph graduation for the epidemic curve
		cairo_set_line_width (cr, 2); 
		cairo_move_to(cr,758,295);
		cairo_line_to(cr,758,305);
		cairo_move_to(cr,758,295);
		cairo_line_to(cr,763,300);
		cairo_move_to(cr,763,300);
		cairo_line_to(cr,758,305);
		cairo_move_to(cr,508,310);
		cairo_show_text (cr, "0");
		cairo_stroke(cr);
		
		// for the caption of x-axis epidemic curve
		cairo_move_to(cr,600,330);
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Simulation time step:");
		cairo_stroke(cr);
		
		float unit_x_axis_of_epidemic_graph;
		char *x_axis_label_for_epidemic_curve=new char[30];
	        cairo_set_source_rgb (cr, 0, 0, 0);
		
		// For the x-axis epidemic curve graduation
		
		if( time_stamp_from_gui<=10)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<time_stamp_from_gui;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i); 
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		    
		    
		  }
		  
		  
		}
		
		if( time_stamp_from_gui>10 && time_stamp_from_gui<=20)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/2;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*2);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*1.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		  
		  
		  if( time_stamp_from_gui>20 && time_stamp_from_gui<=30)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/3;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*3);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*2.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		
		  if( time_stamp_from_gui>30 && time_stamp_from_gui<=40)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/4;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*4);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*3.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		
		
		  if( time_stamp_from_gui>40 && time_stamp_from_gui<=50)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/5;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*5);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*4.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		
		  if( time_stamp_from_gui>50 && time_stamp_from_gui<=60)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/6;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*6);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*5.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		
		
		  if( time_stamp_from_gui>60 && time_stamp_from_gui<=70)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/7;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*7);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*6.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		
		
		  if( time_stamp_from_gui>70 && time_stamp_from_gui<=80)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/8;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*8);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*7.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		
		  if( time_stamp_from_gui>80 && time_stamp_from_gui<=90)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/9;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*9);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*8.8,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		
		
		  if( time_stamp_from_gui>90 && time_stamp_from_gui<=100)
		{
		  unit_x_axis_of_epidemic_graph= 250.0/time_stamp_from_gui ;
		  
		  for(int i=1;i<=time_stamp_from_gui/10;i++)
		  {
		     sprintf(x_axis_label_for_epidemic_curve, "%d", i*10);
		     cairo_move_to(cr,508+ unit_x_axis_of_epidemic_graph*i*9.2,310);
		     cairo_show_text (cr, x_axis_label_for_epidemic_curve);
		    
		     }
		    
		  }
		  
		  // For the y-axis epidemic curve graduation
		  char *y_axis_label_for_epidemic_curve=new char[30];
	          cairo_set_source_rgb (cr, 0, 0, 0);
		  
		  float unit_y_axis_of_epidemic_graph = 150.0 / 72.0;
		   for(int i=1;i<8;i++)
		  {
		     sprintf(y_axis_label_for_epidemic_curve, "%d", i*9);
		     cairo_move_to(cr,490,300-unit_y_axis_of_epidemic_graph*i*8.2);
		     cairo_show_text (cr, y_axis_label_for_epidemic_curve);
		    
		   }
		   
		       	// The legend of the graph network 


 
		cairo_set_source_rgb (cr, 0, 0,1);
		cairo_arc (cr,330,710,4.0,0,2*M_PI);
		cairo_fill(cr);
		cairo_stroke(cr);
		cairo_set_source_rgb (cr, 1, 0,0);
		cairo_move_to(cr,340,720);
		cairo_show_text (cr, "Susceptible");
		
		cairo_set_source_rgb (cr, 1, 0,0);
		cairo_arc (cr,330,730,4.0,0,2*M_PI);
		cairo_fill(cr);
		cairo_stroke(cr);
		cairo_set_source_rgb (cr, 0, 0,0);
		cairo_move_to(cr,340,740);
		cairo_show_text (cr, "Infected");
		
		cairo_set_source_rgb (cr, 0, 1,0);
		cairo_arc (cr,330,750,4.0,0,2*M_PI);
		cairo_fill(cr);
		cairo_stroke(cr);
		cairo_set_source_rgb (cr, 0, 0,0);
		cairo_move_to(cr,340,760);
		cairo_show_text (cr, "Recovered");
		cairo_stroke(cr);
		
		// Legend for the degree distribution
		
		cairo_set_source_rgb (cr, 0, 0, 1);
		cairo_set_line_width (cr, 0.6);
		cairo_move_to(cr,765,450);
		cairo_line_to(cr,775,450);
		cairo_stroke(cr);
		cairo_set_source_rgb (cr, 0, 0,0);
		cairo_move_to(cr,780,450);
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Degree Distbution");
		cairo_stroke(cr);
		
		
 
  
	    cairo_set_source_rgb(cr, 0, 0, 0);
	    cairo_set_line_width (cr, 0.1); 
	    
	    
	    double coordinate_storage[N*2];
	    int cnt1=0,counter=0;
	    double ii=0;  
	    const char *inname = "map_coordinate.txt";
	    ifstream infile(inname);  
	  
	      while (infile >> ii) 
	      {
		  coordinate_storage[cnt1++]=ii;
	  
	      }
	      
	    ifstream file( "map_coordinate.txt" ) ;
	    string line ;
	    vector<string> lines ;
	    
	      while( getline( file, line ) ) lines.push_back( line ) ;
	    
	    
	      for(unsigned int j=0;j<lines.size();j++)
	      {
		for(int k=0;k<2;k++)
		  {
		  points[j][k]=coordinate_storage[counter];
		  counter++;
		  
		    }
			  
		  } 
		  
	   ifstream file2( "total_degree.txt" ) ; 
	      int total_degree_from_file[N];
	      int highest_degree_in_file=0;
	      while (!file2.eof())
	      {
		  for(int m=0; m<N; m++)// rows number

		  {
		    file2 >>total_degree_from_file[m];
		    if (highest_degree_in_file<total_degree_from_file[m])
		    {
		      highest_degree_in_file=total_degree_from_file[m];
		    
		    }  
		
		  }
		
	      }
	      // code to sort 5 influential degree in the degree list.
	      
	      int temporary_variable;
	      for(int i=1;i<N;i++)
		{
		  for(int j=0;j<N-i;j++)
		    {
		      if(total_degree_from_file[j] < total_degree_from_file[j+1])
			{
			temporary_variable=total_degree_from_file[j];
			total_degree_from_file[j]=total_degree_from_file[j+1];
			total_degree_from_file[j+1]=temporary_variable;
			}
		  }
		} 
		
		cout<<"Sorted array of degree:"<<endl;
		int similar_degree_counter=0;
		for(int i=0;i<5;i++)
		{
		  if(total_degree_from_file[i] == total_degree_from_file[i+1] && similar_degree_counter==0 )
		  {
		    similar_degree_counter++;
		    cout<< total_degree_from_file[i] <<endl;
		  }
		  else
		     cout<< total_degree_from_file[i] <<endl;
		    
		}
		
		// Deleting the duplicate data in degree 
	      
	   
	      
	      
	      //  cout<< random_out_degree_picker<<endl;
	      
	      cout<< highest_degree_in_file<<endl;
	      
	      cairo_set_source_rgb (cr, 0, 0, 0);
	      
	      char *highest_degree=new char[30];
	      sprintf(highest_degree, "%d", highest_degree_in_file);
	      cairo_move_to(cr,749,510);
	
	      
	      
	      
	       int cnt5=0,cnt10=0,cnt15=0,cnt20=0,cnt25=0,cnt30=0,cnt35=0,cnt40=0,cnt45=0,cnt50=0,
	     cnt55=0,cnt60=0,cnt65=0,cnt70=0,cnt75=0,cnt80=0,cnt85=0,cnt90=0,cnt95=0,cnt100=0;
	 for(int i=0;i<72;i++)
	 {
	    if( total_degree_from_file[i]<=5 )
	      
		 cnt5++;
	    else if(total_degree_from_file[i]>5 && total_degree_from_file[i]<=10)
	    
		cnt10++;
	    
	    else if(total_degree_from_file[i]>10 && total_degree_from_file[i]<=15)
		cnt15++;

	    else if(total_degree_from_file[i]>15 && total_degree_from_file[i]<=20)
		cnt20++;
	    
	    else if(total_degree_from_file[i]>20 && total_degree_from_file[i]<=25)
		cnt25++;
	    
	    else if(total_degree_from_file[i]>25 && total_degree_from_file[i]<=30)
		cnt30++;
	    
	    else if(total_degree_from_file[i]>30 && total_degree_from_file[i]<=35)
		cnt35++;
	    
	    else if(total_degree_from_file[i]>35 && total_degree_from_file[i]<=40)
		cnt40++;
	    
	    else if(total_degree_from_file[i]>40 && total_degree_from_file[i]<=45)
	      cnt45++;
	    
	    else if(total_degree_from_file[i]>45 && total_degree_from_file[i]<=50)
		cnt50++;
	    
	    else if(total_degree_from_file[i]>50 && total_degree_from_file[i]<=55)
		cnt55++;
	    
	    else if(total_degree_from_file[i]>55 && total_degree_from_file[i]<=60)
		cnt60++;
	    
	    else if(total_degree_from_file[i]>60 && total_degree_from_file[i]<=65)
		cnt65++;
	    
	    else if(total_degree_from_file[i]>65 && total_degree_from_file[i]<=70)
		cnt70++;
	     
	    else if(total_degree_from_file[i]>70 && total_degree_from_file[i]<=75)
		cnt75++;
	    
	    else if(total_degree_from_file[i]>75 && total_degree_from_file[i]<=80)
		cnt80++;
	    
	    else if(total_degree_from_file[i]>80 && total_degree_from_file[i]<=85)
		cnt85++;
	    
	    else if(total_degree_from_file[i]>85 && total_degree_from_file[i]<=90)
		cnt90++;
	    
	    else if(total_degree_from_file[i]>90 && total_degree_from_file[i]<=95)
		cnt95++;
	    
	    else if(total_degree_from_file[i]>95 && total_degree_from_file[i]<=100)
		cnt100++;
	 }
	 cout<<"frequency mapper:"<<endl;
	 
	 int degree_frequency_mapper[]={cnt5,cnt10,cnt15,cnt20,cnt25,cnt30,cnt35,cnt40,cnt45,cnt50,cnt55,cnt60,cnt65,cnt70,cnt75,cnt80,
	 cnt85,cnt90,cnt95,cnt100};
	 
	int highest_degree_frequency=0; 
	for(int i=0;i<20;i++){
	  if(degree_frequency_mapper[i]>highest_degree_frequency)
	  {
	    highest_degree_frequency=degree_frequency_mapper[i];
	  }
	 // cout<<degree_frequency_mapper[i]<<endl;
	}
	//cout<<highest_degree_frequency<<endl;
	
	 
	
	
	 int highest_node_position=100;
	 
	
	
	char *highest_frequency=new char[30];
	char *highest_position=new char[30];
	char *y_axis_legend= new char[30];
	sprintf(highest_frequency, "%d", highest_degree_frequency+1); 
	sprintf(highest_position, "%d", highest_node_position); 
	cairo_move_to(cr,490,360);
	cairo_show_text (cr, highest_frequency);
	
	

	
	 double unit_x_axis,unit_y_axis;
	 unit_x_axis= (242.0/100) ; //100 is the maximum highest degree
	 unit_y_axis= (150.0/highest_degree_frequency);	
	 cout << unit_x_axis<<"," << unit_y_axis <<endl;
	
	 //setting up the Y-axis of the histogram with the interval of 3
	 
	 for(int i=1;i<=highest_degree_frequency/3;i++)
	 {
	   
	   sprintf(y_axis_legend, "%d", i*3); 
	   cairo_move_to(cr,490,510-unit_y_axis*i*3);
	   cairo_show_text (cr, y_axis_legend);
	  // cout<< i<<endl;
	   
	}
	 

	//cairo_set_source_rgb (cr, 0, 0, 1);
	cairo_set_line_width (cr, unit_x_axis*5);
	
	// char *y_axis_graduation=new char[30];
	 
	cairo_set_source_rgb (cr, 0, 0, 1);
	 
	 for(int i=0;i<20;i++)
	{
	
	cairo_move_to(cr,508+unit_x_axis*i*5+2,500);
	cairo_line_to(cr,508+unit_x_axis*i*5+2,500-unit_y_axis*degree_frequency_mapper[i]);
	cairo_stroke(cr);
	
	  
	}
	
	char *x_axis_graduation=new char[30];
	 cairo_set_source_rgb (cr, 0, 0, 0);
	 
	 for(int i=0;i<=10;i++)
	 {
	
	   sprintf(x_axis_graduation, "%d", i*10); 
	   cairo_move_to(cr,508+unit_x_axis*i*10,510);
	  cairo_show_text (cr, x_axis_graduation);
	 
	 }
	 
	 //Removing the duplicates array in the list of the sorted array::
	 
	    int *p;
	      int k,size;
	      size=N;
	      p= total_degree_from_file;
	      for(int i=0;i<size;i++)
	      {
		for(int j=0;j<size;j++)
		  {
		    if(i==j)
		      {
			continue;
		      }
	      
	        else if(*(p+i)==*(p+j))
		{
		      k=j;
		      size--;
		      while(k < size)
		      {
			  *(p+k)=*(p+k+1);
			  k++;
		      }
			j=0;
		 }
		}
	    }
	    
		  cout<<"Array after removing duplicates:"<<endl;
		  
	  
	    for(int i=0;i < size;i++)
	      {
	      
		  cout<<total_degree_from_file[i]<<endl;
	      }
	      
	      
	      	      	      	      	      	    		
	 cairo_stroke(cr);  
	  	 	// Code to compute centrality       
	typedef property < edge_weight_t, double > WeightMap; 
	typedef property < vertex_centrality_t, double > CentralityMap; 
	typedef adjacency_list<vecS, vecS, directedS, 
	CentralityMap, WeightMap> UGraph; 
	UGraph ug(N); 
	
	int cnt=0,x2,y2,x1,y1,dist;
	int xco_mem[N],yco_mem[N],for_y=0;
	 
	  for(int m=0;m<N*2;m++)
	    {
	    
		if(m<73)
		xco_mem[m]=coordinate_storage[m];
		else
		{
		yco_mem[for_y]=coordinate_storage[m];
		for_y++;
		}
		
	    
	    
	    }
	 
	 
	 
	 
	 
      for(int i=0;i<N;i++)
	{
	  for(int j=0;j<N;j++)
	  {
	    if (adjacency_matrix[i][j]==1 )
	      {
		    
		cnt ++;
	 
		//function calling to calculate the distance "weight"
		x2=xco_mem[i];
		y2=yco_mem[i];
		x1=xco_mem[j];
		y1=yco_mem[j];
		dist=calculate_distance(x1,y1,x2,y2);
		

		add_edge(i,j,dist,ug);
	  
       }
	
	    else if (adjacency_matrix[j][i]==1)
	    {
	
	      cnt ++;
	      
	      
		//function calling to calculate the distance "weight"
	      
	      x2=xco_mem[i];
	      y2=yco_mem[i];
	      x1=xco_mem[j];
	      y1=yco_mem[j];
	      dist=calculate_distance(x1,y1,x2,y2);
	      
	      add_edge(i,j,dist,ug); 
	
	
       }
   
     }
   }
   
	  // for the calculation of the betweeness
  
	int i=0,highest_node=0;
	double store_centrality[N],highest_centrality;
      
      brandes_betweenness_centrality(ug, 
				    get(vertex_centrality,ug), 
				    get(edge_weight, ug) 
				    ); 

      boost::property_map<UGraph, vertex_centrality_t>::type 
	b = get(vertex_centrality, ug); 


      graph_traits < UGraph  >::vertex_iterator vi, vi_end;
      
      double average_centrality=0;
      for (tie(vi, vi_end) = vertices(ug); vi != vi_end; ++vi) { 
	store_centrality[i]=b[*vi];
	printf("BRANDES centr[%d] = %lf\n", 
		*vi, 
		b[*vi]); 
		average_centrality=average_centrality+b[*vi];
		i++;
      } 
      
      average_centrality=average_centrality/i;
      highest_centrality  = store_centrality[0];
      
       
    for(int j=0;j<N;j++)
    {
	if(store_centrality[j]> highest_centrality)
	{ 
	highest_centrality=store_centrality[j];
	highest_node=j;
	}
    }
    
    
    
	char *highest_centrality_nodes=new char[30];
	char *density=new char[30];
	cairo_move_to(cr,530,610);
	cairo_show_text (cr, "highest central nodes:");
	cairo_move_to(cr,530,630);
	cairo_show_text (cr, "graph density:");
	sprintf(highest_centrality_nodes, "%d", highest_node); 
	cairo_move_to(cr,650,610);
	cairo_show_text (cr, highest_centrality_nodes);
	float aa=2*edge_counter;
	float bb= N*(N-1);
	
	float graph_density= aa/bb;
	cout<<"Edge counter::"<<edge_counter<<","<<graph_density<<endl;
	sprintf(density, "%f",graph_density ); 
	cairo_move_to(cr,650,630);
	cairo_show_text (cr, density);
	cairo_move_to(cr,530,650);
	cairo_show_text(cr,"Sorted Degree List of the nodes:");
	
	
	char *degree_lister=new char[30];
	for(int i=0;i<10;i++)
	{
	  sprintf(degree_lister, "%d",total_degree_from_file[i] );
	  cairo_move_to(cr,700+i*30,650);
	  cairo_show_text (cr,degree_lister);
	}
	
	
	
	
	cairo_stroke(cr);
	
    
	// sorting the 5 different nodes according to betweeness
	 
	 
	cairo_set_source_rgba(cr, 0, 0, 1,1);
	cairo_set_line_width (cr, 0.3); 
	cairo_arc(cr,points[highest_node][0]+10,points[highest_node][1],4, 0,M_PI*2);		
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
	cairo_destroy(cr);
	
	cout<<"Sorted array of centrality_nodes:" << endl;
	
	 bubble(store_centrality); 
	
	
      
     
	 }
                        
		//cairo_move_to(cr,500,200);
		//cairo_show_text(cr,"Does it come::");
	 

	  return FALSE;
      
	  
	}
	
	
	static void simulation_perform(GtkWidget *widget, gpointer data)
	{
	  int call=0;
	  countf++;
	  float aa1[8];
	  counter_for_visualize_button++;
	  
	  gfloat a1,b1,c1,d1;
	  
	  
	
	
	  a1= atoi(gtk_entry_get_text(GTK_ENTRY(data))); 
	  call++;
	   
	   
	  if(call==1)
	  {
	  b1=0; 
	  c1=0;
	  d1=0;
	   // cout<<a<<endl;
	    aa1[0]=a1;
	    aa1[1]=a1;
	    if(countf==1){
	      
	        ofstream outFile0;
		outFile0.open("epidemic_radius.txt");
		outFile0 << aa1[1];
	      
	   
	   
	    cout<<aa1[1]<<endl;
	    }
	  }
	  
	  b1= atof(gtk_entry_get_text(GTK_ENTRY(data)));
	  call++;
	  
	     
	  if(call==2){
	    a1=0;
	    c1=0;
	    d1=0;
	  // cout<<b<<endl;
	   aa1[2]=b1;
	   aa1[3]=b1;
	     if(countf==2)
	     {
	        ofstream outFile;
		
		
		outFile.open("transmission_probablity.txt");
		outFile << aa1[2];
	   
	 
	    cout<<aa1[2]<<endl;
	    }
	
	  }
	  
	  c1= atoi(gtk_entry_get_text(GTK_ENTRY(data)));
	  call++;
	
	 if(call==3){
	    a1=0;
	    b1=0;
	    d1=0;
	  // cout<<b<<endl;
	   aa1[4]=c1;
	   aa1[5]=c1;
	     if(countf==3)
	     {
	    ofstream outFile1;
	    outFile1.open("Infection_period.txt");
	    outFile1 << aa1[4];
	    cout<<aa1[4]<<endl;
	    }
	
	  }
	  
	  
	    d1= atoi(gtk_entry_get_text(GTK_ENTRY(data)));
	  call++;
	
	 if(call==4){
	    a1=0;
	    b1=0;
	    c1=0;
	  // cout<<b<<endl;
	   aa1[6]=d1;
	   aa1[7]=d1;
	     if(countf==4)
	     {
	    cout<<aa1[6]<<endl;
	    time_stamp_from_gui= aa1[6];
	    ofstream outFile_for_time_stamp;
	    outFile_for_time_stamp.open("time_stamp_from_gui.txt"); //opening the file to store the co_ordinate of the map
            outFile_for_time_stamp << time_stamp_from_gui;
	    
	    }
	
	  }
	  // The part below here are responsible for the visualization
	  	     
	      



	}
	
	
static gboolean clicked2(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
  
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);
	  // codes to demonstrate susceptible infected and recovered nodes 
	   unsigned int simulation_time_stamp=time_stamp_from_gui;
		int m[simulation_time_stamp][N];//n[73];
		ifstream inFile ("simulation.txt", ios::in); //file to read the timestamp of the simulation result
		 sim.update_status_table();
				
	      for(unsigned int i=0;i<simulation_time_stamp;i++)
	      {
		for(unsigned int j=0;j<N;j++)
		
		
		inFile>>m[i][j];
	      
	      }
	      
	       // This is for storing the number of susceptible, infected and recovered nodes at all the time stamp in a file 
	 
	  ofstream outFile_infection;
	  outFile_infection.open("infection.txt"); //opening the file to store the co_ordinate of the map
	  int infection_at_each_time_stamp[simulation_time_stamp][3];	
	  int susceptible_nodes=0; // initial information of susceptible nodes
	  int infected_nodes=0; // initial information of infected nodes 
	  int recovered_nodes=0; // initial information of infected nodes 
	
	      
	       for(unsigned int i=0;i<simulation_time_stamp;i++)
		{
	
		
		  for(unsigned int j=0;j<N;j++)
		  {
		    usleep(10000);	
		
                        if(m[i][j]==0 ) //0.03 is the infected probablity and shows the infection occurs 
                        {
			 
			//usleep(100);	
			infection_at_each_time_stamp[i][0]=susceptible_nodes++;  
									
			cairo_set_source_rgb(cr, 0, 0, 1);
			
			cairo_set_line_width (cr, 0.3);
                        cairo_arc(cr,points[j][0]+10,points[j][1],4, 0,M_PI*2);
			
			
			cairo_stroke_preserve(cr);
			cairo_fill(cr); 
			
		
                        }
                        
                        if(m[i][j]==1 )
			{
			infection_at_each_time_stamp[i][1]=infected_nodes++;
			
			cairo_set_source_rgb(cr, 1, 0, 0);
			
			cairo_set_line_width (cr, 0.3);
                        cairo_arc(cr,points[j][0]+10,points[j][1],4, 0,M_PI*2);
			cairo_stroke_preserve(cr);
			cairo_fill(cr);
				  
			  
			} 
			
			 if(m[i][j]==2 )
			{
			  //usleep(100);
			//usleep(6000);   
			infection_at_each_time_stamp[i][2]=recovered_nodes++;	  
			cairo_set_source_rgb(cr, 0, 1, 0);
			
			cairo_set_line_width (cr, 0.3);
                        cairo_arc(cr,points[j][0]+10,points[j][1],4, 0,M_PI*2);
			
			cairo_stroke_preserve(cr);
			cairo_fill(cr);
			
			}
		
		  }
		           
                infection_at_each_time_stamp[i][0]=susceptible_nodes;
		infection_at_each_time_stamp[i][1]=infected_nodes;
		infection_at_each_time_stamp[i][2]=recovered_nodes;
		susceptible_nodes=0;
		infected_nodes=0;
		recovered_nodes=0;

		}
		
		 for(unsigned int i=0;i<simulation_time_stamp;i++)
  { 
    for(unsigned int j=0;j<3;j++)
        {
	  
	   outFile_infection << infection_at_each_time_stamp[i][j]<<" ";
	   
	  
	}
	
	outFile_infection << endl;
  }



 // This code is responsible to draw the epidemic curve reading file 
 
  //cout<< "INF CHK"<<endl;
  int epidemic_graph_drawing_node[simulation_time_stamp][3];
 
	ifstream inFile2 ("infection.txt", ios::in);
	float x_axis_controller= 250.0/simulation_time_stamp;
		
	for(unsigned int i=0;i<simulation_time_stamp;i++)
	      {
		for(unsigned int j=0;j<3;j++)
		{		  
		 inFile2>>epidemic_graph_drawing_node[i][j];  
		cout<<	epidemic_graph_drawing_node[i][j]<<" ";		
	      }
	      cout<<endl;
	      }
	      
	      
	        // for the susceptible_nodes epidemic curve:
	        
	      for (unsigned int i=0;i<=simulation_time_stamp;i++)
	      {
		if (i+1==simulation_time_stamp)
		break;
		else{
		  usleep(90000);
	      
		  cairo_set_source_rgb(cr, 0, 0, 1);
		  cairo_set_line_width (cr, 0.6);
		  cairo_move_to(cr,508+x_axis_controller*i,300-epidemic_graph_drawing_node[i][0]*2); 
		  cairo_arc(cr,508+x_axis_controller*i,300-epidemic_graph_drawing_node[i][0]*2,1.0,0,2*M_PI);
		  cairo_line_to(cr,508+x_axis_controller*(i+1),300-epidemic_graph_drawing_node[i+1][0]*2);
		 
		}
		 cairo_stroke(cr); 
		  
	      }
	      
	      
	      
	      
	      // for the infection epidemic curve:
	      for (unsigned int i=0;i<=simulation_time_stamp;i++)
	      {
		if (i+1==simulation_time_stamp)
		break;
		else{
	          usleep(90000);
		  cairo_set_source_rgb(cr, 1, 0, 0);
		  cairo_set_line_width (cr, 0.6);
		  cairo_move_to(cr,508+x_axis_controller*i,300-epidemic_graph_drawing_node[i][1]*2); 
		  cairo_arc(cr,508+x_axis_controller*i,300-epidemic_graph_drawing_node[i][1]*2,1.0,0,2*M_PI);
		  cairo_line_to(cr,508+x_axis_controller*(i+1),300-epidemic_graph_drawing_node[i+1][1]*2);
		 
		}
		 cairo_stroke(cr); 
		  
	      }
	      
	          // for the recovered_nodes epidemic curve:
	        
	      for (unsigned int i=0;i<=simulation_time_stamp;i++)
	      {
		if (i+1==simulation_time_stamp)
		break;
		else{
	          usleep(90000);
		  cairo_set_source_rgb(cr, 0, 1, 0);
		  cairo_set_line_width (cr, 0.6);
		  cairo_move_to(cr,508+x_axis_controller*i,300-epidemic_graph_drawing_node[i][2]*2); 
		  cairo_arc(cr,508+x_axis_controller*i,300-epidemic_graph_drawing_node[i][2]*2,1.0,0,2*M_PI);
		  cairo_line_to(cr,508+x_axis_controller*(i+1),300-epidemic_graph_drawing_node[i+1][2]*2);
		 
		}
		 cairo_stroke(cr); 
		  
	      }
		
		
		
		
		
		
  
       return TRUE;
  
  
  
  
}	
	
	
	
	
	
	
	
	
	// This is I add for the click event:

static gboolean clicked1(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
   int i;
   static int counter_for_click_stream=0;
  
  
   if (event->button == 1)
    
    {
       for( i=0; i<73;i++)
      
      {
	if(
	   ( (event ->x)==points[i][0]+10 ) ||
	   ( event ->y ==points[i][1] ))
	      
	    
	     break ;
	
	  	
	
      }
      
         
	    
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);
	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_set_line_width (cr, 0.3);        
	cairo_arc(cr, points[i][0]+10, points[i][1], 4, 0, 2*M_PI);	  
		
	  
       
	cairo_fill(cr);
	cairo_stroke(cr);
          //cairo_destroy(cr);
      
             
      cout<<"THIS IS THE CO_ORDINATE OF EVENT :"<<event->x <<","<<event->y<< endl;
      if (i<73 && i>0)
      {
      
      //cout<<"This node is selected:"<< i<<endl;
       ofstream outFile_for_click_stream;
       outFile_for_click_stream.open("clickstream.txt",ofstream::app); //opening the file to store the co_ordinate of the map
       outFile_for_click_stream << i;
       click[counter_for_click_stream]=i;
       outFile_for_click_stream << endl;
     //  cout<<  click[counter_for_click_stream]<<endl;
      }

	  }
	    
	

    return TRUE;
}



	
  
	
	
// This code is responsible for reading the coordintate position of the map:

 int file_read()
  {
  
	double i=0;  
	const char *inname = "map_coordinate.txt";
	int line_of_files_receiver;

	ifstream infile(inname);  
	 
	  int cnt=0;  
	  
	  while (infile >> i) 
	  {
	      coordinate_storage[cnt++]=i;
      
	  }
	      //This code helps to find the number of lines of file
	      
	    ifstream file( "map_coordinate.txt" ) ;
	    string line ;
	    vector<string> lines ;
	    while( getline( file, line ) ) lines.push_back( line ) ;
	    line_of_files_receiver=lines.size();
		  
		  
	int counter=0;
	      
	for(unsigned int j=0;j<lines.size();j++)
	{
	  for(int k=0;k<2;k++)
	  {
	      points[j][k]=coordinate_storage[counter];
	      
	      counter++;

	    }
	    
	} 
	return line_of_files_receiver;
    }
    
     
	
	
	void calling_epidemic_gui()
	{
	
	  GtkWidget *window;

	  GtkWidget *frame;
	  GtkWidget *entry;
	  GtkWidget *entry1;
	  GtkWidget *entry2;
	  GtkWidget *entry3;
	  GtkWidget *hbox;
	  GtkWidget *set;
	
	  GtkWidget *visualize;
	  
	  
	  

	
	  image= cairo_image_surface_create_from_png("prj1.png");
	  
	  
	  frame = gtk_fixed_new();
	  set=gtk_button_new_with_label("set");
	 // fix=gtk_button_new_with_label("fix");
	 // set=gtk_button_new_with_label("set");
	  visualize= gtk_button_new_with_label("visualize");
	
	  entry = gtk_entry_new ();
	  hbox=gtk_hbox_new(0,0);
	  gtk_box_pack_start(GTK_BOX(hbox),entry,0,0,0);
	  gtk_fixed_put(GTK_FIXED(frame), hbox, 800, 48); 
	  gtk_widget_set_size_request(set, 60, 25);
	  gtk_fixed_put(GTK_FIXED(frame), set, 960, 48);
	  
	 
	  entry1 = gtk_entry_new ();
	  hbox=gtk_hbox_new(0,0);
	  gtk_box_pack_start(GTK_BOX(hbox),entry1,0,0,0);
	  gtk_fixed_put(GTK_FIXED(frame), hbox, 800, 98); 
	//  gtk_widget_set_size_request(fix, 60, 25);
	  //gtk_fixed_put(GTK_FIXED(frame), fix, 960, 98);
	  
	
	  
	  entry2=gtk_entry_new ();
	  
	
	  hbox=gtk_hbox_new(0,0);
	  gtk_box_pack_start(GTK_BOX(hbox),entry2,0,0,0);
	  gtk_fixed_put(GTK_FIXED(frame), hbox, 800, 148); 
	  
	  
	  entry3 = gtk_entry_new ();
	  hbox=gtk_hbox_new(0,0);
	  gtk_box_pack_start(GTK_BOX(hbox),entry3,0,0,0);
	  gtk_fixed_put(GTK_FIXED(frame), hbox, 800, 198); 
	  gtk_widget_set_size_request(set, 70, 25);
	  gtk_fixed_put(GTK_FIXED(frame), set, 800, 248);
	  
	  gtk_widget_set_size_request(visualize, 70, 25);
	  gtk_fixed_put(GTK_FIXED(frame), visualize, 880, 248);
	  
	  
	  
	
	  
	  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	  
	   gtk_container_add(GTK_CONTAINER(window), frame);
	   gtk_widget_add_events (window, GDK_BUTTON_PRESS_MASK);
	   
	
	   
	  /*  g_signal_connect(set, "button-press-event", 
      G_CALLBACK(clicked), entry);*/
	    
	    

	       
	    g_signal_connect(window, "button-press-event", 
      G_CALLBACK(clicked1), NULL);
		
	 //   g_signal_connect(simulate, "clicked", 
      //G_CALLBACK(simulation_perform), entry2[0]);
	
	 g_signal_connect(set, "clicked", G_CALLBACK(simulation_perform), entry);  
	 g_signal_connect(set, "clicked", G_CALLBACK(simulation_perform), entry1);  
	 g_signal_connect(set, "clicked", G_CALLBACK(simulation_perform), entry2);
	 g_signal_connect(set, "clicked", G_CALLBACK(simulation_perform), entry3);
	 g_signal_connect(visualize, "button-press-event", G_CALLBACK(clicked2),NULL); 
	
	  /*  	
	   g_signal_connect(simulate, "button-press-event", 
        G_CALLBACK(clicked), entry);*/
	  
	    /*
	    g_signal_connect(simulate, "clicked", 
      G_CALLBACK(simulation_perform), entry3); */
	    
	    
	    
	    g_signal_connect(visualize, "clicked", 
     G_CALLBACK(on_expose_event), NULL); 
	
	  g_signal_connect(window, "expose-event",
	      G_CALLBACK (on_expose_event), NULL);
	  
	   g_signal_connect(G_OBJECT(window), "destroy",
   G_CALLBACK(gtk_main_quit), NULL);
  
	
	  
	// g_signal_connect(window, "destroy",
	  //  G_CALLBACK (gtk_main_quit), NULL);
	  
	  

	  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	  gtk_window_set_default_size(GTK_WINDOW(window), 1016+10, 821+10); 
	  gtk_window_set_title(GTK_WINDOW(window), "epidemic visualization");
	 
	  gtk_widget_set_app_paintable(window, TRUE);

	  gtk_widget_show_all(window);

	 
	
		  
	  
	}
	
	
	
    
  };
  
  #endif