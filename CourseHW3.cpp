#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class Course {
    protected:
    char* name;
    char* id;
    public:
    void printDetails();
    Course();
    Course(const char* courseName,const char* courseID);
    ~Course();
};

void Course::printDetails(){
    printf("Course name: %s\n",name);
    printf("Course ID: %s\n",id);
}

Course::Course(){
    name=(char *)malloc(sizeof(char)*100);
    strcpy(name, "Default Course");
    id =(char *)malloc(sizeof(char)*100);
}

Course::Course(const char* courseName,const char* courseID){
    name=(char *)malloc(sizeof(char)*100);
    strcpy(name, courseName);
    id =(char *)malloc(sizeof(char)*100);
    strcpy(id, courseID);
}

Course::~Course(){
    //printf("deconstructing course %s\n",name);
    free(name);
    free(id);
}

class CourseDept: public Course{
    protected:
    char* department;
    int level;
    public:
    void printDetails();
    CourseDept();
    CourseDept(const char* courseName, const char* courseID, const char* dept, int lvl);
    ~CourseDept();
};

void CourseDept::printDetails(){
    printf("Course name: %s\n",name);
    printf("Course ID: %s\n",id);
    printf("Department: %s\n",department);
    printf("Level: %d\n",level);
}

CourseDept::CourseDept() : Course(){
    department = (char *)malloc(sizeof(char)*100);
    strcpy(department, "Default Department");
    level = 0;  
}

CourseDept::CourseDept(const char* courseName, const char* courseID,const char* dept, int lvl) : Course(courseName,courseID){
    department = (char *)malloc(sizeof(char)*100);
    strcpy(department, dept);
    level = lvl;
}

CourseDept::~CourseDept(){
    //printf("deconstructing course %s\n",name);
    free(department);
}

int main(){
    Course courseOne("Systems Software","3232");
    CourseDept courseTwo("Universal Justice","2010","CRJU",1);
    courseOne.printDetails();
    courseTwo.printDetails();
}