//
// Created by 35207 on 2018/11/23 0023.
//

#include "gtest/gtest.h"
#include <iostream>

using namespace std;

namespace CPP_11_FEATURE_CHAPTER_3 {


    /**
     *
     * �̳й��캯��
     * ��ʹ�û������ͺ�����˼����չ�����캯����
     *
     * ��Ҫע��Ĭ��ֵ���������ɶ�����캯���汾�������
     * ��Ĭ�ϲ����Ĺ��캯������С��
     *
     */
     class ClassA{
     public:
         ClassA(){}
         ClassA(int i){}
         ClassA(double d, int i){};
     };

     class ClassB : ClassA{
     public:
         using ClassA::ClassA; //�̳й��캯��
     };

     class ClassC{
     public:
         ClassC(){}
         ClassC(int i){}
     };

     /**
      * ��̳е����
      */
     class ClassD : ClassA, ClassC {
     public:
         using ClassA::ClassA;
         using ClassC::ClassC;
         ClassD(int i){}    //��ֹ���캯����ͻ
     };

     TEST(CPP_11_FEATURE, CHAPTER_3_DRIVER_CONSTRUCTOR){
        ClassB b(100);  //͸�����õ�A�Ĺ��캯��
     }


     /**
      * ί�ɹ��캯��
      */
     class ClassE{
     public:
         ClassE() { Init(); }

         /**
          * C++98������
          * ClassE(int a) : a(a) { Init(); }
          * ClassE(char* b) : b(b) { Init(); }
          */

         /**
          * C++11������
          * ί�ɹ��캯�������г�ʼ����
          */

         ClassE(int a) : ClassE() { this->a = a; }
         ClassE(char* b) : ClassE() { this->b = b; }

     private:
         int a { 100 };
         char* b { "aa" };
         void Init(){};
     };

     /**
      * ���Ի�һ��д��
      * ��������ͨ����ʼ�����ʼ������
      */
     class ClassF{
     public:
         //ί�ɹ��캯������Ҳ������ί�ɹ��캯��
         //������Ҫע��ѭ�����õ����
         ClassF() : ClassF(1){}
         ClassF(int i) : ClassF(i, 'a'){}
         ClassF(char b) : ClassF(1, b){}

     private:
         ClassF(int i, char b) : i(i), b(b) {}
         int i;
         char b;
     };

     /**
      * ί�ɹ��캯����ģ�幹�캯�����һ������
      */

     /**
      * ��ֵ���ã��ƶ����������ת��
      *
      * ���һ����������ָ���Ա�Ļ�Ҫ�ر�С�Ŀ������캯���ı�д��
      * ���׳����ڴ�й©
      */

     class ClassG{
     public:
         ClassG() : d(new int(0)) {
             cout << "Construct: " << ++n_cstr << endl;
         }
         //��Ҫ�Լ�ʵ�ֿ������캯����Ĭ�Ͽ������캯�������й©
         ClassG(ClassG & g) : d(new int(*g.d)) {
             cout << "Copy Construct: " << ++n_cptr << endl;
         }
         ~ClassG() {
             cout << "Destruct: " << ++n_dstr << endl;
             delete d;
         }

     private:
         int * d;
         static int n_cstr;
         static int n_dstr;
         static int n_cptr;
     };

     int ClassG::n_cstr = 0;
     int ClassG::n_cptr = 0;
     int ClassG::n_dstr = 0;

     /**
      * �ƶ�����
      * ���ֱ��ʹ�ÿ������캯���Ļ�����ɶ�ε���ʱ���캯���Ŀ���
      * ���ʹ���ƶ�����Ļ��򲻻��з�������
      */
     class ClassG{
     public:
         ClassG() : d(new int(3)){
             cout << ""
         }

     private:
         int *d;
     };



}