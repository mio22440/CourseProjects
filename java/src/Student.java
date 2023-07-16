package com.company;

public class Student {
    int sid;
    String name;

    Student(){
        sid = -1;
        name = new String("none");
    }

    Student(int sid, String name){
        this.sid = sid;
        this.name = new String(name);
    }

    int GetId(){
        return this.sid;
    }
    String GetName(){
        return this.name;
    }
    void ChangeId(int sid){
        this.sid = sid;
    }
    void ChangeName(String name){
        this.name = name;
    }
    void PrintStudent(){
        System.out.print("The course id is:"+this.sid+"\t");
        System.out.println("The course name is:"+this.name);
    }
}

class StudentTest{
        public void test(){
        System.out.println("--STUDENT TEST--");
        
        Student[] student_arr = new Student[3];
        student_arr[0] = new Student(201, "MingXiao");
        student_arr[1] = new Student(202, "HuaXiao");
        student_arr[2] = new Student(203, "HongXiao");

            PrintStudentArr(student_arr);
            //add course
            student_arr = AddStudent(student_arr, 204, "ExtraStudent");

            System.out.println("After add:");
            PrintStudentArr(student_arr);
            //change the course info
            ChangeStudentInfo(student_arr, 201, "MingXiao123");
            //print again
            System.out.println("After changing:");

            PrintStudentArr(student_arr);
            //delete an object
            student_arr = DeleteStudent(student_arr, 204);

            System.out.println("After delete:");

            PrintStudentArr(student_arr);


        }

    void PrintStudentArr(Student[] arr){
        int i;
        for(i = 0; i < arr.length; i++){
            if(null == arr[i]){
                System.out.println("arr[" + i + "] is null");
                break;
            }
            arr[i].PrintStudent();
        }
    }
    //Search by id
    int SearchStudent(Student[] arr, int sid){
        int find = -1, i;
        for(i = 0; i < arr.length; i++){
            if(sid == arr[i].GetId())
                find = i;
        }

        return find;
    }

    Student[] AddStudent(Student[] arr, int sid, String name){
        int goal = SearchStudent(arr, sid);
        if(-1 != goal){
            System.out.println("The course has Id as " + sid +"has existed !");
            return arr;
        }
        else{
            int i, j;
            Student[] NewArr = new Student[arr.length + 1];
            for(i = 0; i < arr.length; i++){
                NewArr[i] = arr[i];
            }
            NewArr[i] = new Student(sid, name);
            System.out.println("Add course has id " + sid +" success!");

            return NewArr;
        }
    }

    Student[] DeleteStudent(Student[] arr, int sid){
        int goal = SearchStudent(arr, sid);
        if(-1 == goal){
            System.out.println("Student has Id as" + sid +"not found !");
            return arr;
        }
        else{
            int i, j;
            Student[] NewArr = new Student[arr.length - 1];
            for(i = 0; i < goal; i++){
                NewArr[i] = arr[i];
            }
            for(i = goal, j = goal+1; i < NewArr.length && j < arr.length; i++, j++){
                NewArr[i] = arr[j];
            }
            System.out.println("Delete course has id " + sid +" success!");

            return NewArr;
        }
    }

    void ChangeStudentInfo(Student[] arr, int sid, String name){
        int goal = SearchStudent(arr, sid);
        if(-1 == goal){
            System.out.println("Student has Id as" + sid +"not found !");
            return;
        }
        else{
            arr[goal].ChangeId(sid);
            arr[goal].ChangeName(name);
        }
    }
}
