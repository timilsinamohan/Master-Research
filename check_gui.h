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

#ifndef check_gui_H
#define check_gui_H


using namespace std;
using namespace boost;
int break_point=0;
  

cairo_surface_t *image;
class check_gui
{

 
 
public: 
static gboolean on_expose_event(GtkWidget *widget,
    GdkEventExpose *event,
    gpointer data)
{
  cairo_t *cr;
 
 
  cr = gdk_cairo_create (widget->window);
   gint width, height;
  gtk_window_get_size(GTK_WINDOW(widget), &width, &height);
  
static double alpha = 1;

 image = cairo_image_surface_create_from_png("prj1.png");

 cairo_set_source_surface(cr, image, 10, 10);
 cairo_paint_with_alpha(cr, alpha);

 
double i=0;
   
 const char *inname = "map_coordinate.txt";

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
	
	double points[lines.size()][2];
	int counter=0;
      
     for(unsigned int j=0;j<lines.size();j++){
     for(int k=0;k<2;k++){
	points[j][k]=coordinate_storage[counter];
	counter++;


		}
	}

//Random Adjacency matrix creation
 int a[lines.size()][lines.size()];
 int node[lines.size()];
 
 for (unsigned int i=0;i<lines.size();i++)
  {
     node[i]=i; //storing the information of the nodes
   }

	
for(unsigned int i=0;i<lines.size();i++){
 if (break_point==0){// || break_point==3){
  
  cairo_set_source_rgb(cr, 0, 1, 0);
  cairo_set_line_width (cr, 0.3); 
  cairo_arc(cr, points[i][0]+10, points[i][1], 7, 0,M_PI*2);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
  usleep(15000);
 }

else{
break;
 }

}

  cairo_set_source_rgba(cr, 0, 0, 1, 4*0.1);
  cairo_set_line_width (cr, 0.3); 
for(unsigned int i=0;i<lines.size();i++){

        for(unsigned int j=0;j<lines.size();j++)
        {
                if (break_point==0 || break_point==3)
                { 
                        if(a[i][j]==1 )
                        {
                      
                        cairo_move_to(cr,points[i][0]+10,points[i][1]);

                        cairo_line_to(cr,points[j][0]+10,points[j][1]);
                        //cairo_stroke_preserve(cr);
                       cairo_stroke(cr);
                      
                        }
                      
                }
                else
                {
               break;
               }
                }       
usleep(200000);
}

// Epidemic curve and barchart development

  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width (cr, 2); 
  
//for Y-Axis epidemic curve

 cairo_move_to(cr,750,70);
 cairo_line_to(cr,750,250);
 cairo_move_to(cr,745,70);
 cairo_line_to(cr,755,70);
 cairo_line_to(cr,750,65);
 cairo_line_to(cr,745,70); 
// cairo_show_text (cr, "Y");
 
 //for Y-Axis barchart
 cairo_move_to(cr,750,350);
 cairo_line_to(cr,750,530);
 cairo_move_to(cr,745,350);
 cairo_line_to(cr,755,350);
 cairo_line_to(cr,750,345);
 cairo_line_to(cr,745,350);
 //cairo_show_text (cr, "Y");

 //for X-Axis epidemic curve
 cairo_move_to(cr,750,250);
 cairo_line_to(cr,1000,250);
 cairo_move_to(cr,1000,245);
 cairo_line_to(cr,1000,255);
 cairo_move_to(cr,1000,245);
 cairo_line_to(cr,1005,250);
 cairo_move_to(cr,1005,250);
 cairo_line_to(cr,1000,255);
// cairo_show_text (cr, ">");
 cairo_move_to(cr,750,260);
 cairo_show_text (cr, "O");
 
 
 //for X-Axis barchart
 cairo_move_to(cr,750,530);
 cairo_line_to(cr,1000,530);
 cairo_move_to(cr,1000,530);
 cairo_move_to(cr,1000,525);
 cairo_line_to(cr,1000,535);
 cairo_line_to(cr,1005,530);
 cairo_line_to(cr,1000,525);
// cairo_show_text (cr, "X");
 cairo_move_to(cr,750,540);
 cairo_show_text (cr, "O");
 cairo_stroke(cr);
 

// for the caption of y axis epidemic curve
  cairo_move_to(cr,610,160);
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_show_text (cr, "Infected Poultry farms");

// for the caption of y axis barchart
  cairo_move_to(cr,630,440);
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_show_text (cr, "Poultry farms");
  
// for the caption of x-axis epidemic curve
 cairo_move_to(cr,850,280);
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "Number of days");
 
// for the caption of x-axis barchart
 cairo_move_to(cr,850,560);
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "Epidemic level");
 
 
//for labeling epidemic curve x-axis
 cairo_move_to(cr,833,260);          //750+250÷3 [30 days and length of the axis is 250]
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "10");

 cairo_move_to(cr,916,260);          //833+250÷3 [30 days and length of the axis is 250]
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "20");
 
 cairo_move_to(cr,985,260);          //916+250÷3 [30 days and length of the axis is 250] a bit change for the scaling
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "30");
 
 //for labeling barchart x-axis
  cairo_move_to(cr,775,540); 
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_show_text (cr, "Tran");
  cairo_move_to(cr,832,540); 
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_show_text (cr, "Iso");
  cairo_move_to(cr,877,540); 
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_show_text (cr, "Inf");
  cairo_move_to(cr,922,540); 
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_show_text (cr, "Rec");
  cairo_move_to(cr,967,540); 
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_show_text (cr, "Des");
  
  // Legend of the graph:
 
 cairo_set_source_rgb (cr, 1, 1,0);
 cairo_arc (cr,760,570,7.0,0,2*M_PI);
 cairo_fill(cr);
 cairo_stroke(cr);
 cairo_set_source_rgb (cr, 0, 0,0);
 cairo_move_to(cr,770,580);
 cairo_show_text (cr, "Tran:=> Transmitter");
 
 
 cairo_set_source_rgb (cr, 0, 1,0);
 cairo_arc (cr,760,590,7.0,0,2*M_PI);
 cairo_fill(cr);
 cairo_stroke(cr);
  cairo_set_source_rgb (cr, 0, 0,0);
 cairo_move_to(cr,770,600);
 cairo_show_text (cr, "Iso:=> Isolated");
 
 cairo_set_source_rgb (cr, 1, 0,0);
 cairo_arc (cr,760,610,7.0,0,2*M_PI);
 cairo_fill(cr);
 cairo_stroke(cr);
 cairo_set_source_rgb (cr, 0, 0,0);
 cairo_move_to(cr,770,620);
 cairo_show_text (cr, "Inf:=> Infected");
 
 cairo_set_source_rgb (cr, 0, 1,1);
 cairo_arc (cr,760,630,7.0,0,2*M_PI);
 cairo_fill(cr);
 cairo_stroke(cr);
 cairo_set_source_rgb (cr, 0, 0,0);
 cairo_move_to(cr,770,640);
 cairo_show_text (cr, "Rec:=> Reciever");
 
 cairo_set_source_rgb (cr, 0, 0,0);
 cairo_arc (cr,760,650,7.0,0,2*M_PI);
 cairo_fill(cr);
 cairo_stroke(cr);
 cairo_set_source_rgb (cr, 0, 0,0);
 cairo_move_to(cr,770,660);
 cairo_show_text (cr, "Des:=> Destroyed");
 
 
  
// Labeling Y-axis epidemic curve
 
 cairo_move_to(cr,730,250-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "12");

 cairo_move_to(cr,730,250-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "24");

 cairo_move_to(cr,730,250-30-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "36");
 
 cairo_move_to(cr,730,250-30-30-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "48");
 
 cairo_move_to(cr,730,250-30-30-30-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "60");
 
 cairo_move_to(cr,730,250-30-30-30-30-30-20);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "72");
 
 // Labeling Y-axis barchart
 
 cairo_move_to(cr,730,530-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "12");
 
 cairo_move_to(cr,730,530-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "24");
 
 cairo_move_to(cr,730,530-30-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "36");
 
 cairo_move_to(cr,730,530-30-30-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "48");
 
 cairo_move_to(cr,730,530-30-30-30-30-30);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "60");
 
  cairo_move_to(cr,730,530-30-30-30-30-30-20);          
 cairo_set_source_rgb (cr, 0, 0, 0);
 cairo_show_text (cr, "72");
//cairo_destroy(cr); 
 
 
  break_point++;
cout<< break_point<<"\t";

 // This code is responsible for network computation and it is all about the boost library
 
  typedef adjacency_list<vecS, vecS,undirectedS, 
    
       property<vertex_degree_t,int> > Graph1;
       
    typedef adjacency_list<vecS, vecS,directedS, 
    
       property<vertex_degree_t,int> > Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    typedef graph_traits<Graph>::vertices_size_type size_type;
    typedef std::pair<std::size_t, std::size_t> Pair; 
    typedef graph_traits<Graph1>::vertex_descriptor Vertex;
    typedef graph_traits<Graph1>::vertices_size_type size_type;
    Graph g(lines.size());
    Graph1 g1(lines.size());

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
   cout<<"Out Degree calculation.............................."<<endl;
   
  for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ui++){
    deg[*ui] = out_degree(*ui, g); 
    cout<<deg[*ui]<<endl;
  }
  	 cout<<"Total Degree calculation.............................."<<endl;
  
  //graph converting to the undirected to calculate the in-degree (directed->undirected)
  
   graph_traits<Graph1>::vertex_iterator ui1, ui1_end;
   property_map<Graph1,vertex_degree_t>::type deg1 = get(vertex_degree, g1);
   for (boost::tie(ui1, ui1_end) = vertices(g1); ui1 != ui1_end; ui1++){
   deg1[*ui1]=degree(*ui1, g1);
   cout<<deg1[*ui1]<<endl; //Here we will get the total degree of the each nodes
    }
    
   //calculation of the total indegree

  cout<<"indegree calculation................"<<endl;
  for(unsigned int i=0;i<lines.size();i++)
  {
    degree_in[i]=deg1[i]-deg[i];
    cout<<degree_in[i]<<endl;  
  }

  std::cout << "vertex set: ";
  print_vertices(g, node);
  std::cout << std::endl;

  std::cout << "edge set: ";
  print_edges(g, node);
  std::cout << std::endl;
  
  std::cout << "incident edges: " << std::endl;
  print_graph(g, node);
  std::cout << std::endl;
  // counting the red nodes:
  
  int red_node_counter=0;
  int sky_blue_node_counter=0;
  int green_node_counter=0;
  int black_node_counter=0;
  int yellow_node_counter=0;
  
 
  
   for(unsigned int i=0;i<lines.size();i++){
   if(degree_in[i]==0 && deg[i]>0)
   {  //Transmitter nodes
    
     cairo_set_source_rgb (cr, 1, 1,0);
    
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
    
    
     cairo_arc (cr,points[i][0]+10,points[i][1],7.0,0,2*M_PI);//self edge looping
     yellow_node_counter++;
     cairo_fill(cr);
    
     //cairo_stroke (cr);
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
     //cairo_set_source_rgb (cr, 0, 0, 0);
     //cairo_show_text (cr, "Transmitter");
     
     cairo_stroke (cr);
     usleep(25000);
           
    }
     
    else if (degree_in[i]==0 && deg[i]==0){ //if in_degree equals to out degree is zero then node is isolated 
     // cout<<"equal node:"<<i<<endl;
     cairo_set_source_rgb (cr, 0, 1,0); 
     cairo_move_to(cr,points[i][0],points[i][1]);
     cairo_arc (cr,points[i][0]+10,points[i][1],7.0,0,2*M_PI);//self edge looping
     green_node_counter++;
     cairo_fill(cr);
      cairo_move_to(cr,points[i][0]+10,points[i][1]);
     //cairo_set_source_rgb (cr, 0, 0, 0);
    // cairo_show_text (cr, "Isolated");
     
     cairo_stroke (cr);
      usleep(25000);
     
  	  }
     
    else if(deg[i]>degree_in[i])
    { //Receiver nodes or infected nodes
     cairo_set_source_rgb (cr, 1, 0,0);
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
     cairo_arc (cr,points[i][0]+10,points[i][1],7.0,0,2*M_PI);//self edge looping
     red_node_counter++;
     cairo_fill(cr);
     
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
     //cairo_set_source_rgb (cr, 0, 0, 0);
     //cairo_show_text (cr, "Infected");
     
     cairo_stroke (cr);
      usleep(25000);
     
    
    }
	
	
    else if(degree_in[i]== deg[i])
    { //Transmitting and receiving the disease
    
     cairo_set_source_rgb (cr, 0, 1,1);
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
     cairo_arc (cr,points[i][0]+10,points[i][1],7.0,0,2*M_PI);//self edge looping
     sky_blue_node_counter++;
     cairo_fill(cr);
     
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
    //cairo_set_source_rgb (cr, 0, 0, 0);
    // cairo_show_text (cr, "Receiver");
     cairo_stroke (cr);
      usleep(25000);
    
    }
    
    else if(degree_in[i]> deg[i]) { // All dead nodes 

     cairo_set_source_rgb (cr, 0, 0,0);
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
     cairo_arc (cr,points[i][0]+10,points[i][1],7.0,0,2*M_PI);//self edge looping
     black_node_counter++;
     cairo_fill(cr);
     
     cairo_move_to(cr,points[i][0]+10,points[i][1]);
    // cairo_set_source_rgb (cr, 0, 0, 0);
    // cairo_show_text (cr, "Destroyed");
     cairo_stroke (cr);
      usleep(25000);
}
    
    }
   // Codes to draw the bar chart to demonstrate the node statistics 
  cairo_set_line_width (cr, 15); 
  cairo_set_source_rgb (cr, 1, 1,0);
  cairo_move_to(cr,790,528);
  cairo_line_to(cr,790,528-yellow_node_counter*2.5);
  cairo_stroke(cr);
 
  cairo_set_source_rgb(cr, 0, 1,0);
  cairo_move_to(cr,841,528);
  cairo_line_to(cr,841,528-green_node_counter*2.5);
   cairo_stroke(cr);
  
  cairo_set_source_rgb(cr, 1, 0,0);
  cairo_move_to(cr,884,528);
  cairo_line_to(cr,884,528-red_node_counter*2.5);
  cairo_stroke(cr);

  cairo_set_source_rgb(cr, 0, 1,1);
  cairo_move_to(cr,929,528);
  cairo_line_to(cr,929,528-sky_blue_node_counter*2.5);
  cairo_stroke(cr);
  
  cairo_set_source_rgb(cr, 0, 0,0);
  cairo_move_to(cr,980,528);
  cairo_line_to(cr,980,528-black_node_counter*2.5);
  cairo_stroke(cr);
  
  cout<<"total number of red  nodes are:"<< red_node_counter<<endl;
  char* rnc = new char[30]; 
  sprintf(rnc, "%d",red_node_counter ); 
  cairo_move_to(cr,884,528-red_node_counter*2.5-4);
  cairo_show_text (cr, rnc);
  
  
  cout<<"total number of yellow  nodes are:"<< yellow_node_counter<<endl;
  char* ync = new char[30];
  sprintf(ync, "%d",yellow_node_counter ); 
  cairo_move_to(cr,790,528-yellow_node_counter*2.5-4);
  cairo_show_text (cr, ync);
  

 
  cout<<"total number of black nodes are:"<<  black_node_counter<<endl;
  char* bnc = new char[30]; 
  sprintf(bnc, "%d", black_node_counter );
  cairo_move_to(cr,992,528-black_node_counter*2.5-4);
  cairo_show_text (cr, bnc);
  
  cout<<"total number of green nodes are:"<<  green_node_counter<<endl;
  char* gnc = new char[30]; 
  sprintf(gnc, "%d",green_node_counter ); 
  cairo_move_to(cr,841,528-green_node_counter*2.5-4);
  cairo_show_text (cr, gnc);
  
  
  cout<<"total number of sky blue nodes are:"<<  sky_blue_node_counter<<endl;
  char* snc = new char[30]; //hc= highest ceniality
  sprintf(snc, "%d",sky_blue_node_counter );
  cairo_move_to(cr,929,528-sky_blue_node_counter*2.5-4);
  cairo_show_text (cr, snc); 
  
    //Codes to draw the epidemic curve
    int r[30], min=5 ;
     for(int i=0;i<=29;i++)
     
     {
      r[i] = (rand() % (red_node_counter+1-min))+min;
     }
     
    cairo_set_line_width (cr, 0.3); 
    for(int i=0;i<=29;i++)
    {
      cairo_move_to(cr,750+8*i,250-r[i]*2.5); 
      cairo_set_source_rgb (cr, 1, 0,0);
      cairo_arc(cr,750+8*i,250-r[i]*2.5,1.0,0,2*M_PI);
      usleep(200000);
	if((i+1)>29)
	  break;
      cairo_line_to(cr,750+8*(i+1),250-r[i+1]*2.5);
      
     
      cairo_stroke_preserve(cr);
     
     
    }
    
   
    
  
 

cairo_destroy(cr); 


   return 0;
 }


void calling_epidemic_gui(){
{

  GtkWidget *window;
 // gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);



  g_signal_connect(G_OBJECT(window), "expose-event",
  G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
   G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1016+10, 821+10); 
  gtk_window_set_title(GTK_WINDOW(window), "epidemic visualization");
  
  gtk_widget_set_app_paintable(window, TRUE);
  gtk_widget_show_all(window);

 // gtk_main();

 
}
}
};
#endif
