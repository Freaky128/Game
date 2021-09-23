#include "Spawner.h"
#include "GameC.h"

extern Manager manager;


int Spawner::activeBears = 0;

void Spawner::spawnBear()
{
	int spawnNum = 0;

	if (activeBears == 0 && (((GameC::camera.x - 150) >= 400 * SCALE) || (400 * SCALE >= (GameC::camera.x + GameC::camera.w + 150)) || ((GameC::camera.y - 150) >= 600 * SCALE) || (600 * SCALE >= (GameC::camera.y + GameC::camera.h + 150))))
	{
		spawnNum = rand() % 2;

		if (spawnNum == 1)
		{
			auto& bear(manager.addEntity());
			bear.addComponent<TransformComponent>((400 * SCALE), (600 * SCALE), 34, 22, 34, 22, SCALE); // magic numbers
			bear.addComponent<SpriteComponent>("Assets/bear_v2.png", true, "bear");
			bear.addComponent<ColliderComponent>("bear");
			bear.addComponent<AnimalBehaviour>();
			bear.addGroup(GameC::groupEnemies);

			activeBears++;
		}

	}

}