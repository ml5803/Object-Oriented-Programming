//
//  Student.hpp
//  Michael
//
//  Created by 周凯旋 on 3/9/18.
//  Copyright © 2018 Kaixuan Zhou. All rights reserved.
//

#ifndef Student_h
#define Student_h

#include <string>
#include <vector>
#include <iostream>
class Course;
class Student{
    friend std::ostream& operator<<(std::ostream& os,const Student& stud);
public:
    Student(const std::string& name): name(name){}
    const std::string& getName() const;
    void addCourse(Course* course);
    void dropCourse(Course* course);
private:
    std::string name;
    std::vector <Course*> courseTaken;
};


#endif /* Student_hpp */
