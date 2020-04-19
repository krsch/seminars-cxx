#include <iostream>

class BB {
public:
  int sm = 0;
  BB(int x = 0) : sm(x) {
    std::cout << "BB::BB()\n";
  }
};

class B : public virtual BB {
protected:
  int a = 0;
  B() : BB{5} {}

public:
  virtual int f() const {return 3;}
  int g() const {return f();}
};

class B2 : public virtual BB {
  int x = 0;
public:
  int g() const {return 5;}
};

class D : public B, public B2 {
  int& c;
public:
  D() : B(), c(a) {}
  using B::g;
  int f() const override {return sm;}
};

void make_smth(B const& b)
{
  std::cout << b.g() << "\n";
}

int main() {
  D d;
  B &b = d;
  B2 &b2 = d;
  // b.sm = 4;
  std::cout << b2.sm << "\n";
  std::cout << "B: " << b.g() << ", D: "<< d.g() << "\n";
  make_smth(d);
  return 0;
}