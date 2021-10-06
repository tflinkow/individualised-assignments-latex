#ifndef LIBSYMCOMP_MATHEMATICS_HPP
#define LIBSYMCOMP_MATHEMATICS_HPP

#include <symengine/expression.h>

#include "exprrep.hpp"

namespace symcomp
{
    /// Evaluates an expression by substituting \p var with \p value.
    /// \param what The expression.
    /// \param var The variable to substitute.
    /// \param value The value to use.
    /// \return An \c ExprRep object returning the result.
    symcomp::ExprRep EvaluateAt(const std::string& what, const std::string& var, double value);

    /// Solves the equation \p what == 0.
    /// \param what The expression.
    /// \param var The variable.
    /// \return A collection of \c ExprRep objects, each representing a real solution.
    symcomp::ExprRepCollection Solve(const std::string& what, const std::string& var);

    /// Calculates the derivative of \p what with respect to \p var.
    /// \param what The expression to differentiate.
    /// \param var The variable to differentiate with respect to.
    /// \return The derivative of \p what.
    symcomp::ExprRep Differentiate(const std::string& what, const std::string& var);

    /// Returns the identity matrix of the specified \p size.
    /// \param size The size of the matrix, i.e. a size x size matrix will be returned.
    /// \return The identity matrix of the specified size.
    symcomp::ExprRep IdentityMatrix(int size);

    /// Calculates the determinant of the specified matrix.
    /// \param matrix The matrix.
    /// \return The determinant of the specified matrix.
    symcomp::ExprRep Determinant(const std::string& matrix);

    /// Multiplies the specified matrix by the specified scalar.
    /// \param scalar The number or symbol to multiply the matrix with.
    /// \param matrix The matrix.
    /// \return A matrix where each element of \p matrix has been multiplied with \p scalar.
    symcomp::ExprRep MultiplyMatrixByScalar(const std::string& scalar, const std::string& matrix);

    /// Subtracts \p b from \p a, i.e. calculates \p a - \p b.
    /// \param a The matrix \p a.
    /// \param b The matrix to subtract from \p a.
    /// \return A matrix.
    symcomp::ExprRep SubMatrices(const std::string& a, const std::string& b);

    /// Returns a collection of all eigenvalues of the specified matrix.
    /// \param matrix The matrix.
    /// \return All eigenvalues of \p matrix.
    symcomp::ExprRepCollection Eigenvalues(const std::string& matrix);
}

#endif // LIBSYMCOMP_MATHEMATICS_HPP
