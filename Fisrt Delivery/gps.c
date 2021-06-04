#include"tm4c123gh6pm.h"
#include"math.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include"stdio.h"
#include "lcd.h"
#include "gps.h"
#include "uart.h"
#include "stdbool.h"
/*******************************************************************************
 *                      GLOBAL VARIABLES                                  *
 *******************************************************************************/
volatile double r_distance = 0.0;  
char latitudeResult[10];
char longitudeResult[10];
char AltitudeResult[10];
static volatile double arr[4];
static volatile int k = 0;
static volatile int state = 0;
/*******************************************************************************
 *                      FUNCTION DECLERATION                                  *
 *******************************************************************************/
 /*********************************************************************************
  * Description : Function used to fetch values of longitude,latitude ,and altitude
  using GPGGA string
  * Arguments   : none
  * Return      : none
  *********************************************************************************/
//$GPGGA,235317.000,4003.9039,N,10512.5793,W,1,08,1.6,1577.9,M,-20.7,M,,0000*5F
//$GPGGA,105317.709,8960.0000,N,00000.0000,E,0,0,,137.0,M,13.0,M,,*4C
void readGPSa()
{
    char c0, GPSValues[100], parseValue[12][20], *token;
    double latitude = 0.0, longitude = 0.0, Altitude = 0.0 , sec = 0.0, result = 0.0, min = 0.0;
    int index = 0, deg;
    //do the following at least once
    do
    {
        c0=UART_recieveByte(u1_C);
        switch (c0)
        {
        case '$':
            state++;
            break;
        case 'G':
            state = state==1?2:state==3?4:state==4?5:0;
            break;
        case 'P':
            state = state==2?3:0;
            break;
        case 'A':
            state = state==5?6:0;
            break;
        case ',':
            if(state != 6) break;            
            c0=UART_recieveByte(u1_C); 
            // get values in GPMRC until *A
            while (c0 != '*') {
                GPSValues[index] = c0;     //Start save values we get from GPS in GPSValues
                c0=UART_recieveByte(u1_C);  
                index++;
            }
            /*cut string GPS values put it in pasreValue*/
            index = 0;
            token = strtok(GPSValues, ","); //cut until you find ","
            //walk through other tokens 
            while (token != NULL) {
                strcpy(parseValue[index], token); //copy what is in token into parseValue
                token = strtok(NULL, ",");        
                index++;
            }
            /* finishing cutting*/
            /***********************/
            // if parseValue[5] = "1" Active , or , "0" Void
            if (strcmp(parseValue[5], "1") == 0) 
            {
                state=7;
                latitude = atof(parseValue[1]);  //convert latitude value from string to float 
                longitude = atof(parseValue[3]); //convert longitude value from string to float 
                Altitude = atof(parseValue[8]);  //convert altitude value from string to float 
                /*calculate latitude*/
                deg = latitude / 100;
                min = latitude - (double)(deg * 100);   
                sec = min / 60.00;
                result = deg + sec;
                arr[k] = result;   //save the latitude reading of nth point 
                k++;
                sprintf(latitudeResult, "%f", result);  // The string "latitudeResult" is stored into buffer with its value instead of printing on stdout
                UART_sendString("\r\n\n",u0);
				UART_sendString(latitudeResult,u0);
                /* finishing calculation*/
                /***********************/
                /*calculate longitude*/
                deg = longitude / 100;
                min = longitude - (double)(deg * 100);
                sec = min / 60.00;
                result = deg + sec;
                arr[k] = result;    //save the longitude reading of nth point 
                k++;
                sprintf(longitudeResult, "%f", result); // The string "longitudeResult" is stored into buffer with its value instead of printing on stdout
                UART_sendString("\r\n",u0);
				UART_sendString(longitudeResult,u0);

                /* finishing calculation*/
                /***********************/
                //Altitude
                //float_string(Altitude, AltitudeResult);
                sprintf(AltitudeResult, "%f", Altitude);// The string "altitudeResult" is stored into buffer with its value instead of printing on stdout
                UART_sendString("\r\n",u0);
				UART_sendString(AltitudeResult,u0);

                if (k == 4) //If we collect readings of two points <latitude,longiude> 
                {
                    
                    dis(); //call dis funcation to calculate distance between those two points
                    k = 2; 
                    //swap 2nd point data to be the 1st one 
                    arr[0] = arr[2]; 
                    arr[1] = arr[3];
                }
            }
            else
            {
				UART_sendString("\n\r  Reading GPS Data\n\n\n",u0);
                state = 0;
            }
            break;
        default:
            state = 0;
            break;
        }
    } while (state != 7);
}
/*********************************************************************************
 * Description : Function used to fetch values of longitude ,and latitude using 
 GPRMC string
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
//$GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C
void readGPSs(void)
{
    char  GPSValues[100], parseValue[12][20], *token;

    double latitude = 0.0, longitude = 0.0, sec = 0.0, result = 0.0, min = 0.0;
    int index = 0, deg;
    char c1;
    //do the following at least once
    do
    {
        c1 = UART_recieveByte(u1_C);
        switch (c1)
        {
        case '$':
            state++;
            break;
        case 'G':
            state = state==1?2:0;
            break;
        case 'P':
            state = state==2?3:0;
            break;
        case 'R':
            state = state==3?4:0;
            break;
        case 'M':
            state = state==4?5:0;
            break;
        case 'C':
            state = state==5?6:0;
            break;
        case ',':
            if(state != 6) break;
            state=7;
            c1 =  UART_recieveByte(u1_C);
            // get values in GPMRC until *A
            while (c1 != '*') {
                GPSValues[index] = c1;
                c1 =  UART_recieveByte(u1_C);
                index++;
            }
            /*cut string GPS values put it in ParseValue*/
            index = 0;
            token = strtok(GPSValues, ",");//cut until you find ","
            //walk through other tokens 
            while (token != NULL) {
                strcpy(parseValue[index], token);//copy what is in token into parseValue
                token = strtok(NULL, ",");
                index++;
            }
            /* finishing calculation*/
            /***********************/
            // if SaveValue[1] = "A" Active , or , "V" Void
            if (strcmp(parseValue[1], "A") == 0) 
            {
                latitude = atof(parseValue[2]);//convert latitude value from string to float 
                longitude = atof(parseValue[4]);//convert longitude value from string to float 
                /*caluclate latitude*/
                deg = latitude / 100;
                min = latitude - (double)(deg * 100);
                sec = min / 60.00;
                result = deg + sec;
                float_string(result, latitudeResult);
                arr[k] = result;//save the latitude reading of nth point 
                k++;
                /* finishing calculation*/
                /***********************/
                /* calculate longitude*/
                deg = longitude / 100;
                min = longitude - (double)(deg * 100);
                sec = min / 60.00;
                /* finishing calculation*/
                /***********************/  
                result = deg + sec;
                float_string(result, longitudeResult);
                arr[k] = result;//save the longitude reading of nth point 
                k++;
                delay_5ms(); //time taken between each point reading 
                if (k == 4) //If we collect readings of two points <latitude,longiude> 
                {
                    dis(); //call dis funcation to calculate distance between those two points
                    k = 2;
                    //swap 2nd point data to be the 1st one 
                    arr[0] = arr[2];
                    arr[1] = arr[3];
                }
            }
            else
            {
				UART_sendString("\n\r  Reading GPS Data\n\n\n",u0);
                state = 0;
            }

            break;
        default:
            state = 0;
            break;
        }
    } while (state != 7);
}
/*********************************************************************************
 * Description : Function used to calculate total distance moved
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void dis(){
    int R=6371000; //Earth radius 
    double phy1 = arr[0]*PI/180; 
    double phy2 = arr[2]*PI/180;
    double deltaphy = (arr[2]-arr[0])*PI/180;
    double landa = (arr[3]-arr[1])*PI/180;
    double a = sin(deltaphy/2)*sin(deltaphy/2)+cos(phy1)*cos(phy2)*sin(landa/2)*sin(landa/2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R*c;
    r_distance+=d; //total distance
//when LCD is used
#if LCDUSE
    LCD_clearScreen(); //clear the LCD screen from any past data
    LCD_intgerToString(r_distance); //convert r_distance into string to be showen 
#endif
}
/*********************************************************************************
 * Description : Function used to convert degree into rad
 * Arguments   : degree
 * Return      : onedeg*degree
 *********************************************************************************/
long double torad(const long double degree)
{
    long double onedeg = (PI)/180;
    return (onedeg * degree);
}
/*********************************************************************************
 * Description : Function used to calculate total distance moved
 * Arguments   : none
 * Return      : ans
 *********************************************************************************/
long double distance_g ()
{
    //convert values into rad
    arr[0]=torad(arr[0]); 
    arr[1]=torad(arr[1]);
    arr[2]=torad(arr[2]);
    arr[3]=torad(arr[3]);
    long double dlong = arr[3]-arr[1];
    long double dlat  = arr[2]-arr[0];
    long double ans = pow(sin(dlat/2),2)+cos(arr[0])*cos(arr[2])*pow(sin(dlong/2),2);
    ans=2*asin(sqrt(ans));
    long double r = 6371;
    ans =ans*r;
    r_distance+=ans;
    return ans;
}
/*********************************************************************************
 * Description : Function used to calculate total distance moved
 * Arguments   : arr[]
 * Return      : none
 *********************************************************************************/
void get_distance(double arr[])
{
    //r_distance set it as gloable value
    double R, dlon, dlat, a, c, distance;
    // include math library
    // approximate radius of earth in km
    R = 6373.0;
    //lon2 - lon1
    dlon = (arr[3] - arr[1])*(double)(PI / 180);
    //lat2 - lat1
    dlat = (arr[2] - arr[0])*(double)(PI / 180);
    a = sin((dlat / 2) * 2 + cos(arr[0]) * cos(arr[2]) * sin(dlon / 2) * 2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    distance = R * c;
    // calculate all distance
    r_distance += distance;
    // printf("\ndist = %lf\n", r_distance);
}
/*********************************************************************************
 * Description : Function used to convert number into string
 * Arguments   : str[],num
 * Return      : none
 *********************************************************************************/
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
/*********************************************************************************
 * Description : Function used to convert float number into string
 * Arguments   : x,c[]
 * Return      : none
 *********************************************************************************/
void float_string(float x, char c[]){
    int y = (int)x;
    x=x-y;
    char tmp[10];
    tostring(tmp, y);
    y=(int)(x*100000);
    char tmp1[5];
    tostring(tmp1,y);
    strcat(tmp,".");
    strcat(tmp,tmp1);
    strcpy(c,tmp);

}
