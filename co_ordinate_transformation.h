
#include <stdlib.h>
#include <cairo.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cairo-svg.h> 
#include <fstream>  
#include "shapefil.h"
#ifndef co_ordinate_transformation_H
#define co_ordinate_transformation_H

using namespace std;
 
class co_ordinate_transformation{
public:
 double	x_co[146];
 double y_co[146];
 ofstream outFile; 
   

void co_ordinate(string str1){

 DBFHandle	hDBF;
    int		*panWidth, i, iRecord;
    char	szFormat[32];
    static const char *pszFilename = NULL;
    int		nWidth, nDecimals;
    int		bHeader = 0;
    int		bRaw = 0;
    int		bMultiLine = 0;
    char	szTitle[12];
    int 	cnt=0; 
    double 	f[146];
  	



 
   
   

/* -------------------------------------------------------------------- */
/*      Handle arguments.                                               */
/* -------------------------------------------------------------------- */
 /*   for( i = 1; i < argc; i++ )
    {
        if( strcmp(argv[i],"-h") == 0 )
            bHeader = 1;
        else if( strcmp(argv[i],"-r") == 0 )
            bRaw = 1;
        else if( strcmp(argv[i],"-m") == 0 )
            bMultiLine = 1;
        else
            pszFilename = argv[i];
    }
*/
// static const char *pszFilename;
   pszFilename=str1.c_str();



/* -------------------------------------------------------------------- */
/*      Display a usage message.                                        */
/* -------------------------------------------------------------------- */
    if( pszFilename == NULL )
    {
	printf( "dbfdump [-h] [-r] [-m] xbase_file\n" );
        printf( "        -h: Write header info (field descriptions)\n" );
        printf( "        -r: Write raw field info, numeric values not reformatted\n" );
        printf( "        -m: Multiline, one line per field.\n" );
	exit( 1 );
    }

/* -------------------------------------------------------------------- */
/*      Open the file.                                                  */
/* -------------------------------------------------------------------- */
    hDBF = DBFOpen( pszFilename, "rb" );
    if( hDBF == NULL )
    {
//	printf( "DBFOpen(%s,\"r\") failed.\n", argv[1] );
	exit( 2 );
    }
    
/* -------------------------------------------------------------------- */
/*	If there is no data in this file let the user know.		*/
/* -------------------------------------------------------------------- */
    if( DBFGetFieldCount(hDBF) == 0 )
    {
	printf( "There are no fields in this table!\n" );
	exit( 3 );
    }

/* -------------------------------------------------------------------- */
/*	Dump header definitions.					*/
/* -------------------------------------------------------------------- */
    if( bHeader )
    {
        for( i = 0; i < DBFGetFieldCount(hDBF); i++ )
        {
            DBFFieldType	eType;
            const char	 	*pszTypeName;

            eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );
            if( eType == FTString )
                pszTypeName = "String";
            else if( eType == FTInteger )
                pszTypeName = "Integer";
            else if( eType == FTDouble )
                pszTypeName = "Double";
            else if( eType == FTInvalid )
                pszTypeName = "Invalid";

            printf( "Field %d: Type=%s, Title=`%s', Width=%d, Decimals=%d\n",
                    i, pszTypeName, szTitle, nWidth, nDecimals );
        }
    }

/* -------------------------------------------------------------------- */
/*	Compute offsets to use when printing each of the field 		*/
/*	values. We make each field as wide as the field title+1, or 	*/
/*	the field value + 1. 						*/
/* -------------------------------------------------------------------- */
    panWidth = (int *) malloc( DBFGetFieldCount( hDBF ) * sizeof(int) );

    for( i = 0; i < DBFGetFieldCount(hDBF) && !bMultiLine; i++ )
    {
	DBFFieldType	eType;
        
	eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );
	if( unsigned (strlen(szTitle)) > unsigned( nWidth) )
	    panWidth[i] = strlen(szTitle);
	else
	    panWidth[i] = nWidth;

	if( eType == FTString )
	    sprintf( szFormat, "%%-%ds ", panWidth[i] );
	else
	    sprintf( szFormat, "%%%ds ", panWidth[i] );
	printf( szFormat, szTitle );
    }
    printf( "\n" );

/* -------------------------------------------------------------------- */
/*	Read all the records 						*/
/* -------------------------------------------------------------------- */
    for( iRecord = 0; iRecord < DBFGetRecordCount(hDBF); iRecord++ )
    {
        if( bMultiLine )
            printf( "Record: %d\n", iRecord );
        
	for( i = 0; i < DBFGetFieldCount(hDBF); i++ )
	{
            DBFFieldType	eType;
            
            eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );

            if( bMultiLine )
            {
                printf( "%s: ", szTitle );
            }
            
/* -------------------------------------------------------------------- */
/*      Print the record according to the type and formatting           */
/*      information implicit in the DBF field description.              */
/* -------------------------------------------------------------------- */
            if( !bRaw )
            {
                if( DBFIsAttributeNULL( hDBF, iRecord, i ) )
                {
                    if( eType == FTString )
                        sprintf( szFormat, "%%-%ds", nWidth );
                    else
                        sprintf( szFormat, "%%%ds", nWidth );

                    printf( szFormat, "(NULL)" );
                }
                else
                {
                    switch( eType )
                    {
                      case FTString:
                        sprintf( szFormat, "%%-%ds", nWidth );
                        printf( szFormat, 
                                DBFReadStringAttribute( hDBF, iRecord, i ) );
                        break;
                        
                      case FTInteger:
                        sprintf( szFormat, "%%%dd", nWidth );
                        printf( szFormat, 
                                DBFReadIntegerAttribute( hDBF, iRecord, i ) );
			
                        break;
                        
                      case FTDouble:
			
                        sprintf( szFormat, "%%%d.%dlf", nWidth, nDecimals );
                        printf( szFormat, 
                                DBFReadDoubleAttribute( hDBF, iRecord, i ) );
			f[cnt]=DBFReadDoubleAttribute( hDBF, iRecord, i );
			//printf( "\n" );
			//f[cnt]=DBFReadDoubleAttribute( hDBF, iRecord, i );
			cnt++;
			
			
                       
			
	
                        break;
                        
                      default:
                        break;
                    }
                }
            }


/* -------------------------------------------------------------------- */
/*      Just dump in raw form (as formatted in the file).               */
/* -------------------------------------------------------------------- */
            else
            {
                sprintf( szFormat, "%%-%ds", nWidth );
                printf( szFormat, 
                        DBFReadStringAttribute( hDBF, iRecord, i ) );
            }
		
//My code extension
//printf("%d",cnt);

/*
for(i=0;i<cnt;i++){
printf("%lf",f[i]);
printf("\n");
}*/
/* -------------------------------------------------------------------- */
/*      Write out any extra spaces required to pad out the field        */
/*      width.                                                          */
/* -------------------------------------------------------------------- */
	    if( !bMultiLine )
	    {
		sprintf( szFormat, "%%%ds", panWidth[i] - nWidth + 1 );
		printf( szFormat, "" );
	    }

            if( bMultiLine )
                printf( "\n" );

	    fflush( stdout );
	}
	printf( "\n" );
    }
	
	printf("%d",cnt);
	printf( "\n" );
	printf("%d",iRecord);
	printf( "\n" );
	
	
// code to display all the recorded co_ordinate position of the map
	for(i=0;i<cnt;i++){
	if(i%2==0)
	x_co[i]=f[i];
	
        else	
	y_co[i]=f[i];
	}

//code to store respective x and y coordintate of the cities in the map
	/*
	for(int i=0;i<cnt;i++){
	
       
	x_co[i]=f[i];
	else
	y_co[i]=f[i];	 
	}
*/
//code to use cairo graphics to draw the node points




	
    DBFClose( hDBF );

   
}

	void drawing_points()
	{


       cairo_surface_t *surface;
        cairo_surface_t *surface1; 
 
  	cairo_t *cr;
   	cairo_t *cr1;

        surface = cairo_image_surface_create_from_png ("prj1.png"); //reading the png file 
        cr = cairo_create(surface);
        int w = cairo_image_surface_get_width (surface);
        int h = cairo_image_surface_get_height (surface); 
        cout<<w<<"\t"<<h<<endl;
   
      surface1 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h); //this is for the surface without background
    cr1 = cairo_create(surface1);
	ofstream outFile;
	outFile.open("map_coordinate.txt"); //opening the file to store the co_ordinate of the map
	
	 if (outFile.fail())          // Check for file creation and return error.
   	{
      	cout << "Error opening \"map_coordinate.txt\" for output.\n";

      	 }
 	
	int k;
    for(k=0;k<73;k++){
      outFile<< x_co[k*2]<<"\t"<<821-y_co[k*2+1]<<endl;
	}
	 outFile.close(); //closes the file
        int m;
    for(m=0;m<73;m++){
      cout<<"x_co:"<<x_co[m*2] <<"\t"<<"y_co:"<<821-y_co[m*2+1]<<"\n";
	}

     cairo_set_source_rgb (cr, 1, 0, 0);
      cairo_arc (cr,x_co[2*k],821-y_co[2*k+1],5,0,2*M_PI);
      cairo_fill(cr); 
      cairo_stroke (cr);

      cairo_set_source_rgb (cr1, 1, 0, 0);
      cairo_arc (cr1,x_co[2*k],821-y_co[2*k+1],2,0,2*M_PI);
      cairo_fill(cr1); 
      cairo_stroke (cr1);		 
	
 


 cairo_surface_write_to_png(surface, "thai_img.png"); //Display the read file 
 
 cairo_surface_destroy (surface);
 cairo_destroy(cr);  
 
 cairo_surface_write_to_png(surface1, "thai_img1.png"); 
 cairo_surface_destroy (surface1);
 cairo_destroy(cr1);   


}

};
#endif
