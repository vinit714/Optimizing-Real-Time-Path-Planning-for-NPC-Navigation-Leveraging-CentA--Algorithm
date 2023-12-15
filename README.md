# Optimizing Real-Time Path Planning for NPC Navigation: Leveraging CentA* Algorithm to Enhance Efficiency and Adaptability

This project introduces CentA*, an extension of the A* algorithm, for optimized NPC pathfinding in game development. Implemented in Unreal Engine 5, the algorithm enhances starting and ending node selection, improving efficiency. The system, developed with Blueprints and C++, features diverse enemy behaviors governed by a behavior tree. The balance between accuracy and efficiency in pathfinding accommodates obstacles, dynamic environments, and multiple agents. The project highlights the critical role of pathfinding algorithms in creating realistic and immersive gaming experiences. CentA* stands out as an improvement over traditional A*, offering enhanced NPC behavior and an elevated gaming experience.
 
# Introduction
AI pathfinding plays a pivotal role in game development, enabling non-player characters (NPCs) to seamlessly navigate the intricate landscapes of a virtual world. Pathfinding algorithms are instrumental in determining the most efficient route for NPCs, enhancing the realism and immersion of gameplay.
+ The project introduces the Cent A* Algorithm, a specialized version of the A* algorithm, for enhanced pathfinding.
+ Behavior Trees (BT) are employed to structure and control NPC behavior, representing a directed acyclic graph.
+ Each node in the BT signifies a specific behavior or action, with edges defining the control flow between nodes.
+ The Cent A* Algorithm is integrated into the BT framework, optimizing NPC navigation and behavior in the game world.

# Objective of the Project
+ Have a grid and good pathfinding Algorithm for our NPC AI.
+ Reload the algorithm at every frame tick of the game so we can have a dynamic and real-time path-finding algorithm.
+ Attach grid mesh with NPC with Spring arm such that grid moves along with NPC providing it extra and limited range at the same time.
+ Construct a Behaviour tree such that it acts as the brain of the AI.
+ Our Behaviour Tree should be able to encounter any type of disturbance in the way.

# Architecture
![WhatsApp Image 2023-12-15 at 19 11 21](https://github.com/vinit714/Optimizing-Real-Time-Path-Planning-for-NPC-Navigation-Leveraging-CentA--Algorithm/assets/52816788/40dc93c0-e731-43a5-bc6f-7907d08ef778)


# METHODOLOGY
In our approach to game development, pathfinding is crucial for NPC navigation. We employ a specialized algorithm that identifies the most promising start and end positions, calculated by distances falling under the A* algorithm's path. The algorithm execution optimizes NPC navigation, initiating behavior earlier than traditional A* techniques. This proactive approach integrates seamlessly, allowing diverse NPC behaviors and enhancing overall artificial intelligence interaction in the game environment.

## Innovation Idea of The Project
+ Creating a new algorithm that can work better than the existing path-finding algorithms.
+ Modified the A* algorithm by using heuristic as Euclidean distance instead of using Manhattan distance and starting the path-finding from the closest block to reaching the closest enemy block.
![image](https://github.com/vinit714/Optimizing-Real-Time-Path-Planning-for-NPC-Navigation-Leveraging-CentA--Algorithm/assets/52816788/608b144c-7225-42f3-8cea-5823a9b46779)

This algorithm is similar to the A* algorithm in finding the F-Cost value of each node. But the performance differentiates when either the Start or Target object falls under different nodes at a time as in Figure. This helps with the object that has greater areas and acts as an early behavior trigger in the pathfinding.

## Proposed Modules and their Algorithm Description
The proposed algorithm of the project can be found [here](../blob/master/Algorithm.txt)



