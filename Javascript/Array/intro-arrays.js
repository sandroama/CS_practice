const strings = ['a','b','c','d']
// 4*4 = 16 bytes
console.log(strings[0]); 

//push - add one element
strings.push('e'); // O(1)
//pop
strings.pop();
strings.pop(); //O(1);

// unshift - add at the beggining of the array
strings.unshift('x') // O(n)

//splice
strings.splice(2,0,'alien'); // O(n)

console.log(strings);