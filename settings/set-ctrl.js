app.controller('settings-ctrl', function($scope,$rootScope) {

$rootScope.back=[$rootScope.back[0]];
  $scope.inc=function(x) {
  $scope.bckf('settings/setpage.htm');
  $rootScope.sp=x;
  }

});
