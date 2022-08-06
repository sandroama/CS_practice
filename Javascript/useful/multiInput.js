// using rest parameter
function add(...args){
    return args.reduce(function(acc,cur){
        return acc + cur;
    });
}

console.log(add(1,2,3));
console.log(add(1,2,3,4,5,6,7));
console.log(add(1,2,3,4,5));
console.log(add(100,200,300,400,500));
