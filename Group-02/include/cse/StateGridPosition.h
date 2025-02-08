/**
 * @file StateGridPosition.h
 * @author Bram Hogg
 *
 *
 */

#include <cse/StateGrid.h>

#pragma once

#ifndef CSEG2_INCLUDE_CSE_STATEGRIDPOSITION_H
#define CSEG2_INCLUDE_CSE_STATEGRIDPOSITION_H

namespace cse {
///Point object for the position
struct Point {
  ///The position of the object
  double x = 0;
  double y = 0;
};

class StateGridPosition {

 private:
  ///The orientation in degrees
  double m_object_orientation = 0;

  Point m_object_position;

  Point m_central_position;

  ///The state grid this position is referring to
  StateGrid* m_state_grid = nullptr;

 public:
  Point create_point(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
  }

  ///Get the stategrid this position is associated with
  StateGrid* get_state_grid() {
    return m_state_grid;
  }

  ///Possibly getState, but can be done in only necessary places as well

  ///Get central position of the stategrid
  Point get_grid_position() {
    return m_central_position;
  }

  ///Get the position of the object this stategrid is associated with
  Point get_object_position() {
    return m_object_position;
  }

  ///Set position of object this stategrid is associated with
  void set_object_position(double x, double y) {
    m_object_position = create_point(x, y);
  }

  double get_object_orientation();

  ///Set the object's orientation, 0-359 degrees
  void set_object_orientation(double orientation) {
    m_object_orientation = orientation;
  }

  ///Calculates the object's position, still working on specs
  Point calculate_object_position();
};
}  // namespace cse

#endif  //CSEG2_INCLUDE_CSE_STATEGRIDPOSITION_H
