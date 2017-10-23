#include <iostream>

struct Base {
};

struct D1 : Base {
};

struct D2 : Base {
    void foo() {
        std::cout << "D2: " << __func__ << std::endl;
    }
};

struct D3 : D1, D2 {
};

// base указывает на экземпляр Base, соответствующий D1
// нужно вернуть указатель на экземпляр Base, соответсвующий D2
Base * D1BaseToD2Base(const Base *base)
{
    return static_cast<D2 *>(static_cast<D3 *>(static_cast<D1 *>(const_cast<Base *>(base))));
}

int main() {
    D3 d3;
    Base *ptr = static_cast<D1 *> (&d3);

    ptr = D1BaseToD2Base(ptr);
    static_cast<D2 *> (ptr)->foo();
    
    return 0;
}
