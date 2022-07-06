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
        const newNode={
            value:value,
            next:null
        };
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
}


const myLinkedList= new LinkedList(17);
myLinkedList.append(23);
myLinkedList.append(29);
myLinkedList.append(31);
myLinkedList.prepend(13);
console.log(myLinkedList);