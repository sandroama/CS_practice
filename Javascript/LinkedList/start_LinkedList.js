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
    }

}


const myLinkedList= new LinkedList(17);
myLinkedList.append(23);
myLinkedList.append(29);
myLinkedList.append(31);
myLinkedList.prepend(13);
myLinkedList.insert(39);
myLinkedList.printList();
// console.log(myLinkedList);