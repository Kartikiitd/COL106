#include <iostream>
#include "stack_a.h"
using namespace std;
#include <stdexcept>
   Stack_A::Stack_A(){
      size = 0;
   }
   void Stack_A::push(int data){
      if(size==1024){
         throw runtime_error("Stack Full");
      }
      else{
         stk[size]=data;
         size +=1;
      }
   }
   int Stack_A::pop(){
      if(size==0){
         throw runtime_error("Empty Stack");
      }
      else{
         int popedval=stk[size-1];
         size -=1;
         return popedval;

      }
   }

   int Stack_A::get_element_from_top(int idx){
      if(idx>=size){
        throw runtime_error( "Index out of range");
      }
      else{
         return stk[size-idx-1];
      }
   }

   int Stack_A::get_element_from_bottom(int idx){
      if(idx>=size){
        throw runtime_error( "Index out of range");
      }
      else{
         return stk[idx];
      }
   }

   void Stack_A::print_stack(bool top_or_bottom){
      if(top_or_bottom==1){
         for(int i=size-1;i>=0;i--){
            cout<<stk[i]<<endl;
         }
      }
      else{
         for(int i=0;i<size;i++){
            cout<<stk[i]<<endl;
         }
      }

   }

   int Stack_A::add(){
      if(size<=1){
         throw runtime_error("Not Enough Arguments");
      }
      else{
         int num1 = pop();
         int num2 = pop();
         push(num1+num2);
         return(get_element_from_top(0));

      }
   }

   int Stack_A::subtract(){
      if(size<=1){
         throw runtime_error("Not Enough Arguments");
      }
      else{
         int num1 = pop();
         int num2 = pop();
         push(num2 - num1);
         return(get_element_from_top(0));
      }
   }

   int Stack_A::multiply(){
      if(size<=1){
         throw runtime_error("Not Enough Arguments");
      }
      else{
         int num1 = pop();
         int num2 = pop();
         push(num2 * num1);
         return(get_element_from_top(0));
      }
   }

   int Stack_A::divide(){
      if(size<=1){
        throw runtime_error("Not Enough Arguments");
      }
      else{
         int num1 = pop();
         int num2 = pop();
         if(num1==0){
           throw runtime_error("Divide by Zero Error");
         }
         else{
            int  out = num2/num1;
            int rem = num2%num1;
            if (num1*num2>=0){
               push(out);
               // return(get_element_from_top(0));
               
            }
            if (num1*num2<0 && rem!=0){
               push(out-1);
               // return(get_element_from_top(0));
            }
            if (num1*num2<0 && rem==0){
               push(out);
               // return(get_element_from_top(0));
            }
         }

      }
      return(get_element_from_top(0));

   }

   int* Stack_A::get_stack(){
      return stk;
   } // Get a pointer to the array

   int Stack_A::get_size(){
      return size;
   } // Get the size of the stack

