// In this case, there are 7 bugs. You can probably expect to have not quite this many in an exam question, but the more bugs you see, the better practice it is
// there are bug(s) here. Fix them and ensure the class works as it should
// 2 marks per bug

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

class User {
public:
  virtual bool is_admin() {
    return false;
  }

  virtual ~User() = default;

  const std::string& get_username() const { return username; }

private:
  std::string username;
};

class Admin: public User {
public:
  bool is_admin() override {
    return true;
  }

  void add_child(const User* user) {
    children.push_back(user);
  }

private:
  // potentially weak pointers?
  std::vector<const User*> children;
};

class Computer {
  auto get_user(const std::string& username) {
    const auto username_match = [&username] (const auto& user) {
      return user->get_username() == username;
    };
    return std::find_if(users.begin(), users.end(), username_match);
  }

  bool login(const std::string& username) {
    auto user = get_user(username);
    if (user == users.end())
      return false;
    current_user = user->get();
    return true;
  }

  bool delete_user(const std::string& username) {
    if (current_user && !current_user->is_admin())
      return false;
    auto user = get_user(username);
    if (user != users.end())
      users.erase(get_user(username));
    return user != users.end();
  }

  bool add_user(User&& user) {
    if (current_user && current_user->is_admin()) {
      users.push_back(std::make_unique<User>(std::move(user)));
      dynamic_cast<Admin*>(current_user)->add_child(users.back().get());
      return true;
    }
    return false;
  }

private:
  std::vector<std::unique_ptr<User>> users;
  User* current_user;
};


int main() {
  Computer c;
}
