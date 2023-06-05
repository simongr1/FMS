/*
 ============================================================================
 Name        : main.c
 Author      : Simon Grimm
 Version     :
 Copyright   : Your copyright notice
 Description : A FMS Programm
 ============================================================================
 */

#include "fms.h"

int main(void) {

	Generate_Time_Table(fmsList);

	Generate_Duration_Table(fmsList);

	Generate_Distance_Table(fmsList);
}
