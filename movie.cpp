#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std::string& category, const std::string& name, double price, int qty, const std::string& genre, const std::string& rating) 
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> kw = parseStringToWords(name_);
    kw.insert(convToLower(genre_));
    return kw;
}

std::string Movie::displayString() const {
    std::ostringstream stream;
    stream.precision(2);
    stream << std::fixed;
    stream << name_ << '\n' << "Genre: " << genre_ << " Rating: " << rating_ << '\n'
           << price_ << " " << qty_ << " left.";
    return stream.str();
}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << std::endl << rating_ << std::endl;
}
