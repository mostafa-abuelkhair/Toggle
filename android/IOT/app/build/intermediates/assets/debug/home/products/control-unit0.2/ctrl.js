app.controller('unit-ctrl', function($scope,$rootScope) {

$scope.names=[];
for(var i=0;i<$rootScope.p.swhs.length;i++){
  var t=$rootScope.lsg('control-unit0.2/name'+i);
 $scope.names[i]= t==undefined?"name"+(i+1):t;
}
$scope.nc=function(x){
  $rootScope.lss('control-unit0.2/name'+x,$scope.names[x])
}

});
