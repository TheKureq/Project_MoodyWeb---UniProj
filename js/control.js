$(document).ready(function(){
    $(".led").click(function(){
        var p = $(this).attr('id');
        $.get("http://10.0.0.12:80/", {pin:p});
    });
});