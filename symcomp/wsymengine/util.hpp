#ifndef LIBSYMCOMP_UTIL_HPP
#define LIBSYMCOMP_UTIL_HPP

#include <symengine/expression.h>
#include <symengine/matrix.h>
#include <symengine/parser.h>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

#define LOG(msg) std::cout << msg << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl

namespace symcomp::util
{
    /// Creates a \c SymEngine::Expression from the specified string \p str.
    /// \param str The string containing a mathematical expression.
    /// \return A \c SymEngine::Expression.
    inline SymEngine::Expression StringToSymEngineExpression(const std::string& str)
    {
        return { SymEngine::parse(str) };
    }

    inline std::string MatrixToBasic(const SymEngine::MatrixBase& matrix)
    {
        std::ostringstream oss;

        for (int i = 0; i < matrix.nrows(); ++i)
        {
            oss << "[";

            for (int j = 0; j < matrix.ncols() - 1; ++j)
            {
                oss << *matrix.get(i, j) << ", ";
            }

            oss << *matrix.get(i, matrix.ncols() - 1) << "] ";
        }

        return oss.str();
    }

    /// Creates the LaTeX representation of a \c SymEngine::MatrixBase.
    /// \param matrix The matrix object.
    /// \return A string containing the LaTeX representation of the matrix.
    inline std::string MatrixToLaTeX(const SymEngine::MatrixBase& matrix)
    {
        std::ostringstream oss;
        oss << "\\begin{bmatrix}";

        for (int i = 0; i < matrix.nrows(); ++i)
        {
            for (int j = 0; j < matrix.ncols() - 1; ++j)
            {
                oss << *matrix.get(i, j) << " & ";
            }

            oss << *matrix.get(i, matrix.ncols() - 1) << " \\\\";
        }

        oss << "\\end{bmatrix}";

        return oss.str();
    }

    inline void RemoveWhiteSpace(std::string& s)
    {
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    }

    inline std::vector<std::vector<std::string>> GetMatrixForParse(const std::string& text)
    {
        auto rowCount = std::count(text.begin(), text.end(), ']');

        std::vector<std::vector<std::string>> rows;
        rows.reserve(rowCount);

        std::stringstream ss;
        ss.str(text);

        std::string segment;

        while (std::getline(ss, segment, ']'))
        {
            auto columnCount = std::count(segment.begin(), segment.end(), ',') + 1;

            std::vector<std::string> rowElements;
            rowElements.reserve(columnCount);

            std::stringstream ss2;
            ss2.str(segment.substr(1)); // segment[0] is "[" (the row marker)
            std::string element;

            while (std::getline(ss2, element, ','))
            {
                rowElements.push_back(element);
            }

            rows.push_back(rowElements);
        }

        return rows;
    }

    inline SymEngine::MatrixBase* DenseMatrixFromString(const std::string& what)
    {
        // Format: m rows a [ r1, r2, ..., rn ]
        RemoveWhiteSpace(const_cast<std::string&>(what));

        auto rows = GetMatrixForParse(what);

        // TODO: NEW IS BAD BAD

        // what if column count is not the same for all rows?
        auto matrix = new SymEngine::DenseMatrix(rows.size(), rows[0].size());

        for (int i = 0; i < matrix->nrows(); ++i)
        {
            for (int j = 0; j < matrix->ncols(); ++j)
            {
                auto value = SymEngine::parse(rows[i][j]);
                matrix->set(i, j, value);
            }
        }

        return matrix;
    }

    /// Returns a \c SymEngine::Integer if the specified value is a whole number (e.g. 4.0 or 7.0) and returns a
    /// \c SymEngine::Number otherwise.
    /// \param a The number.
    /// \return A \c SymEngine::Number which might be a \c SymEngine::Integer.
    inline SymEngine::RCP<const SymEngine::Number> TryToInt(double a)
    {
        // https://stackoverflow.com/a/26343165/7571171
        if (std::fmod(a, static_cast<decltype(a)>(1.0)) == 0.0)
        {
            return SymEngine::integer(static_cast<int>(a));
        }
        
        return SymEngine::number(a);
    }

    /// Throws an error if the Lua function \p function was not called with the expected number of parameters.
    /// \param L The Lua stack.
    /// \param function The function called.
    /// \param expected The expected number of parameters.
    inline void LuaAssertParamCount(lua_State* L, const std::string& function, int expected)
    {
        auto actual = lua_gettop(L);

        if (actual != expected) [[unlikely]]
        {
            std::ostringstream oss;
            oss << "function '" << function << "' expected " << expected << " parameters, got " << actual;

            luaL_error(L, oss.str().c_str());
        }
    }
}

#endif // LIBSYMCOMP_UTIL_HPP
