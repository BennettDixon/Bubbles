
# Bubbles the Robotic Bartender

Bubbles was a personal project of mine during my gap year between high school and Holberton. It operates with a belt, two stepper motors, and optical spirits. Moves a cup along the belt, to the correct spirit, and moves the dispenser up to ultimately trigger the optic, dispensing the shot. Google search "robot bartender" for similar results to mine. Picture hopefully coming soon. 


## Goals

- Create Raspberry pi webserver that allows IOT connectivity
- Create web app / Xamarin app for iOS/Android to connect w/ bubbles
- Refactor code and functions now that I have a better understanding of C
- Implement serial interface between motor and pumps script. Currently only works as standalone motors or pumps script.


## Files
|                |Use                        |Implementation                         |
|----------------|-------------------------------|-----------------------------|
|`bubblesPumps.ino`|Controls large-pumps and perlistic-pumps via relays in bursts for accurate dosing|Always searching for a serial write from the mother arduino running `bubblesMotors.ino` telling it what pump to pump and how many mL. Accomplishes this by doing math based on pump type from experiements I did testing my large and perlistic pumps.|
|`bubblesMotors.ino`|Controls position of cup along belt (x-axis) as well as dispenser motor (y-axis).            |Controls a stepper motor connected to a stepper belt. Once it reaches an optic dispenses with other stepper motor NEED TO IMPLEMENT: unless pump optic. If it is pump optic it will send a serial command to child arduino running `bubblesPumps.ino`.|
