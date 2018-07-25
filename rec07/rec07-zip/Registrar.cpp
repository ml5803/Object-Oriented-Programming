#include "Student.h"
#include "Course.h"
#include "Registrar.h"

using namespace std;


void Registrar::printReport() const{
    cout << *this;
}

void Registrar::addCourse(const string& courseName){
    courses.push_back(new Course(courseName));
}

void Registrar::addStudent(const string& name){
    students.push_back(new Student(name));
}

void Registrar::enrollStudentInCourse(const string& student, const string& course){
    size_t studentInd = students.size()+1;
    size_t courseInd = courses.size()+1;
    //find student
    for (size_t i = 0; i < students.size(); ++i){
        if (students[i]->getName() == student){
            studentInd = i;
            break;
        }
    }

    //find course
    for (size_t i = 0; i < courses.size(); ++i){
        if (courses[i]->getName() == course){
            courseInd = i;
            break;
        }
    }

    //enroll student to course
    if (studentInd < students.size() && courseInd < courses.size()){
        students[studentInd]->addCourse(courses[courseInd]);
        courses[courseInd]->addStudent(students[studentInd]);
        cout << student << " is now taking " << course << endl;
    }else{
        cout << "Unable to enroll student: Either course or student does not exist." << endl;
    }
}

void Registrar::cancelCourse(const string& cName){
    size_t ind = courses.size();
    Course* holder = nullptr;

    //find ind of course to remove
    for (size_t i = 0; i < courses.size(); ++i){
        if (courses[i]->getName() == cName){
            ind = i;
            break;
        }
    }

    //make student drop course
    for(Student* stud: students){
        stud->dropCourse(courses[ind]);
    }

    if(ind < courses.size()){
        for (size_t i = ind; i < courses.size()-1; ++i){
            holder = courses[i];
            courses[i] = courses[i+1];
            courses[i+1] = holder;
        }
        cout << courses[courses.size()-1]->getName() << " has been canceled.\n";
        delete courses[courses.size()-1];
        courses.pop_back();
    }else{
        cout << cName << " does not exist. \n";
    }
}

void Registrar::purge(){
    for (size_t i = 0; i < students.size(); ++i){
        delete students[i];
    }

    for (size_t i = 0; i < courses.size(); ++i){
        delete courses[i];
    }
    students.clear();
    courses.clear();
}

ostream& operator<<(ostream& os, const Registrar& reg){
    os << "Registrar:==================\n";
    os << "Courses: ";
    for(const Course* course: reg.courses){
        os << course->getName() << " ";
    }
    os << endl;
    os << "Students: ";
    for(const Student* student: reg.students){
        os << student->getName() << " ";
    }

    for(const Course* course: reg.courses){
        os << *course;
    }

    for(const Student* student: reg.students){
        os << *student;
    }
    return os;
}

