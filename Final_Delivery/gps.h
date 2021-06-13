
#ifndef GPS_H_
#define GPS_H_
#include "microconfig.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define PI 3.142857
/*******************************************************************************
 *                      Prototype Functions                                    *
 *******************************************************************************/
long double distance_g ();
void dis();
void get_distance(double arr[]);
void readGPSs(void);
void readGPSa(void);
char* itoa(int num, char* str, int base);
void float_string(float x, char c[]);
void tostring(char str[], int num);
#endif /* GPS_H_ */
