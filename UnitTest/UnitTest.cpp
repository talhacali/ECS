#define BOOST_TEST_MODULE ECS_UnitTest
#include <boost/test/unit_test.hpp>
#include "ECS.h";
#include "Transform.h"
#include "Life.h"
#include "Player.h"
#include "Enemy.h"
#include "Movement.h"
#include "Render.h"


ECS::EntityComponentSystem ecs;

BOOST_AUTO_TEST_SUITE(id_tests)

BOOST_AUTO_TEST_CASE(class_id_test)
{

	ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20);
	ECS::EntityHandle eh2 = ecs.CreateEntity<Enemy>();

	BOOST_CHECK(((Player*)ecs.GetEntity<Player>(eh1.entityId))->classID == 0);
	BOOST_CHECK(((Enemy*)ecs.GetEntity<Enemy>(eh2.entityId))->classID == 1);

	ECS::ComponentHandle ch1 = ecs.CreateComponent<Transform, Player>(eh1.entityId, 1.0f, 2.0f, 3.0f);
	ECS::ComponentHandle ch2 = ecs.CreateComponent<Lifetime, Player>(eh2.entityId);

	BOOST_CHECK( ((Transform*)ecs.GetComponent<Transform>(eh1.entityId))->classID == 0 );
	BOOST_CHECK( ((Lifetime*)ecs.GetComponent<Lifetime>(eh2.entityId))->classID == 1 );

	ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20,30);
	ECS::SystemHandle sh2 = ecs.CreateSystem<Render>();

	BOOST_CHECK(((Movement*)ecs.GetSystem<Movement>(sh1.systemId))->classID == 0);
	BOOST_CHECK(((Render*)ecs.GetSystem<Render>(sh2.systemId))->classID == 1);
	
}

BOOST_AUTO_TEST_CASE(id_test)
{

	ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20);
	ECS::EntityHandle eh2 = ecs.CreateEntity<Player>("Player2",30);

	ECS::EntityID id1 = ((Player*)ecs.GetEntity<Player>(eh1.entityId))->entityID;
	ECS::EntityID id2 = ((Player*)ecs.GetEntity<Player>(eh2.entityId))->entityID;

	BOOST_CHECK(((Player*)ecs.GetEntity<Player>(eh1.entityId))->entityID == 1);
	BOOST_CHECK(((Player*)ecs.GetEntity<Player>(eh2.entityId))->entityID == 2);

	ECS::ComponentHandle ch1 = ecs.CreateComponent<Transform, Player>(eh1.entityId, 1.0f, 2.0f, 3.0f);
	ECS::ComponentHandle ch2 = ecs.CreateComponent<Transform, Player>(eh2.entityId,10.0f,20.0f,30.0f);

	BOOST_CHECK(((Transform*)ecs.GetComponent<Transform>(eh1.entityId))->componentID == 1);
	BOOST_CHECK(((Lifetime*)ecs.GetComponent<Transform>(eh2.entityId))->componentID == 2);

	ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20, 30);
	ECS::SystemHandle sh2 = ecs.CreateSystem<Movement>(100,200,300);

	BOOST_CHECK(((Movement*)ecs.GetSystem<Movement>(sh1.systemId))->systemID == 1);
	BOOST_CHECK(((Render*)ecs.GetSystem<Movement>(sh2.systemId))->systemID == 2);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(system_tests)

BOOST_AUTO_TEST_CASE(entity_register_test)
{
	ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20, 30); //id = 3

	ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20); //id = 3
	ECS::EntityHandle eh2 = ecs.CreateEntity<Player>("Player2", 30); //id = 4

	ecs.RegisterEntity<Movement>(sh1.systemId, eh1.entityId);
	ecs.RegisterEntity<Movement>(sh1.systemId, eh2.entityId);

	Movement* m = ((Movement*)ecs.GetSystem<Movement>(sh1.systemId));

	BOOST_CHECK(m->entities.at(0) == 3);
	BOOST_CHECK(m->entities.at(1) == 4);

}

BOOST_AUTO_TEST_CASE(entity_unregister_test)
{
	ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20, 30); //id = 4
	ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20); //id = 5
	ECS::EntityHandle eh2 = ecs.CreateEntity<Player>("Player2", 30);
	ecs.RegisterEntity<Movement>(sh1.systemId, eh1.entityId);
	ecs.RegisterEntity<Movement>(sh1.systemId, eh2.entityId);

	Movement* m = ((Movement*)ecs.GetSystem<Movement>(sh1.systemId));

	BOOST_CHECK(m->entities.size() == 2);
	ecs.UnregisterEntity<Movement>(sh1.systemId, eh1.entityId);
	BOOST_CHECK(m->entities.size() == 1);

	ecs.Init();

	ecs.Update(100);
}

BOOST_AUTO_TEST_CASE(entity_delete_test)
{
	ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20, 30); //id = 4

	ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20); //id = 5
	ECS::EntityHandle eh2 = ecs.CreateEntity<Player>("Player2", 30);
	
	ECS::ComponentHandle ch1 = ecs.CreateComponent<Transform, Player>(eh1.entityId, 1.0f, 2.0f, 3.0f);
	ECS::ComponentHandle ch2 = ecs.CreateComponent<Transform, Player>(eh2.entityId, 10.0f, 20.0f, 30.0f);

	ecs.RegisterEntity<Movement>(sh1.systemId, eh1.entityId);
	ecs.RegisterEntity<Movement>(sh1.systemId, eh2.entityId);

	ecs.DeleteEntity<Player, Transform, Movement>(eh1.entityId, ch1, sh1.systemId);

	Player* p1 = ((Player*)ecs.GetEntity<Player>(eh1.entityId));
	Player* p2 = ((Player*)ecs.GetEntity<Player>(eh2.entityId));

	BOOST_CHECK(p1 == nullptr);
	BOOST_CHECK(p2 != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()