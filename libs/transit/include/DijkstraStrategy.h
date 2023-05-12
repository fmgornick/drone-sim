#ifndef DIJKSTRA_STRATEGY_H_
#define DIJKSTRA_STRATEGY_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @brief this class inhertis from the IStrategy class and is responsible for
 * generating the beeline that the drone will take.
 */
class DijkstraStrategy : public IStrategy {
 public:
  /**
   * @brief Construct a new Dijkstra Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  DijkstraStrategy(Vector3 position, Vector3 destination, const IGraph* graph);

  /**
   * @brief Destroy the Dijkstra Strategy object
   */
  ~DijkstraStrategy();

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
#endif  // DIJKSTRA_STRATEGY_H_
