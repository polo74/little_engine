#include <game.hpp>

int game(int argc, char **argv)
	/**
	 * The main program
	 */
{
	Window window;
	Display display;
	Keys keys(window.getWindow());
	Debug debug;
	Physics physics;
	physics.setDebug(&debug);
	Entities entities;
	Sound sound;
	Gui gui;

	// Creating the player

	AnimatedEntity * player;
	{

		btTransform transform;
		btMotionState * motionState;
		btCollisionShape * collisionShape;
		btVector3 localInertia;
		btRigidBody * body;

		const float mass = 0.0f;
		float fallHeight = 100.f;

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0), btScalar(fallHeight), btScalar(0)));
		//transform.setOrigin(btVector3(btScalar(0), btScalar(100), btScalar(100)));

		motionState = new btDefaultMotionState(transform);
		collisionShape = new btSphereShape(btScalar(1));
		localInertia = btVector3(btScalar(0.), btScalar(0.), btScalar(0.));

		collisionShape->calculateLocalInertia(mass, localInertia);

		body = new btRigidBody(mass, motionState, collisionShape, localInertia);

		player = new AnimatedEntity(NULL, new Body(&physics, body));

		//physics.addRigidBody(body);
	}

	// Create the camera

	Camera * camera = new Camera(player);

	// Creating the ground

	{
		btTransform transform;
		btMotionState * motionState;
		btCollisionShape * collisionShape;
		btVector3 localInertia;
		btRigidBody * body;

		const double mass = 0.0f;
		const double fallHeight = 0.f;

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0), btScalar(fallHeight), btScalar(0)));

		motionState = new btDefaultMotionState(transform);
		collisionShape = new btBoxShape(btVector3 (btScalar(100), btScalar(1), btScalar(100)));
		localInertia = btVector3(btScalar(0.), btScalar(0.), btScalar(0.));

		body = new btRigidBody(mass, motionState, collisionShape, localInertia);

		Entity * entity = new Entity(new Mesh("cube"), new Body(&physics, body)) ;
		entities.add(entity);
	}

	// Creating the building

	for (int i = 0; i < 1; i++)
	{
		fprintf(stdout, "%d : ", i);
		btTransform transform;
		btMotionState * motionState;
		btCollisionShape * collisionShape;
		btVector3 localInertia;
		btRigidBody * body;

		const double mass = 10000000.0f;
		const double fallHeight = 5.f;

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0), btScalar(fallHeight), btScalar(0)));

		motionState = new btDefaultMotionState(transform);
		collisionShape = new btBoxShape(btVector3 (btScalar(10), btScalar(25), btScalar(10)));
		localInertia = btVector3(btScalar(0.), btScalar(0.), btScalar(0.));

		collisionShape->calculateLocalInertia(mass, localInertia);

		body = new btRigidBody(mass, motionState, collisionShape, localInertia);

		Entity * entity = new Entity(new Mesh("cube"), new Body(&physics, body)) ;
		entities.add(entity);
	}

	float power = 0;
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		// move depend of the keys
/*
		{
			if (Keys::forward || Keys::rearward || Keys::right || Keys::left)
				player->move(glm::vec3((Keys::left - Keys::right) * .1f, 0, (Keys::forward - Keys::rearward) * .1f));
		}
*/
		if (Keys::look_right || Keys::look_left || Keys::look_up)
		{
			player->rotate(glm::vec3(Keys::look_up * .1f, (Keys::look_left - Keys::look_right) * .1f, 0.0f));
		}

		if (Keys::fire)
		{
			power += 5 * window.getEllapsedTime();
			fprintf(stdout, "%f\n", power);
		}
		else if(power != 0)
		{
			// Drop a ball
			{
				glm::mat4 transform = player->getBody()->getTransform();

				glm::vec3 scale;
				glm::quat rotation;
				glm::vec3 position;
				glm::vec3 skew;
				glm::vec4 perspective;

				glm::decompose(transform, scale, rotation, position, skew, perspective);

				glm::vec4 start = glm::vec4(position, 1.0f);
				glm::vec4 velocity = glm::vec4(position, 1.0f);

				{
					start = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * start;
					start = glm::vec4(position, 0.0f) + (glm::toMat4(rotation) * (start - glm::vec4(position, 0.0f)));
				}

				{
					velocity = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, power)) * velocity;
					velocity = (glm::toMat4(rotation) * (velocity - glm::vec4(position, 0.0f)));
				}

				btRigidBody * body = drop(start, velocity);
				Entity * entity = new Entity(new Mesh("ball"), new Body(&physics, body)) ;
				entities.add(entity);
			}
			power = 0;
		}

		keys.update(window.getWindow());
		physics.update(window.getEllapsedTime());

		int width = window.getWidth();
		int height = window.getHeight();

		glm::mat4 view = camera->view();
		glm::mat4 projection = camera->projection();

		{
			display.clear();

			// draw the physics bullet debug
			{
				glm::mat4 model = glm::mat4(1);
				physics.debugDraw();
				debug.draw(model, view, projection);
			}

			//Draw each entity
			{
				std::vector<Entity *> tmp = * entities.getEntities();
				for (int i = 0; i < tmp.size() ; i++)
				{
					glm::mat4 model = tmp[i]->getBody()->getTransform();
					tmp[i]->getMesh()->draw(model, view, projection);
				}
			}


			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -.9f, 0));
				model = glm::scale(model, glm::vec3((1/power), .025, 1));
				glm::mat4 projection = glm::ortho(-10, 10, -10, 10);
				gui.drawBox(model, glm::mat4(1.0f), glm::mat4(1.0f), glm::vec3(1.0f - 1.0f/power, 1.0f/power, 0));
			}

			display.draw(&window);
		}
	}
	return 0;
}

btRigidBody * drop(glm::vec3 from, glm::vec3 velocity)
{
	btTransform transform;
	btMotionState * motionState;
	btCollisionShape * collisionShape;
	btVector3 localInertia;
	btRigidBody * body;

	const float mass = 80.0f;

	transform.setIdentity();
	transform.setOrigin(btVector3(btScalar(from.x), btScalar(from.y), btScalar(from.z)));

	motionState = new btDefaultMotionState(transform);
	collisionShape = new btSphereShape(btScalar(1));
	localInertia = btVector3(btScalar(0.), btScalar(0.), btScalar(0.));

	collisionShape->calculateLocalInertia(mass, localInertia);

	body = new btRigidBody(mass, motionState, collisionShape, localInertia);

	body->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));

	return body;
}
