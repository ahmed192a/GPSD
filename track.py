import gmplot
import pandas as pd
import os, sys, string

df = pd.read_csv (r'LOCAT.CSV')
lat =df['latitude'].tolist()
lon =df['longitude'].tolist()

# Create the map plotter:
gmap = gmplot.GoogleMapPlotter(lat[0], lon[0], 18, apikey="AIzaSyDTs6doYJbA3xZ16pIH1AzJKcdwkWGX-o0")

gmap.scatter(lat, lon, color='#3B0B39', size=0.2, marker=False)
gmap.plot(lat,lon,'#ff00f0',edge_width=5)

# Mark a hidden gem:
gmap.marker(lat[0], lon[0], color='cornflowerblue')
gmap.marker(lat[-1], lon[-1], color='#ff0000')

# Draw the map:
gmap.draw('map.html')
os.startfile("LOCAT.KML")
os.startfile("map.html")

