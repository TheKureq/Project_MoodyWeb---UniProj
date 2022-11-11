$(document).ready(function(){
    $(".button").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {select:p});
    });
    $(".axis1").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis1:p});
    });
    $(".axis2").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis2:p});
    });
    $(".axis3").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis3:p});
    });
    $(".axis4").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis4:p});
    });
    $(".axis5").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis5:p});
    });
});