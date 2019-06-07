app.controller('tree-ctrl', function($scope,$rootScope) {

$scope.d={
           s:[{
                t:{name:'home',id:"asd"},
                s:[
                   {t:{name:'room1',id:"asd1"},s:[]},
                   {t:{name:'room2',id:"asd2"},s:[]},
                   {
                     t:{name:'room3',id:"asd3"},
                     s:[
                         {t:{name:'out1',id:"asd4"},s:[]},
                         {t:{name:'out2',id:"asd5"},s:[]}
                       ]
                   }
                  ]
              }]
         };


$scope.node=function(ob){

//ob.s.push({t:"new",s:[]});
$('#myModal').modal('toggle');
$scope.t=ob.t;
}

$scope.products=[{id:'asd',o:0},{id:'asd2',o:0}];

$scope.p=function(ob){
return $scope.products.find((e)=>e.id==ob.t.id);
}

});
