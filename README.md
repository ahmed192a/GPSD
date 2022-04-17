# GPS Tracking system
Tracking System using Tiva c and GPS to get the Coordinates and Save them in SD card<br>
these Coordinates can be displayed on PC using python script in the project or Google earth<br>
For More details [check the report](https://github.com/ahmed192a/GPSD/blob/master/Micro2.pdf)

## The project is implemented using the following hardware:
* Tiva-c
* NEO6 GPS Module  
* SD-card Module
* SD-card
* LCD
## Main Flow
The Tracking system gets the coordinates of the user using GPS and create file on SD-card to save them.<br>
The LCD is used to print the distance and the current coordinates in real time and alert the user when he exceeds 100 meter(100 meter is the goal).<br>
The user then can take the SD-card and insert it in any PC and easly view his Path on the map.<br>
This system creates Two files for coordinates.
- one can be viewed usign Google map API
- another one can be viewed using google earth

### Preview in Google Earth
![image](https://user-images.githubusercontent.com/42156372/163712937-9166a807-cd2d-409d-a665-5b8c12d7387c.png)
### Preview in Google Map
![image](https://user-images.githubusercontent.com/42156372/163713004-e00107d5-6e68-4eb0-8e3a-f2f54dcb5532.png)


### Contributors
