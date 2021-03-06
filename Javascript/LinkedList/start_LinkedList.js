// let myLinkedList={
//     head: {
//         value:10,
//         next:{
//             value:5,
//             next:{

//             }
//         }
//     }
// }

// 17 --> 23 --> 29

class Node{
    constructor(value){
        this.value = value;
        this.next =null;
    }
}
class LinkedList{
    constructor(value){
        this.head={
            value:value,
            next: null
        }
        this.tail=this.head;
        this.length=1;
    }
    append(value){
        //
        // const newNode={
        //     value:value,
        //     next:null
        // };
        // implementing with class
        const newNode = new Node(value);

        this.tail.next=newNode;
        this.tail=newNode;
        this.length++;
        return this;
    }
    prepend(value){
        const newHead={
            value:value,
            next:this.head,
        };
        this.head=newHead;
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
        const newNode = new Node(value);
        const leader = this.traverseToIndex(index-1);
        const connector= leader.next;
        leader.next=newNode;
        newNode.next=connector;
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

    remove(index){
        const leader = this.traverseToIndex(index-1);
        const delNode = leader.next;
        leader.next = delNode.next;
        this.lenght--;
        return this.printList();

    }

}


const myLinkedList= new LinkedList(17);
myLinkedList.append(23);
myLinkedList.append(29);
myLinkedList.append(31);
myLinkedList.prepend(13);
myLinkedList.insert(39,2);
myLinkedList.printList();
myLinkedList.remove(5);
console.log(myLinkedList.printList());
//console.log(myLinkedList);