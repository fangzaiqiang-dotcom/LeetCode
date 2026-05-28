#include <iostream>
#include <string>
using namespace std;

// 基类
class Person
{
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a)
    {
        cout << "Person 构造" << endl;
    }
    void showInfo()
    {
        cout << "姓名：" << name << " 年龄：" << age << endl;
    }
    ~Person()
    {
        cout << "Person 析构" << endl;
    }
};

// 公有继承
class Student : public Person
{
private:
    int id;
public:
    // 派生类构造 先调用基类构造
    Student(string n, int a, int i) : Person(n, a), id(i)
    {
        cout << "Student 构造" << endl;
    }
    void stuShow()
    {
        // protected 成员子类可直接访问
        cout << "学生学号：" << id
            << " 姓名：" << name << " 年龄：" << age << endl;
    }
    ~Student()
    {
        cout << "Student 析构" << endl;
    }
};

int main()
{
    Student s("张三", 18, 2026001);
    s.showInfo();    // 继承基类方法
    s.stuShow();     // 自己独有方法
    return 0;
}












//2.
#include <iostream>
using namespace std;

// 基类
class Animal
{
public:
    // 虚函数 实现多态
    virtual void speak()
    {
        cout << "动物发出声音" << endl;
    }
    // 虚析构！防止内存泄漏
    virtual ~Animal()
    {
        cout << "Animal 虚析构" << endl;
    }
};

// 派生类1
class Dog : public Animal
{
public:
    // 重写虚函数
    void speak() override
    {
        cout << "小狗汪汪叫" << endl;
    }
    ~Dog()
    {
        cout << "Dog 析构" << endl;
    }
};

// 派生类2
class Cat : public Animal
{
public:
    void speak() override
    {
        cout << "小猫喵喵叫" << endl;
    }
    ~Cat()
    {
        cout << "Cat 析构" << endl;
    }
};

// 多态调用函数 统一接口
void doSpeak(Animal& a)
{
    a.speak(); // 动态绑定 调用对应子类方法
}

int main()
{
    Dog d;
    Cat c;

    doSpeak(d);
    doSpeak(c);

    // 基类指针指向派生类 经典多态
    Animal* p = new Dog;
    p->speak();
    delete p;

    p = new Cat;
    p->speak();
    delete p;
    return 0;
}


//

#include <iostream>
using namespace std;

// 抽象基类 包含纯虚函数
class Shape
{
public:
    // 纯虚函数
    virtual double getArea() = 0;
    virtual void show() = 0;
    virtual ~Shape() {}
};

// 圆形
class Circle : public Shape
{
private:
    double r;
public:
    Circle(double rad) : r(rad) {}
    double getArea() override
    {
        return 3.14 * r * r;
    }
    void show() override
    {
        cout << "圆形 半径：" << r << endl;
    }
};

// 矩形
class Rect : public Shape
{
private:
    double w, h;
public:
    Rect(double wi, double he) :w(wi), h(he) {}
    double getArea() override
    {
        return w * h;
    }
    void show() override
    {
        cout << "矩形 宽：" << w << " 高：" << h << endl;
    }
};

void printArea(Shape& s)
{
    s.show();
    cout << "面积：" << s.getArea() << endl;
}

int main()
{
    // Shape s; 报错！抽象类不能实例化
    Circle c(5);
    Rect r(3, 4);

    printArea(c);
    printArea(r);
    return 0;
}




#include <iostream>
using namespace std;

class Base
{
public:
    void func(int x)
    {
        cout << "基类 func(int) " << x << endl;
    }
    virtual void test()
    {
        cout << "基类 test" << endl;
    }
};

class Derive : public Base
{
public:
    // 1. 隐藏：同名不同参 屏蔽父类
    void func(double x)
    {
        cout << "派生类 func(double) " << x << endl;
    }
    // 2. 重写：虚函数同名同参
    void test() override
    {
        cout << "派生类 test" << endl;
    }
};

int main()
{
    Derive d;
    d.func(10.5);
    // d.func(10); 报错 父类int版本被隐藏

    Base& b = d;
    b.test(); // 多态调用派生类
    return 0;
}



#include <iostream>
using namespace std;

class A
{
public:
    virtual void fun() { cout << "A" << endl; }
};
class B :public A
{
public:
    void fun()overrid7e { cout << "B" << endl; }
};

void print(A a) // 值传递 发生切片
{
    a.fun();
}

void print2(A& a) // 引用 不切片 实现多态
{
    a.fun();
}

int main()
{
    B b;
    print(b);   // 切片 输出A
    print2(b);  // 多态 输出B
    return 0;
}
