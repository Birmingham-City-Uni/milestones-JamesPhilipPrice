# milestones-JamesPhilipPrice
milestones-JamesPhilipPrice created by GitHub Classroom
## Milestone 1: Design and planning
The two main game mechanics that the game will be built around are vision cones and visual representation of sound to simulate a 3D FPS in 2D and to bring in the need for a strategy with stealth when playing against AI. The first mechanics listed are quite similar in effect, so another game mechanic that will be added into the game is camouflage that is dependant on the player's camouflage, lighting and environment.

### Design inspirations
The inspiration for the first mechanic was Escape from Tarkov (Escape from Tarkov official page, 2017), which utilises sounds to help players locate where enemies are when they do not have the enemy in their line of sight.
The second mechanic was inspired by Metal gear solid 3: Snake eater (Metal Gear Solid 3: Snake Eater, 2004), which allows the player to change camouflage and hide in various areas of a level to change how sleathy the character is by comparing the camo to the surrounding environment.

## Update: 30/11/20
So far there is a base entity class that all entities will use, like players, enemies, containers and just about anything moveable or shootable.
So far the begginings of an enemy AI is being created, which is built off the container class, meaning that when the enemy dies the player will be able to go up to the body and loot it.
Here is an example of how a class would be based off of the Entity class:

<img src="Documentation_assets/diagrams/class.png?raw=true"/>

## Update: 10/12/20
I have done an initial code profile to get an idea of how the game's performance is and the data is shown in the screenshot bellow:
<img src="Documentation_assets/diagrams/codeProfile1.png?raw=true"/>

## Update: 05/01/21
I have implemented a basic vision cone system for the enemy AI and almost completed a ray-casting-like system for detecting if there is anything obstruction the view of the AI looking at the player
