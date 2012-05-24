
#include <time>
#include <stdio>
#include <stdlib>
#include <math>
#include <string.h>

#include "whihr_radproj.h"

int main( int argc, char *argv[] )
{
	printf("\n");
	if( argc != 2 )
	{
		printf("\nUsage: %s <input_filename>\n", argv[0]);
		exit(-1);
	}

	FILE *fp= fopen(argv[1],"r");
	if( !fp )
	{
		printf("Error in open %s!", argv[1]);
		exit(0);
	}

	double radlat=31.8669, radlon = 117.2578, radh=165.5;
	CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
	p->Initialized(40.0, 0, 0, 1000); 

	char sname[24],tmp[256];
	float thelon, thelat;
	double ele, az,L, x, y,dh;
	
	ele = 0;
	while(!feof(fp))
	{
		fscanf(fp,"%s %f %f", sname, &thelon, &thelat) ;
		fgets(tmp,256,fp) ;

		p->gps_to_tilt(thelon,thelat,ele, az,L,dh);
		
		x = L*sin(az*PI/180.0);
		y = L*cos(az*PI/180.0);
	
		printf("%-12s %.4f %.4f %6.2f %6.2f %d %d\n", \
			sname, thelon, thelat, az, L, \
			(int)(x+231+0.5),(int)(231-y+0.5));
	}

	delete p;

//	printf("\nRadGrid of LatLon done.\n");

	fclose(fp);
	return 0;
}

//
//===================================================== bottom line ===========
//