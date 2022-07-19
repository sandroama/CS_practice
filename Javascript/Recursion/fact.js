// two functions of showcasing recursive and iterative versions of factorial.

function FactorialRecursive(num){
    if(num>=0 && num<=2 ){
        return num;
    }
    return num * FactorialRecursive(num-1);
}

function FactorialIterative(num){
    let answer =1;
    if(num>=0 && num<=2){
        return num;
    }

    for(let i =2; i<=num; i++){
        answer=answer*i;
    }
    return answer;
}

console.log(FactorialIterative(6));
console.log(FactorialRecursive(6));

// FactorialRecursive(5);