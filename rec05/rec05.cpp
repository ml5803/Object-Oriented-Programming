/*
    Michael Li
    rec05: More pointers
*/
#include <iostream>
#include <vector>
#include <string>
#include <ostream>

using namespace std;

class Section{
public:
    friend ostream& operator<<(ostream& os, const Section& sec){
        os << "Section: " << sec.secID << ", ";
        os << sec.timeSlot;
        if(sec.studentList.size() == 0){
            os << "Students: None " << endl;
        }else{
            os << "Students:" << endl;
            for(Student* ptr: sec.studentList){
                os<<*ptr;
            }
        }
        return os;
    }

    Section(const string& secID, const string& weekday, int time): secID(secID), timeSlot(TimeSlot(weekday,time)){
    }

    ~Section(){
        cout << "\nSection: " << secID << " is being deleted" << endl;
        for(size_t i = 0; i < studentList.size(); ++i){
            cout << "Deleting " << studentList[i]->getName() << endl;
            delete studentList[i];
        }
    }

    Section(const Section& old): secID(old.secID), timeSlot(old.timeSlot){
        for(size_t i = 0; i < old.studentList.size(); ++i){
            studentList.push_back(new Student(*old.studentList[i]));
        }
    }

    void display() const{
        cout << secID << ", ";
        timeSlot.display();
        if(studentList.size() == 0){
            cout << "Students: None " << endl;
        }else{
            cout << "Students:" << endl;
            for(Student* ptr: studentList){
                ptr->display();
            }
        }
    }

    void setGrade(const string& name, int grade, int week){
        for(Student* sptr: studentList){
            if(sptr->getName() == name){
                sptr->setGrade(grade,week-1);
            }
        }
    }

    void addStudent(const string& name){
        studentList.push_back(new Student(name));
    }
private:
    class TimeSlot{
    public:
        friend ostream& operator<<(ostream& os, const TimeSlot& ts){
            os << "Time slot: [Day: " << ts.weekday << ", Start time: ";
            if (ts.time <= 12){
                os << ts.time;
                os << "AM";
            }else{
                os << ts.time - 12;
                os << " PM] ";
            }
            return os;
        }

        TimeSlot(const string& weekday, int time): weekday(weekday), time(time){
        }

        void display() const{
            int hourFormat;
            string timeFormat;
            if (time <= 12){
                hourFormat = time;
                timeFormat = "AM";
            }else{
                hourFormat = time - 12;
                timeFormat = "PM";
            }
            cout << "Time slot: [Day: " << weekday << ", Start time: " << hourFormat << " " << timeFormat << "] ";
        }
    private:
        string weekday;
        int time;
    };

    class Student{
    public:
        friend ostream& operator<<(ostream& os, const Student& stud){
            os << "Name: " << stud.sName << ", Grades: ";
            for(size_t i = 0; i < stud.grades.size(); ++i){
                os << stud.grades[i] << " ";
            }
            os << endl;
            return os;
        }

        Student(const string& name): sName(name), grades(vector<int>(14,-1)){
        }

        void display() const{
            cout << "Name: " << sName << ", Grades: ";
            for(size_t i = 0; i < grades.size(); ++i){
                cout << grades[i] << " ";
            }
            cout << endl;
        }

        string getName() const {
            return sName;
        }
        void setGrade(int grade,int ind){
            grades[ind] = grade;
        }
    private:
        string sName;
        vector<int> grades;
    };

    string secID;
    vector<Student*> studentList;
    TimeSlot timeSlot;
};

class LabWorker{
public:
    friend ostream& operator<<(ostream& os, const LabWorker& lb){
        if (lb.section){
            os << lb.name << " has ";
            os << *lb.section;
        }else{
            os << lb.name << " does not have a section" << endl;
        }
        return os;
    }

    LabWorker(const string& name): name(name), section(nullptr){
    }

    void display() const{
        if (section){
            cout << name << " has ";
            section->display();
        }else{
            cout << name << " does not have a section" << endl;
        }
    }

    void addSection(Section& sec){
        section = &sec;
    }

    void addGrade(const string& name, int grade, int week){
        section->setGrade(name,grade,week);
    }
private:
    string name;
    Section* section;
};

void doNothing(Section& sec){
    sec.display();
    return;
}

int main()
{
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
    return 0;
}
