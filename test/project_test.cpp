// Authors: Akide Liu ; Andrew Wang ; Chi Wang
// Date : 13/9/20
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

#include <vo/include/VO_PUBLIC.h>
#include <service/include/SERVICE_PUBLIC.h>
#include <dao/include/PeopleDao.h>
#include <database_connection.h>


using namespace std;

TEST(major,test01){


    // Storage::setCurrentUserById(2);
    // Storage::storagePeople[2]->login(4, "-1");
    // Storage::storagePeople[2]->showStudents();
    // Storage::storagePeople[2]->addNewStudent(new Student(Storage::getSUserId(), "student02"));
    // Storage::storagePeople[2]->showStudents();
    //
    PeopleServices::ListAllUsers();

    PeopleServices *ps01 = new TutorServices();
    ps01->showStudents();




}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // ::testing::GTEST_FLAG(filter) = "database*";
    // ::testing::GTEST_FLAG(filter) = "major*";

    return RUN_ALL_TESTS();
}





TEST(major,login) {

   

    for(int i = 1; i < 5; i++){
        vector<string> check{"1", "-1","1", "-1","1"}; 
        bool result =  PeopleServices::login(i, check[i - 1]);

       if(i < 6 && i%2 == 0){
        // bool result =  PeopleServices::login(1,"-1");
        EXPECT_EQ(result, true);   
        } else {
        EXPECT_EQ(result, false);   
        }  


    }

}

TEST(People_Services,logout){
    for (int i = 1; i < 10; i++){
        if(i < 5){
            bool actual = PeopleServices::logout(i);
            EXPECT_EQ(actual,true);
        }
        if(i > 5){
            bool actual = PeopleServices::logout(i);
            EXPECT_EQ(actual,false);
        }
    }
}


TEST(People_Services,addNewTutor){

    //user id automatically increased and managed by database

    Tutor *check01 = new Tutor(0, "test_tutor");

    PeopleServices * ps = new PeopleServices();

    bool result01 =  ps->addNewTutor(check01);

    EXPECT_EQ(result01, true);

    vector<People *> result02 = PeopleDao::selectPeopleByName(check01->getName());

    EXPECT_EQ(result02.size(),1);
    EXPECT_EQ(result02[0]->getName(), "test_tutor");
    EXPECT_EQ(result02[0]->getUserLevel(), 2);
    EXPECT_EQ(result02[0]->getPassword(), "-1");
    EXPECT_EQ(result02[0]->getTitle(), "tutor");
    EXPECT_EQ(result02[0]->isActive1(), true);


    mysql::connection db = database_connection::getConnection();

    db.execute("delete peopleSubject.* from peopleSubject where peopleSubject.user_id in (select people.user_id from people where people.name = 'test_tutor');");

    db.execute("delete people.* from people where people.name = 'test_tutor';");

    delete ps;

    delete check01;

}

TEST(People_Services,addNewStudent){

    //user id automatically increased and managed by database

    Student *check01 = new Student(0, "test_student");

    PeopleServices * ps = new PeopleServices();

    bool result01 =  ps->addNewStudent(check01);

    EXPECT_EQ(result01, true);

    vector<People *> result02 = PeopleDao::selectPeopleByName(check01->getName());

    EXPECT_EQ(result02.size(),1);
    EXPECT_EQ(result02[0]->getName(), "test_student");
    EXPECT_EQ(result02[0]->getUserLevel(), 1);
    EXPECT_EQ(result02[0]->getPassword(), "-1");
    EXPECT_EQ(result02[0]->getTitle(), "student");
    EXPECT_EQ(result02[0]->isActive1(), true);


    mysql::connection db = database_connection::getConnection();

    db.execute("delete people.* from people where people.name = 'test_student';");

    delete ps;
    delete check01;

}

//test temporary passed, the sixth line from the bottom needs to replace the function show all users in Peopleservice.
TEST(People_Services,resetUserPasswordById){
    // copy from test PeopleDap_test just replace the "PeopleDao::updatePeopleResetPassword" to PeopleServices::r.esetUserPasswordById
    map<int, string> check{
            {1, "123456"},
            {2, "niashdjk"},
            {3,"kasldb"},
    };

    for (const auto &kv : check) {

        //People *p = PeopleDao::selectOnePeople(kv.first);

        //EXPECT_EQ(p->getPassword(), kv.second);

        //delete p;

        EXPECT_TRUE(PeopleServices::resetUserPasswordById(kv.first));

    }
    vector<People *> pCheck = PeopleDao::listAllUsers();

    for (auto & i : pCheck) {
        EXPECT_EQ(i->getPassword(), "-1");
    }

}