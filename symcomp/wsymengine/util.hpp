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

    /// Creates a basic representation of the specified matrix.
    /// \param matrix The matrix.
    /// \return A string representing the matrix.
    inline std::string MatrixToBasic(const SymEngine::MatrixBase& matrix)
    {
        std::ostringstream oss;

        for (auto i = 0; i < matrix.nrows(); ++i)
        {
            oss << "[";

            for (auto j = 0; j < matrix.ncols() - 1; ++j)
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

        for (auto i = 0; i < matrix.nrows(); ++i)
        {
            for (auto j = 0; j < matrix.ncols() - 1; ++j)
            {
                oss << SymEngine::latex(*matrix.get(i, j)) << " & ";
            }

            oss << SymEngine::latex(*matrix.get(i, matrix.ncols() - 1)) << " \\\\";
        }

        oss << "\\end{bmatrix}";

        return oss.str();
    }

    /// Removes all whitespace from the specified string.
    /// \param s The string.
    inline void RemoveWhiteSpace(std::string& s)
    {
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    }

    /// Parses the specified string into a collection representing the rows, where each row is a collection of
    /// strings representing the column elements of that row.
    /// \param text The string containing the matrix.
    /// \return A collection of rows, where each row is a collection of strings representing a single row entry.
    inline std::vector<std::vector<std::string>> GetMatrixForParse(const std::string& text)
    {
        // Format: [ row1 ] [ row2 ] ... [ rowM ]
        // M times ] -> M rows
        auto rowCount = std::count(text.begin(), text.end(), ']');

        std::vector<std::vector<std::string>> rows;
        rows.reserve(rowCount);

        std::stringstream ss;
        ss.str(text);

        // one row, e.g. [ rowK ]
        std::string segment;

        while (std::getline(ss, segment, ']'))
        {
            // Format of a row here:
            // [ 1, 2, 10, -4, 6
            // 5 times , -> 6 elements
            auto columnCount = std::count(segment.begin(), segment.end(), ',') + 1;

            std::vector<std::string> rowElements;
            rowElements.reserve(columnCount);

            std::stringstream ss2;
            ss2.str(segment.substr(1)); // segment[0] is "[" (the row marker)

            // a single element, e.g. 10 or 4x etc.
            std::string element;

            while (std::getline(ss2, element, ','))
            {
                rowElements.push_back(element);
            }

            rows.push_back(rowElements);
        }

        return rows;
    }

    /// Parses a matrix from a string which formats a
    /// m x n matrix as [a_11, a_22, ..., a_1n] [a_21, a_22, ..., a_2n] ... [a_m1, a_m2, ..., a_mn]
    /// because SymEngine does not yet seem able to do so.
    inline std::shared_ptr<SymEngine::DenseMatrix> DenseMatrixFromString(const std::string& what)
    {
        // Format: m rows a [ r1, r2, ..., rn ]
        RemoveWhiteSpace(const_cast<std::string&>(what));

        auto rows = GetMatrixForParse(what);

        // what if column count is not the same for all rows?
        auto matrix = std::make_shared<SymEngine::DenseMatrix>(rows.size(), rows[0].size());

        for (auto i = 0; i < matrix->nrows(); ++i)
        {
            for (auto j = 0; j < matrix->ncols(); ++j)
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
