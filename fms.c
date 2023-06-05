/*
 * fms.c
 *
 *  Created on: 19.02.2022
 *      Author: lufti
 */


#include "fms.h"

double Sin_Deg(double x)
{
	return sin((x)*M_PI/180.0);
}

double Cos_Deg(double x)
{
	return cos((x)*M_PI/180.0);
}

double Calculate_Degree(Coordinate Co){
	/*Turns lat or lon into degree*/
	double deg;
	deg = (Co.degree)+(Co.minute)/60 + (Co.second)/3600;
	return deg;

}

void Generate_Time_Table(FMS * pFMS){

	/*Initialize*/
	printf("%10s|%10s|%4s|%4s|%9s|%8s|%8s\n\n",
			"Airline","Flight No.","from","to","Departure","Arrival","Airplane");
	printf("%10s|%10s|%4s|%4s|%9s|%8s|%8s\n\n",
			"----------","----------","----","----","---------","--------","--------");

	/*
	 * After the pointer has been incremented until it reaches the end of the array,
	 * the pointer has to be reset to its starting point.
	 * Otherwise, the pointer  can't be used again.
	 * Therefore, the original starting point is saved in the following variable,
	 * and later on the pointer is reset
	 *
	 *Save original Pointer position of Airline*/
	Airline *p_airlineOriginal = pFMS->pAirline;





	for(int airlineNum=0; airlineNum<pFMS->cntAirline;airlineNum++){

		/*Save original Pointer position of Airplane*/
		Airplane *p_airplaneOriginal = pFMS->pAirline->pAirplane;

		for(int airplaneNum=0; airplaneNum < pFMS->pAirline->cntAirplane; airplaneNum++){

			/*Save original Pointer position of FlightPath*/
			FlightPath *p_filghtPathOriginal = pFMS->pAirline->pAirplane->pFlightPath;

			for(int flightPathNum=0; flightPathNum < pFMS->pAirline->pAirplane->cntFlightPath; flightPathNum++){

				/*Print time Table*/
				printf("%10s|%10s|%4s|%4s|    %02d:%02d|   %02d:%02d|%8s\n\n",
						pFMS->pAirline->airlineName,//Airline
						pFMS->pAirline->pAirplane->pFlightPath->flightPathName,//Flight No.
						pFMS->pAirline->pAirplane->pFlightPath->pDepartureAirport->iata,//from
						pFMS->pAirline->pAirplane->pFlightPath->pArrivalAirport->iata,//to
						pFMS->pAirline->pAirplane->pFlightPath->departure.hour,//Departure
						pFMS->pAirline->pAirplane->pFlightPath->departure.minute,
						pFMS->pAirline->pAirplane->pFlightPath->arrival.hour,//Arrival
						pFMS->pAirline->pAirplane->pFlightPath->arrival.minute,
						pFMS->pAirline->pAirplane->airVehicleRegistriation);//Airplane

				//go to the next FlightPath (pointer is incremented)
				pFMS->pAirline->pAirplane->pFlightPath++;
			}
			/*Reset Flight Path Pointer*/
			pFMS->pAirline->pAirplane->pFlightPath = p_filghtPathOriginal;

			//go to the next airplane (pointer is incremented)
			pFMS->pAirline->pAirplane++;


		}
		/*Reset Airplane Pointer*/
		pFMS->pAirline->pAirplane = p_airplaneOriginal;

		//go to the next airline (pointer is incremented)
		pFMS->pAirline++;


	}
	printf("\n");

	/*Reset Airline Pointer*/
	pFMS->pAirline = p_airlineOriginal;
}

void Generate_Duration_Table(FMS * pFMS){

	int durationHour;
	int durationMin;
	int totalHour;
	int totalMin;

	/*Save original Pointer position of Airline*/
	Airline *p_airlineOriginal = pFMS->pAirline;

	for(int airlineNum=0; airlineNum<pFMS->cntAirline;airlineNum++){

		/*Save original Pointer position of Airplane*/
		Airplane *p_airplaneOriginal = pFMS->pAirline->pAirplane;

		for(int airplaneNum=0; airplaneNum < pFMS->pAirline->cntAirplane; airplaneNum++){

			/*Save original pointer position of FlightPath*/
			FlightPath *p_filghtPathOriginal = pFMS->pAirline->pAirplane->pFlightPath;


			/*Initialize for every plane a new table*/
			printf("%10s|%10s|%4s|%4s|%8s\n\n",
					"Airline","Flight No.","from","to","Duration");
			printf("%10s|%10s|%4s|%4s|%8s\n\n",
					"----------","----------","----","----","--------");

			/*Reset variable*/
			totalHour=0;
			totalMin=0;

			for(int flightPathNum=0; flightPathNum < pFMS->pAirline->pAirplane->cntFlightPath; flightPathNum++){

				/*Calculate Duration*/
				durationHour = (pFMS->pAirline->pAirplane->pFlightPath->arrival.hour)-(pFMS->pAirline->pAirplane->pFlightPath->departure.hour);
				durationMin = (pFMS->pAirline->pAirplane->pFlightPath->arrival.minute)-(pFMS->pAirline->pAirplane->pFlightPath->departure.minute);

				/* Adjust for negative value of Minutes*/
				if(durationMin<0){
					//one hour is subtracted
					durationHour--;
					//the hour is transferred to the minutes
					durationMin += 60;
				}

				/*Add to total*/
				totalHour += durationHour;
				totalMin += durationMin;

				/*Print out duration table*/
				printf("%10s|%10s|%4s|%4s|  %02d:%02d\n\n",
						pFMS->pAirline->airlineName,//Airline
						pFMS->pAirline->pAirplane->pFlightPath->flightPathName,//Flight No.
						pFMS->pAirline->pAirplane->pFlightPath->pDepartureAirport->iata,//from
						pFMS->pAirline->pAirplane->pFlightPath->pArrivalAirport->iata,//to
						durationHour,//Duration
						durationMin);

				//go to the next Flightpath (pointer is incremented)
				pFMS->pAirline->pAirplane->pFlightPath++;
			}
			/*Calculate total time
			 *
			 * Check how many complete hours added up in totalMin variable
			 * int is used, because only the whole number(hours) is needed*/
			int n = totalMin/60;
			//Hours are transferred to the total
			totalHour += n;
			//the transferred hours are subtracted from the total Minutes
			totalMin -= n*60;

			printf("Total flight Time for %s %s is %02d:%02d\n\n",pFMS->pAirline->airlineName,
					pFMS->pAirline->pAirplane->airplaneName, totalHour, totalMin);

			/*Reset Flight Path Pointer*/
			pFMS->pAirline->pAirplane->pFlightPath = p_filghtPathOriginal;

			//go to the next airplane (pointer is incremented)
			pFMS->pAirline->pAirplane++;

			printf("\n");
		}
		/*Reset Airplane Pointer*/
		pFMS->pAirline->pAirplane = p_airplaneOriginal;

		/*go to the next airline (pointer is incremented)*/
		pFMS->pAirline++;
	}
	/*Reset Airline Pointer*/
	pFMS->pAirline = p_airlineOriginal;

}

void Generate_Distance_Table(FMS * pFMS){
	/*Variables*/

	/*Departure airport in degree*/
	double lat1;
	double lon1;

	/*Arrival airport in degree*/
	double lat2;
	double lon2;

	double distance;
	double totalDistance;

	/*Save original Pointer position of Airline*/
	Airline *p_airlineOriginal = pFMS->pAirline;

	/*Start of programm*/
	for(int airlineNum=0; airlineNum<pFMS->cntAirline;airlineNum++){

		/*Save original Pointer position of Airplane*/
		Airplane *p_airplaneOriginal = pFMS->pAirline->pAirplane;

		for(int airplaneNum=0; airplaneNum < pFMS->pAirline->cntAirplane; airplaneNum++){

			/*Save original pointer position of FlightPath*/
			FlightPath *p_filghtPathOriginal = pFMS->pAirline->pAirplane->pFlightPath;

			/*Initialize for every plane a new table*/
			printf("%10s|%10s|%4s|%4s|%8s\n\n",
					"Airline","Flight No.","from","to","Distance");
			printf("%10s|%10s|%4s|%4s|%8s\n\n",
					"----------","----------","----","----","--------");

			/*Reset Total*/
			totalDistance = 0;

			for(int flightPathNum=0; flightPathNum < pFMS->pAirline->pAirplane->cntFlightPath; flightPathNum++){

				/*Calculate distance*/
				lat1 = Calculate_Degree(pFMS->pAirline->pAirplane->pFlightPath->pDepartureAirport->latitude);
				lon1 = Calculate_Degree(pFMS->pAirline->pAirplane->pFlightPath->pDepartureAirport->longtiude);
				lat2 = Calculate_Degree(pFMS->pAirline->pAirplane->pFlightPath->pArrivalAirport->latitude);
				lon2 = Calculate_Degree(pFMS->pAirline->pAirplane->pFlightPath->pArrivalAirport->longtiude);

				distance = 6378.388 * acos(Sin_Deg(lat1) * Sin_Deg(lat2) + Cos_Deg(lat1) * Cos_Deg(lat2) * Cos_Deg(lon2 - lon1));

				/*Add to total distance*/
				totalDistance += distance;

				/*Print distance table*/
				printf("%10s|%10s|%4s|%4s|%7.2f\n\n",
						pFMS->pAirline->airlineName,//Airline
						pFMS->pAirline->pAirplane->pFlightPath->flightPathName,//Flight No.
						pFMS->pAirline->pAirplane->pFlightPath->pDepartureAirport->iata,//from
						pFMS->pAirline->pAirplane->pFlightPath->pArrivalAirport->iata,//to
						distance);//Distance

				//go to the next Flightpath (pointer is incremented)
				pFMS->pAirline->pAirplane->pFlightPath++;
			}
			/*Print total distance*/
			printf("Total flight distance for %s %s is %.2f\n\n",pFMS->pAirline->airlineName,
					pFMS->pAirline->pAirplane->airplaneName, totalDistance);

			/*Reset Flight Path Pointer*/
			pFMS->pAirline->pAirplane->pFlightPath = p_filghtPathOriginal;

			//go to the next airplane (pointer is incremented)
			pFMS->pAirline->pAirplane++;

			printf("\n");

		}
		/*Reset Airplane Pointer*/
		pFMS->pAirline->pAirplane = p_airplaneOriginal;

		//go to the next airline (pointer is incremented)
		pFMS->pAirline++;
	}
	/*Reset Airline Pointer*/
	pFMS->pAirline = p_airlineOriginal;

	printf("\n");





}
