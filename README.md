# greenhouse
mini greenhouse

## server (cloud functions):
- [x] route to add new log entry
- [ ] route to fetch and return simplified settings (as xml for arduino)

## client (arduino):
Should control water pump, fan and servo for opening top hatch  
Should gather and send sensor data, temprature, humidity and soil moisture

- [ ] startup: fetch settings from cloud fn
- [ ] startup/continuously: check local sensors temprature, humidity, soil moisture
- [ ] continuously: (every 10min) send sensor data to firebase cloud fn
- [ ] activate pump for water
- [ ] activate fan for air flow
- [ ] activate servo for opening / closing top hatch for air flow

## client (webpage):
single page app with a few graphs showing timelines and current temprature, humidity and soil moisture

- [ ] graph for temprature
- [ ] graph for humidity
- [ ] graph for soil moisture
- [ ] show current temprature
- [ ] show current humidity
- [ ] show current soil moisture
