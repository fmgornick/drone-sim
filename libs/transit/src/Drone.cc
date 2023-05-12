#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }

  if (nearestEntity) {
    nearestEntity->SetAvailability(
        false);  // set availability to the nearest entity
    available = false;
    pickedUp = false;
    destination = nearestEntity->GetPosition();
    std::string robotStrategyName = nearestEntity->GetStrategyName();
    toRobot = new BeelineStrategy(this->position, this->destination);
    if (robotStrategyName.compare("astar") == 0) {
      toFinalDestination = new AstarStrategy(
          nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
    } else if (robotStrategyName.compare("dfs") == 0) {
      toFinalDestination = new DfsStrategy(
          nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
    } else if (robotStrategyName.compare("dijkstra") == 0) {
      toFinalDestination = new DijkstraStrategy(
          nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
    }
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  if (available) {
    GetNearestEntity(scheduler);
  }

  if (nearestEntity) {
    if (toRobot) {  // Got to robot
      if (toRobot->IsCompleted() == false) {
        toRobot->Move(this, dt);
      } else {
        toRobot = NULL;
      }
    } else if (toFinalDestination) {  // Pick up robot and go to the final
                                      // destination
      if (toFinalDestination->IsCompleted() == false) {
        toFinalDestination->Move(this, dt);

        // Moving robot
        nearestEntity->SetPosition(this->position);
        nearestEntity->SetDirection(this->direction);
      } else {
        toFinalDestination = NULL;
        available = true;
        nearestEntity = NULL;
      }
    }
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}
