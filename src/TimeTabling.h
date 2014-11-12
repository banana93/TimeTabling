#ifndef TimeTabling_H
#define TimeTabling_H

typedef struct Perspective Perspective;

struct Perspective
{
  int time;
  char *venue;
  char *day;
  char subjectType;
  char *group;
  char *nameOfLecturer;
  char *subjectCode;
};

void checkPerspective(Perspective *perspective1, Perspective *perspective2);

// I think inside the perspective each of them is struct, right?
//check whether correct or not, James
typedef struct Course Course;
typedef struct Lecturer Lecturer;
typedef struct Group Group;
typedef struct Programme Programme;

struct Course
{
	char *courseCode;
	char *courseName;
};

struct Lecturer
{
	char *lecturerName;
};

struct Group
{
	int groupSize;
};

struct Programme
{
	int numberOfGroup;
};
// the struct might still need to edit later on, because dr poh said pointer to pointer, which im abit confused

char *getCourseName(Course newCourse);
char *getCourseCode(Course newCourse);

#endif // TimeTabling_H
