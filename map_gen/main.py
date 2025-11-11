import os
import math
import requests
from concurrent.futures import ThreadPoolExecutor

# Configuration - Customize these!
min_lat = 42.385353   # Minimum latitude (bottom)
max_lat = 42.397196   # Maximum latitude (top)
min_lon = -72.538261  # Minimum longitude (left)
max_lon = -72.521675  # Maximum longitude (right)
min_zoom = 17    # Min zoom level (broad view)
max_zoom = 17    # Max zoom level (detailed)
tile_server = "https://tile.openstreetmap.org/{z}/{x}/{y}.png"  # OSM server

# Functions to convert lat/lon to tile numbers
def deg2num(lat_deg, lon_deg, zoom):
    lat_rad = math.radians(lat_deg)
    n = 2.0 ** zoom
    xtile = int((lon_deg + 180.0) / 360.0 * n)
    ytile = int((1.0 - math.asinh(math.tan(lat_rad)) / math.pi) / 2.0 * n)
    return xtile, ytile

# Download a single tile
def download_tile(z, x, y):
    url = tile_server.format(z=z, x=x, y=y)
    path = f"tiles/{z}/{x}/{y}.png"
    os.makedirs(os.path.dirname(path), exist_ok=True)
    if os.path.exists(path):
        print(f"Tile {z}/{x}/{y} already exists.")
        return
    try:
        response = requests.get(url, headers={"User-Agent": "OfflineMapDownloader/1.0"})
        if response.status_code == 200:
            with open(path, 'wb') as f:
                f.write(response.content)
            print(f"Downloaded {z}/{x}/{y}")
        else:
            print(f"Failed {z}/{x}/{y}: {response.status_code}")
    except Exception as e:
        print(f"Error downloading {z}/{x}/{y}: {e}")

# Get all tiles for the area
tiles = []
for zoom in range(min_zoom, max_zoom + 1):
    min_x, min_y = deg2num(max_lat, min_lon, zoom)
    max_x, max_y = deg2num(min_lat, max_lon, zoom)
    for x in range(min_x, max_x + 1):
        for y in range(min_y, max_y + 1):
            tiles.append((zoom, x, y))

# Download in parallel (faster)
with ThreadPoolExecutor(max_workers=10) as executor:
    executor.map(lambda args: download_tile(*args), tiles)

print("Download complete! Upload 'tiles' folder to your server.")