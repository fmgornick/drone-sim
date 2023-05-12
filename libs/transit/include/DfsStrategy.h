#ifndef DFS_STRATEGY_H_
#define DFS_STRATEGY_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @brief this class inhertis from the IStrategy class and is responsible for
 * generating the beeline that the drone will take.
 */
class DfsStrategy : public IStrategy {
 public:
  /**
   * @brief Construct a new DFS Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  DfsStrategy(Vector3 position, Vector3 destination, const IGraph* graph);

  /**
   * @brief Destroy the DFS Strategy object
   */
  ~DfsStrategy();

  /**
   * @brief Move toward next position
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  void Move(IEntity* entity, double dt);

  /**
   * @brief Check if the trip is completed
   *
   * @return True if complete, false if not complete
   */
  bool IsCompleted();

 private:
  std::vector<std::vector<float>> path;
  int currentIndex;
  int maxIndex;
};
#endif  // DFS_STRATEGY_H_
