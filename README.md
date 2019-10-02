# Graphics : Assignment 2
### Assphalt : Plane version

## About
This game has been developed to emulate a fighter plane. The plane flies across the vast sea, as it shoots down enemies with bombs and missiles.

---
## Run the game 
Execute following commands inside of the ```build``` folder.

```
cmake ..
make all
./assphalt
```

---
## Controls 

*Views*

Keys  | Functions
------------- | -------------
F | Follow Cam View. Default. Camera sits on top of the plane and follows the movement of the plane. |
H  | Switches to Helicopter View. Movement of mouse causes camera to rotate around the camera. | 
P  | Gives the first person view of the plane, of how the plane sees the world. |
T | Tower view. View of the plane as viewed by a person at the same height as the plane. |
U | Top view. The plane as viewed from above. |

*Gameplay*

Keys  | Functions
------------- | -------------
A | Rotates plane to the left, about Y - Axis |
D  | Rotates plane to the right, about Y - Axis | 
Q  | Rotates counter-clockwise, as looked from Z - Axis | 
E  | Rotates clockwise, as looked from Z - Axis | 
S  | Go back | 
L  | Pitches plane | 
B  | Pitches plane | 
Left Click  | Shoots missile | 
Right Click  | Drops bombs. Limited number of bombs are available. | 
Space  | Rise in altitude | 
Down Key  | Decrease in altitude | 

---

## Files

List of files changed to make the game, and their functions.

Filename  | Code contained
------------- | -------------
ball.cpp  | All primitive objects constructed by ball.cpp |
ball.h  | Header file for ball.cpp |
ball.cpp  | All primitive objects constructed by ball.cpp |
bomb.h  | Header file for most primitive objects |
bomb.cpp  | Code for primitive objects construction |
camview.cpp  | Changes view on keypress |
config.h  | Contains variables to be accessed by all files. |
functions.h  | Header file for all functions used throughout the files |
ground.cpp  | Contains code to create the sea |
ground.h  | Header file for ground.cpp |
handleinput.cpp  | Handles all input given through the keyboard, and calls appropriate functions |
main.cpp  | Main file containing code that starts the game |
obstacles.cpp  | Class for obstacles |
obstacles.h  | Header file for obstacles.cpp |
obstacleFunctions.cpp  | Helper functions that aid in construction of the obstacles. |
plane.cpp  | Plane constructor code |
plane.h  | Header file for plane.cpp |
planeFunctions.cpp  | Helper file, which aids in constructing the plane piece by piece, using primitives like cylinder, cone, triangles etc. |






