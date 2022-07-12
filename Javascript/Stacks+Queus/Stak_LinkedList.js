//          Stacks
// LIFO -> Last In First Out 
// Lookup O(n)
// Pop O(1)
// Push O(1)
// Peek O(1)

class Node {
    constructor(value){
      this.value = value;
      this.next = null;
    }
  }
  
  class Stack {
    constructor(){
      this.top = null;
      this.bottom = null;
      this.length = 0;
    }
    peek() {
      return this.top;
    }
    push(value){
      const newTop = new Node(value);
      if(this.length===0){
        this.top=newTop;
        this.bottom= newTop;
      }else{
        const pointer = this.top;
        this.top = newTop;
        newTop.next=pointer;
      } 
      this.length++; 
      return this;
    }
    pop(){
      if(!this.top){
        return null;
      }
      if(this.length===0){
        this.bottom = null;

      }
      const pointer = this.top;
      this.top = this.top.next;
      this.length--;
      return pointer;
    }
    //isEmpty
  }
  
  const myStack = new Stack();
  myStack.push('Google');
  myStack.push('Udemy');
  myStack.push('DC');
  myStack.pop();
  console.log(myStack);
  
  
  
  
  //Discord
  //Udemy
  //google