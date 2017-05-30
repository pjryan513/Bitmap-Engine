// interactive table of contents
// we have divs' that have id

let x = function(i){
  return "p"+i
}

let i = 1

let curr_element = document.getElementById(x(i))
// console.log(document.getElementById("p1"))
// while we still have a p# element, do {}
while(null != curr_element){
  console.log(curr_element)
  ++i
  curr_element = document.getElementById(x(i))
}
