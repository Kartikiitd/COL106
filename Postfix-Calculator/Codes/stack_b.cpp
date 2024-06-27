#include <iostream>
#include "stack_b.h"
using namespace std;
#include <stdexcept>


 
    
Stack_B::Stack_B(){
    try {
    stk = new int[1024];}//change here the  value to 1024
    catch(const bad_alloc& e){
        throw runtime_error("Out of Memory");
    }
    size=0;
    capacity=1024;//change here the  value to 1024
}


Stack_B::~Stack_B(){
    delete stk;
}

void Stack_B::push(int data){
    if(size==capacity){
        try{
        int * temp = new int[capacity*2];
        for(int i=0;i<size;i++){
            temp[i]=stk[i];
        }
        delete stk;
        stk=temp;
        stk[size]=data;
        capacity *=2;
        size +=1;
        }
        catch(const bad_alloc& e){
            throw runtime_error("Out of Memory");
        }
        
        }
    else{
        stk[size]=data;
        size+=1;
    }
}

int Stack_B::pop(){
    if(size==0){
        throw runtime_error("Empty Stack");
      }
    else{
        if(capacity==1024){//change here the value to 1024
            int popedval=stk[size-1];
            size -=1;
            return popedval;
        }
        if(capacity>=2*1024){
            if(size-1>capacity/4){
                int popedval=stk[size-1];
                size -=1;
                return popedval;
            }
            else{
                try{
                int * temp1 = new int[capacity/2];
                for(int i=0;i<size;i++){
                    temp1[i]=stk[i];
                }
                delete stk;
                stk=temp1;
                capacity=capacity/2;
                int popedval=stk[size-1];
                size -=1;
                return popedval;
                }
                catch(const bad_alloc& e){
                throw runtime_error("Out of Memory");
        }
            }
        }


      }
      return 0;
}

int Stack_B::get_element_from_top(int idx){
    if(idx>=size){
        throw runtime_error( "Index out of range");
      }
    else{
        return stk[size-idx-1];
      }
}

int Stack_B::get_element_from_bottom(int idx){
    if(idx>=size){
        throw runtime_error( "Index out of range");
      }
    else{
        return stk[idx];
      }
}

void Stack_B::print_stack(bool top_or_bottom){
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

int Stack_B::add(){
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
int Stack_B::subtract(){
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
int Stack_B::multiply(){
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
int Stack_B::divide(){
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
            //    return(get_element_from_top(0));
               
            }
            if (num1*num2<0 && rem!=0){
               push(out-1);
            //    return(get_element_from_top(0));
            }
            if (num1*num2<0 && rem==0){
               push(out);
            //    return(get_element_from_top(0));
            }
         }

      }
      return(get_element_from_top(0));
} 

int* Stack_B::get_stack(){
    return stk;
} // Get a pointer to the array

int Stack_B::get_size(){
    return size;
} // Get the size of the stack
