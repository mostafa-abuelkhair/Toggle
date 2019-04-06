

function ajqueue (ur){
  this.qus=[];
  this.repeatb=true;
  var obr=this;
this.repeat=function (mills,qu){
  this.repeatb=true;
  var func = this.h(qu).complete;
qu.complete=function(){
  window.setTimeout(re,mills);
  func();
}
  function re(){
    if(obr.repeatb){
    obr.ajq(qu);
}
}
re();

}
this.addq = function(obj){
  this.ajq(obj)
}
this.stop = function(){
  obr.repeatb=false;
  obr.qus=[];
}
this.h=function(j){
  var qu ={complete:function(){}};
  for (var key in j) {
  qu[key]=j[key];
}
return qu;
}
this.ajq = function(obj){

function rec(){

  var ob={url:ur};
  for (var key in obr.qus[0]) {
  ob[key]=obr.qus[0][key];
  }

  var ofunc=ob.complete;
   ob.complete =function(){
     obr.qus.shift();
   if( obr.qus.length!=0){rec();}
   ofunc();
 };

$.ajax(ob);

}

 obr.qus.push(obr.h(obj));
if( obr.qus.length==1){
rec();
}
}
}

/*var qc = new ajqueue('http://192.168.1.5');
alert(qc.repeatb);
qc.addq({data:{g:'g'},error:()=>{alert('good')}});
qc.addq({data:{g:'h'}});
qc.repeat(1000,{data:{g:'r'}});*/
