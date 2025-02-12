/**
 * @file StateGridPosition.cpp
 * @author Bram Hogg
 */

#include <cse/StateGridPosition.h>

namespace cse {
Point StateGridPosition::calculate_object_position() {
  ///Calculate the position of the object and return the point
  Point default_object_position;
  default_object_position.x = 0;
  default_object_position.y = 0;
  return default_object_position;
}

///Get the orientation of the object, 0-359 degrees
double StateGridPosition::get_object_orientation() {
  while (m_object_orientation >= 360) {
    m_object_orientation -= 360;
  }
  return m_object_orientation;
}
StateGridPosition::StateGridPosition(const std::string& name)
{
    m_central_position = create_point(0, 0);
    m_object_orientation = 0;
    m_state_grid = nullptr;
    m_object_position = create_point(0, 0);
}

}  // namespace cse