// Authors: Akide Liu ; Andrew Wang ; Chi Wang
// Date : 24/9/20
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#ifndef OOP_PROJECT_PEOPLESERVICESH_
#define OOP_PROJECT_PEOPLESERVICESH_

#include <iostream>
#include <vector>
#include <algorithm>

#include <prettyprint.hpp>
#include <vo/include/People.h>
#include <vo/include/VO_PUBLIC.h>

class PeopleServices {

public:
    /*
     * static utils functions
     */

    static bool logout(int user_id);

    static bool login(int user_id, string password);

    static bool initPassword();

    static bool changePassword(int user_id, const string password);

    static void ListAllUsers();

    static int checkUserLevelById(int user_id);

    static bool resetUserPasswordById(int user_id);//void to bool

    static bool lockUser(int user_id);

    static bool unlockUser(int user_id);

    /*
     * userAction functions
     */

    virtual bool addNewTutor(Tutor *people);// change the object to tutor according to the form in peopledao_test.cpp

    virtual void modifyTutorById(int user_id);

    virtual bool addNewStudent(Student *people);// change the object to tutor according to the form in peopledao_test.cpp

    virtual void modifyStudentById(int user_id);

    virtual bool addNewSubject(Subject *subject);

    virtual void modifySubjectById(int subject_id);

    virtual void showStudents();

    virtual void showTutors();

    virtual void showSubjects();


private:

    static int s_user_id;

    static int s_subject_id;

    static PeopleServices * currentUser;

public:
    static void setCurrentUser(PeopleServices *&currentUser);

public:
    static PeopleServices * getCurrentUser();

};


#endif //OOP_PROJECT_PEOPLESERVICESH_
