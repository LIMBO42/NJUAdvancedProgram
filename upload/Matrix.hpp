#pragma once

#include <memory>
#include <stdexcept>
#include <vector>


/**
 * The matrix type defines a common
 * interface for matrix operations.
 */
template <typename T>
class matrix {
 protected:
  /**
   * TODO: Add implementation
   *
   * Construct a new matrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   *
   */
  matrix(int rows, int cols) {}

  /** The number of rows in the matrix */
  int rows_;
  /** The number of columns in the matrix */
  int cols_;

  /**
   * TODO: Allocate the array in the constructor.
   * TODO: Deallocate the array in the destructor.
   * A flattened array containing the elements of the matrix.
   */
  T *linear_;

 public:
  /** @return The number of rows in the matrix */
  virtual int GetRowCount() const = 0;

  /** @return The number of columns in the matrix */
  virtual int GetColumnCount() const = 0;

  /**
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual T GetElement(int i, int j) const = 0;

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual void SetElement(int i, int j, T val) = 0;

  /**
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  virtual void FillFrom(const std::vector<T> &source) = 0;

  /**
   * Destroy a matrix instance.
   * TODO: Add implementation
   */
  virtual ~matrix() = default;
};

/**
 * The Rowmatrix type is a concrete matrix implementation.
 * It implements the interface defined by the matrix type.
 */
template <typename T>
class Rowmatrix : public matrix<T> {
 public:
  /**
   * TODO: Add implementation
   *
   * Construct a new Rowmatrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   */
  Rowmatrix(int rows, int cols) : matrix<T>(rows, cols) {}

  /**
   * TODO: Add implementation
   * @return The number of rows in the matrix
   */
  int GetRowCount() const override { return 0; }

  /**
   * TODO: Add implementation
   * @return The number of columns in the matrix
   */
  int GetColumnCount() const override { return 0; }

  /**
   * TODO: Add implementation
   *
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  T GetElement(int i, int j) const override {
    //throw NotImplementedException{"Rowmatrix::GetElement() not implemented."};
  }

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  void SetElement(int i, int j, T val) override {}

  /**
   * TODO: Add implementation
   *
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  void FillFrom(const std::vector<T> &source) override {
    //throw NotImplementedException{"Rowmatrix::FillFrom() not implemented."};
  }

  /**
   * TODO: Add implementation
   *
   * Destroy a Rowmatrix instance.
   */
  ~Rowmatrix() override = default;

 private:
  /**
   * A 2D array containing the elements of the matrix in row-major format.
   *
   * TODO:
   * - Allocate the array of row pointers in the constructor.
   * - Use these pointers to point to corresponding elements of the `linear` array.
   * - Don't forget to deallocate the array in the destructor.
   */
  T **data_;
};

/**
 * The RowmatrixOperations class defines operations
 * that may be performed on instances of `Rowmatrix`.
 */
template <typename T>
class RowmatrixOperations {
 public:
  /**
   * Compute (`matrixA` + `matrixB`) and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix addition
   */
  static std::unique_ptr<Rowmatrix<T>> Add(const Rowmatrix<T> *matrixA, const Rowmatrix<T> *matrixB) {
    // TODO: Add implementation
    return std::unique_ptr<Rowmatrix<T>>(nullptr);
  }

  /**
   * Compute the matrix multiplication (`matrixA` * `matrixB` and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix multiplication
   */
  static std::unique_ptr<Rowmatrix<T>> Multiply(const Rowmatrix<T> *matrixA, const Rowmatrix<T> *matrixB) {
    // TODO: Add implementation
    return std::unique_ptr<Rowmatrix<T>>(nullptr);
  }

  /**
   * Simplified General matrix Multiply operation. Compute (`matrixA` * `matrixB` + `matrixC`).
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @param matrixC Input matrix
   * @return The result of general matrix multiply
   */
  static std::unique_ptr<Rowmatrix<T>> GEMM(const Rowmatrix<T> *matrixA, const Rowmatrix<T> *matrixB,
                                            const Rowmatrix<T> *matrixC) {
    // TODO: Add implementation
    return std::unique_ptr<Rowmatrix<T>>(nullptr);
  }
};

