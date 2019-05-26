*********************************
* DIG DUG in GOLD DIGGER engine *
*********************************
by Patrick Winkelholz, assignment for Programming 4 at DAE

The Gold Digger engine is a 2D SDL driven game engine that applies many design patterns
of the book "Game Programming Patterns" by Robert Nystrom. For example:

	Command 
	used for input handling, both for actual player input and AI input, 
	see Commands.h, Agents.h, DigDugAgents.h

	Component
	used for individual components, see BaseComponent.h
	
	Observer
	used to update the score display when an enemy is defeated / update the lives
	display when a player died, see Observer.h, Subject.h, DigDugObservers.h

	Singleton
	used for Manager classes such as the SceneManager and Renderer, see Singleton.h

	State
	used for specific behaviour depending on an objects state. see Entity.h, DigDugStates.h

	Game Loop / Update
	used for framerate independant code, see GoldDigger.h

One of the most unique features of the GoldDigger engine is the Entity class. 
While figuring out the general structure of the engine I noticed that i was having a lot of cases where
i needed access to different components of a gameObject within a component. My common solution was to 
save references to all the required components that get initialized once at the start. This resulted in 
many classes having a large member list of pointers to different components, which wasn't very pretty.

While working with this approach i realized a pattern. The components that referenced each other the most
were the ones defining some part of an objects behaviour. Especially Input, Controller, State, BaseBehaviour
needed references to each other a lot. Since any object usually needs exactly one of all these components i 
decided to combine them inside the Entity component, which all of it's parts (Input, Controller, State and 
behaviour) have access to. They are no longer seperate components but have been replaced by an Agent (only 
responsible for generating input for this entity (player presses buttons, AI making decisions)), a Behaviour 
(defining the behaviour specific to the kind of gameObject) and a State (defining behaviour specific to the
state the entity is currently in).
I considered many times to combine the State and Behaviour classes into one, since they essentially do the 
same thing, define how the object behaves, BUT i decided against it
If i only had object specific behaviours, i would have duplicate a lot of code, for example the enemies and
the player can both walk but without a walking state that code would have to be present in both the enemy 
behaviour and the player behaviour. 
If i Only had state specific behaviours, transitions would be a lot harder. The code to check if an enemie 
has died would need to be present in all the states he can die in. (he can die while idle, walking, 
attacking and so on). So i think the best solution is splitting the behaviour up in Object defined behaviour
(handled in Behaviour classes) and State defined behaviour (handled in State classes).

The rest of the engines design is pretty straight forward. Some very generic and reuseable game specific 
pieces of code (for example the playerInputAgent or the MoveHorizontal / Vertical Command) are part of the
engine since i think most 2D games will be able to make use of them.

Github repo link:
https://github.com/PatrickWinkelholz/Prog4Engine