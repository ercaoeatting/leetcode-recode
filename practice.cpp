#include <iostream>
#include <map>

using namespace std;

class ShoppingCartManager {
public:
    // 获取购物车实例
    static ShoppingCartManager& getInstance() {
        static ShoppingCartManager instance;
        return instance;
    }

    // 添加商品到购物车
    void addToCart(const string& itemName, int quantity) { cart[itemName] += quantity; }

    // 查看购物车
    void viewCart() const {
        for (const auto& item : cart) { cout << item.first << " " << item.second << endl; }
    }

private:
    // 私有构造函数
    ShoppingCartManager() {}

    // 购物车存储商品和数量的映射
    map<string, int> cart;
};

int main() {
    string itemName;
    int quantity;

    while (cin >> itemName >> quantity) {
        // 获取购物车实例并添加商品
        ShoppingCartManager& cart = ShoppingCartManager::getInstance();
        cart.addToCart(itemName, quantity);
    }

    // 输出购物车内容
    const ShoppingCartManager& cart = ShoppingCartManager::getInstance();
    cart.viewCart();

    return 0;
}