//-----------------------REGISTERING THE APPLICATION AND DEPENDENCIES-----------------------

var application = angular.module("Application", ['ngCookies','ngRoute']);
//----------------------CONFIGURING THE APPLICATION------------------------


application.config([ '$routeProvider', function(routeProvider) {
	routeProvider.when('/addUser', {
		templateUrl : 'addUser.html',
		controller : 'AddUserController'
	}).when('/viewUser', {
		templateUrl : 'viewUser.html',
		controller : 'viewController'
	}).when('/loginpage', {
		templateUrl : 'partials/loginpage.html',
		controller : 'RouteController'
	}).when('/viewPlan_Admin', {
		templateUrl : 'viewPlan_Admin.html',
		controller : 'RouteController'
	}).when('/performance', {
		templateUrl : 'performance.html',
		controller : 'chartController'
	}).otherwise({
		templateUrl:'adminWelcome.html'
	});
} ]);




//-------------------------------------------------------------

/*application.filter('CountFilter', function() {

	return function(numericValue) {
		var listOfNumberAsString = ["One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Tweleve"];
		return listOfNumberAsString[numericValue - 1];
	};

});*/

//---------------------------------------------------------------------

//------------------------------------------------------------------------------------------
var applicationCustomer = angular.module("ApplicationCustomer", ['ngCookies','ngRoute']);

applicationCustomer.config([ '$routeProvider', function(routeProvider) {
	routeProvider.when('/viewPlans', {
		templateUrl : 'viewPlans.html',
		
	}).when('/myDetails', {
		templateUrl :'myDetails.html',
		controller:'userdetailsController'
	}).when('/myBill', {
		templateUrl : 'tablegenerator.html	',
		controller:'billGeneratorController'
	}).when('/billUsage', {
		templateUrl : 'billusage.html',
		controller:'billUsageController'
	}).otherwise({
		redirectTo:'/'
	});
} ]);

var URI = getURI();


