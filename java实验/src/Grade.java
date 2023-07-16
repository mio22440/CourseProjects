package com.company;

 class Grade {
    int gid;
    int cid;
    int tid;
    int[] sid;
    int[] score;

    private int stu_cnt;

    Grade(){
        this.gid = -1;
        this.cid = -1;
        this.tid = -1;
        this.sid = new int[50];
        this.score = new int[50];

        this.stu_cnt = 0;
    }
    Grade(int gid, int cid, int tid){
        this.gid = gid;
        this.cid = cid;
        this.tid = tid;
        this.sid = new int[50];
        this.score = new int[50];

        this.stu_cnt = 0;
    }

    void ChangeGid(int gid){
        this.gid = gid;
    }
    void ChangeCid(int cid){
        this.cid = cid;
    }
    void ChangeTid(int tid){
        this.tid = tid;
    }
    void ChangeId(int gid, int cid, int tid){
        this.gid = gid;
        this.cid = cid;
        this.tid = tid;
    }



    void AddGrade(Student stu, int score){
        this.sid[stu_cnt] = stu.GetId();
        this.score[stu_cnt] = score;

        stu_cnt++;
    }



    void PrintGrade(){
        int i;//print count
        System.out.println("The grade id is: "+this.gid);
        System.out.println("The course id is: "+this.cid);
        System.out.println("The teacher id is: "+this.tid);
        System.out.print("The course has "+this.stu_cnt+" student, ");
        System.out.println("the grade is followed: ");
        for(i = 0; i < this.stu_cnt; i++){
            System.out.println("The student id is: "+this.sid[i]+", The student's grade is: "+this.score[i]);
        }
        System.out.println();
    }
}

class GradeTest{
    void test(){
        System.out.println("--GRADE TEST--");

        Grade[] grade_arr = new Grade[3];
        grade_arr[0] = new Grade(301, 001, 101);
        grade_arr[1] = new Grade(302, 002, 102);
        grade_arr[2] = new Grade(303, 003, 103);

        Student MingXiao = new Student(201, "MingXiao");
        Student HuaXiao = new Student(202, "HuaXiao");
        Student HongXiao = new Student(203, "HongXiao");
        Student ExtraStudent = new Student(209, "ExtraStudent");
        /*
        * Another way to create students:
        * Students[] s = new Student[3];
        *
        * s[0] = new Student(201, "MingXiao");
        * s[1] = new Student(202, "HuaXiao");
        * s[2] = new Student(203, "HongXiao");
        * */

        grade_arr[0].AddGrade(MingXiao, 60);
        grade_arr[0].AddGrade(HuaXiao, 80);
        grade_arr[0].AddGrade(HongXiao, 100);
        grade_arr[0].PrintGrade();

        grade_arr[1].AddGrade(MingXiao, 59);
        grade_arr[1].AddGrade(HuaXiao, 79);
        grade_arr[1].AddGrade(HongXiao, 99);
        grade_arr[1].PrintGrade();

        grade_arr[2].AddGrade(MingXiao, 58);
        grade_arr[2].AddGrade(HuaXiao, 78);
        grade_arr[2].AddGrade(HongXiao, 98);
        grade_arr[2].PrintGrade();

        grade_arr[0].AddGrade(ExtraStudent, 2333);
        System.out.println("After add extra:");
        PrintAll(grade_arr);

        System.out.println("After delete extra:");
        DeleteGrade(grade_arr, 001, 209);
        PrintAll(grade_arr);

    }

    int SearchGrade(Grade[] arr, int cid, int sid){
        int i;
        int GoalCourse = -1;
        for(i = 0; i < arr.length; i++){//find the right course
            if(arr[i].cid == cid)
                GoalCourse = i;
        }

        if(-1 == GoalCourse){
            System.out.println("The grade has course id as" + cid + " is not found !");
            return -1;
        }

        int j;
        int GoalGrade = -1;
        for(i = 0; i < arr.length; i++){//find the right student's grade
            for(j = 0; j < arr[i].sid.length; j++){
                if(arr[i].sid[j] == sid)
                    GoalGrade = arr[i].score[j];
            }
        }
        if(-1 == GoalGrade)
            System.out.println("the student as Id" + sid +" do not has course Id as" + cid + " grade !");


        return GoalGrade;
    }

    int DeleteGrade(Grade[] arr, int cid, int sid){
        int isExist = SearchGrade(arr, cid, sid);
        if(-1 == isExist)
            return 1;


        int i;
        int GoalCoursePos = -1;
        for(i = 0; i < arr.length; i++){//find the right course
            if(arr[i].cid == cid)
                GoalCoursePos = i;
        }

        int[] NewSid = new int[arr[GoalCoursePos].sid.length - 1];//create new array to save sid
        int j, flag = -1;//flag is used to judge if break the second "for";
        int GoalGradePos = -1;
        for(i = 0; i < arr.length; i++){//find the right student's grade
            for(j = 0; j < arr[i].sid.length; j++){
                if(arr[i].sid[j] == sid) {
                    flag = 1;
                    GoalGradePos = j;
                    break;
                }
            }

            if(1 == flag)
                break;
        }

        for(i = 0; i < NewSid.length; i++){
            if(i != GoalGradePos)
                NewSid[i] = arr[GoalCoursePos].sid[i];
        }

        System.out.println("delete successfully !");

        arr[GoalCoursePos].sid = NewSid;
        return 1;
    }

    void PrintAll(Grade[] arr){
        int i;
        for(i = 0; i < arr.length; i++){
            System.out.println("------------------beautiful cut-----");
            arr[i].PrintGrade();
        }

    }
}
