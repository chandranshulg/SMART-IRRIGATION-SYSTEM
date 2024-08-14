import time
import random
from flask import Flask, render_template, jsonify
import requests

app = Flask(__name__)

# Mock data for soil moisture sensors (percentage) and plant types
soil_moisture = {
    'zone_1': random.uniform(30, 70),
    'zone_2': random.uniform(30, 70),
    'zone_3': random.uniform(30, 70)
}

plant_types = {
    'zone_1': 'Cactus',
    'zone_2': 'Tomatoes',
    'zone_3': 'Lawn'
}

# Weather API endpoint and API key (replace 'your_api_key' with a real one)
WEATHER_API_URL = "http://api.weatherapi.com/v1/forecast.json"
API_KEY = "your_api_key"
location = "New York"

# Water usage tracking
water_usage = {
    'total_usage': 0,
    'zone_usage': {
        'zone_1': 0,
        'zone_2': 0,
        'zone_3': 0
    }
}

def get_weather_forecast():
    """Fetch the weather forecast."""
    try:
        response = requests.get(f"{WEATHER_API_URL}?key={API_KEY}&q={location}&days=1")
        weather_data = response.json()
        forecast = weather_data['forecast']['forecastday'][0]['day']['daily_chance_of_rain']
        return forecast
    except:
        print("Failed to fetch weather data.")
        return 0

def check_soil_moisture(zone):
    """Check the soil moisture level in a given zone."""
    moisture = soil_moisture[zone]
    if moisture < 40:
        return "LOW"
    elif moisture > 60:
        return "HIGH"
    else:
        return "NORMAL"

def adjust_watering_based_on_plant(plant_type):
    """Adjust watering duration based on plant type."""
    if plant_type == "Cactus":
        return 1  # 1 minute
    elif plant_type == "Tomatoes":
        return 5  # 5 minutes
    elif plant_type == "Lawn":
        return 10  # 10 minutes

def control_irrigation(zone):
    """Control the irrigation for a specific zone."""
    moisture_status = check_soil_moisture(zone)
    if moisture_status == "LOW":
        watering_duration = adjust_watering_based_on_plant(plant_types[zone])
        water_usage['total_usage'] += watering_duration * 10  # Assume 10 liters/minute
        water_usage['zone_usage'][zone] += watering_duration * 10
        print(f"Zone {zone}: Watering for {watering_duration} minutes.")
    elif moisture_status == "HIGH":
        print(f"Zone {zone}: Soil moisture is high. No watering needed.")
    else:
        print(f"Zone {zone}: Soil moisture is normal. Monitoring continues.")

def smart_irrigation_control():
    """Main control function for smart irrigation system."""
    forecast_chance_of_rain = get_weather_forecast()
    if forecast_chance_of_rain > 50:
        print("High chance of rain. Postponing irrigation.")
    else:
        for zone in soil_moisture.keys():
            control_irrigation(zone)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def get_data():
    global soil_moisture, water_usage
    return jsonify({
        'soil_moisture': soil_moisture,
        'water_usage': water_usage,
    })

HTML_TEMPLATE = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Irrigation System Dashboard</title>
    <style>
        body {{
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f4f4f4;
            color: #333;
        }}
        header {{
            background-color: #4CAF50;
            color: white;
            padding: 20px;
            text-align: center;
        }}
        section {{
            margin: 20px;
            padding: 20px;
            background-color: white;
            border-radius: 5px;
        }}
        h2 {{
            color: #4CAF50;
        }}
        .data-box {{
            display: flex;
            justify-content: space-around;
        }}
        .data-item {{
            text-align: center;
            width: 30%;
            padding: 10px;
            background-color: #e0f7fa;
            border-radius: 10px;
        }}
        footer {{
            text-align: center;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            position: fixed;
            bottom: 0;
            width: 100%;
        }}
    </style>
</head>
<body>
    <header>
        <h1>Smart Irrigation System Dashboard</h1>
        <p>Real-time monitoring and control</p>
    </header>

    <section>
        <h2>Current Status</h2>
        <div class="data-box">
            <div class="data-item">
                <h3>Zone 1 Soil Moisture (%)</h3>
                <p id="zone_1_moisture">0</p>
            </div>
            <div class="data-item">
                <h3>Zone 2 Soil Moisture (%)</h3>
                <p id="zone_2_moisture">0</p>
            </div>
            <div class="data-item">
                <h3>Zone 3 Soil Moisture (%)</h3>
                <p id="zone_3_moisture">0</p>
            </div>
        </div>
    </section>

    <section>
        <h2>Water Usage</h2>
        <div class="data-box">
            <div class="data-item">
                <h3>Total Usage (liters)</h3>
                <p id="total_usage">0</p>
            </div>
            <div class="data-item">
                <h3>Zone 1 Usage (liters)</h3>
                <p id="zone_1_usage">0</p>
            </div>
            <div class="data-item">
                <h3>Zone 2 Usage (liters)</h3>
                <p id="zone_2_usage">0</p>
            </div>
            <div class="data-item">
                <h3>Zone 3 Usage (liters)</h3>
                <p id="zone_3_usage">0</p>
            </div>
        </div>
    </section>

    <footer>
        <p>&copy; 2024 Smart Irrigation System</p>
    </footer>

    <script>
        function fetchData() {{
            fetch('/data')
                .then(response => response.json())
                .then(data => {{
                    document.getElementById('zone_1_moisture').innerText = data.soil_moisture.zone_1.toFixed(2);
                    document.getElementById('zone_2_moisture').innerText = data.soil_moisture.zone_2.toFixed(2);
                    document.getElementById('zone_3_moisture').innerText = data.soil_moisture.zone_3.toFixed(2);
                    document.getElementById('total_usage').innerText = data.water_usage.total_usage.toFixed(2);
                    document.getElementById('zone_1_usage').innerText = data.water_usage.zone_usage.zone_1.toFixed(2);
                    document.getElementById('zone_2_usage').innerText = data.water_usage.zone_usage.zone_2.toFixed(2);
                    document.getElementById('zone_3_usage').innerText = data.water_usage.zone_usage.zone_3.toFixed(2);
                }});
        }}
        setInterval(fetchData, 1000);  // Fetch data every second
    </script>
</body>
</html>
"""

# Save the HTML template
with open('templates/index.html', 'w') as f:
    f.write(HTML_TEMPLATE)

if __name__ == '__main__':
    print("Starting Smart Irrigation System...")
    
    # Simulate the system running every minute
    while True:
        smart_irrigation_control()
        time.sleep(60)  # Wait for 1 minute before the next update
        
        # For Flask, run the app only if script is executed directly
        app.run(debug=True)
