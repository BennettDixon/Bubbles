
# Bubbles the Robotic Bartender

Bubbles was a personal project of mine during my gap year between high school and Holberton. It operates with a belt, two stepper motors, and optical spirits. Moves a cup along the belt, to the correct spirit, and moves the dispenser up to ultimately trigger the optic, dispensing the shot. Google search "robot bartender" for similar results to mine. Picture hopefully coming soon. 


## Goals

- Create Raspberry pi webserver that allows IOT connectivity
- Create web app / Xamarin app for iOS/Android to connect w/ bubbles
- Refactor code and functions now that I have a better understanding of C


## Files
|                |Use                        |Implementation                         |
|----------------|-------------------------------|-----------------------------|
|`bubblesPumps.ino`|Controls large-pumps and perlistic-pumps via relays|Always searching from a serial write from the mother arduino running `bubblesMotors.ino` telling it when to pump and for how long|
|`bubblesMotors.ino`|Controls position of cup along belt.            |Controls a stepper motor connected to a stepper belt, must do some testing to find proper optic step places (automate in future)| 
