#ifndef TimeTabling_H
#define TimeTabling_H



typedef struct Class Class;
typedef struct Course Course;
typedef struct Lecturer Lecturer;
typedef struct Group Group;
typedef struct Programme Programme;


struct Course
{
	char *courseCode;
	char *courseName;
  int hoursOfLecture;
  int hoursOfTutorial;
  int hoursOfPractical;
};

struct Lecturer
{
	char *lecturerName;
  char *department;
};

struct Group
{
	int groupSize;
};

struct Programme
{
	int numberOfGroup;
  char *groupName;
};

struct Class 
{
}

char *getCourseName(Course newCourse);
char *getCourseCode(Course newCourse);

#endif // TimeTabling_H
