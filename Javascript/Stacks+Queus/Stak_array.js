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
      this.array=[];
    }
    peek() {
      return this.array[this.array.length-1];
    }

    push(value){
      this.array.push(value);
      return this;
    }
    pop(){
      this.array.pop();
      return this;
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