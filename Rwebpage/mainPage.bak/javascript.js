// Get the modal

var modal = document.getElementById("myModal");
console .log ( modal );
var xm = 5;
console .log (xm);

var mybtn = document.getElementById("myBtnsome");     // Get the button that opens the modal
var span1 = document.getElementsByClassName("close1")[0];
var span = document.getElementsByClassName("close")[0]; // Get the <span> element that closes the modal
mybtn.onclick = function()  // When the user clicks the button, open the modal 
{
  modal.style.display = "block";
}
function openSubPageWhenClick() 
{
  console.log(modal)
  modal.style.display = "block";
};

var delayTimeInstance;
var cellInstance;
function subPageCloseBtn () {
  console.log ('closing window')
  modal.style.display     = "none";
  cellInstance.innerHTML  = delayTimeInstance
}

// When the user clicks on <span> (x), close the modal
span.onclick = function() {
  modal.style.display = "none";
}

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
  if (event.target == modal) {
    modal.style.display = "none";
  }
}


function sliderFunc() {
  console.log ("hi from slider")
  jslider_varible = document.getElementById('jslider1');
  slider_value_show = document.getElementById('sliderValShow');
  slider_value_show.innerHTML = 'Delay Time ' + jslider_varible.value + ' min';
  delayTimeInstance = jslider_varible.value + ' min';
  
};

function checkBox(valValue) {
  console.log (valValue)
  delayTimeInstance = valValue
}














//document.addEventListener('contextmenu', event => event.preventDefault());
window.onscroll = function() {myFunction1()};

function myFunction1() 
{
  var header = document.getElementById("myHeader");
  var sticky = header.offsetTop;

// console.log (sticky)
// console.log (window.pageYOffset)

  if (window.pageYOffset > sticky) 
  {
    header.classList.add("sticky");
  } 
  else 
  {
    header.classList.remove("sticky");
  }
}




var postion = 0;
function newElementTable( arg )
{
  var table = document.getElementById("myTable")
  var y = table.rows[1].cloneNode(true);
  y.getElementsByClassName('1').className = table.rows.length.toString();
  table.appendChild(y)
  table.lastChild.getElementsByClassName('1').className = '5';
  console.log (table.rows.length) 
}

function daySelect(arg) 
{
  var some = document.getElementsByClassName(arg);
  console.log(some[0].style.backgroundColor)
  if (some[0].style.backgroundColor == 'blue')
  {
    some[0].style.backgroundColor = "red"
  }
  else if (some[0].style.backgroundColor == 'red')
  {
    some[0].style.backgroundColor = "blue"
  } 
  else
  {
    some[0].style.backgroundColor = "blue"
  }

  console.log(arg)
  some.dot = "red";

}
function selectFun1()
{
  var some = document.getElementsByClassName('dot');
  for (var i = 0; i < some.length; i++) 
  {
    some[i].style.backgroundColor = 'blue'
  }
}
function selectFun2()
{
var some = document.getElementsByClassName('dot');
for (var i = 0; i < some.length; i++) {
  some[i].style.backgroundColor = 'red'
}
}



  var instance;
  (function () 
  {
  if (window.addEventListener) 
  {
    window.addEventListener('load', run, false);
  } 
  else if (window.attachEvent) 
  {
    window.attachEvent('onload', run);
  }

  
  function run() 
  {
      var t = document.getElementById('myTable');
      t.onclick = function (event) 
      {
          event = event || window.event; //IE8
          var target = event.target || event.srcElement;
          while (target && target.nodeName != 'TR') // find TR
          { 
              target = target.parentElement;
          }
          //if (!target) { return; } //tr should be always found
          var cells = target.cells; //cell collection - https://developer.mozilla.org/en-US/docs/Web/API/HTMLTableRowElement
          //var cells = target.getElementsByTagName('td'); //alternative
          if (!cells.length || target.parentNode.nodeName == 'THEAD') {
              return;
          }
          
          var buttonX = cells[postion].getElementsByClassName('btn');
          //cellInstance = cells[postion].getElementsByClassName('btn');

          console .log ("postion " + postion)
          //console .log (cellInstance) 
          if ( postion == 0 )
          {
            
            var timeSelector = cells[postion + 1]
            var vtime   = timeSelector.getElementsByClassName('timeElement')[0] 
            var vslider = timeSelector.getElementsByClassName('sliderElement')[0] 

            if (buttonX[0].innerHTML == "At")
            {
              buttonX[0].innerHTML = "After";
              vslider.style.display = ''
              vtime.style.display = 'none'

            }
            else if (buttonX[0].innerHTML == "After")
            {
              buttonX[0].innerHTML = "At";
              vslider.style.display = 'none'
              vtime.style.display = ''
            }
            else
            {
              console.log ("ok lets see")
              buttonX[0].innerHTML = "After";
              vslider.style.display = ''
              vtime.style.display = 'none'

            }
          }
          if ( postion == 1 )
          {
            
            cellInstance = cells[1].getElementsByClassName('sliderElement')[0]
            console.log ('ok postion 1');
            console .log (cellInstance) 
            var timeSelector = cells[postion]
            var vtime   = timeSelector.getElementsByClassName('timeElement') 
            var vslider =  timeSelector.getElementsByClassName('sliderElement') 

            if (vtime[0].style.display == 'none')
            {
              console.log ('ok time is disable');
              openSubPageWhenClick()
            }
            else
            {
              console.log ('ok slider is disable');
            }


          }
          if ( postion == 2 )
          {
            
            if ( buttonX[0].innerHTML == 'Short' )
            {
              buttonX[0].innerHTML = "Medium";
            }
            else if ( buttonX[0].innerHTML == 'Medium' )
            {
              buttonX[0].innerHTML = "Large";
            }
            else if ( buttonX[0].innerHTML == 'Large' )
            {
              buttonX[0].innerHTML = "Short";
            }
            else 
            {
              buttonX[0].innerHTML = "Medium";
            }
          }
          if (postion == 3)
          {
            
             var i = cells[1].parentNode.rowIndex;
             document.getElementById("myTable").deleteRow(i);
            console.log (i);
          }
          //console.log ( cells[postion] )
          //var buttonX = cells[postion].getElementsByClassName('btn');

          

      };
  }

})();
function selectFun3()
{
  var some = document.getElementsByClassName('dot');
  for (var i = 0; i < some.length; i++) 
  {
    if (some[i].style.backgroundColor == 'blue')
    {
      some[i].style.backgroundColor = "red"
    }
    else if (some[i].style.backgroundColor == 'red')
    {
      some[i].style.backgroundColor = "blue"
    } 
    else
    {
      some[i].style.backgroundColor = "blue"
    }

  }

  

}
function atBtn(arg)
{
  postion = 0;
}
function timeBtn(arg)
{
  postion = 1;
}
function alTyBtn(arg)
{
  postion = 2;
}
function deleBtn(arg)
{
  postion = 3;
}



function myFunction()
{
  if ( instance != null ) 
  {
    jslider_varible = document.getElementById('jslider');
    slider_value_show = document.getElementById('id_slider_value_show');
    instance.innerHTML = jslider_varible.value + ' Min';
  }
};

// open sub window for delay adjustment

