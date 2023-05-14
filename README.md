# Top Game 
![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)![topGameLogo.png](data%2FtopGameLogo.png)
___
- **Top Game** a top-down view type of game, where the playerCamera looks at the player from above. 
- The objective is to find a coin, whilst avoiding obstacles.
- This project utilizes the [Threepp library](https://github.com/markaren/threepp)

### Building Top Game
- To build this project it is required to install [vcpkg](https://vcpkg.io/en/getting-started.html) and use -DCMAKE_TOOLCHAIN_FILE.
- Here is an example of a -DCMAKE_TOOLCHAIN_FILE that can be added to the CMake Options: 
- `-DCMAKE_TOOLCHAIN_FILE=C:\src/vcpkg/scripts/buildsystems/vcpkg.cmake`

### The Objective Of Top Game
- In **Top Game** the objective is to try and find a coin. When the player collects the coin it will give the player some score and move to a new location.
- During the search for the coin the player will stumble upon some sharp spikes. These spikes deals damage to the player if it interacts with them.
- When the players health reaches Zero, the score, health and position of the player resets to the start values.

## Project Design
 
### There is a few elements to the game
 - Player
 - World
 - Spike
 - Coin
 - MapFileReader
 - Raycasters
 - KeyInput

#### Player
 The player consist of five files, each handles a separate part of the player. 
 Combined they take care of and make sure that the player has:
 - a Camera
 - a 3D model
 - a way for the player to move
 - a way for the camera to move with the player
 - a way to keep track and update the status of the player

Here is a [player](examples/playerModelExample.cpp)

![player.png](doc%2Fplayer.png)

#### World
 The world generates a playing field with a plane and a bunch of boxes. the position and size of these boxes gets parsed from mapWallData.txt. 
 while the world is generating it check for which quadrant the box are in and colors it accordingly. This to help the user locate their where abouts

Here is a [world visualization example](examples/worldVisualizerExample.cpp)

![world.png](doc%2Fworld.png)

#### Spike
 The spike deals damage to the player, how many and where to position them are parsed from mapSpikeData.txt.

Here is a [spike visualization example](examples/spikeVisualizerExample.cpp)

![spike.png](doc%2Fspike.png)

#### Coin
The coin gives the player points when ever it gets interacted with, which locations it can exist on are parsed from mapCoinData.txt.

Here is a [coin visualization example](examples/coinVisualizerExample.cpp)

![coin.png](doc%2Fcoin.png)

#### KeyInput 
 KeyInput record if some buttons are pressed. 
 These button presses are used by the game to let the user control the movement of the player and to let the user reset the game. 
-  *W - Move Forwards*
-  *S - Move Backwards*
-  *A - Move Left*
-  *D - Move Right*
-  *R - Resets Score, Health and Player Position*

#### Raycasters
 The raycasters checks each layer for a collision. For hitdetection with the walls the Raycaster calculatates a new force vector with the help of projection vectors. 
 For the coin and spike objects the raycaster just checks if the player contains either.

[Insert Picture of simple Projection Vector]

#### MapFileReader
 The mapFileReader is used as its name describes, to get the data for objects that gets placed in the scene using comma seperated values, *CSV*

## Some Last Notes:

### The Code
 Generally the code has been writen with the help of [Threepp examples](https://github.com/markaren/threepp/tree/master/examples) and the documentation from [three.js](https://threejs.org/)

### Known Bugs
 - If a box from the world crosses the center line of the x,y coordinate system but the box position is not either x = 0,0 or y = 0.0, then the box will just have solid color from the closest quadrant
 - The player can get partly stuck inside the wall, to get out turn very sharply away from the wall.
 - Spike damage has not been timed with the clock, such that just the mere presence of a Core i9 and RTX 4090, can make a simple touch of the spike devastating, move with caution.


