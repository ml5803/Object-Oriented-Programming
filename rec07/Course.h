#ifndef Course_hpp
#define Course_hpp

#include <vector>
#include <string>
#include <iostream>

class Student;

class Course{
public:
    friend std::ostream& operator<<(std::ostream& os, const Course& course);
    Course(const std::string& name):cName(name){}
    const std::string& getName() const;
    void addStudent(Student* student);
private:
    std::string cName;
    std::vector<Student*> studentTaking;
};

#endif /* Course_hpp */
