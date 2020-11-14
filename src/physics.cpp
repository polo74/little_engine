#include "physics.hpp"

#include "entity.hpp"

Physics::Physics()
{
	btVector3 worldMin(btScalar(-1000.), btScalar(-1000.), btScalar(-1000.));
	btVector3 worldMax(btScalar(1000.), btScalar(1000.), btScalar(1000.));
	btVector3 gravity(btScalar(0.), btScalar(-9.8), btScalar(0.));
	//btVector3 gravity(btScalar(0.), btScalar(9.8), btScalar(0.));

	btCollisionConfiguration * collisionConfiguration;
	btCollisionDispatcher * collisionDispatcher;
	btBroadphaseInterface * broadphaseInterface;
	btConstraintSolver * constraintSolver;
	btDiscreteDynamicsWorld * world;

	collisionConfiguration = new btDefaultCollisionConfiguration();
	collisionDispatcher = new btCollisionDispatcher(collisionConfiguration);
	broadphaseInterface = new btAxisSweep3(worldMin, worldMax);
	constraintSolver = new btSequentialImpulseConstraintSolver();
	
	/*
	btDantzigSolver* mlcp = new btDantzigSolver();
	//btSolveProjectedGaussSeidel* mlcp = new btSolveProjectedGaussSeidel;
	btMLCPSolver* sol = new btMLCPSolver(mlcp);
	constraintSolver = sol;
	*/

	world = new btDiscreteDynamicsWorld(collisionDispatcher, broadphaseInterface, constraintSolver, collisionConfiguration);

	//world->getSolverInfo().m_minimumSolverBatchSize = 128;  
	//world->getSolverInfo().m_minimumSolverBatchSize = 1;  
	//world->getSolverInfo().m_numIterations = 100;

	world->setGravity(gravity);

	this->world = world;
}

Physics::~Physics()
{
	delete world;
}
/*
const btCollisionObject * Physics::test()
{
	btConvexShape * shape = new btBoxShape( btVector3(100,10,10));

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( btVector3(0, 0, 0) );

	btTransform transform1;
	transform.setIdentity();
	transform.setOrigin( btVector3(0, 0, 0.01) );

	btCollisionWorld::ClosestConvexResultCallback callback(btVector3(0, 0, 0), btVector3(0, 0, 0));

	world->convexSweepTest(shape, transform, transform1, callback);

	return callback.m_hitCollisionObject;
}
*/
/*
const btCollisionObject * Physics::rayTest(glm::vec3 from, glm::vec3 to)
{
	btCollisionWorld::ClosestRayResultCallback callback(
			btVector3(from.x, from.y, from.z),
			btVector3(to.x, to.y, to.z)
			);

	world->rayTest(
			btVector3(from.x, from.y, from.z),
			btVector3(to.x, to.y, to.z),
			callback
		      );

	if (callback.hasHit())
	{	
		return callback.m_collisionObject;
	}
	else
	{
		return NULL;
	}
}
*/

void Physics::addRigidBody(btRigidBody * body)
{
	world->addRigidBody(body);
}

void Physics::setDebug(btIDebugDraw * debug)
{
	this->world->setDebugDrawer(debug);
}

void Physics::debugDraw()
{
	world->debugDrawWorld();
}

void Physics::removeRigidBody(btRigidBody * body)
{
	world->removeRigidBody(body);
}

void Physics::addConstrain(btTypedConstraint * constrain)
{
	world->addConstraint(constrain);
}

void Physics::removeConstrain(btTypedConstraint * constrain)
{
	world->removeConstraint(constrain);
}

void Physics::update(float step)
{
	if (world)
	{
		world->stepSimulation(step);
		world->debugDrawWorld();
/*
		int * numManifolds;
		int tmp = world->getDispatcher()->getNumManifolds();
		numManifolds = &tmp;
		for (int i = 0; i < * numManifolds -1; i++)
		{
			btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);

			const btCollisionObject * collisionA = contactManifold->getBody0();
			const btCollisionObject * collisionB = contactManifold->getBody1();

			assert (collisionA);
			assert (collisionB);

			Entity * obA = static_cast<Entity *>(collisionA->getUserPointer());
			Entity * obB = static_cast<Entity *>(collisionB->getUserPointer());

			if (obA != NULL && obB != NULL)
			{
				int firePowerA = 0;
				int firePowerB = 0;

				//obA->collision(firePowerB);
				//obB->collision(firePowerA);
			}
			* numManifolds = world->getDispatcher()->getNumManifolds();
		}
		*/
	}
}

