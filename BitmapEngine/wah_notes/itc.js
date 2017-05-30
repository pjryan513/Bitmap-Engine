// interactive table of contents

// take in an integer, return the corresponding paragraph id
let x = function(i){
  return "p"+i
}

// select the body
let body = document.getElementById("body")
// create a paragraph_controller div
let div = document.createElement("div")
div.id = "paragraph_controller"
div.class = "controller"
// set its position to fixed
div.style = "position:fixed;width:190px;height:600px;background-color:lightblue;left:50px;top:50px;border:2px solid black;"

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
 *
 *
 */
let i = 1
let curr_element = document.getElementById(x(i))
// while we still have a p# element, do {}
while(null != curr_element){
  console.log(curr_element) // log to console the curr element for testing

  // access the positional data of each paragraph
  let rect = curr_element.getBoundingClientRect()

  // for each paragraph, create a sub_div and append it to the control ul
  let sub_div = document.createElement("div")


  sub_div.style = "margin: 2px 2px 2px 2px; background-color:white;"
  let li = document.createElement("li")
  // li.appendChild(document.createTextNode("para : " + i))
  // sub_div.appendChild(li)
  sub_div.appendChild(document.createTextNode("para : " + i))

  // ul.appendChild(li)
  div.appendChild(sub_div)


  console.log(rect)
  ++i
  curr_element = document.getElementById(x(i))
}
