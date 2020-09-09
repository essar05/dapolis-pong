# dapolis-pong

## Specifications

### Engine code additions:
- **Ess3D:Entity**
  - update
  - draw
		
- **Ess3D:Entity2D : Ess3D:Entity**
- **Ess3D:EntityManager**

### Game code additions:
- (Ess3D:?) **World**
  - score ? (or in gameplayscreen)
  - b2World
		
  - **Player1 : Ess3D:Entity2D**
    - b2Data
  - **Player2 : Ess3D:Entity2D**
    - b2Data
  - **Ball : Ess3D:Entity2D**
    - b2Data


### Objectives
#### Iteration 1:		
- Move Players up & down
- spawn ball with random direction
- if ball touches left wall or right wall, add 1 score to player2 or player1 respectively
- if either player reaches 5 points, he wins (best of 9)
- display score using GUI
- display background image
		
#### Iteration 2:
- smooth updates (physics interpolation)
- Animations for the players & ball
- scale bg image to window size
- play sounds on contact & point score
- add main menu screen
- create release build
