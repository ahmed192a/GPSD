/*
 * APP.c
 *
 *  Created on: Jun 13, 2021
 *      Author: ah132
 */

#include "APP.h"

/*******************************************************************************
 *                      Global Variables                                  *
 *******************************************************************************/
extern char latitudeResult[];
extern char longitudeResult[];
extern char AltitudeResult[];
extern double r_distance;
extern volatile unsigned char g_Interrupt_Flag ;

/*------------------------------------*/
uint16_t arrived = 0;        /*local variable clear arrived flag if reach the distenation (100 m)*/
#if SDCARDUSE
uint8_t returnStatus,sdcardType;
fileConfig_st *srcFilePtr;
#endif
#if CSV
fileConfig_st *srcFilePtr_C;
#endif

/*********************************************************************************
 * Description : Function to initialize the SD-Card
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void init_SD_Card(){
    do{
        returnStatus = SD_Init(&sdcardType);
        if(returnStatus)
        {
            if(returnStatus == SDCARD_NOT_DETECTED)
            {
                UART_sendString("\n\r SD card not detected..", u0);
            }
            else if(returnStatus == SDCARD_INIT_FAILED)
            {
                UART_sendString("\n\r Card Initialization failed..", u0);
            }
            else if(returnStatus == SDCARD_FAT_INVALID)
            {
                UART_sendString("\n\r Invalid Fat filesystem", u0);
            }
        }
        else
        {
            UART_sendString("\n\rSD Card Detected!", u0);
            break;
        }
    } while(1);
}
/*********************************************************************************
 * Description : Function to create kml and CSV files inside sd card
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void Create_files(){
    
    srcFilePtr = FILE_Open("locat.kml",WRITE,&returnStatus);
    if(srcFilePtr == 0)
    {
        UART_sendString("\n\rFile Opening Failed", u0);
    }
    else
    {
        UART_sendString("\n\rEntering begin the kml file..\n", u0);
        FILE_Putstr(srcFilePtr, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                    "<kml>\n"
                    "<Document>\n"
                    "\t<name>Placemark.kml</name>\n"
                    "\t<Style id=\"yellowPoly\">\n"
                    "\t\t<LineStyle>\n"
                    "\t\t\t<color>ff0000ff</color>\n"
                    "\t\t\t<width>6</width>\n"
                    "\t\t</LineStyle>\n"
                    "\t\t<PolyStyle>\n"
                    "\t\t\t<color>7f00ff00</color>\n"
                    "\t\t</PolyStyle>\n"
                    "\t</Style>\n"
                    "\t<Placemark>\n"
                    "\t\t<styleUrl>#yellowPoly</styleUrl>\n"
                    "\t\t<LineString>\n"
                    "\t\t\t<altitudeMode>relativeToGround</altitudeMode>\n"
                    "\t\t\t<coordinates>\n");
        FILE_PutCh(srcFilePtr, EOFF);
        UART_sendString("\n\rData saved, closing the file.\n", u0);
        FILE_Close(srcFilePtr);
    }
    delay_ms();
#if CSV
    srcFilePtr_C = FILE_Open("locat.csv",WRITE,&returnStatus);
    if(srcFilePtr_C == 0)
    {
        UART_sendString("\n\rFile Opening Failed", u0);
    }
    else
    {
        UART_sendString("\n\rEntering begin the kml file..\n", u0);
        FILE_Putstr(srcFilePtr_C, "latitude,longitude\n");
        FILE_PutCh(srcFilePtr_C, EOFF);
        UART_sendString("\n\rData saved, closing the file.\n", u0);
        FILE_Close(srcFilePtr_C);
    }
#endif
}

/*********************************************************************************
 * Description : Function to insert Longitudes, Latitudes, Altitudes data inside sd card
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void Insert_data(){
    srcFilePtr = FILE_Open("locat.kml",WRITE,&returnStatus);
    if(srcFilePtr == 0)
    {
        UART_sendString("\n\rFile Opening Failed", u0);
    }
    else
    {
        UART_sendString("\n\rEntering Data..\n", u0);
        FILE_Putstr(srcFilePtr, longitudeResult);
        FILE_PutCh(srcFilePtr, ',');
        FILE_Putstr(srcFilePtr, latitudeResult);
        FILE_PutCh(srcFilePtr, ',');
        FILE_Putstr(srcFilePtr, AltitudeResult);
        FILE_Putstr(srcFilePtr, " \n");
        FILE_PutCh(srcFilePtr, EOFF);
        UART_sendString("\n\rData saved, closing the file.\n", u0);
        FILE_Close(srcFilePtr);
    }
#if CSV
    srcFilePtr_C = FILE_Open("locat.csv",WRITE,&returnStatus);
    if(srcFilePtr_C == 0)
    {
        UART_sendString("\n\rFile Opening Failed", u0);
    }
    else
    {
        UART_sendString("\n\rEntering Data..\n", u0);
        FILE_Putstr(srcFilePtr_C, longitudeResult);
        FILE_PutCh(srcFilePtr_C, ',');
        FILE_Putstr(srcFilePtr_C, latitudeResult);
        FILE_Putstr(srcFilePtr_C, "\n");
        FILE_PutCh(srcFilePtr_C, EOFF);
        UART_sendString("\n\rData saved, closing the file.\n", u0);
        FILE_Close(srcFilePtr_C);
    }
#endif
}

/*********************************************************************************
 * Description : Function to close the files
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void close_files(){
#if SDCARDUSE
    srcFilePtr = FILE_Open("locat.kml",WRITE,&returnStatus);
    if(srcFilePtr == 0)
    {
        UART_sendString("\n\rFile Opening Failed", u0);
    }
    else
    {
        UART_sendString("\n\rEntering Data.. close kml file\n", u0);
        FILE_Putstr(srcFilePtr, "\t\t\t</coordinates>\n"
                    "\t\t\t<tesselate>1</tesselate>\n"
                    "\t\t</LineString>\n"
                    "\t</Placemark>\n"
                    "</Document>\n"
                    "</kml>\n");
        FILE_PutCh(srcFilePtr, EOFF);
        UART_sendString("\n\rData saved, closing the file.\n", u0);
        FILE_Close(srcFilePtr);
    }
#endif
}
