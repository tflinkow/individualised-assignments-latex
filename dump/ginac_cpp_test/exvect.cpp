#include <iostream>
#include <vector>
#include <algorithm>
#include <ginac/ginac.h>

//using namespace GiNaC;

GiNaC::symbol x("x");

void integral_do_print_latex(const GiNaC::integral& intg, const GiNaC::print_latex& c, unsigned level)
{
    std::string varname = GiNaC::ex_to<GiNaC::symbol>(intg.op(0)).get_name();

    if (level > intg.precedence())
    {
        c.s << "\\left(";
    }

    // If you know that an expression holds an integral, you can get the integration variable, 
    // the left boundary, right boundary and integrand by respectively calling .op(0), .op(1), .op(2), and .op(3).

    c.s << "\\int_{";
    intg.op(1).print(c);
    c.s << "}^{";
    intg.op(2).print(c);
    c.s << "}";

    intg.op(3).print(c, intg.precedence());

    c.s << "\\;\\mathrm{d}";

    if (varname.size() > 1)
    {
        c.s << "\\," << varname;
    }
    else
    {
        c.s << varname;
    }

    if (level > intg.precedence())
    {
        c.s << "\\right)";
    }
}

std::ostream& print_ordered(const GiNaC::ex& expr, GiNaC::symbol& x, std::ostream& os)
{
    std::vector<GiNaC::ex> terms(expr.begin(), expr.end());
    std::sort(std::begin(terms), std::end(terms), [x](const GiNaC::ex& lhs, const GiNaC::ex& rhs) { return lhs.degree(x) > rhs.degree(x); });

    bool first = true;

    for (auto term : terms) 
    {
        // if the first term is positive, do not print the '+'
        if (term.coeff(term) > 0 && !first)
        {
            os << '+';
        }

        os << term;
        first = false;
    }

    return os;
}

void my_print_poly_as_latex(const GiNaC::add& poly, const GiNaC::print_latex& c, unsigned level)
{
    // TODO: THIS IS THE UGLY PART: a global variable X !!
    print_ordered(poly, ::x, c.s);
}

int main()
{
    
    GiNaC::ex poly(-3*x-5+GiNaC::pow(x,2)+7*GiNaC::pow(x,5)-12*GiNaC::pow(x,2));
    poly = poly.diff(x);
    GiNaC::ex intg = GiNaC::integral(x, 0, 1, poly / 2);

    std::cout << GiNaC::latex;

    // standard GiNaC, non-predictable order
    std::cout << poly << std::endl;
    std::cout << intg << std::endl;

    // ordered by powers of x descendingly
    GiNaC::set_print_func<GiNaC::add, GiNaC::print_latex>(my_print_poly_as_latex);

    std::cout << poly << std::endl;
    std::cout << intg << std::endl;

    // int_a^b f(x) dx instead of int_a^b dx f(x)
    GiNaC::set_print_func<GiNaC::integral, GiNaC::print_latex>(integral_do_print_latex);
    std::cout << intg << std::endl;
}