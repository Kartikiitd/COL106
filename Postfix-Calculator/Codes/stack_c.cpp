#include <iostream>
#include "list.h"
#include "stack_c.h"
using namespace std;
#include <exception>


    Stack_C ::Stack_C(){
        try{
        stk = new List();}
        catch(const bad_alloc& e){
            throw runtime_error("Out of Memory");
        }
    }

    // Destructor
    Stack_C ::~Stack_C(){
        stk->~List();
    }

    void Stack_C ::push(int data){
        stk->insert(data);
    }

    int Stack_C ::pop(){
        if(stk->get_size()==0){
            throw runtime_error("Empty Stack");
        }
        int result =stk->delete_tail();
        return result;
        

    }

    int Stack_C ::get_element_from_top(int idx){
        if(idx>=stk->get_size()){
        throw runtime_error( "Index out of range");
        }
        else{
        Node * temp = stk->get_head();
        int iter = 0;
        int relpos = stk->get_size()-idx-1;
        while(iter !=relpos){
            temp = temp->next;
            iter +=1;
        }
        return temp->next->get_value();
      }
        
    }

    int Stack_C ::get_element_from_bottom(int idx){
        if(idx>=stk->get_size()){
        throw runtime_error( "Index out of range");
        }
        else{
        Node * temp = stk->get_head();
        int iter = 0;
        while(iter !=idx){
            temp = temp->next;
            iter +=1;
        }
        return temp->next->get_value();
      }
    }

    void Stack_C ::print_stack(bool top_or_bottom){
        if(stk->get_size()==0){
            return;
        }
        if(top_or_bottom==1){
            Node *temp = stk->get_head()->next;
            Node *backit = NULL;
            while(!temp->is_sentinel_node()){
                temp = temp->next;
            }
            backit=temp;//this is my sentinel end it;
            Node * iter = backit->prev;
            while (! iter->is_sentinel_node())
            {
               cout<<iter->get_value()<<endl;
               iter = iter->prev; 
            }
            return;

        }
        if(top_or_bottom==0){
            Node * temp = stk->get_head()->next;
            while (! temp->is_sentinel_node())
            {
                cout<<temp->get_value()<<endl;
            }
            return ;
            
        }
    }

    int Stack_C ::add(){
        if(stk->get_size()<=1){
         throw runtime_error("Not Enough Arguments");
      }
      else{
         int num1 = pop();
         int num2 = pop();
         push(num1+num2);
         return(get_element_from_top(0));

      }
    }

    int Stack_C ::subtract(){
        if(stk->get_size()<=1){
         throw runtime_error("Not Enough Arguments");
      }
      else{
         int num1 = pop();
         int num2 = pop();
         push(num2 - num1);
         return(get_element_from_top(0));
      }
    }

    int Stack_C ::multiply(){
        if(stk->get_size()<=1){
         throw runtime_error("Not Enough Arguments");
      }
      else{
         int num1 = pop();
         int num2 = pop();
         push(num2 * num1);
         return(get_element_from_top(0));
      }
    }

    int Stack_C ::divide(){
        if(stk->get_size()<=1){
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

    List* Stack_C ::get_stack(){
        return stk;
    } // Get a pointer to the linked list representing the stack

    int Stack_C ::get_size(){
        return stk->get_size();
    } // Get the size of the stack

