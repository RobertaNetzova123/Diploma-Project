var i = 0
var k = 0

$(document).ready(function(){
  $("input[id='btn1']").click(function(){
    $("input[id='btn1']").attr('value', 'Count: '+ ++i);
  });
});