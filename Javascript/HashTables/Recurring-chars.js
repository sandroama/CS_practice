// Given an array = [2,5,1,2,3,5,1,2,4]
// [2,1,1,2,3,5,1,2,4]

function recur(arr){
    var myMap=new Map();
    for(let i=0; i<arr.length;i++){
        if(!myMap.get(arr[i])){
            myMap.set(arr[i],i);
        }else{
            console.log( arr[i]);
        }
    }
}
const k= [2,5,1,2,3,5,1,2,4]
recur(k);

function firstRecurringCharachter(input){
    for(let i=0;i<input.length;i++){
        for(let j=i+1;j<input.length;j++){
            if(input[i]===input[j]){
                return input[i];
            }
        }
    }
    return undefined;
}

function firstRecurringCharachter2(input){
    let map = {};
    for(let i =0;i<input.length;i++){
        if(map[input[i]]){
            return input[i];
        }else{
            map[input[i]]=i;
        }
        return undefined;
    }

    return undefined;
}

firstRecurringCharachter2([2,5,1,2,3,5,1,2,4]);
