package com.company;

public class Main {

    public static void main(String[] args) {
        CourseTest ct = new CourseTest();
        TeacherTest tt = new TeacherTest();
        StudentTest st = new StudentTest();
        GradeTest gt = new GradeTest();

        ct.Test();System.out.println();
        tt.test();System.out.println();
        st.test();System.out.println();
        gt.test();System.out.println();

        Menu mn = new Menu();

    }
}
