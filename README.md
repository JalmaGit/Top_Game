# Top_Game
 This project is named Top_Game and it's a top-down view type of game where the camera looks at the player from above. 
 The project utilises the [Threepp library](https://github.com/markaren/threepp). Currently it's just in a demo stage with no actuall content with focus on getting the game to just work.
 
## There is two elements to the game
 - The Player
 - WorldGen

### The Player
 - The Player has some stuff attached to it
 *A camera*
 *An stl-file*
 *A shadowBox*
 *Keylistner*
 
 The player is shown with the help of an stl-modell that has been importeted with the help of the STL-loader example found in threepp.
 From the STL-loader there has been loaded a shadowBox that acts as a collision modell and is used to check for if the player thouches an object on the map.
 The player is set up so that it can move in the **X**- and **Y**-axis. 
 This means that the program uppdates the position of the camera, stl-file and shadowBox when asked to do so.
 The keybindings that has been set up with the Keylistner is:
 
 *W - Move Uppwards*
 *S - Move Downwards*
 *A - Move Left*
 *D - Move Right*
 
 
 ### WorldGen
 - Then the world is created. The world consists of:
 *plane*
 *worldBorder*
 *box/Boxes*

The **plane** is used as the floor of the map and has static picture from Andenes, Picture taken from [norgeibilde.no.](https://www.norgeibilder.no/)
The size of the plane is the size of the picture which is 1195x1739 pixels.
The **worldBorder** is set right outside of the planes dimensions.
There is also placed a box close to the centre of the map.
both the box and the border has been given hitboxes so that they can interact with the player

### Top_Game Game
The game is currently desigend so that the player can move around it and explore. If the shadowbox finds itself in the same cordinates as
either the box or the worldBorder, its posititon is reset to a previous postition where it was not in the same cordinates as the box/worldBorder.
The player is only moved after every move and check by the shadowBox and will not move if the shadowBox intersected with the box/worldBorder.

### The Code
Currently most of the code has just been done through the main.cpp file. It was just recenetly that the world has been started programmed by making it an Object called WorldGen. The WorldGen Object currently only contains the worldBorder. Some of the most utilized functions like the Box creation and Plane creation has been moved into their own cpp file, where they get defined with the help of a header file. There is a struct for the keyListner that is used to detect when a key is pressed and returns a boolean value.


### The future:
- Continue to make the worldGen object so it can be used for the creation of the world, and maybe make it possible to add more box objects with a mouseListner.
- Make a player Class that takes care of the player.
- Move the logic off the main.cpp file.
