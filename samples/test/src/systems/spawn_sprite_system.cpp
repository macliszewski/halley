#include "systems/spawn_sprite_system.h"

#include "components/position_component.h"
#include "components/sprite_animation_component.h"
#include "components/sprite_component.h"
#include "components/time_component.h"
#include "components/velocity_component.h"

using namespace Halley;

void SpawnSpriteSystem::update(Time)
{
	auto& world = getWorld();
	auto& resources = getAPI().core->getResources();
	const int targetEntities = Debug::isDebug() ? 200 : 10000;
	const int nToSpawn = std::min(targetEntities - int(world.numEntities()), std::max(1, targetEntities / 60));
	auto anim = resources.get<Animation>("ella.yaml");
	for (int i = 0; i < nToSpawn; i++) {
		auto& r = Random::getGlobal();

		world.createEntity()
			.addComponent(new PositionComponent(Vector2f(r.getFloat(0.0f, 1280.0f), r.getFloat(0.0f, 720.0f))))
			.addComponent(new VelocityComponent(Vector2f(r.getFloat(200.0f, 300.0f), 0.0f).rotate(Angle1f::fromDegrees(r.getFloat(0.0f, 360.0f)))))
			.addComponent(new SpriteComponent())
			.addComponent(new TimeComponent(r.getFloat(0.0f, 2.0f)))
			.addComponent(new SpriteAnimationComponent(AnimationPlayer(anim, "run")));
	}
}

REGISTER_SYSTEM(SpawnSpriteSystem)
