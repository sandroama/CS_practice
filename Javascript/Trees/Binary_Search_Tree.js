// Pros: 
// Efficient 
// Ordered 
// Flexible Size

class Node {
    constructor(value){
      this.left = null;
      this.right = null;
      this.value = value;
    }
  }
  
  class BinarySearchTree {
    constructor(){
      this.root = null;
    }
    insert(value){
      const newNode = new Node(value);
      if(this.root === null){
        this.root  = newNode;
      }
      else{
        let currentNode = this.root;
        while(true){
            if(value < currentNode.value){
                // go left 
                if(!currentNode.left){
                    currentNode.left = newNode;
                    return this;
                } else{
                    currentNode = currentNode.left;
                }
            }else{
                if(!currentNode.right){
                    currentNode.right  = newNode;
                    return this;
                }
                else{
                    currentNode=currentNode.right;
                }
            }
        }
      }
    }
    lookup(value){
      if(!this.root){
        return false;
      }
      let currentNode=this.root;
      while(currentNode){

        if(currentNode.value===value){
            return currentNode;
        }
        else if(value < currentNode.value){
            currentNode=currentNode.left;
        }
        else{
            currentNode=currentNode.right;
        }
      }
    }
    remove(value){
        if(!this.root){
            return false;
        }
        let currentNode = this.root;
        let parentNode = null;
        while(currentNode){
            if(value < currentNode.value){
                parentNode = currentNode;
                currentNode=parentNode.left;
            }
            else if(value > currentNode.value){
                parentNode=currentNode;
                currentNode=currentNode.right;
            }
            else if(currentNode.value === value){
                // case 1: No right child
                if(currentNode.right===null){
                    if(parentNode===null){
                        this.root = currentNode.left;
                    }else{
                        // parent > current val
                        if(currentNode.value < parentNode.value){
                            parentNode.left = currentNode.left;
                        }
                        // if parent < curr val, make left child a right child of parent
                        else if(currentNode.value>parentNode.value){ 
                            parentNode.right=currentNode.left;
                        }
                    }
                }
                // case 2: Right child which doesnt have a left child
                else if(currentNode.right.left = null){
                    if(parentNode === null){
                        this.root = currentNode.left;
                    }
                    else{
                        currentNode.right.left = currentNode.left;
                    }
                }
            }
        }
    }
    // remove
  }
  
  const tree = new BinarySearchTree();
  tree.insert(9);
  tree.insert(4);
  tree.insert(6);
  tree.insert(20);
  tree.insert(170);
  tree.insert(15);
  tree.insert(1);
  JSON.stringify(traverse(tree.root));
  console.log("");
  console.log(JSON.stringify(traverse(tree.root)));
  console.log("");

  //     9
  //  4     20
  //1  6  15  170
  
  function traverse(node) {
    const tree = { value: node.value };
    tree.left = node.left === null ? null : traverse(node.left);
    tree.right = node.right === null ? null : traverse(node.right);
    return tree;
  }
  
  
  
  
  
  