// Prepend O(1)
// Append O(1)
// Lookup O(n)
// Insert O(n)
// Delete O(n)

class Node{
    constructor(value){
        this.value = value,
        this.next =null,
        this.prev = null
    };
}
class DoublyLinkedList{
    constructor(value){
        this.head={
            value:value,
            next: null,
            prev:null
        };
        this.tail=this.head;
        this.length=1;
    }
    append(value){
        const newNode = {
            value: value,
            next: null,
            prev: null
        };
        newNode.prev = this.tail;
        this.tail.next=newNode;
        this.tail=newNode;
        this.length++;
        return this;
    }
    prepend(value){
        const newHead={
            value:value,
            next:this.head,
            prev: null,
        };
        this.head=newHead;
        this.head.prev=newHead;
        this.length++;
        return this;
    }
    printList(){
        const array = [];
        let currentNode = this.head;
        while(currentNode != null){
            array.push(currentNode.value);
            currentNode = currentNode.next;
        }
        return array;
    }

    insert(index, value){ // inser a new node at a given index
        if(index ==0 ){
            this.prepend(value);
            return this.printList();
        }
        if(index >= this.length){
            return this.append(value);
        }
        const newNode = {
            value: value,
            next: null,
            prev: null
        };
        const leader = this.traverseToIndex(index-1);
        const follower= leader.next;
        leader.next=newNode;
        newNode.next=follower;
        follower.prev = newNode;

        this.length++;
        return this.printList();
    }

    traverseToIndex(index){
        // check param
        let counter =0;
        let currentNode = this.head;
        while(counter !== index){
            currentNode = currentNode.next;
            counter++;
        }
        return currentNode;
    }

    remove(index){ // 
        const leader = this.traverseToIndex(index-1);
        const delNode = leader.next;
        leader.next = delNode.next;
        this.lenght--;
        return this.printList();

    }

}


const myLinkedList= new DoublyLinkedList(17);
