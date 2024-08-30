# Smart Irrigation System

This application is a smart irrigation system built using Flask, designed to monitor soil moisture levels and adjust watering schedules based on real-time data and weather forecasts. The system optimizes water usage while ensuring that different plant types receive the appropriate amount of water.

## Overview

The Smart Irrigation System application monitors soil moisture levels across different zones in a garden or farm. It also checks weather forecasts to decide whether irrigation should be postponed due to an expected rain. The system automatically adjusts the watering duration based on the plant type in each zone and tracks water usage to ensure efficient water management.

## Features

- **Real-Time Monitoring:** Monitors soil moisture levels in multiple zones and displays the data on a dashboard.
- **Weather Integration:** Fetches weather forecasts to avoid unnecessary watering when rain is expected.
- **Plant-Specific Watering:** Adjusts watering duration based on the type of plants in each zone (e.g., Cactus, Tomatoes, Lawn).
- **Water Usage Tracking:** Tracks total water usage and usage per zone, helping to manage water resources effectively.
- **Simulated Data:** Uses randomly generated data to simulate real-world sensor readings.

## How to Use

1. Clone the repository or download the code.
2. Install Flask and other dependencies:
    ```bash
    pip install Flask requests
    ```
3. Replace the placeholder `"your_api_key"` in the code with your actual Weather API key.
4. Run the application:
    ```bash
    python app.py
    ```
5. Open your web browser and go to `http://127.0.0.1:5000/` to access the dashboard.
6. The dashboard will automatically update with real-time soil moisture data and water usage statistics.

## Technologies Used

- **Flask:** A lightweight Python web framework for building the web server.
- **Requests:** A Python library used to make HTTP requests to the Weather API.
- **HTML5 & CSS3:** For structuring and styling the dashboard interface.
- **JavaScript:** For fetching and updating the dashboard with real-time data.

## Future Enhancements

- **User Interface:** Improve the user interface to provide more detailed data visualizations.
- **Advanced Controls:** Allow users to manually control irrigation settings or override automated decisions.
- **Historical Data:** Store and display historical soil moisture and water usage data for analysis.

## License

This project is open-source and available under the MIT License. Feel free to use, modify, and distribute as needed.

## Author

Created by Chandranshu.
