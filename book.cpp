#include "book.h"
#include "util.h"

Book::Book(const std::string& category, const std::string& name, double price, int qty, const std::string& isbn, const std::string& author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> key_set = parseStringToWords(name_);
    std::set<std::string> author_keys = parseStringToWords(author_);
    key_set.insert(isbn_);
    key_set = setUnion(key_set, author_keys);
    return key_set;
}

std::string Book::displayString() const {
    return name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << isbn_ << std::endl << author_ << std::endl;
}
