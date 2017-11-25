#include <string>
#include <vector>
#include <iostream>

class Person {
public:
  Person(const std::string& first, const std::string& last): first_name{first}, last_name{last} {}
  // take this as a little bit of magic for now. I'll explain it if we have time today, otherwise next week
  virtual ~Person() = default;

  std::string full_name() {
    return first_name + ' ' + last_name;
  }

  virtual std::string print() {
    return full_name() + " (Generic person)";
  }

private:
  std::string first_name;
  std::string last_name;
};

class Student: public Person {
public:
  Student(const std::string& first, const std::string& last, const std::string& zid): Person{first, last}, zid{zid} {}
  virtual ~Student() = default;

  std::string print() {
    return full_name() + " (student, id=" + zid + ")";
  }

private:
  std::string zid;
};

class Teacher: public Person {
public:
  Teacher(const std::string& first, const std::string& last, const std::string& course): Person{first, last}, course{course} {}
  virtual ~Teacher() = default;

  std::string print() {
    return full_name() + " (teacher, teaching " + course + ")";
  }

private:
  std::string course;
};

int main() {
  Person p{"Patricia", "Parker"};
  Student s{"Sam", "Smith", "z1234567"};
  Teacher t{"Tom", "Taylor", "COMP2041"};

  {
    Person person_concrete = p;
    Person& person_ref = p;
    Person* person_ptr = &p;

    Person student_concrete = s;
    std::cout << student_concrete.print() << '\n';
    Person& student_ref = s;
    std::cout << student_ref.print() << '\n';
    Person* student_ptr = &s;
    std::cout << student_ptr->print() << '\n';


    // let's convert this back to a student
    Student& student = dynamic_cast<Student&>(student_ref);
    std::cout << "Student " << student.print() << '\n';

    // what happens if we do the same thing with teacher?
    Person& teacher_ref = t;
    Student* teacher = dynamic_cast<Student*>(&teacher_ref);
    std::cout << "Teacher " << teacher << '\n';

    // or person?
    Student* person = dynamic_cast<Student*>(&person_ref);
    std::cout << "Person " << person << '\n';
  }

  {
    Student student_concrete = s;
    Student& student_ref = s;
    Student* student_ptr = &s;
  }
}
