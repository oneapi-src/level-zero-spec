function getBuildId(inputId){
    var length = 6 - inputId.length;
    var outId = inputId;
    while(length > 0){
        outId = "0" + outId;
        length--;
    }
    return outId;
}

function colouredTd(cell, val, greater, newColor){
    if(parseInt(val,10)>greater){
        cell.bgColor = newColor
    }
    cell.innerHTML = val
}


function colouredTdWithString(cell, val, intVal, greater, newColor){
    if(intVal>greater){
        cell.bgColor = newColor;
    }
    cell.innerHTML = val
}
