//
//  Registrar.hpp
//  Michael
//
//  Created by 周凯旋 on 3/9/18.
//  Copyright © 2018 Kaixuan Zhou. All rights reserved.
//

#ifndef Registrar_h
#define Registrar_h

#include <iostream>
#include <string>
#include <vector>

class Course;
class Student;

class Registrar{
public:
    friend std::ostream& operator<<(std::ostream& os, const Registrar& reg);
    Registrar(){}
    void printReport() const;
    void addCourse(const std::string& courseName);
    void addStudent(const std::string& name);
    void enrollStudentInCourse(const std::string& student, const std::string& course);
    void cancelCourse(const std::string& cName);
    void purge();
private:
    std::vector<Course*> courses;
    std::vector<Student*> students;
};

#endif /* Registrar_hpp */
