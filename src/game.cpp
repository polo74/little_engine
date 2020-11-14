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

		const float mass = 80.0f;
		float fallHeight = 100.f;

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0), btScalar(fallHeight), btScalar(0)));

		motionState = new btDefaultMotionState(transform);
		collisionShape = new btSphereShape(btScalar(1));
		localInertia = btVector3(btScalar(0.), btScalar(0.), btScalar(0.));

		//collisionShape->calculateLocalInertia(mass, localInertia);

		body = new btRigidBody(mass, motionState, collisionShape, localInertia);

		player = new AnimatedEntity(NULL, new Body(&physics, body));

		physics.addRigidBody(body);
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

	// Drop a ball

	{
		btRigidBody * body = drop(glm::vec3(0, 100, 100), glm::vec3(0, -9, -10));
		Entity * entity = new Entity(new Mesh("ball"), new Body(&physics, body)) ;
		entities.add(entity);
	}

	while (!glfwWindowShouldClose(window.getWindow()))
	{
		// move depend of the keys

		{
			if (Keys::forward || Keys::rearward || Keys::right || Keys::left)
				player->move(glm::vec3((Keys::left - Keys::right) * .1f, 0, (Keys::forward - Keys::rearward) * .1f));
		}

		if (Keys::look_right || Keys::look_left || Keys::look_up)
		{
			player->rotate(glm::vec3(Keys::look_up * .1f, (Keys::look_left - Keys::look_right) * .1f, 0.0f));
		}

		if (Keys::fire)
		{
			btRigidBody * body = drop(glm::vec3(0, 100, 100), glm::vec3(0, 0, -10));
			Entity * entity = new Entity(new Mesh("ball"), new Body(&physics, body));
			entities.add(entity);
		}

		keys.update(window.getWindow());
		//player->update();
		//entities.update();
		physics.update(window.getEllapsedTime());

		int width = window.getWidth();
		int height = window.getHeight();

		glm::mat4 view = camera->view();
		glm::mat4 projection = camera->projection();

		display.clear();

		std::vector<Entity *> tmp = * entities.getEntities();
		for (int i = 0; i < tmp.size() ; i++)
		{
			glm::mat4 model = tmp[i]->getBody()->getTransform();
			tmp[i]->getMesh()->draw(model, view, projection);
		}

		{
			//glm::mat4 model = player->getBody()->getTransform();
			//player->getMesh()->draw(model, view, projection);
		}
		physics.debugDraw();

		glm::mat4 model = glm::mat4(1);
		debug.draw(model, view, projection);

		projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(50, 50, 0.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(.5, .5, 1));
		model = translate * scale;

		gui.draw(model, glm::mat4(1), projection, glm::vec3(255, 255.0, 0), "le test du test");

		display.draw(&window);
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

	const float mass = 10000.0f;

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
