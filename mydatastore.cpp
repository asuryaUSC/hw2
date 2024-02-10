#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <algorithm>

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    for (auto& pair : keywordsToProducts) {
        for (auto prod : pair.second) {
            delete prod;
        }
    }

    for (auto& pair : users) {
        delete pair.second;
    }

    keywordsToProducts.clear();
    users.clear();
    userCarts.clear();
}

void MyDataStore::addProduct(Product* p) {
    std::set<std::string> keys = p->keywords();
    for (auto& key : keys) {
        keywordsToProducts[key].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users[u->getName()] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> foundProducts;
    for (auto& term : terms) {
        if (keywordsToProducts.find(term) != keywordsToProducts.end()) {
            if (foundProducts.empty() && type == 0) {
                foundProducts = keywordsToProducts[term];
            } else {
                if (type == 0) {
                    foundProducts = setIntersection(foundProducts, keywordsToProducts[term]);
                } else {
                    foundProducts = setUnion(foundProducts, keywordsToProducts[term]);
                }
            }
        }
    }
    return std::vector<Product*>(foundProducts.begin(), foundProducts.end());
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for (auto& pair : keywordsToProducts) {
        for (auto prod : pair.second) {
            prod->dump(ofile);
        }
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for (auto& pair : users) {
        pair.second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(const std::string& username, Product* p) {
    if (users.find(username) != users.end()) {
        userCarts[username].push_back(p);
    } else {
        std::cout << "Invalid request" << std::endl;
    }
}

void MyDataStore::viewCart(const std::string& username) {
    if (userCarts.find(username) != userCarts.end()) {
        int itemNum = 1;
        for (auto& product : userCarts[username]) {
            std::cout << itemNum++ << ". ";
            std::cout << product->displayString() << std::endl;
        }
    } else {
        std::cout << "Cart is empty or user not found." << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    if (userCarts.find(username) != userCarts.end()) {
        auto& cart = userCarts[username];
        auto it = cart.begin();
        while (it != cart.end()) {
            Product* product = *it;
            User* user = users[username];
            if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
                user->deductAmount(product->getPrice());
                product->subtractQty(1);
                it = cart.erase(it);
            } else {
                ++it;
            }
        }
    } else {
        std::cout << "User not found." << std::endl;
    }
}
