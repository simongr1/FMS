/*
 * fms.h
 *
 *  Created on: 19.02.2022
 *      Author: lufti
 */

#ifndef FMS_H_
#define FMS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Structures*/

typedef struct Coordinate{
	double degree;
	double minute;
	double second;
}Coordinate;

typedef struct Airport{
	char icao[5];
	char iata[5];
	Coordinate latitude;
	Coordinate longtiude;
	float heightASML;
}Airport;

typedef struct Time{
	unsigned char hour;
	unsigned char minute;
}Time;

typedef struct FlightPath{
	char flightPathName[30];
	Airport *pDepartureAirport;
	Airport *pArrivalAirport;
	Time departure;
	Time arrival;
}FlightPath;

typedef struct Airplane{
	char airplaneName[30];
	char airVehicleRegistriation[10];
	FlightPath *pFlightPath;
	unsigned int cntFlightPath;
}Airplane;

typedef struct Airline{
	char airlineName[30];
	Airplane *pAirplane;
	unsigned int cntAirplane;
}Airline;

typedef struct FMS{
	Airline *pAirline;
	unsigned int cntAirline;
}FMS;

/* Arrays */

FlightPath flightPathList[3][5];
Airline airlineList[3];
Airplane airplaneList[3][1];
FMS fmsList[1];



/*Functions*/
double Calculate_Degree(Coordinate Co);
double Sin_Deg(double x);
double Cos_Deg(double x);
void Generate_Time_Table(FMS * pFMS);
void Generate_Distance_Table(FMS * pFMS);
void Generate_Duration_Table(FMS * pFMS);




#endif /* FMS_H_ */
