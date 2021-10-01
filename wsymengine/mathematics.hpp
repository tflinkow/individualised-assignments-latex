#ifndef LIBSYMCOMP_MATHEMATICS_HPP
#define LIBSYMCOMP_MATHEMATICS_HPP

#include <symengine/expression.h>
#include <symengine/parser.h>
#include <symengine/solve.h>

#include "util.hpp"
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
}

#endif // LIBSYMCOMP_MATHEMATICS_HPP
