/*
 * fms_data.c
 *
 *  Created on: 19.02.2022
 *      Author: lufti
 */


#include "fms.h"

/*Airports*/

Airport Hamburg ={
		{"EDDH"},
		{"HAM"},
		{53, 37, 49},{9,59,18},
		11
};
Airport Berlin ={
		{"EDDB"},
		{"BER"},
		{52, 21, 44},{13,30,2},
		45.5
};
Airport Duesseldorf ={
		{"EDDL"},
		{"DUS"},
		{51,16,51},{6,45,26},
		36
};
Airport Koeln_Bonn ={
		{"EDDK"},
		{"CGN"},
		{50,51,57},{7,8,34},
		77
};
Airport Frankfurt ={
		{"EDDF"},
		{"FRA"},
		{50,1,59},{8,34,14},
		100
};
Airport Stuttgart ={
		{"EDDS"},
		{"STR"},
		{48,41,24},{9,13,19},
		360
};
Airport Muenchen ={
		{"EDDM"},
		{"MUC"},
		{48,21,14},{11,47,10},
		448
};



/*Arrays*/

//List of all flight paths each plane has
FlightPath flightPathList[3][5]={

		//Flight Paths of A380(Lufthansa)
		{
				{ {"LH 2147"},&Muenchen,&Hamburg,{11,30},{14,30} },
				{ {"LH 2147"},&Hamburg,&Frankfurt,{15,30},{16,30} },
				{ {"LH 2147"},&Frankfurt,&Muenchen, {18,30},{20,30} },
				{ {"LH 2147"},&Muenchen,&Hamburg,{20,45},{22,00}},
				{ {"LH 2147"},&Hamburg,&Muenchen,{22,30},{23,30} }
		},

		//Flight Paths of A320(EuroWings)
		{
				{{"EW 5953"},&Muenchen,&Duesseldorf,{3,00},{4,15} },
				{{"EW 5953"},&Duesseldorf,&Berlin,{8,00},{10,00} },
				{{"EW 5953"},&Berlin,&Koeln_Bonn,{10,12},{13,15} },
				{{"EW 5953"},&Koeln_Bonn,&Muenchen,{18,00},{20,30} },
				{{"EW 5953"},&Muenchen,&Duesseldorf,{21,45},{23,30} }
		},

		//Flight Paths of B747(TUIFly)
		{
				{{"X3 2174"},&Hamburg,&Stuttgart,{8,00},{10,00}},
				{{"X3 2174"},&Stuttgart,&Berlin,{10,15},{13,00} },
				{{"X3 2174"},&Berlin,&Frankfurt,{13,10},{15,00} },
				{{"X3 2174"},&Frankfurt,&Hamburg,{15,12},{17,00} },
				{{"X3 2174"},&Hamburg,&Frankfurt,{22,00},{24,00} },

		}
};

Airplane airplaneList[3][1]={
		//Lufthansa planes (there can be multiple planes but currently every airline has only one plane)
		{
				{{"A380"},{"D-AIMA"},flightPathList[0],sizeof(flightPathList[0])/sizeof(flightPathList[0][0])}
		},

		//Eurowings planes
		{
				{{"A320"},{"D-AIAB"},flightPathList[1],sizeof(flightPathList[1])/sizeof(flightPathList[1][0])}
		},

		//TUIFly planes
		{
				{{"B747"},{"D-ABCD"},flightPathList[2],sizeof(flightPathList[2])/sizeof(flightPathList[2][0])}
		}
};

//List of different airlines in this FMS
Airline airlineList[3]={

		{
				{"Lufthansa"},
				airplaneList[0],//Points to the first section of the airplane list
				sizeof(airplaneList[0])/sizeof(airplaneList[0][0])
		},
		{
				{"EuroWings"},
				airplaneList[1],
				sizeof(airplaneList[1])/sizeof(airplaneList[1][0])

		},
		{
				{"TUIFly"},
				airplaneList[2],
				sizeof(airplaneList[2])/sizeof(airplaneList[2][0])

		},
};

//List of different FMS (currently only one)
FMS fmsList[1]={

		{airlineList,sizeof(airlineList)/sizeof(airlineList[0])}
};





