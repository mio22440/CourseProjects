package com.company;

public class Teacher {
    int tid;
    String name;

    Teacher(){
        this.tid = -1;
        this.name = new String("none");
    }

    Teacher(int tid, String name){
        this.tid = tid;
        this.name = new String(name);
    }

    int GetId(){
        return this.tid;
    }
    String GetName(){
        return this.name;
    }
    void ChangeId(int tid){
        this.tid = tid;
    }
    void ChangeName(String name){
        this.name = name;
    }
    void PrintTeacher(){
        System.out.print("The teacher id is:"+this.tid+"\t");
        System.out.println("The teacher name is:"+this.name);
    }
}

class TeacherTest{
    void test(){
        System.out.println("--TEACHER TEST--");
        Teacher[] teacher_arr = new Teacher[3];
        teacher_arr[0] = new Teacher(101, "JingHe");
        teacher_arr[1] = new Teacher(102, "YanmeiYang");
        teacher_arr[2] = new Teacher(103, "YixingZhao");

        PrintTeacherArr(teacher_arr);
        //add Teacher
        teacher_arr = AddTeacher(teacher_arr, 104, "ExtraTeacher");

        System.out.println("After add:");
        PrintTeacherArr(teacher_arr);
        //change the Teacher info
        ChangeTeacherInfo(teacher_arr, 101, "JingHe123");
        //print again
        System.out.println("After changing:");

        PrintTeacherArr(teacher_arr);
        //delete an object
        teacher_arr = DeleteTeacher(teacher_arr, 104);

        System.out.println("After delete:");

        PrintTeacherArr(teacher_arr);


    }

    void PrintTeacherArr(Teacher[] arr){
        int i;
        for(i = 0; i < arr.length; i++){
            if(null == arr[i]){
                System.out.println("arr[" + i + "] is null");
                break;
            }
            arr[i].PrintTeacher();
        }
    }
    //Search by id
    int SearchTeacher(Teacher[] arr, int tid){
        int find = -1, i;
        for(i = 0; i < arr.length; i++){
            if(tid == arr[i].GetId())
                find = i;
        }

        return find;
    }

    Teacher[] AddTeacher(Teacher[] arr, int Cid, String Name){
        int goal = SearchTeacher(arr, Cid);
        if(-1 != goal){
            System.out.println("The Teacher has Id as " + Cid +"has existed !");
            return arr;
        }
        else{
            int i, j;
            Teacher[] NewArr = new Teacher[arr.length + 1];
            for(i = 0; i < arr.length; i++){
                NewArr[i] = arr[i];
            }
            NewArr[i] = new Teacher(Cid, Name);
            System.out.println("Add Teacher has id " + Cid +" success!");

            return NewArr;
        }
    }

    Teacher[] DeleteTeacher(Teacher[] arr, int tid){
        int goal = SearchTeacher(arr, tid);
        if(-1 == goal){
            System.out.println("Teacher has Id as" + tid +"not found !");
            return arr;
        }
        else{
            int i, j;
            Teacher[] NewArr = new Teacher[arr.length - 1];
            for(i = 0; i < goal; i++){
                NewArr[i] = arr[i];
            }
            for(i = goal, j = goal+1; i < NewArr.length && j < arr.length; i++, j++){
                NewArr[i] = arr[j];
            }
            System.out.println("Delete Teacher has id " + tid +" success!");

            return NewArr;
        }
    }

    void ChangeTeacherInfo(Teacher[] arr, int tid, String NewName){
        int goal = SearchTeacher(arr, tid);
        if(-1 == goal){
            System.out.println("Teacher has Id as" + tid +"not found !");
            return;
        }
        else{
            arr[goal].ChangeId(tid);
            arr[goal].ChangeName(NewName);
        }
    }
}
