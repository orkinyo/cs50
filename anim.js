function Move()
{
    var elem = document.getElementById("animate");
    var speed = parseInt(document.getElementById("speed").value);
    if(!speed)
    {
        document.getElementById("texttoshow").innerHTML="give speed!";
    }
    var id;
    pos = 0;
    for(var i = 0 ; i < speed; i++)
    {
        id = setInterval(frame, 5);
    }
    function frame() {
    if (pos == 350) {
      clearInterval(id);
      ran++;
      pos = 0;
    } else {
      pos++;
      elem.style.top = pos + 'px';
      elem.style.left = pos + 'px';
    }
  }

}

function sleep(milliseconds) {
  const date = Date.now();
  let currentDate = null;
  do {
    currentDate = Date.now();
  } while (currentDate - date < milliseconds);
}

