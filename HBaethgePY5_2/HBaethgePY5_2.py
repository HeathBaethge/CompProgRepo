import folium
import webbrowser

map1 = folium.Map(location=[35.7, 139.768], zoom_start=10)

folium.CircleMarker(location=[35.7, 139.768], radius=150, popup="Tokyo").add_to(map1)

folium.Marker([35.7, 139.768]).add_to(map1)
folium.Marker([35.67, 139.694], popup="Shibuya").add_to(map1)

folium.PolyLine(locations=[(35.7, 139.768), (35.67, 139.694)], line_opacity=.6).add_to(map1)

#save the map with changes that were made
map1.save("Tokyo.html")

#open in browser
webbrowser.open("Tokyo.html")