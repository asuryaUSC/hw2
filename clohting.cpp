#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty, const std::string& size, const std::string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) {}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> key_set = parseStringToWords(name_);
    std::set<std::string> brand_keys = parseStringToWords(brand_);
    key_set = setUnion(key_set, brand_keys);
    return key_set;
}

std::string Clothing::displayString() const {
    return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << std::endl << brand_ << std::endl;
}
