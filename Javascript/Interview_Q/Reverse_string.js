// Create a function that reverses a string:
// 'Hi My name is Andrei' should be:
// 'ierdnA si eman vM iH'


// MY SOLUTION
// function reverse(str){
//     if(!str || str.length<2 || typeof str !=='string'){
//         return 'ERROR';
//     }
//     var reversed="";
//     for (let i = str.length-1; i >= 0; i--) 
//     {
//         reversed= reversed+ str[i];
//     }
//     return reversed;
// }

function reverse(str){
    if(!str || str.length<2 || typeof str !=='string'){
        return 'ERROR';
    }
    const backwards=[];
    const totalItems = str.length-1;
    for(let i=totalItems;i>=0;i--){
        backwards.push(str[i]);
    }
    console.log(backwards);

    return backwards.join('');
}
function reverse2(str){
    return str.split('').reverse().join('');
}

const reverse3 = str => str.split('').reverse().join('');
const reverse4 = str => [...str].reverse().join('');


reverse("Hi My name is Andrei");
reverse2("Hi My name is Andrei");
reverse3("Hi My name is Andrei");


//console.log(reverse("Hi My name is Andrei"));