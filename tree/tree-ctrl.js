app.controller('tree-ctrl', function($scope,$rootScope) {

$scope.d={
           s:[{
                t:'home',
                s:[
                   {t:4,s:[]},
                   {t:6,s:[]},
                   {
                     t:10,
                     s:[
                         {t:15,s:[]},
                         {t:18,s:[]}
                       ]
                   }
                  ]
              }]
         };

$scope.node=function(ob){

ob.s.push({t:"new",s:[]});

}

});
