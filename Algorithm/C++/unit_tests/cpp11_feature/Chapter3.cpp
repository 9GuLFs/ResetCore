//
// Created by 35207 on 2018/11/23 0023.
//

#include "gtest/gtest.h"
#include <iostream>
#include <utility>

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
         char* b { (char*)"aa" };
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
         ClassG(const ClassG & g) : d(new int(*g.d)) {
             cout << "Copy Construct: " << ++n_cptr << endl;
         }
         /**
          * �ƶ�����
          * ���ֱ��ʹ�ÿ������캯���Ļ�����ɶ�ε���ʱ���캯���Ŀ���
          * ���ʹ���ƶ�����Ļ��򲻻��з�������
          */
         ClassG(ClassG && g) : d(g.d){
             g.d = nullptr;
             cout << "Move construct: " << ++n_mvtr << endl;
         }
         ~ClassG() {
             cout << "Destruct: " << ++n_dstr << endl;
             delete d;
         }
         int getd(){
             return *d;
         }

     private:
         int * d;
         static int n_cstr;
         static int n_dstr;
         static int n_cptr;
         static int n_mvtr;
     };

     int ClassG::n_cstr = 0;
     int ClassG::n_cptr = 0;
     int ClassG::n_dstr = 0;
     int ClassG::n_mvtr = 0;

     ClassG GetClassG(){
         ClassG result;
         cout << "Resource from " << __func__ << endl;
         return result;
     }
     TEST(CPP_11_FEATURE, CHAPTER_3_CONSTRUCT){
         ClassG g = GetClassG();
        cout << "Resource from " << __func__ << endl;
     }

     /**
      * ʵ����C++98/03ʱ�ƶ������Ѿ������ˣ����磺
      * ĳЩ����µĿ������캯����ʡ��
      * ����ָ��Ŀ���
      * ����ƴ��
      * �����ڵ��û�
      */


     /**
      * ��ֵ����ֵ�Լ���ֵ����
      * ���磺a = b + c
      * aΪ��ֵ��b+cΪ��ֵ
      *
      * ���㷺��˵���ǣ�����ȡ��ַ������ֵ������ȡ��ַ������ֵ
      *
      * ��C++11����ֵ���������
      * 1.����ֵ��xvalue, eXpiring Value��
      *     ������������ֵ��������ʳ����ֵ��������ֵ������ֵ��lambda���ʽ��
      *
      * 2.����ֵ(prvalue, Pure Rvalue)
      *     ����ֵ������صı��ʽ��ͨ���ǽ�Ҫ���ƶ��Ķ��󣬱�����ֵ����T&&�ĺ�������ֵ
      *     std::move�ķ���ֵ����ת��ΪT&&������ת�������ķ���ֵ��
      *
      * ����Ŀ��Ա�ʶ����������Ķ�����ֵ��
      *
      * ʵ��������ֵ���ѹ��ɣ��������Ҳ��Ҫ�������͡�
      *
      * ��ֵ���þ��Ƕ�һ����ֵ�������õ����͡�
      */
      ClassG ReturnRvalue(){
         return ClassG();
      }

      TEST(CPP_11_FEATURE_CHAPTER_3, CHAPTER_3_RVALUE){
          cout << endl;
          //ʹ����ֵ�Է���ֵ����
          ClassG && g1 = ReturnRvalue();
          cout << g1.getd() << endl;

          //δʹ����ֵ
          ClassG g2 = ReturnRvalue();
          cout << g2.getd() << endl;
      }


      TEST(CPP_11_FEATURE, CHAPTER_3_RVALUE_ERROR){
        // ��ֵ�����޷��󶨵���ֵ��
        // int c;
        // int && b = c;

        //������ֵ���ÿ��԰���ֵ
        const bool & judgement = true;
        //δʹ����ֵ
        const bool judgement2 = true;
        //ʵ����ʹ�ó�����ֵ����Ҳ���Լ�����ʱ����Ŀ���
      }


      struct Copyable{
          Copyable() = default;
          Copyable(const Copyable & o){
              cout << "copied" << endl;
          }
          Copyable(Copyable&&) noexcept { }
      };

      Copyable ReturnCopyableRvalue(){ return Copyable(); }
      void AcceptVal(Copyable){}
      void AcceptRef(const Copyable & ){}

      TEST(CPP_11_FEATURE, CHAPTER_3_LVALUE_REF){
          cout << endl;
          cout << "Pass by value" << endl;
          AcceptVal(ReturnCopyableRvalue());    //��ʱ������ֵ
          cout << "Pass by ref" << endl;
          AcceptRef(ReturnCopyableRvalue());    //��ʱֵ��Ϊ���ô���
      }

      void AcceptRvalueRef(Copyable&& s){
          Copyable news = std::move(s);
      }
      /**
       * �ж�һ��ֵ�Ƿ�����ֵ
       */
      TEST(CPP_11_FEATURE, CHAPTER_3_IS_REFRENCE){
          cout << is_reference<string &&>::value << endl;
          cout << is_rvalue_reference<string &&>::value << endl;
          cout << is_lvalue_reference<string &&>::value << endl;
      }

      /**
       * ʹ��std::moveǿ��ת��Ϊ��ֵ
       *
       * std::moveʵ���ϲ����ƶ��κζ�����ֻ�ǽ���ֵǿ��ת��Ϊ��ֵ����
       * ���ڣ�
       * static_cast<T&&>(lvalue);
       * �ڵ��ÿ������캯����ʱ���������������е�ֵ���ù���������
       * class Moveable{
       * public:
       *    Moveable(Moveable && m) :
       *        i(m.i), h(std::move(m.h)){
       *        m.i = nullptr;
       *    }
       * private:
       *    int * i;
       *    int h;
       * }
       *
       * ����iΪָ���Ա����hΪ��ͨ�ĳ�Ա
       * �����ʹ��move����������ô�����ĳ�Ա����h����Ϊ��ֵ�������ڽ�����ֱ�����٣�
       * ������Ҫת��Ϊ��ֵ���ӳ���������
       * ���û���ƶ����캯����Ҳ����ֱ��ʹ�ý�����ֵ���õĿ������캯����ֻ�ǻ���
       * �������ʱ����������������̫�����⡣
       */

        /**
         * �ƶ������һЩ��������
         * ������ƶ����캯������Ϊ��
         * Moveable(const Moveable &&)
         * ���߰Ѻ�������Ϊ
         * const Moveable ReturnRValue()
         * ���ᵼ����ʱ���������������޷�ʹ���ƶ����壬������д��ʱ��һ��Ҫ
         * �ų�����Ҫ��const
         *
         *
         */

        /**
         * C++11�п���/�ƶ����캯����3����ʽ��
         * T Object(T &)
         * T Object(const T &)
         * T Object(T &&)
         * ���г�����ֵ�ǿ������캯������ֵ���ð汾�����ƶ�����汾��Ĭ�������
         * ����������ʽ����һ���ƶ����캯����û���õ��򲻻����ɣ�Ĭ���ƶ����캯��
         * ʵ����Ҳֻ�ǰ�λ�������޷������������һЩ�򵥵Ĳ�������Դ�������û���⣬
         * ���������ƶ����ƶ����ǿ�����
         *
         * C++11֮ǰ��๹�춼�ǿ������壬���ֻ���ƶ�����Ļ�Ƚ���Ȥ��
         * ��ʾֻ�ܱ��ƶ������ܱ�������һ�㶼����Դ���ͣ�����ָ�롢�ļ����ȣ�
         * ���ǿ���ͨ��һЩ������ģ�������ж�һ�������Ƿ�����ƶ�
         */
         TEST(CPP_11_FEATURE, CHAPTER_3_MOVE_TYPE_TRAITS){
             cout << is_move_constructible<int>::value << endl;
             cout << is_trivially_move_constructible<int>::value << endl;
             cout << is_nothrow_move_assignable<int>::value << endl;
         }

     /**
      * �����ƶ�����֮����һ��Ӧ�þ��Ǹ����ܵ��û�
      */
      template <typename T>
      void swap(T& a, T& b){
          T tmp(move(a));
          a = move(b);
          b = move(tmp);
      }

      /**
       * �����������ǿ��ƶ������ʹ���ƶ����壬���������ÿ�������
       */
      TEST(CPP_11_FEATURE, CHAPTER_3_MOVE_SWAP){
          cout << endl;
          int a = 100;
          int b = 200;
          swap(a, b);
          cout << "a:" << a << " b:" << b << endl;
      }

      /**
       * �ƶ����캯��Ҫ�����ܷ�ֹ�쳣�ķ���������ƶ�����δ��ɶ��׳��쳣
       * �Ƿǳ�Σ�յġ�
       * ����Ҫ����һ��noexcept�ؼ��֣�
       * ��֤���׳��쳣��ʱ��ֱ����ֹӦ�ö�����ָ������״̬
       *
       * ����֮�⣺
       * ��������RVO(Return Value Optimization)/NRVO(Named Return Vlaue optimization)�Ż�
       * �����RVO/NRVO��
       * ��ô��ReturnValue�����б�������/�ƶ�������ʱ�����Լ�
       * ��ʱ��������/�ƶ�����b�Ķ�����ͨͨû��
       *
       * A ReturnRvalue() { A a(); return a; }
       * A b = ReturnRvalue();
       *
       * b����ֱ��ʹ����a�ĵ�ַ���κεĿ����Լ��ƶ���û�ˣ������������������ʱ����Ч��
       * �����ƶ����廹�Ƿǳ����õġ�
       *
       */
}