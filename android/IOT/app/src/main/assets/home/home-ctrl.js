app.controller('home-ctrl', function($scope,$rootScope) {

  $scope.inc=function(x) {
  $scope.bckf('home/products/'+x.pid+'/'+x.pid+'.htm');
  $rootScope.p=x;
  }


});
