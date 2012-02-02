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
#define N 73


#ifndef final_gui_H
#define final_gui_H


using namespace boost;

cairo_surface_t *image1;
double network_point_storage[73][73];
double points[73][2]; // global variable for the coordinate points

double calculate_distance(double x1,double y1,double x2,double y2)
{
  
  
  double dist;
  dist =sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
  
  return (dist);
}




class final_gui
{
public:
  
  
  static void create_surfaces() 
  
  {
  image1= cairo_image_surface_create_from_png("prj1.png");
  }
  
 
 int file_read()
 {
  
   double i=0;  
   const char *inname = "map_coordinate.txt";
   int line_of_files_receiver;

  ifstream infile(inname);  
    double coordinate_storage[146];
    int cnt=0;  
    cout << "coordinate file: " << inname << " for reading." << endl;
    
    while (infile >> i) 
    {
	coordinate_storage[cnt++]=i;
 
    }
	//This code helps to find the number of lines of file
	
   ifstream file( "map_coordinate.txt" ) ;
   string line ;
   vector<string> lines ;
   while( getline( file, line ) ) lines.push_back( line ) ;
   cout << "#lines: " << lines.size()<< '\n' ;
   line_of_files_receiver=lines.size();
	
	
	int counter=0;
	
     for(unsigned int j=0;j<lines.size();j++){
     for(int k=0;k<2;k++){
	points[j][k]=coordinate_storage[counter];
	
	counter++;

		}
	} 
   return line_of_files_receiver;
}



  
 static gboolean 
   on_expose_event(GtkWidget *widget,
    GdkEventExpose *event,
    gpointer data)
{
  cairo_t *cr;
 
 
  cr = gdk_cairo_create (widget->window);
  gint width, height;
  gtk_window_get_size(GTK_WINDOW(widget), &width, &height);
  
  static double alpha = 1; 
  cairo_set_source_surface(cr, image1, 10, 10);
  cairo_paint_with_alpha(cr, alpha);
  
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
	      //for the Y axis caption
		cairo_move_to(cr,425,225);
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
		cairo_set_source_rgb (cr, 1, 0, 0);
		cairo_set_line_width (cr, 0.6);
		cairo_move_to(cr,765,250);
		cairo_line_to(cr,775,250);
		cairo_stroke(cr);
		cairo_move_to(cr,780,250);
		
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Infection rate");
		cairo_stroke(cr);
		
		
		cairo_set_source_rgb (cr, 0.5, 0, 0);
		cairo_set_line_width (cr, 0.6);
		cairo_move_to(cr,765,270);
		cairo_line_to(cr,775,270);
		cairo_stroke(cr);
		cairo_move_to(cr,780,270);
		
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Susceptible rate");
		cairo_stroke(cr);
		
		cairo_move_to(cr,744,310);
		cairo_show_text (cr, "30");
		//
		cairo_set_line_width (cr, 2); 
		cairo_move_to(cr,758,295);
		cairo_line_to(cr,758,305);
		cairo_move_to(cr,758,295);
		cairo_line_to(cr,763,300);
		cairo_move_to(cr,763,300);
		cairo_line_to(cr,758,305);
		cairo_move_to(cr,508,310);
		cairo_show_text (cr, "O");
		cairo_stroke(cr);
		
		// for the caption of x-axis epidemic curve
		cairo_move_to(cr,600,320);
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_show_text (cr, "Number of days:");
		cairo_stroke(cr);
		
		// The legend of the graph network 


 
		cairo_set_source_rgb (cr, 1, 1,0);
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

 // code to draw a chicken farm at different parts 

  for(unsigned int i=0;i<73;i++)
  {
  usleep(10000);
  cairo_set_source_rgba(cr, 0, 0, 0,1);
  cairo_set_line_width (cr, 0.3); 
  cairo_arc(cr, points[i][0]+10, points[i][1], 4, 0,M_PI*2);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
 // usleep(100000); 
 
 }
 
 int first_infected_node[0][N];
 
 ifstream inFile1 ("simulation.txt", ios::in);
 int buffer;
 
 for(int i=0;i<N;i++)
      {
	
	  inFile1>>first_infected_node[0][i];  
	  	   		
      }
      
       for(int i=0;i<N;i++)
      {
	
	 if(first_infected_node[0][i]==1)
	 {
	   buffer=i;
	   break;
	 }
	 
	  	   		
      }
      
      cout<<"BUFFER!!" <<buffer<<endl;
      
      
    cairo_set_source_rgba(cr, 1, 0, 0,1);  
    cairo_set_line_width (cr, 0.3);
    cairo_arc(cr, points[buffer][0]+10, points[buffer][1], 4, 0,M_PI*2);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);
      
      
 
 // code to draw the network for the disease and degree distribution
 
 
  
   cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
   cairo_set_line_width (cr, 0.2); 
   
   double points[73][2]; 
   double coordinate_storage[146];
   int cnt=0,counter=0;
   double ii=0;  
   const char *inname = "map_coordinate.txt";
   ifstream infile(inname);  
 
    while (infile >> ii) 
    {
	coordinate_storage[cnt++]=ii;
 
    }
    
   ifstream file( "map_coordinate.txt" ) ;
   string line ;
   vector<string> lines ;
   
    while( getline( file, line ) ) lines.push_back( line ) ;
   
   
    for(unsigned int j=0;j<lines.size();j++){
     for(int k=0;k<2;k++){
	points[j][k]=coordinate_storage[counter];
	counter++;
	
		}
		
	} 
	
	// code to write the adjcencies matrix in file
	ofstream outFile;
	outFile.open("graph_topology.txt"); //opening the file to store the co_ordinate of the map
	
	double distance_storage;
	int adjacency_matrix[73][73];
	for(int i=0;i<73;i++)
	{
	  for(int j=0;j<73;j++)
	  {
	    double x1,x2,y1,y2;
	    x1=points[i][0];
	    y1=points[i][1];
	    x2=points[j][0];
	    y2=points[j][1];
            distance_storage= calculate_distance(x1,y1,x2,y2);
	    if(distance_storage<=115)
	    {
	     adjacency_matrix[i][j]=1;
	     usleep(5000);
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
	
  
	
   
   
   
   
   
   
   
 

	ifstream file2( "total_degree.txt" ) ; 
	int total_degree_from_file[73];
	int highest_degree_in_file=0;
	 while (!file2.eof())
	 {
	    for(int m=0; m<73; m++)// rows number
	  {
	  file2 >>total_degree_from_file[m];
	  if (highest_degree_in_file<total_degree_from_file[m])
	  {
	  highest_degree_in_file=total_degree_from_file[m];
	      
	  }  
	  
	  }
	   
	 }
	 cout<<"Hello !!"<<endl;
	//  cout<< random_out_degree_picker<<endl;
	 
	  cout<< highest_degree_in_file<<endl;
	 
	 cairo_set_source_rgb (cr, 0, 0, 0);
	
	 char *highest_degree=new char[30];
	 sprintf(highest_degree, "%d", highest_degree_in_file);
	 cairo_move_to(cr,749,510);
	// cairo_show_text (cr, highest_degree);
	 cairo_stroke (cr);
	 
	 
	 
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
	  cout<<degree_frequency_mapper[i]<<endl;
	}
	cout<<highest_degree_frequency<<endl;
	
	 
	
	
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
	   cout<< i<<endl;
	   
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
	 
	 cairo_stroke (cr);   
	  
	
	 
	
	
// codes to demonstrate susceptible infected and recovered nodes
	 
	  
	       unsigned int simulation_time_stamp=35;
		//int j_caller=0;
		int m[simulation_time_stamp][N];//n[73];
		
		
		ifstream inFile ("simulation.txt", ios::in); //file to read the timestamp of the simulation result
				
	      for(unsigned int i=0;i<simulation_time_stamp;i++)
	      {
		for(unsigned int j=0;j<N;j++)
		
		
		inFile>>m[i][j];
	      
	      }
	
	
 

	
	
	
	
  for(unsigned int i=0;i<simulation_time_stamp;i++)
  {
	
		
        for(unsigned int j=0;j<N;j++)
        {
	  usleep(3000);
	
		 
            
                        if(m[i][j]==0 ) //0.03 is the infected probablity and shows the infection occurs 
                        {
			 
				
			  
			cairo_set_source_rgb(cr, 1, 1, 0);
			
			cairo_set_line_width (cr, 0.3);
                        cairo_arc(cr,points[j][0]+10,points[j][1],4, 0,M_PI*2);
			
			cairo_stroke_preserve(cr);
			cairo_fill(cr);
		
			
			//if(j_caller>30)
			 // break;
			
			/*else {
			 // usleep(1000); 
			cairo_set_source_rgb(cr, 1, 0, 0);
			cairo_set_line_width (cr, 0.6);
			cairo_move_to(cr,508+8*j_caller,300-m[j_caller]*2); 
			cairo_arc(cr,508+8*j_caller,300-m[j_caller]*2,1.0,0,2*M_PI);
			
			cairo_line_to(cr,508+8*(j_caller+1),300-m[j_caller+1]*2);
			cairo_stroke(cr);
			
			//usleep(10000);  
			cairo_set_source_rgb(cr, 0.5, 0, 0);
			cairo_set_line_width (cr, 0.6);
			cairo_move_to(cr,508+8*j_caller,300-n[j_caller]*2); 
			cairo_arc(cr,508+8*j_caller,300-n[j_caller]*2,1.0,0,2*M_PI);
			//cout<<508+8*j_caller<<","<<300-m[j_caller]*2<<endl;
			
			cairo_line_to(cr,508+8*(j_caller+1),300-n[j_caller+1]*2);
			 cairo_stroke(cr);
			j_caller++;
			}*/
                        }
                        
                        if(m[i][j]==1 )
			{
			
			  
			cairo_set_source_rgb(cr, 1, 0, 0);
			
			cairo_set_line_width (cr, 0.3);
                        cairo_arc(cr,points[j][0]+10,points[j][1],4, 0,M_PI*2);
			
			cairo_stroke_preserve(cr);
			cairo_fill(cr);
			  
			  	  
			  
			  
			} 
			
			 if(m[i][j]==2 )
			{
			//usleep(6000);   
			cairo_set_source_rgb(cr, 0, 1, 0);
			
			cairo_set_line_width (cr, 0.3);
                        cairo_arc(cr,points[j][0]+10,points[j][1],4, 0,M_PI*2);
			
			cairo_stroke_preserve(cr);
			cairo_fill(cr);
			  
			  	  
			  
			  
			} 
                        
                        
                                            
                }
 
}



 
 cairo_destroy(cr); 
   return 0;
 
}




void calling_epidemic_gui(){


  GtkWidget *window;
  GtkWidget *visualize;
   GtkWidget *frame;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  create_surfaces();
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1016+10, 821+10); 
  gtk_window_set_title(GTK_WINDOW(window), "epidemic visualization");
  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);
  visualize = gtk_button_new_with_label("visualize");
  gtk_widget_set_size_request(visualize, 80, 35);
  gtk_fixed_put(GTK_FIXED(frame), visualize, 600, 78);
  
  gtk_widget_set_app_paintable(window, TRUE);
  gtk_widget_show_all(window);
 
 g_signal_connect(G_OBJECT(window), "destroy",
   G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(visualize, "clicked", 
     G_CALLBACK(on_expose_event), NULL);


}

};
#endif