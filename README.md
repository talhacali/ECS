# ECS
ECS is an entity-component-system implementation with modern C++ (the version is C++17). It uses a custom memory manager that I developed for this project. It can be found on [here](https://github.com/talhacali/memory-allocators). ECS can be added to your games/game engines as an x64 static library.

## Memory Manager
The memory manager that is used in the ECS consists of two types of allocators: linear allocator and pool allocator. Throughout the ECS, I used pool allocator because
the size of the allocations is fixed for all objects. As it can be seen in the class diagram, EntityComponentSystem uses pool allocator for Entity, Component and System Managers; Entity,
Component, System Collections use pool allocator for Entities, Components, and Systems. Memory manager provides two options for allocating memory: using pool allocator's own function directly and receiving (void*) or using namespace's allocate template function and receiving pointer of the class that you provide to function as a template argument. In ECS, I used namespace's function because all the types are known in advance.

## Entity Component System
As can be seen in the class diagram, EntityComponentSystem class has Entity, Component, and System managers that are responsible for managing collections and communicating with other managers through EntityComponentSystem class. Collection template classes have entities, components, and systems of the same type and identified and added with their classIDs and stored with their entity/component/system ids.  

Instances of classes that are derived from entity, component, system template classes must be added to ECS by using an instance of EntityComponentSystem. Create functions return handles and these handles are used to link entities, components, and systems with each other. Handles contain class id and id.

![Figure 1: Class diagram](/ECS/ECS/classdiagram.png)

## Usage
All operations are conducted with an instance of EntityComponentSystem and creation operations return a handle. Here is a simple creation of entity, component, and systems:
```cpp
ECS::EntityComponentSystem ecs;

ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20);
ECS::EntityHandle eh2 = ecs.CreateEntity<Enemy>();

ECS::ComponentHandle ch1 = ecs.CreateComponent<Transform, Player>(eh1, 1.0f, 2.0f, 3.0f);
ECS::ComponentHandle ch2 = ecs.CreateComponent<Lifetime, Player>(eh2);

ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20,30);
ECS::SystemHandle sh2 = ecs.CreateSystem<Render>();

ecs.RegisterEntity<Movement>(sh1, eh1);
ecs.RegisterEntity<Movement>(sh1, eh2);

ecs.UnregisterEntity<Movement>(sh1, eh1);
```

I used several resources during the development for both the theoretical background of the ECS and the implementation: 
1. https://www.gamasutra.com/blogs/TobiasStein/20171122/310172/The_EntityComponentSystem__An_awesome_gamedesign_pattern_in_C_Part_1.php
2. https://savas.ca/nomad
3. https://gameprogrammingpatterns.com/component.html
4. https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/
5. https://github.com/junkdog/artemis-odb/wiki/Introduction-to-Entity-Systems
6. http://t-machine.org/index.php/2012/03/16/entity-systems-what-makes-good-components-good-entities/
