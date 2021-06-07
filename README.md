# General

I have a well for my house water source. The well uses a mechanical pressure switch to turn the well on and off. 
Eventualy this switch starts to stick in the off or on position (normally off) and when that happens you have to hit it to reset it. 

# COTS Solid State Relay Control

I could only find one solid state relay based controller, and its very expensive, I paid $180 US. It constantly
goes into an error state that the manufacturer tells me is an 'power error' which doesnt make sense because reseting 
it makes it all work and it doesn't reset itself. Also it has fixed settings for how long the pump can run before it 
shuts itself off to prevent damage and during a full water cycle that time is too short.

# My Solution

*  WEMOS D1 Lite
*  Solid State Relay (Single Phase 120 V in my case)
*  Cheaper Preassure Sensor from Amazon (0v-5v for 0-100 PSI)
*  A resistor to increase the voltage divider on A0 of the WEMOS D1 Lite
*  I2C LCD Display for status

# WORK IN PROGRESS

Currently testing the Unit with hard coded pressure min/max and max runtime and cool downtimes for the pump.

# Futures:
*  User programmable Pressure and Time Parameters directly on WEMOS at run time.
