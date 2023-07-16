package com.company;

public class Course {
    int cid;
    String name;

    Course(){
        this.cid = -1;
        this.name = new String("none");
    }


    Course(int cid, String name){
        this.cid = cid;
        this.name = new String(name);
    }

    int GetId(){
        return this.cid;
    }
    String Getname(){
        return this.name;
    }
    void ChangeId(int cid){
        this.cid = cid;
    }
    void Changename(String name){
        this.name = name;
    }
    void PrintCourse(){
        System.out.print("The course id is:"+this.GetId()+"\t");
        System.out.println("The course name is:"+this.Getname());
    }
}

class CourseTest{
    void Test(){
        System.out.println("--COURSE TEST--");
        //create the course object
        Course[] course_arr = new Course[3];
        course_arr[0] = new Course(001, "Chinese");
        course_arr[1] = new Course(002, "math");
        course_arr[2] = new Course(003, "English");
        /*System.out.println("id\tname");
        System.out.println(Chinese.cid+"\t"+Chinese.name);
        System.out.println(math.cid+"\t"+math.name);
        System.out.println(English.cid+"\t"+English.name);
         */

        //print the course info
        PrintCourseArr(course_arr);
        //add course
        course_arr = AddCourse(course_arr, 004, "ExtraClass");

        System.out.println("After add:");
        PrintCourseArr(course_arr);
        //change the course info
        ChangeCourseInfo(course_arr, 001, "Chinese123");
        //print again
        System.out.println("After changing:");

        PrintCourseArr(course_arr);
        //delete an object
        course_arr = DeleteCourse(course_arr, 004);

        System.out.println("After delete:");

        PrintCourseArr(course_arr);


    }

    void PrintCourseArr(Course[] arr){
        int i;
        for(i = 0; i < arr.length; i++){
            if(null == arr[i]){
                System.out.println("arr[" + i + "] is null");
                break;
            }
            arr[i].PrintCourse();
        }
    }
    //Search by id
    int SearchCourse(Course[] arr, int cid){
        int find = -1, i;
        for(i = 0; i < arr.length; i++){
            if(cid == arr[i].GetId())
                find = i;
        }

        return find;
    }

    Course[] AddCourse(Course[] arr, int cid, String name){
        int goal = SearchCourse(arr, cid);
        if(-1 != goal){
            System.out.println("The course has Id as " + cid +"has existed !");
            return arr;
        }
        else{
            int i, j;
            Course[] NewArr = new Course[arr.length + 1];
            for(i = 0; i < arr.length; i++){
                NewArr[i] = arr[i];
            }
            NewArr[i] = new Course(cid, name);
            System.out.println("Add course has id " + cid +" success!");

            return NewArr;
        }
    }

    Course[] DeleteCourse(Course[] arr, int cid){
        int goal = SearchCourse(arr, cid);
        if(-1 == goal){
            System.out.println("Course has Id as" + cid +"not found !");
            return arr;
        }
        else{
            int i, j;
            Course[] NewArr = new Course[arr.length - 1];
            for(i = 0; i < goal; i++){
                NewArr[i] = arr[i];
            }
            for(i = goal, j = goal+1; i < NewArr.length && j < arr.length; i++, j++){
                NewArr[i] = arr[j];
            }
            System.out.println("Delete course has id " + cid +" success!");

            return NewArr;
        }
    }

    void ChangeCourseInfo(Course[] arr, int cid, String name){
        int goal = SearchCourse(arr, cid);
        if(-1 == goal){
            System.out.println("Course has Id as" + cid +"not found !");
            return;
        }
        else{
            arr[goal].ChangeId(cid);
            arr[goal].Changename(name);
        }
    }
}
