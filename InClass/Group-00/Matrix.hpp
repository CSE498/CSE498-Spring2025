#pragma once

#include <span>
#include <vector>

namespace cse {

  template <typename VALUE_T>
  class Matrix {
  private:
    std::vector< VALUE_T > data;
    size_t num_cols=0;

  public:
    Matrix() = default;
    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) = default;
    Matrix(size_t num_rows, size_t num_cols)
     : data(num_rows*num_cols), num_cols(num_cols) { }
    ~Matrix() { }

    Matrix & operator=(const Matrix &) = default;
    Matrix & operator=(Matrix &&) = default;

    size_t NumCols() const { return num_cols; }
    size_t NumRows() const {
      return num_cols ? (data.size() / num_cols) : 0; }
    size_t NumCells() const { return data.size(); }

    VALUE_T & At(size_t row_id, size_t col_id) {
      assert(row_id < NumRows());
      assert(col_id < NumCols());
      return data[row_id * num_cols + col_id];
    }

    const VALUE_T & At(size_t row_id, size_t col_id) const {
      assert(row_id < NumRows());
      assert(col_id < NumCols());
      return data[row_id * num_cols + col_id];
    }

    std::span<VALUE_T> operator[](size_t row_id) {
      return std::span<VALUE_T>( &data[row_id*num_cols],
                                 &data[(row_id+1)*num_cols] );
    }

    void Resize(size_t new_rows, size_t new_cols, VALUE_T new_default) {
      const size_t new_cells = new_rows * new_cols;
      std::vector< VALUE_T > new_data(new_cells, new_default);

      const size_t min_rows = std::min(NumRows(), new_rows);
      const size_t min_cols = std::min(num_cols, new_cols);
      for (size_t row = 0; row < min_rows; ++row) {
        for (size_t col = 0; col < min_cols; ++col) {
          new_data[row*new_cols+col] = data[row*num_cols+col];
        }
      }

      std::swap(data, new_data);
      num_cols = new_cols;
    }
  };

}