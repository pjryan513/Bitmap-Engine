// interactive table of contents

let hidden = true
if (window.innerWidth > 1358){
  hidden = false
}


// take in an integer, return the corresponding paragraph id
let x = function(i){
  return "p"+i
}

// select the body
let body = document.getElementById("body")
// create a paragraph_controller div
let div = document.createElement("div")
div.id = "paragraph_controller"
div.class = "controller hide-on-med-and-down"
// set its position to fixed
div.style = "position:fixed;width:10%;height:90%;background-color:#039be5;left:50px;top:50px;border:2px solid black;"

if (hidden) {
  div.style = "position:fixed;width:10%;height:90%;background-color:#039be5;left:50px;top:50px;border:2px solid black;visibility:hidden;"
}


// append the controller to the DOM
body.appendChild(div)

// collapse_unordered_list.data-collapsible = "accordion"
// collapse_unordered_list.data-collapsible = "accordion"
/////////////////////////////////////
// <ul class="collapsible" data-collapsible="accordion">
//     <li>
//       <div class="collapsible-header"><i class="material-icons">filter_drama</i>First</div>
//       <div class="collapsible-body"><span>Lorem ipsum dolor sit amet.</span></div>
//     </li>
//     <li>
//       <div class="collapsible-header"><i class="material-icons">place</i>Second</div>
//       <div class="collapsible-body"><span>Lorem ipsum dolor sit amet.</span></div>
//     </li>
//     <li>
//       <div class="collapsible-header"><i class="material-icons">whatshot</i>Third</div>
//       <div class="collapsible-body"><span>Lorem ipsum dolor sit amet.</span></div>
//     </li>
//   </ul>
/////////////////////////////////////
/*
 * loop through the paragraphs
 *    for each paragraph create a paragraph_portal
 *    append each paragraph_portal to the controller
 *    add an event listener to each paragraph_portal
 *    (the event listener will navigate to the corresponding paragraph's y axis offset in the window)
 */

// return the number of paragraph elements contained in the document
let counter = function(){
  let i = 1
  let curr_element = document.getElementById(x(i))
  while (null!=curr_element){
    ++i
    curr_element = document.getElementById(x(i))
  }
  return i-1
}


// let div_lst = []
let div_dict = {}

let i = 1
let curr_element = document.getElementById(x(i))
// while we still have a p# element, do {}
while(null != curr_element){
  // console.log(curr_element) // log to console the curr element for testing
  // access the positional data of each paragraph
  let rect = curr_element.getBoundingClientRect()

  // for each paragraph, create a sub_div and append it to the control ul
  let sub_div = document.createElement("div")
  sub_div.id = "sdp"+i // uniquely identify each sub div
  sub_div.style = "text-align:center;margin: 2px 2px 2px 2px; background-color:white;"

  if (hidden) {
    sub_div.style = "text-align:center;margin: 2px 2px 2px 2px; background-color:white;visibility:hidden;"
  }
  // console.log(curr_element)
  // console.log(curr_element.getAttribute("name"))
  sub_div.appendChild(document.createTextNode(curr_element.getAttribute("name")))

  // ul.appendChild(li)
  // div.appendChild(sub_div)

  // add event listener
  sub_div.addEventListener("click", function(){
    window.scrollTo(0,rect.top)
  })

  // make
  div_dict[i] = sub_div
  // console.log('rect top :', rect.top)
  ++i
  curr_element = document.getElementById(x(i))
}

// select the paragraph controller
let p_controller = document.getElementById("paragraph_controller")

// get the rectangle side data and coordinates of the controller
let controller_rect = p_controller.getBoundingClientRect()

// XXX test print XXX
// console.log('controller rect : ', controller_rect.height)

// determine the number of paragraphs by calling the counter method
var num_paragraphs = counter()
// XXX test print XXX
// console.log('number of paragraphs : ', num_paragraphs)


let height_of_sub_div = (controller_rect.height/num_paragraphs) -5

console.log(window.innerWidth)


i=1
curr_element = document.getElementById(x(i))
while (null!= curr_element){
  // div_lst[i-1].style = "height:"+height_of_sub_div
  // console.log(div_lst[i-1])\
  // console.log(document.getElementById("sdp"+i))
  // let sd = document.getElementById("sdp"+i)
  // console.log(height_of_sub_div);

  let sd = div_dict[i]
  // console.log(sd)
  sd.style = "text-align:center;background-color:white;height:"+height_of_sub_div+"px;margin:4px 4px 4px 4px;"

  sd.class = "hide-on-med-and-down"
  div.appendChild(sd)
  // div.appendChild(sd)
  // div.appendChild(div_lst[i])
  ++i
  curr_element = document.getElementById(x(i))
}
