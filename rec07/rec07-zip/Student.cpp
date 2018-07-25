#include "Student.h"
#include "Course.h"

using namespace std;

const string& Student::getName() const{
    return name;
}

void Student::addCourse(Course* course){
    courseTaken.push_back(course);
}

void Student::dropCourse(Course* course){
    Course* cPtr = nullptr;
    for (size_t i = 0; i < courseTaken.size(); ++i){
        if (courseTaken[i] == course){
            cPtr = courseTaken[i];
            courseTaken[i] = courseTaken[courseTaken.size()-1];
            courseTaken[courseTaken.size()-1] = cPtr;
            courseTaken.pop_back();
            cout << name << " is no longer taking this course.\n";
            return;
        }
    }

    cout << course->getName() << " does not exist. \n";
}

ostream& operator<<(ostream& os,const Student& stud){
    os << endl;
    os << "\t" <<stud.name << " is taking:";
    for (const Course* cour: stud.courseTaken){
        os << cour->getName() << " ";
    }
    return os;
}
