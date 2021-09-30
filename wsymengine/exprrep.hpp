#ifndef LIBSYMCOMP_EXPRREP_HPP
#define LIBSYMCOMP_EXPRREP_HPP

#include <symengine/expression.h>
#include <symengine/parser.h>

#include <gsl/gsl>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include <string>
#include <sstream>

#include "util.hpp"

namespace symcomp
{
    /// A class which represents a mathematical expression.
    class ExprRep
    {
    public:
        /// The basic form of an expression, e.g. "3*x**2+1/2"
        std::string Basic;

        /// The LaTeX form of an expression, e.g. "3x^2+\frac{1/2}"
        std::string LaTeX;

        /// The default constructor.
        ExprRep() = default;

        /// Creates an \c ExprRep object from a basic representation and a corresponding LaTeX one.
        /// \param basic The basic form of the expression.
        /// \param laTeX The LaTeX form of the expression.
        ExprRep(std::string basic, std::string laTeX);

        /// Creates an \c ExprRep object from a basic representation and generates the LaTeX representation.
        /// \param basic The basic form of the expression.
        explicit ExprRep(const std::string& basic);

        /// Creates an \c ExprRep object from a \c SymEngine::Expression object.
        /// \param expression The \c SymEngine::Expression object.
        explicit ExprRep(const SymEngine::Expression& expression);

        /// Creates a table \c T containing the basic form at index 1 and the LaTeX form at index 2 and pushes it to the
        /// Lua stack.
        /// \param L The Lua stack.
        /// \return The number of values pushed to the stack (namely 1, the table.).
        int ReturnToLua(gsl::not_null<lua_State*> L) const;
    };

    /// A collection of multiple \c ExprRep objects.
    typedef std::vector<symcomp::ExprRep> ExprRepCollection;

    /// Creates a table \c T containing multiple \c ExprRep objects and pushes it to the Lua stack.
    /// \param L The Lua stack.
    /// \param collection The collection of \c ExprRep objects.
    /// \return The number of values pushed to the stack (namely 1, the table).
    int ReturnExprRepVectorToLua(gsl::not_null<lua_State*> L, const ExprRepCollection& collection);
}

#endif // LIBSYMCOMP_EXPRREP_HPP
