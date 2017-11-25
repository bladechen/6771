#include <iostream>
#include <string>
#include <vector>

class Book {
public:
  Book(const std::string& name="", double price=0): price{price}, name{name} {}
  virtual ~Book() = default;

  const std::string& get_name() const { return name; }
  virtual double net_price(unsigned n) const { return n * price; }

protected:
  double price;

private:
  std::string name;

};

class Disc_book: public Book {
public:
  Disc_book(const std::string& name="", double price=0, double discount=0): Book{name, price}, discount{discount} {}

  double net_price(unsigned n) const override;

private:
  double discount;
};

double Disc_book::net_price(unsigned n) const {
  return n * (1 - discount) * price;
}

class Bulk_disc_book: public Disc_book {
public:
  Bulk_disc_book(const std::string& name="", double price=0, double discount=0, unsigned min_qty=1): Disc_book{name, price, discount}, min_qty{min_qty} {}

  double net_price(unsigned n) const override;

private:
  unsigned min_qty;
};

double Bulk_disc_book::net_price(unsigned n) const {
  if (n >= min_qty)
    return Disc_book::net_price(n);
  else
    return Book::net_price(n);
}

void print_total(std::ostream& os, const Book& b, unsigned n) {
  os << "name: " << b.get_name() << " number sold: " << n << " total price: " << b.net_price(n) << '\n';
}

int main() {
  Book b{"Non-discounted book", 10};
  Disc_book db{"discounted book", 10, 0.1};
  Bulk_disc_book bdb{"bulk discounted book", 10, 0.1, 3};

  std::vector<Book*> books{&b, &db, &bdb};

  for (const auto& book : books)
    for (auto n = 0; n < 5; ++n)
      print_total(std::cout, *book, n);
}
