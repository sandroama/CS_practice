const basket = ['apples','grapes','pears'];

// linked list: apples -> grapes -> pears

const obj1={a:true};
const obj2=obj1;
obj1.a='boo';
console.log(obj1);
console.log(obj2);
delete obj1;
console.log('obj2',obj2);
console.log('obj1',obj1);

