app.controller('tree-ctrl', function($scope,$rootScope) {

/*$scope.d={
           s:[{
                t:{name:'home',id:"n",out:'roots'},
                s:[
                   {t:{name:'room1',id:"12d34f5hjkli",out:'ch1'},s:[]},
                   {t:{name:'room2',id:"",out:'roots'},s:[]},
                   {
                     t:{name:'room3',id:"",out:'roots'},
                     s:[
                         {t:{name:'out1',id:"",out:'roots'},s:[]},
                         {t:{name:'out2',id:"",out:'roots'},s:[]}
                       ]
                   }
                  ]
              }]
         };*/

         $scope.d={
                    s:[{
                         t:{name:'home',id:"",out:'roots'},
                         s:[]
                       }]
                  };


$scope.node=function(oba,idx){


$('#myModal').modal('toggle');
$scope.t=oba[idx].t;
$scope.oba=oba;
$scope.idx=idx;
}

/*$scope.products=[
  {id:'12d34f5hjkli',pid:'control unit0.2',name:'control unit',outputs:{ch1:1,ch2:0,ch3:1,ch4:0,ch5:0}}
  ,{id:'asd2',pid:'control unit0.2',name:'control_unit',outputs:{ch1:0,ch2:1,ch3:1,ch4:0,ch5:1}}
];*/

$scope.p=function(ob){
return $rootScope.products.find((e)=>e.id==ob.t.id);
}

$scope.mc=function(){$('#myModal').modal('toggle');}

$scope.req=function(d){
  $scope.p(d).querys.fq({ord:d.t.out+'/'+($scope.p(d).outputs[d.t.out]? '0':'1')});
}

});
