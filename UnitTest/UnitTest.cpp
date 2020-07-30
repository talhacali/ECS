#define BOOST_TEST_MODULE ECS_UnitTest
#include <boost/test/unit_test.hpp>
#include "ECS.h";
#include "Transform.h"
#include "Life.h"
#include "Player.h"
#include "Enemy.h"
#include "Movement.h"
#include "Render.h"

BOOST_AUTO_TEST_SUITE(id_tests)

ECS::EntityComponentSystem ecs;

BOOST_AUTO_TEST_CASE(class_id_test)
{

	ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20);
	ECS::EntityHandle eh2 = ecs.CreateEntity<Enemy>();

	BOOST_CHECK(((Player*)ecs.GetEntity<Player>(eh1))->classID == 0);
	BOOST_CHECK(((Enemy*)ecs.GetEntity<Enemy>(eh2))->classID == 1);

	ECS::ComponentHandle ch1 = ecs.CreateComponent<Transform, Player>(eh1, 1.0f, 2.0f, 3.0f);
	ECS::ComponentHandle ch2 = ecs.CreateComponent<Lifetime, Player>(eh2);

	BOOST_CHECK( ((Transform*)ecs.GetComponent<Transform>(eh1))->classID == 0 );
	BOOST_CHECK( ((Lifetime*)ecs.GetComponent<Lifetime>(eh2))->classID == 1 );

	ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20,30);
	ECS::SystemHandle sh2 = ecs.CreateSystem<Render>();

	BOOST_CHECK(((Movement*)ecs.GetSystem<Movement>(sh1))->classID == 0);
	BOOST_CHECK(((Render*)ecs.GetSystem<Render>(sh2))->classID == 1);
	
}

BOOST_AUTO_TEST_CASE(id_test)
{

	ECS::EntityHandle eh1 = ecs.CreateEntity<Player>("player1", 20);
	ECS::EntityHandle eh2 = ecs.CreateEntity<Player>("Player2",30);

	ECS::EntityID id1 = ((Player*)ecs.GetEntity<Player>(eh1))->entityID;
	ECS::EntityID id2 = ((Player*)ecs.GetEntity<Player>(eh2))->entityID;

	BOOST_CHECK(((Player*)ecs.GetEntity<Player>(eh1))->entityID == 1);
	BOOST_CHECK(((Player*)ecs.GetEntity<Player>(eh2))->entityID == 2);

	ECS::ComponentHandle ch1 = ecs.CreateComponent<Transform, Player>(eh1, 1.0f, 2.0f, 3.0f);
	ECS::ComponentHandle ch2 = ecs.CreateComponent<Transform, Player>(eh2,10.0f,20.0f,30.0f);

	BOOST_CHECK(((Transform*)ecs.GetComponent<Transform>(eh1))->componentID == 1);
	BOOST_CHECK(((Lifetime*)ecs.GetComponent<Transform>(eh2))->componentID == 2);

	ECS::SystemHandle sh1 = ecs.CreateSystem<Movement>(10, 20, 30);
	ECS::SystemHandle sh2 = ecs.CreateSystem<Movement>(100,200,300);

	BOOST_CHECK(((Movement*)ecs.GetSystem<Movement>(sh1))->systemID == 1);
	BOOST_CHECK(((Render*)ecs.GetSystem<Movement>(sh2))->systemID == 2);

}

BOOST_AUTO_TEST_SUITE_END()
