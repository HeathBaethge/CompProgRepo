import geocoder

#Forward Geocoding
print("Forward Example")
g = geocoder.osm('Waco, Tx')
print(g.latlng)
print(g.postal)
print(g.country)
print("\n")

#reverse Geocoding
print("Reverse Example")
g = geocoder.arcgis([45.15, -75.14], method='reverse')
print(g.city)
print(g.state)
print(g.country)
print("\n")

#IP Address 1
print("IP Address Example 1")
g = geocoder.ip('199.7.157.0')
print(g.ip)
print(g.postal)
print(g.latlng)
print(g.city + " " + g.state)
print("\n")

#IP Address 2
print("IP Address Example 2")
g = geocoder.ip('me')
print(g.ip)
print(g.postal)
print(g.latlng)
print(g.city + " " + g.state)
print("\n")

#House Address
print("House Address")
g = geocoder.osm("453 Booth Street, Ottawa ON")
print(g.housenumber)
print(g.postal)
print(g.street)
print(g.city)
print(g.state)
print(g.country)