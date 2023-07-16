package com.company;
import java.util.Scanner;

public class Menu {
    public void ShowMenu(Course[] CourArr, Teacher[] TeacArr, Student[] StudArr, Grade[] GradArr){
        System.out.println("---------menu-----------");

        System.out.println("1.Course");
        System.out.println("2.Teacher");
        System.out.println("3.Student");
        System.out.println("4.Grade");
        System.out.println("\t\tinput number to chose~");

        int choice = 0;
        Scanner sc = new Scanner(System.in);
        switch (choice){
            case 1:

        }
        System.out.println(choice);
    }

    void ShowCourseMenu(Course[] CourArr){

    }
    void ShowTeacherMenu(Teacher[] TeacArr){

    }
    void ShowStudentMenu(Student[] StudArr){

    }
    void ShowGradeMenu(Grade[] GradArr){

    }

}
