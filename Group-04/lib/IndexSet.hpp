#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <optional>
#include <utility>
#include <vector>

namespace cse {
/**
 * @brief A class that efficiently stores and recalls ranges of numbers in a
 * set.
 *
 * IndexSet provides an efficient way to store sets of integers by maintaining
 * them as ranges. For example, the sequence 1,2,3,5,6,7 would be stored as two
 * ranges: [1,4) and [5,8). This is particularly efficient when storing
 * consecutive numbers.
 *
 * The class automatically merges adjacent or overlapping ranges and splits
 * ranges when removing elements. All ranges are stored in the half-open
 * interval format [start, end) where end is exclusive.
 */
class IndexSet {
 public:
  // Iterator class definitions
  class iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = std::size_t*;
    using reference = std::size_t&;

    iterator(const std::vector<std::pair<std::size_t, std::size_t>>& ranges,
             std::size_t range_idx = 0, std::size_t current = 0)
        : ranges_(&ranges), range_idx_(range_idx), current_(current) {
      // If this is an end iterator (range_idx >= size)
      if (range_idx_ >= ranges_->size()) {
        current_ = 0;
        return;
      }
      // Otherwise, start at the beginning of the specified range
      current_ = (*ranges_)[range_idx_].first;
    }

    value_type operator*() const { return current_; }

    iterator& operator++() {
      if (range_idx_ >= ranges_->size()) return *this;

      current_++;
      // If we've reached the end of the current range
      if (current_ >= (*ranges_)[range_idx_].second) {
        range_idx_++;
        // If there are more ranges, move to the start of the next range
        if (range_idx_ < ranges_->size()) {
          current_ = (*ranges_)[range_idx_].first;
        }
        // If no more ranges, set current to end position
        else {
          current_ = 0;  // End position
        }
      }
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const iterator& other) const {
      return ranges_ == other.ranges_ && range_idx_ == other.range_idx_ &&
             current_ == other.current_;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

   private:
    const std::vector<std::pair<std::size_t, std::size_t>>* ranges_;
    std::size_t range_idx_;
    std::size_t current_;
  };

  class const_iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = const std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = const std::size_t*;
    using reference = const std::size_t&;

    const_iterator(
        const std::vector<std::pair<std::size_t, std::size_t>>& ranges,
        std::size_t range_idx = 0, std::size_t current = 0)
        : ranges_(&ranges), range_idx_(range_idx), current_(current) {
      // If this is an end iterator (range_idx >= size)
      if (range_idx_ >= ranges_->size()) {
        current_ = 0;
        return;
      }
      // Otherwise, start at the beginning of the specified range
      current_ = (*ranges_)[range_idx_].first;
    }

    std::remove_const_t<value_type> operator*() const { return current_; }

    const_iterator& operator++() {
      if (range_idx_ >= ranges_->size()) return *this;

      current_++;
      // If we've reached the end of the current range
      if (current_ >= (*ranges_)[range_idx_].second) {
        range_idx_++;
        // If there are more ranges, move to the start of the next range
        if (range_idx_ < ranges_->size()) {
          current_ = (*ranges_)[range_idx_].first;
        }
        // If no more ranges, set current to end position
        else {
          current_ = 0;  // End position
        }
      }
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const const_iterator& other) const {
      return ranges_ == other.ranges_ && range_idx_ == other.range_idx_ &&
             current_ == other.current_;
    }

    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }

   private:
    const std::vector<std::pair<std::size_t, std::size_t>>* ranges_;
    std::size_t range_idx_;
    std::size_t current_;
  };

  // Constructors
  IndexSet() = default;
  ~IndexSet() = default;
  IndexSet(size_t start, size_t end) {
    ranges_.emplace_back(start, end);
    total_size_ = end - start;  // Fix: Set correct total size
  }

  // Copy operations
  IndexSet(const IndexSet&) = default;
  IndexSet& operator=(const IndexSet&) = default;

  // Move operations
  IndexSet(IndexSet&& other) noexcept
      : ranges_(std::move(other.ranges_)), total_size_(other.total_size_) {
    // Clear the moved-from object
    other.ranges_.clear();
    other.total_size_ = 0;
  }

  IndexSet& operator=(IndexSet&& other) noexcept {
    if (this != &other) {
      ranges_ = std::move(other.ranges_);
      total_size_ = other.total_size_;
      // Clear the moved-from object
      other.ranges_.clear();
      other.total_size_ = 0;
    }
    return *this;
  }

  /**
   * @brief Adds an index to the set
   * @param index The index to add
   *
   * If the index is adjacent to or within an existing range, the ranges will
   * be automatically merged. For example, if [1,4) exists and we insert 4,
   * the range becomes [1,5).
   */
  void insert(std::size_t index) {
    // First check if the index is already in a range to avoid duplicate work
    auto range_idx = find_range_index(index);
    if (range_idx < ranges_.size() && ranges_[range_idx].first <= index &&
        ranges_[range_idx].second > index) {
      return;  // Already in set
    }

    // Track old size before merging to determine if we need to increment
    // total_size_
    std::size_t old_total = 0;
    for (const auto& range : ranges_) {
      old_total += range.second - range.first;
    }

    // Insert new range [index, index+1)
    ranges_.emplace_back(index, index + 1);

    // Merge any overlapping ranges - this will handle cases where the new index
    // is adjacent to or overlaps with existing ranges
    merge_overlapping_ranges();

    // Recalculate total size after merging
    total_size_ = 0;
    for (const auto& range : ranges_) {
      total_size_ += range.second - range.first;
    }

    // If total size didn't increase after merging, we must have merged with an
    // existing range In this case, we need to increment the size since we added
    // a new index
    if (total_size_ == old_total) {
      total_size_++;
    }
  }

  void insert_range(const std::size_t start, const std::size_t end) {
    if (start >= end) return;  // Invalid range

    // Insert new range directly
    ranges_.emplace_back(start, end);

    // Merge overlapping ranges
    merge_overlapping_ranges();

    // Recalculate total size
    total_size_ = 0;
    for (const auto& range : ranges_) {
      total_size_ += range.second - range.first;
    }
  }

  /**
   * @brief Removes an index from the set
   * @param index The index to remove
   *
   * If the index is in the middle of a range, the range will be split.
   * For example, if [1,5) exists and we remove 3, we get [1,3) and [4,5).
   */
  void remove(std::size_t index) {
    // Find the range containing this index
    auto range_idx = find_range_index(index);
    if (range_idx >= ranges_.size() || ranges_[range_idx].first > index ||
        ranges_[range_idx].second <= index) {
      return;  // Index not in set
    }

    auto& range = ranges_[range_idx];
    if (range.first == index) {
      // Case 1: Removing from start of range
      range.first++;
      if (range.first == range.second) {
        // Range became empty, remove it
        ranges_.erase(ranges_.begin() + range_idx);
      }
    } else if (range.second == index + 1) {
      // Case 2: Removing from end of range
      range.second--;
    } else {
      // Case 3: Removing from middle of range - need to split into two ranges
      auto second_half = std::make_pair(index + 1, range.second);
      range.second = index;
      ranges_.insert(ranges_.begin() + range_idx + 1, second_half);
    }

    total_size_--;
  }

  /**
   * @brief Checks if an index is in the set
   * @param index The index to check
   * @return true if the index is in the set, false otherwise
   */
  bool contains(std::size_t index) const {
    // Find potential containing range and verify index is within its bounds
    auto range_idx = find_range_index(index);
    return range_idx < ranges_.size() && ranges_[range_idx].first <= index &&
           ranges_[range_idx].second > index;
  }

  /**
   * @brief Returns the total number of indices in the set
   * @return The sum of the sizes of all ranges
   */
  std::size_t size() const { return total_size_; }

  /**
   * @brief Returns a vector containing all indices in the set
   * @return Vector of indices in ascending order
   */
  std::vector<std::size_t> get_all_indices() const {
    std::vector<std::size_t> result;
    result.reserve(total_size_);  // Preallocate to avoid reallocations

    // Expand each range into individual indices
    for (const auto& range : ranges_) {
      for (std::size_t i = range.first; i < range.second; ++i) {
        result.push_back(i);
      }
    }

    return result;
  }

  /**
   * @brief Gets the next range after the given index
   * @param index The reference index
   * @return The next range if it exists, std::nullopt otherwise
   *
   * If the index is within a range, returns the next range after the
   * containing range. If the index is between ranges, returns the next range.
   */
  std::optional<std::pair<std::size_t, std::size_t>> get_next_range(
      std::size_t index) const {
    auto range_idx = find_range_index(index);

    // If index is in a range, we want the next range
    if (range_idx < ranges_.size() && ranges_[range_idx].first <= index &&
        ranges_[range_idx].second > index) {
      range_idx++;
    }

    // Return next range if it exists
    if (range_idx < ranges_.size()) {
      return ranges_[range_idx];
    }
    return std::nullopt;
  }

  /**
   * @brief Gets the previous range before the given index
   * @param index The reference index
   * @return The previous range if it exists, std::nullopt otherwise
   */
  std::optional<std::pair<std::size_t, std::size_t>> get_prev_range(
      std::size_t index) const {
    auto range_idx = find_range_index(index);

    // Handle edge cases
    if (range_idx == 0 || ranges_.empty()) {
      return std::nullopt;
    }

    // If index is in current range, return previous range
    if (range_idx < ranges_.size() && ranges_[range_idx].first <= index &&
        ranges_[range_idx].second > index) {
      if (range_idx == 0) return std::nullopt;
      return ranges_[range_idx - 1];
    }

    // Otherwise return the range before the found position
    return ranges_[range_idx - 1];
  }

  /**
   * @brief Gets the range containing the given index
   * @param index The index to find
   * @return The containing range if it exists, std::nullopt otherwise
   */
  std::optional<std::pair<std::size_t, std::size_t>> get_containing_range(
      std::size_t index) const {
    auto range_idx = find_range_index(index);

    // Verify the range actually contains the index
    if (range_idx < ranges_.size() && ranges_[range_idx].first <= index &&
        ranges_[range_idx].second > index) {
      return ranges_[range_idx];
    }
    return std::nullopt;
  }

  void offset(const size_t offset) {
    for (auto& [start, end] : ranges_) {
      start += offset;
      end += offset;
    }
  }

  /**
   * @brief Adds another index set to the end of this one, starting at the index
   * @param indexSet The IndexSet to append
   * @param index The index to start appending
   */
  void append_at(const IndexSet& indexSet, const std::size_t index) {
    // Create a copy of the input IndexSet and offset it by the starting index
    IndexSet offsetSet = indexSet;
    offsetSet.offset(index);

    // Add all ranges from the offset set to this set
    for (const auto& range : offsetSet.ranges_) {
      insert_range(range.first, range.second);
    }
  }

  /**
   * @brief Computes the union of this set with another
   * @param other The other set to union with
   * @return A new set containing all elements that are in either set
   */
  IndexSet operator|(const IndexSet& other) const {
    IndexSet result = *this;  // Start with a copy of this set
    // Add all ranges from the other set
    for (const auto& range : other.ranges_) {
      result.insert_range(range.first, range.second);
    }
    return result;
  }

  /**
   * @brief Computes the intersection of this set with another
   * @param other The other set to intersect with
   * @return A new set containing all elements that are in both sets
   */
  IndexSet operator&(const IndexSet& other) const {
    IndexSet result;

    // For each range in this set
    for (const auto& range1 : ranges_) {
      // For each range in the other set
      for (const auto& range2 : other.ranges_) {
        // Find intersection of ranges
        auto start = std::max(range1.first, range2.first);
        auto end = std::min(range1.second, range2.second);

        // If ranges overlap, add their intersection
        if (start < end) {
          result.insert_range(start, end);
        }
      }
    }
    return result;
  }

  /**
   * @brief Computes the difference of this set with another
   * @param other The set to subtract
   * @return A new set containing elements that are in this set but not in other
   */
  IndexSet operator-(const IndexSet& other) const {
    IndexSet result = *this;  // Start with a copy of this set

    // Remove each range from the other set
    for (const auto& range : other.ranges_) {
      for (std::size_t i = range.first; i < range.second; ++i) {
        result.remove(i);
      }
    }
    return result;
  }

  /**
   * @brief Computes the symmetric difference of this set with another
   * @param other The other set
   * @return A new set containing elements that are in either set but not both
   */
  IndexSet operator^(const IndexSet& other) const {
    IndexSet result;

    // Get the union and intersection
    IndexSet union_set = *this | other;
    IndexSet intersect_set = *this & other;

    // Symmetric difference is union minus intersection
    result = union_set - intersect_set;

    return result;
  }

  /**
   * @brief Checks if this set is a subset of another
   * @param other The potential superset
   * @return true if this set is a subset of other
   */
  bool operator<=(const IndexSet& other) const {
    // For each index in this set, check if it's in other
    for (const auto& range : ranges_) {
      for (std::size_t i = range.first; i < range.second; ++i) {
        if (!other.contains(i)) return false;
      }
    }
    return true;
  }

  /**
   * @brief Checks if this set is a superset of another
   * @param other The potential subset
   * @return true if this set is a superset of other
   */
  bool operator>=(const IndexSet& other) const { return other <= *this; }

  // Iterator methods
  iterator begin() { return iterator(ranges_); }
  iterator end() { return iterator(ranges_, ranges_.size(), 0); }
  const_iterator begin() const { return const_iterator(ranges_); }
  const_iterator end() const {
    return const_iterator(ranges_, ranges_.size(), 0);
  }
  const_iterator cbegin() const { return const_iterator(ranges_); }
  const_iterator cend() const {
    return const_iterator(ranges_, ranges_.size(), 0);
  }

 private:
  // Internal representation - vector of ranges
  // Each range is represented as [start, end) pair where end is exclusive
  std::vector<std::pair<std::size_t, std::size_t>> ranges_;
  std::size_t total_size_ = 0;  // Cache of total number of indices

  /**
   * @brief Merges any overlapping or adjacent ranges
   *
   * This function is called after insertions to maintain the invariant
   * that ranges are non-overlapping and non-adjacent. It first sorts
   * the ranges by start position, then merges any ranges that overlap
   * or are adjacent.
   */
  void merge_overlapping_ranges() {
    if (ranges_.empty()) return;

    // Sort ranges by start position to ensure we can merge in one pass
    std::sort(ranges_.begin(), ranges_.end());

    // Create new vector for merged ranges
    std::vector<std::pair<std::size_t, std::size_t>> merged;
    merged.reserve(ranges_.size());  // Reserve space to avoid reallocations
    merged.push_back(ranges_[0]);

    for (std::size_t i = 1; i < ranges_.size(); i++) {
      auto& back = merged.back();
      // Check if ranges are adjacent (back.second == ranges_[i].first - 1)
      // or overlapping (back.second >= ranges_[i].first)
      if (back.second >= ranges_[i].first - 1) {
        // Merge the ranges by extending the end of the previous range
        back.second = std::max(back.second, ranges_[i].second);
      } else {
        // Ranges are not adjacent or overlapping, add as new range
        merged.push_back(ranges_[i]);
      }
    }

    ranges_ = std::move(merged);
  }

  /**
   * @brief Finds the index of the range that could contain the given index
   * @param index The index to find
   * @return The index of the potential containing range
   *
   * Uses binary search to efficiently find the range that could contain
   * the given index. The returned range needs to be checked to confirm
   * it actually contains the index.
   */
  std::size_t find_range_index(std::size_t index) const {
    // Use binary search to find the range that could contain this index
    // The comparison function looks at range.second because we store ranges
    // as [start, end) intervals
    return std::lower_bound(ranges_.begin(), ranges_.end(), index,
                            [](const auto& range, std::size_t val) {
                              return range.second <= val;
                            }) -
           ranges_.begin();
  }
};

}  // namespace cse
