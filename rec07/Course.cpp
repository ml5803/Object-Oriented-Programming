#include "Course.h"
#include "Student.h"

using namespace std;

const string& Course::getName() const{
    return cName;
}

void Course::addStudent(Student* student){
    studentTaking.push_back(student);
}

ostream& operator<<(ostream& os, const Course& course){
    os << endl;
    os << "\t" << course.cName << endl;
    os << "\tStudents Taking This Course: ";
    for(const Student* stud: course.studentTaking){
        os << stud->getName() << " ";
    }
    return os;
}
