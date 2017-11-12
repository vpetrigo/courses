#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>

// базовый класс фигуры (полиморфный)
struct Shape {
    virtual ~Shape() = default;
};

// прямоугольник
struct Rectangle : Shape {
};

// треугольник
struct Triangle : Shape {
};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape *a, Shape *b);

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape *a, Shape *b);

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template <class Base, class Result, bool Commutative> struct Multimethod2 {
    using multimethod_fun = std::function<Result(Base *, Base *)>;
    using key_type = std::pair<std::type_index, std::type_index>;
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid
    // f - это функция или функциональный объект
    // принимающий два указателя на Base
    // и возвращающий значение типа Result
    void addImpl(const std::type_info &t1, const std::type_info &t2,
                 multimethod_fun f)
    {
        multimethod_map_.emplace(key_type{t1, t2}, f);
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(const Base *a, const Base *b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно
        // проверить есть ли реализация для b и а
        auto type_indexes = _get_type_indexes(a, b);
        auto retval = _find_arg(type_indexes.first, type_indexes.second);

        if (!retval && Commutative) {
            retval = _find_arg(type_indexes.second, type_indexes.first);
        }

        return (retval != nullptr);
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base *a, Base *b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        auto type_indexes = _get_type_indexes(a, b);
        auto callable = _find_arg(type_indexes.first, type_indexes.second);

        if (!callable && Commutative) {
            callable = _find_arg(type_indexes.second, type_indexes.first);
            return callable(b, a);
        }

        return callable(a, b);
    }

  private:
    multimethod_fun _find_arg(const std::type_index &type_index1,
                              const std::type_index &type_index2) const
    {
        auto it = multimethod_map_.find({type_index1, type_index2});

        if (it != multimethod_map_.cend()) {
            return it->second;
        }

        return nullptr;
    }

    auto _get_type_indexes(const Base *a, const Base *b) const
        -> decltype(std::make_pair(std::type_index(typeid(*a)),
                                   std::type_index(typeid(*b))))
    {
        return std::make_pair(std::type_index(typeid(*a)),
                              std::type_index(typeid(*b)));
    }

    std::map<key_type, multimethod_fun> multimethod_map_;
};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape *a, Shape *b)
{
    std::cout << "Is intersect: RECT-RECT" << std::endl;
    return true;
}

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape *a, Shape *b)
{
    std::cout << "Is intersect: RECT-TRIANGLE" << std::endl;
    return true;
}

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_t_r(Shape *a, Shape *b)
{
    std::cout << "Is intersect: TRIANGLE-RECT" << std::endl;
    return true;
}

int main()
{
    Shape *a = new Rectangle{};
    Shape *b = new Triangle{};
    Shape *c = new Rectangle{};

    std::cout << typeid(*a).name() << " " << typeid(*b).name() << std::endl;

    Multimethod2<Shape, bool, true> mm;

    mm.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);
    mm.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

    if (mm.hasImpl(a, b)) {
        std::cout << "Has impl RECT-TRIANGLE" << std::endl;
        mm.call(a, b);
    }

    if (mm.hasImpl(b, a)) {
        std::cout << "Has impl TRIANGLE-RECT" << std::endl;
        mm.call(b, a);
    }

    if (mm.hasImpl(a, c)) {
        std::cout << "Has impl RECT-RECT" << std::endl;
        mm.call(a, c);
    }

    if (mm.hasImpl(c, a)) {
        std::cout << "Has impl RECT-RECT" << std::endl;
        mm.call(c, a);
    }
}