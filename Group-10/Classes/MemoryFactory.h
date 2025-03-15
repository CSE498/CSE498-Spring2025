/* --- MemoryFactory.h --- */

/* ------------------------------------------
Author: Devon FoxElster
Date: 1/31/2025
------------------------------------------ */

#include <assert.h>

#include <algorithm>
#include <list>
#include <stdexcept>
#include <tuple>

static constexpr int DEFAULT_SIZE = 10;

#ifndef MEMORYFACTORY_H
#define MEMORYFACTORY_H
namespace cse {
/**
 * @brief A Class designed to allocate objects in bulk in order to speed up
 * processes
 * @tparam Object A templated object pointing to the factory type
 */
template <typename Object>
class MemoryFactory {
 private:
  /// @brief Size of the MemoryFactory
  int allocationSize_;

  /// @brief List containing all allocated objects
  std::list<Object*> allocatedBlock_;

  /// @brief Points to the next available Object
  typename std::list<Object*>::iterator nextAvailable_;

  /// @brief Int indicating how many free objects are left
  int reservedObjects_ = 0;

  /// @brief Default Value for all Objects
  Object defaultObject_;

  /**
   * @brief Private Function to handle dynamic expansion of allocated objects
   *
   * @param allocationAmount how many objects to be allocated for future use
   * @param initialState Object instance that should be assigned to all new
   * objects
   *
   * AllocateObjects iterates over the allocation amount and reserves new
   * objects.
   *
   * Use Cases:
   *  Initial Construction - This creates all initial objects
   *  Expansion - This doubles the current size of the MemoryFactory
   */
  void AllocateObjects_(int allocationAmount, Object initialState = Object{}) {
    for (int i = 0; i < allocationAmount; i++) {
      Object* newObject = new Object{};

      /* If the desired state is not DEFAULT
       * then reassign the object to the desired value */
      *newObject = (*newObject != initialState) ? initialState : *newObject;
      allocatedBlock_.push_back(newObject);

      /** The function is only ever called when no objects exist in the
       * MemoryFactory or if all current objects are reserved, so the reserved
       * point should now point at the newest object to be added to the factory
       */
      if (i == 0) {
        nextAvailable_ = --allocatedBlock_.end();
      }
    }
  }

  /**
   * @brief Doubles the amount of allocated Objects within the MemoryFactory
   */
  void ExpandSpace_() {
    AllocateObjects_(allocationSize_, defaultObject_);
    allocationSize_ = allocationSize_ * 2;
  }

  /**
   * @brief Identifies whether an Object Pointer is reserved by the
   * MemoryFactory instance
   *
   * @param targetObject pointer to the Object being searched for
   * @return list iterator pointing either to the Object* or the
   * list.end() iterator
   */
  std::list<Object*>::iterator Contains_(Object* targetObject) {
    return std::find(allocatedBlock_.begin(), allocatedBlock_.end(),
                     targetObject);
  }

 public:
  /**
   * @brief MemoryFactory Basic Constructor
   *
   * @param newAllocSize New count of initially allocated objects
   * @param initialState Alternate starting value for all Objects in the factory
   */
  MemoryFactory(int newAllocSize = DEFAULT_SIZE, Object initialState = Object{}) {
    // No point in a MemoryFactory that doesn't store objects
    assert(newAllocSize > 0);
    allocationSize_ = newAllocSize;
    AllocateObjects_(allocationSize_, initialState);
    defaultObject_ = initialState;
  }

  /**
   * Copy and Move Constructors as well as the Assignment Operator are disabled
   * to prevent copies of Object* and dynamic memory deletion complications
   */
  MemoryFactory(const MemoryFactory& other) = delete;
  MemoryFactory(const MemoryFactory&& other) = delete;
  MemoryFactory& operator=(const MemoryFactory& other) = delete;

  /**
   * @brief MemoryFactory Basic Destructor
   */
  ~MemoryFactory() {
    assert(reservedObjects_ == 0 &&
           "All objects must be returned to the factory before it deletes to "
           "avoid undefined behavior");

    for (auto object : allocatedBlock_) {
      delete object;
    }
  }

  /**
   * @brief Returns a pointer to a reserved Object for the user
   *
   * @tparam newArgs Any arguments to pass to the Object's constructor
   *
   * @return A pointer to the reserved Object
   */

  template <typename... newArgs>
  [[nodiscard]] Object* Allocate(newArgs... assignedValues) {
    // MemoryFactory is out of space
    if (nextAvailable_ == allocatedBlock_.end()) {
      ExpandSpace_();
    }
    Object* allocatedObject = *nextAvailable_;
    nextAvailable_++;
    reservedObjects_++;

    // If no constructor arguments are passed use the default value
    if (sizeof...(assignedValues) != 0) {
      *allocatedObject = Object{assignedValues...};
    } else {
      *allocatedObject = defaultObject_;
    }
    return allocatedObject;
  }

  /**
   * @brief Returns an object to the MemoryFactory once it is done being used
   * @param targetObject Object pointer to the deallocated Object
   *
   * @details Will take the returned Object, reset it to the default state, and
   * add it back to the pool of available Objects
   */
  void Deallocate(Object* targetObject) {
    // This needs to point to an object
    assert(targetObject != nullptr);

    // Returns an iterator to the object if it exists in the factory
    auto objectLocation = Contains_(targetObject);
    if (objectLocation != allocatedBlock_.end()) {
      // Remove the object from its arbitrary location within the factory
      allocatedBlock_.erase(objectLocation);

      /* Reassign the object to the default value, then move it to the end where
       * it registers as available
       */
      *targetObject = defaultObject_;
      allocatedBlock_.push_back(targetObject);
      reservedObjects_--;
    } else {
      throw std::invalid_argument(
          "This object does not belong to this MemoryFactory");
    }
  }

  /**
   * @brief Returns number of remaining objects in the factory
   *
   * @return The number of available Objects in the MemoryFactory
   */
  int GetSpace() const { return allocationSize_ - reservedObjects_; }

  /**
   * @brief Returns how many Objects are allocated by the factory
   *
   * @return The total number of Objects in the MemoryFactory
   */
  int GetSize() const { return allocationSize_; }
};
}  // namespace cse
#endif  // MEMORYFACTORY_H
