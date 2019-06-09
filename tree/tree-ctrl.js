app.controller('tree-ctrl', function($scope,$rootScope) {


         var it={
                    s:[{
                         t:{name:'home',id:"",out:'roots'},
                         s:[]
                       }]
                  };

          var tree = $rootScope.lsg('tree')
          $scope.d= tree==undefined? it : JSON.parse(tree);


$scope.node=function(oba,idx){

$('#myModal').modal('toggle');
$scope.t=oba[idx].t;
$scope.oba=oba;
$scope.idx=idx;

}

$scope.p=function(ob){
return $rootScope.products.find((e)=>e.id==ob.t.id);
}

$scope.mc=function(){
  $('#myModal').modal('toggle');
  $rootScope.lss('tree',JSON.stringify($scope.d));
}

$scope.req=function(d){
if($scope.con(d)){

  var st=$scope.st(d)? '0':'1';

  var re =(d)=>{
    for(var x of d.s){
     if (x.t.out=='roots'){re(x);}
     else {$scope.p(x).querys.fq({ord:x.t.out+'/'+st});}
    }
  };

  if(d.t.out=='roots'){ re(d); }

  else { $scope.p(d).querys.fq({ord:d.t.out+'/'+($scope.p(d).outputs[d.t.out]? '0':'1')}); }

}
}

$scope.st=function(d){

  if(d.t.out=='roots'){
    for(var x of d.s){
      if (x.t.out=='roots'){
        var k= $scope.st(x);
        if(k){return k;}
      }
      else if ($scope.p(x).outputs[x.t.out]){return true;}

    }
    return false;
  }

  else {
  return ($scope.p(d).outputs[d.t.out]);
       }

}

$scope.con=function(d){

  if(d.t.out=='roots'){
    for(var x of d.s){
      if (x.t.out=='roots'){
        var k= $scope.con(x);
        if(k){return k;}
      }
      else if ($scope.p(x)!=undefined){return true;}

    }
    return false;
  }

  else {
  return ($scope.p(d)==undefined? false:true);
       }

}

});
